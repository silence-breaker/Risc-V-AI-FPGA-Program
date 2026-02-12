import sys
import os
import cv2
import numpy as np
import yaml
import time
import torch  # 必须导入 torch
from tqdm import tqdm

# --- 1. 环境与路径设置 ---
sys.path.append(r"../modelzoo_utils")

import icraft
from icraft.xir import *
from icraft.xrt import *
from icraft.host_backend import * 
from icraft.zg330backend import * 
from pyrtutils.icraft_utils import *
from pyrtutils.Netinfo import Netinfo
from pyrtutils.utils import *

# 导入工具包
from yolov5_utils import *
# 导入官方后处理函数
from post_process_yolov5 import get_det_results_soft, get_det_results_hard, non_max_suppression, scale_coords, vis, get_Stride

def main():
    # ================= 配置区域 =================
    # 1. 配置文件路径 (确保是 ZG 版本)
    YAML_PATH = "../cfg/yolov5s_ZG_int8_demo.yaml" 
    
    # 2. 输入视频路径
    VIDEO_INPUT = "my_test_video.mp4" 
    
    # 3. 输出视频路径
    VIDEO_OUTPUT = "../io/output/result_video.mp4"
    # ===========================================

    print(f"[Info] Loading config from {YAML_PATH}")
    if not os.path.exists(YAML_PATH):
        print(f"[Error] Config file not found: {YAML_PATH}")
        return

    # --- 2. 加载配置 ---
    with open(YAML_PATH, "r", encoding='utf-8') as f:
        cfg = yaml.load(f, Loader=yaml.FullLoader)

    print("[Info] Forcing backend to 'host' for local simulation...")
    runBackend = "host"
    
    # 获取模型路径
    folderPath = cfg["imodel"]["dir"]
    stage = cfg["imodel"]["stage"]
    JSON_PATH, RAW_PATH = getJrPath(folderPath, stage, runBackend)
    
    # 路径容错处理
    if not os.path.exists(JSON_PATH):
        JSON_PATH = os.path.join("..", JSON_PATH)
        RAW_PATH = os.path.join("..", RAW_PATH)

    print(f"[Info] Model JSON: {JSON_PATH}")
    
    # 获取参数
    conf_thres = cfg["param"]["conf"]
    iou_thres = cfg["param"]["iou_thresh"]
    anchors = cfg["param"]["anchors"]
    # 必须获取类别数，Hard模式需要
    number_of_class = cfg.get("param", {}).get("number_of_class", 80) 
    
    # --- 3. 初始化引擎 ---
    network = loadNetwork(JSON_PATH, RAW_PATH)
    netinfo = Netinfo(network)
    
    # 打印 DetPost 状态
    print(f"[Info] DetPost On: {netinfo.DetPost_on}")
    
    device = openDevice(runBackend, "127.0.0.1", netinfo.mmu, False)
    session = initSession(runBackend, network, device, -1, netinfo.mmu, False, False)
    session.enableTimeProfile(True)
    session.apply()

    # --- 4. 视频流循环 ---
    cap = cv2.VideoCapture(VIDEO_INPUT)
    if not cap.isOpened():
        print(f"[Error] Cannot open video: {VIDEO_INPUT}")
        return

    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fps = cap.get(cv2.CAP_PROP_FPS) or 25

    os.makedirs(os.path.dirname(VIDEO_OUTPUT), exist_ok=True)
    out_writer = cv2.VideoWriter(VIDEO_OUTPUT, cv2.VideoWriter_fourcc(*'mp4v'), fps, (width, height))

    print(f"[Info] Processing video... Press 'q' to stop.")
    
    frame_id = 0
    strides = get_Stride(netinfo)

    try:
        while True:
            ret, frame = cap.read()
            if not ret: break
            
            frame_id += 1
            t0 = time.time()
            img_raw = frame.copy()

            # 4.1 预处理
            img = letterbox(img_raw, new_shape=(netinfo.i_cubic[0].h, netinfo.i_cubic[0].w), stride=32, auto=False)[0]
            img = img[:, :, ::-1].copy() # BGR to RGB
            img_tensor = np.expand_dims(img, axis=0)
            input_tensor = numpy2Tensor(img_tensor, network)

            # 4.2 推理
            output_tensors = icraftRun(session, [input_tensor])

            # 4.3 后处理 (关键修改部分)
            # 转为 numpy
            generated_output = []
            output_tensors_cpu = [] # for soft mode
            for tensor in output_tensors:
                host_mem = tensor.to(xrt.HostDevice.MemRegion())
                generated_output.append(np.asarray(host_mem))
                output_tensors_cpu.append(host_mem)

            if netinfo.DetPost_on:
                # === Hard Decode 模式 (你的 ZG 模型走这里) ===
                # 获取 raw 数据宽度作为 ANCHOR_LENGTH
                anchor_len = np.array(generated_output[0]).shape[3]
                
                # 解码 raw data
                scores_list, box_list, id_list = get_det_results_hard(
                    generated_output, 
                    netinfo.o_scale, 
                    anchor_len, 
                    anchors, 
                    strides, 
                    number_of_class, 
                    netinfo.detpost_bit
                )

                # 使用 OpenCV NMS 进行过滤
                if len(box_list) > 0:
                    indices = cv2.dnn.NMSBoxes(
                        bboxes=box_list, 
                        scores=scores_list, 
                        score_threshold=conf_thres, 
                        nms_threshold=iou_thres
                    )
                    
                    final_boxes = []
                    final_scores = []
                    final_ids = []
                    
                    if len(indices) > 0:
                        for i in indices.flatten():
                            final_boxes.append(box_list[i])
                            final_scores.append(scores_list[i])
                            final_ids.append(id_list[i])
                    
                    # 格式化以便绘图: (x, y, w, h) -> (x1, y1, x2, y2)
                    det_array = []
                    for i in range(len(final_boxes)):
                        x, y, w, h = final_boxes[i]
                        det_array.append([x, y, x+w, y+h])
                    
                    if len(det_array) > 0:
                        det_array = np.array(det_array)
                        # 坐标还原
                        det_array = scale_coords(img.shape[:2], det_array, img_raw.shape).round()
                        # 画图
                        result_image = vis(img_raw, boxes=det_array, scores=final_scores, cls_ids=final_ids, conf=conf_thres, class_names=COCO_CLASSES)
                    else:
                        result_image = img_raw
                else:
                    result_image = img_raw

            else:
                # === Soft Decode 模式 (普通模型走这里) ===
                pred = get_det_results_soft(output_tensors_cpu, torch.Tensor(anchors), strides)
                pred = non_max_suppression(pred, conf_thres=conf_thres, iou_thres=iou_thres)
                
                det = pred[0]
                if len(det):
                    det[:, :4] = scale_coords(img.shape[:2], det[:, :4], img_raw.shape).round()
                    result_image = vis(img_raw, boxes=det[:,:4], scores=det[:,4], cls_ids=det[:,5], conf=conf_thres, class_names=COCO_CLASSES)
                else:
                    result_image = img_raw

            # 计算 FPS
            infer_fps = 1.0 / (time.time() - t0)
            cv2.putText(result_image, f"FPS: {infer_fps:.2f}", (20, 40), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 255, 0), 2)
            cv2.putText(result_image, "Mode: Hard" if netinfo.DetPost_on else "Mode: Soft", (20, 80), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 255), 2)

            # 显示与保存
            cv2.imshow("Icraft Video Simulation", result_image)
            out_writer.write(result_image)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

            print(f"Frame {frame_id} | FPS: {infer_fps:.2f} | DetPost: {netinfo.DetPost_on}", end="\r")

    except KeyboardInterrupt:
        print("\n[Info] Stopped.")
    except Exception as e:
        print(f"\n[Error] {e}")
        import traceback
        traceback.print_exc()
    finally:
        cap.release()
        out_writer.release()
        cv2.destroyAllWindows()
        print(f"\n[Info] Done. Saved to {VIDEO_OUTPUT}")

if __name__ == "__main__":
    main()