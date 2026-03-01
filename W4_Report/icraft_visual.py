import numpy as np
import cv2
import matplotlib.pyplot as plt
import os
import math
from typing import List, Tuple

# ====================== 路径配置 ======================
FTMPHQB_PATH = r"D:\icraft\project\yolov5_7.0\yolov5_7.0_icraft\2_compile\config\3_deploy\imodel\ZG\int8\.icraft\logs\yolov5s\ftmpHQB"
TEST_IMAGE_PATH = r"D:\icraft\project\yolov5_7.0\yolov5_7.0_icraft\data\images\bus.jpg"
SAVE_PATH = r"./icraft_visual_result"
NUM_CLASSES = 80
INPUT_SHAPE = (640, 640)
# ====================================================

os.makedirs(SAVE_PATH, exist_ok=True)
os.makedirs(os.path.join(SAVE_PATH, "feature_map"), exist_ok=True)
os.makedirs(os.path.join(SAVE_PATH, "detection"), exist_ok=True)

def parse_hqb(file_path: str, dtype=np.int8) -> np.ndarray:
    try:
        with open(file_path, "rb") as f:
            data = np.fromfile(f, dtype=dtype)
        return data
    except Exception as e:
        print(f"读取文件失败 {file_path}: {e}")
        return np.array([])

def auto_reshape_for_vis(data: np.ndarray) -> np.ndarray:
    """尝试自动将1D数据重塑为 (H, W, C) 用于可视化，假设特征图大致是正方形"""
    size = data.size
    if size == 0: return None
    
    # 常见通道数猜测
    possible_channels = [255, 128, 64, 32, 256, 512, 3] 
    
    for c in possible_channels:
        if size % c == 0:
            hw = size // c
            h = int(math.sqrt(hw))
            if h * h == hw:
                # 完美匹配正方形 (H, H, C)
                try:
                    return data.reshape((h, h, c))
                except:
                    continue
    return None # 无法自动匹配

def plot_feature_map_heatmap(feature_map: np.ndarray, save_name: str, channel: int = 0):
    if feature_map is None:
        return
    
    # 防止通道越界
    if channel >= feature_map.shape[2]:
        channel = 0
        
    single_chan = feature_map[:, :, channel]
    
    # 归一化
    min_val, max_val = single_chan.min(), single_chan.max()
    if max_val - min_val > 1e-8:
        single_chan = (single_chan - min_val) / (max_val - min_val) * 255
    else:
        single_chan = np.zeros_like(single_chan)
        
    single_chan = single_chan.astype(np.uint8)
    
    plt.figure(figsize=(8, 8))
    plt.imshow(single_chan, cmap="viridis")
    plt.axis("off")
    plt.title(f"{save_name} - Ch{channel} - {feature_map.shape}", fontsize=10)
    save_path = os.path.join(SAVE_PATH, "feature_map", f"{save_name}_chan{channel}.png")
    plt.savefig(save_path, bbox_inches="tight", pad_inches=0)
    plt.close()
    print(f"保存热力图: {save_path}")

def yolov5_postprocess(output_data: np.ndarray, conf_thres: float = 0.25, iou_thres: float = 0.45) -> List[np.ndarray]:
    # 确保输入是 (25200, 85)
    if output_data.ndim != 2 or output_data.shape[1] != (NUM_CLASSES + 5):
        print(f"后处理输入维度错误: {output_data.shape}，跳过后处理")
        return []

    box_xywh = output_data[..., :4]
    conf = output_data[..., 4:5]
    cls_prob = output_data[..., 5:]
    
    cls = np.argmax(cls_prob, axis=-1, keepdims=True)
    # 修复之前的语法错误
    cls_conf = conf * cls_prob[np.arange(len(cls_prob)), cls.squeeze()][:, None]
    
    mask = cls_conf >= conf_thres
    if not np.any(mask):
        print("没有检测到任何置信度达标的目标。")
        return []
        
    mask = mask.squeeze()
    box_xywh = box_xywh[mask]
    cls_conf = cls_conf[mask]
    cls = cls[mask]
    
    if len(box_xywh) == 0: return []

    box_xyxy = np.copy(box_xywh)
    box_xyxy[:, 0] = box_xywh[:, 0] - box_xywh[:, 2] / 2
    box_xyxy[:, 1] = box_xywh[:, 1] - box_xywh[:, 3] / 2
    box_xyxy[:, 2] = box_xywh[:, 0] + box_xywh[:, 2] / 2
    box_xyxy[:, 3] = box_xywh[:, 1] + box_xywh[:, 3] / 2
    
    indices = cv2.dnn.NMSBoxes(box_xyxy[:, :4].tolist(), cls_conf.squeeze().tolist(), conf_thres, iou_thres)
    
    detections = []
    if len(indices) > 0:
        for i in indices:
            i = i if isinstance(i, int) else i[0]
            det = np.concatenate([box_xyxy[i], [cls_conf[i][0]], [cls[i][0]]])
            detections.append(det)
    return detections

def draw_detection_box(image: np.ndarray, detections: List[np.ndarray]) -> np.ndarray:
    # 简化的绘制逻辑
    for det in detections:
        x1, y1, x2, y2, conf, cls_id = det
        x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
        cv2.rectangle(image, (x1, y1), (x2, y2), (0, 0, 255), 2)
        label = f"{int(cls_id)}: {conf:.2f}"
        cv2.putText(image, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    return image

def main():
    if not os.path.exists(TEST_IMAGE_PATH):
        print(f"错误：找不到图片 {TEST_IMAGE_PATH}")
        return
        
    img = cv2.imread(TEST_IMAGE_PATH)
    if img is None: 
        print("图片读取失败")
        return
    img = cv2.resize(img, INPUT_SHAPE)

    if not os.path.exists(FTMPHQB_PATH):
        print(f"错误：找不到日志目录 {FTMPHQB_PATH}")
        return

    hqb_files = [f for f in os.listdir(FTMPHQB_PATH) if f.endswith(".ftmp")]
    if not hqb_files:
        print("没有找到 .ftmp 文件")
        return
    
    # 尝试按数字排序
    try:
        hqb_files.sort(key=lambda x: int(os.path.splitext(os.path.basename(x))[0]))
    except:
        hqb_files.sort()

    print(f"找到 {len(hqb_files)} 个文件。开始处理...")

    # 1. 可视化中间层
    # 只取前几个和最后几个文件演示，避免太多
    files_to_vis = hqb_files[:3] + hqb_files[-3:] 
    
    for hqb_file in files_to_vis:
        path = os.path.join(FTMPHQB_PATH, hqb_file)
        data = parse_hqb(path, dtype=np.int8) # 默认尝试 int8
        
        # 自动探测维度
        feat = auto_reshape_for_vis(data)
        if feat is not None:
            plot_feature_map_heatmap(feat, os.path.splitext(hqb_file)[0], channel=0)
        else:
            print(f"跳过 {hqb_file}: 无法自动推断维度 (Size: {data.size})")

    # 2. 处理最终检测 (取最后一个文件)
    last_file = hqb_files[-1]
    last_path = os.path.join(FTMPHQB_PATH, last_file)
    print(f"--- 处理检测结果: {last_file} ---")

    # 定义目标大小 (25200 * 85)
    target_count = 25200 * (NUM_CLASSES + 5)
    
    yolo_data = None
    
    # 尝试方案 A: float32 读取
    data_f32 = parse_hqb(last_path, dtype=np.float32)
    if data_f32.size == target_count:
        print("匹配到 float32 格式")
        yolo_data = data_f32.reshape((25200, NUM_CLASSES + 5))
    else:
        print(f"float32读取大小 ({data_f32.size}) 不匹配目标 ({target_count})")
        
        # 尝试方案 B: int8 读取 (假设输出是量化过的)
        # 注意：如果输出是 int8，你需要反量化参数 (scale/zero_point) 才能得到正确的 conf/coords
        # 这里仅作演示，直接除以一个经验值或者不处理，看能否出框
        data_i8 = parse_hqb(last_path, dtype=np.int8)
        if data_i8.size == target_count:
             print("匹配到 int8 格式 (注意：由于缺乏反量化参数，检测框可能不准)")
             yolo_data = data_i8.astype(np.float32).reshape((25200, NUM_CLASSES + 5))
             # 简单的反量化尝试 (根据你的具体模型修改)
             # yolo_data = (yolo_data - Z) * S 
        else:
            print(f"int8 读取大小 ({data_i8.size}) 也不匹配")

    if yolo_data is not None:
        dets = yolov5_postprocess(yolo_data, conf_thres=0.1, iou_thres=0.45) # 降低阈值测试
        print(f"检测到 {len(dets)} 个目标")
        img_res = draw_detection_box(img.copy(), dets)
        cv2.imwrite(os.path.join(SAVE_PATH, "detection", "result.jpg"), img_res)
        print(f"检测结果保存至 {os.path.join(SAVE_PATH, 'detection', 'result.jpg')}")
    else:
        print("无法解析最终输出文件。")

if __name__ == "__main__":
    main()