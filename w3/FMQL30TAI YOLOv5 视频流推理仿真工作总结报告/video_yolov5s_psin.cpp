#include <icraft-xrt/core/session.h>
#include <icraft-xrt/dev/host_device.h>
#include <icraft-xrt/dev/buyi_device.h>
#include <icraft-xrt/dev/zg330_device.h>
#include <icraft-backends/buyibackend/buyibackend.h>
#include <icraft-backends/zg330backend/zg330backend.h>
#include <icraft-backends/hostbackend/cuda/device.h>
#include <icraft-backends/hostbackend/backend.h>
#include <icraft-backends/hostbackend/utils.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <iomanip> // 用于 FPS 格式化
#include "postprocess_yolov5.hpp" 
#include "icraft_utils.hpp"
#include "yaml-cpp/yaml.h"

using namespace icraft::xrt;
using namespace icraft::xir;

// ==========================================
// 1. 辅助函数：LetterBox
// ==========================================
struct LetterBoxInfo {
    float ratio;
    int dw, dh;
    cv::Mat dst;
};

LetterBoxInfo letterbox(const cv::Mat& src, int target_h, int target_w) {
    int in_w = src.cols;
    int in_h = src.rows;
    float scale = std::min((float)target_w / in_w, (float)target_h / in_h);
    int new_w = std::round(in_w * scale);
    int new_h = std::round(in_h * scale);

    cv::Mat resized;
    cv::resize(src, resized, cv::Size(new_w, new_h));

    int dw = (target_w - new_w) / 2;
    int dh = (target_h - new_h) / 2;
    int top = dh, bottom = target_h - new_h - dh;
    int left = dw, right = target_w - new_w - dw;

    cv::Mat dst;
    cv::copyMakeBorder(resized, dst, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(114, 114, 114));

    return { scale, dw, dh, dst };
}

// ==========================================
// 2. 辅助函数：画框
// ==========================================
void draw_bboxes(cv::Mat& frame, 
                 const std::vector<std::tuple<int, float, cv::Rect2f>>& nms_res, 
                 const LetterBoxInfo& lb_info, 
                 const std::vector<std::string>& LABELS) 
{
    for (const auto& res : nms_res) {
        int cls_id = std::get<0>(res);
        float score = std::get<1>(res);
        cv::Rect2f box = std::get<2>(res);

        float x = (box.x - lb_info.dw) / lb_info.ratio;
        float y = (box.y - lb_info.dh) / lb_info.ratio;
        float w = box.width / lb_info.ratio;
        float h = box.height / lb_info.ratio;

        x = std::max(0.0f, x);
        y = std::max(0.0f, y);
        w = std::min(w, (float)frame.cols - x);
        h = std::min(h, (float)frame.rows - y);

        cv::Scalar color(0, 255, 0);
        cv::rectangle(frame, cv::Rect(x, y, w, h), color, 2);

        std::string label = (cls_id < LABELS.size() ? LABELS[cls_id] : std::to_string(cls_id)) + 
                            " " + cv::format("%.2f", score);
        
        int baseLine;
        cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        cv::rectangle(frame, cv::Point(x, y), cv::Point(x + labelSize.width, y - labelSize.height - baseLine), color, -1);
        cv::putText(frame, label, cv::Point(x, y - baseLine), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);
    }
}

// ==========================================
// 3. 主函数
// ==========================================
int main(int argc, char* argv[])
{
    try
    {
        // --- 配置加载 ---
        std::string yaml_path = (argc > 1) ? argv[1] : "../cfg/yolov5s_ZG_int8_demo.yaml";
        YAML::Node config = YAML::LoadFile(yaml_path);
        
        auto imodel = config["imodel"];
        std::string stage = imodel["stage"].as<std::string>();
        std::string folderPath = imodel["dir"].as<std::string>();
        std::string runBackend = imodel["run_backend"].as<std::string>();
        
        checkBackend(runBackend);
        auto JR_PATH = getJrPath(runBackend, folderPath, stage);
        
        auto dataset = config["dataset"];
        auto LABELS = toVector(dataset["names"].as<std::string>());
        
        auto param = config["param"];
        float conf = param["conf"].as<float>();
        float iou_thresh = param["iou_thresh"].as<float>();
        int N_CLASS = param["number_of_class"].as<int>();
        auto ANCHORS = param["anchors"].as<std::vector<std::vector<std::vector<float>>>>();
        bool fpga_nms = param["fpga_nms"].as<bool>();
        bool MULTILABEL = param["multilabel"].as<bool>();

        // --- Icraft 初始化 ---
        Network network = loadNetwork(JR_PATH.first, JR_PATH.second);
        NetInfo netinfo = NetInfo(network);

        if (netinfo.DetPost_on) updateDetpost(netinfo, conf);

        bool cudaMode = imodel["cudamode"].as<bool>();
        bool mmuMode = (runBackend == "buyi") ? imodel["mmuMode"].as<bool>() : true;
        int ocmOption = (runBackend == "zg330") ? imodel["ocm_option"].as<int>() : -1;

        Device device = openDevice(runBackend, imodel["ip"].as<std::string>(), netinfo.mmu || mmuMode, cudaMode);
        Session session = initSession(runBackend, network, device, ocmOption, netinfo.mmu || mmuMode, 
                                      imodel["speedmode"].as<bool>(), imodel["compressFtmp"].as<bool>());
        session.enableTimeProfile(true);
        session.apply();

        // ---------------------------------------------------------
        // 视频流初始化
        // ---------------------------------------------------------
        std::string video_path = "my_test_video.mp4"; 
        std::string output_path = "cpp_result.mp4"; // 输出文件名

        cv::VideoCapture cap(video_path);
        if (!cap.isOpened()) {
            std::cerr << "[Error] Cannot open video: " << video_path << std::endl;
            return -1;
        }

        // --- [新增] 初始化 VideoWriter ---
        int width = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
        int height = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        double fps_video = cap.get(cv::CAP_PROP_FPS);
        if (fps_video <= 0) fps_video = 25.0; // 防止 FPS 读取失败

        cv::VideoWriter writer;
        // 使用 mp4v 编码，如果 Windows 上报错，可以尝试改为 cv::VideoWriter::fourcc('M', 'J', 'P', 'G') 并保存为 .avi
        writer.open(output_path, cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps_video, cv::Size(width, height), true);
        
        if (!writer.isOpened()) {
            std::cerr << "[Warning] Could not open video writer. Result will not be saved." << std::endl;
        } else {
            std::cout << "[Info] Saving result to: " << output_path << std::endl;
        }

        std::cout << "[Info] Start Inference..." << std::endl;

        cv::Mat frame;
        int net_h = netinfo.i_cubic[0].h;
        int net_w = netinfo.i_cubic[0].w;

        while (true) {
            cap >> frame;
            if (frame.empty()) break;
            
            auto t_start = std::chrono::high_resolution_clock::now();

            // 1. 预处理
            LetterBoxInfo lb_info = letterbox(frame, net_h, net_w);
            cv::Mat img_rgb;
            cv::cvtColor(lb_info.dst, img_rgb, cv::COLOR_BGR2RGB);
            Tensor img_tensor = CvMat2Tensor(img_rgb, network);

            // 2. 推理
            dmaInit(runBackend, netinfo.ImageMake_on, img_tensor, device);
            std::vector<Tensor> outputs = session.forward({ img_tensor });
            if (runBackend != "host") device.reset(1);

            // 3. 后处理 (Hard Decode)
            std::vector<std::tuple<int, float, cv::Rect2f>> nms_res;
            if (netinfo.DetPost_on) {
                std::vector<int> id_list;
                std::vector<float> score_list;
                std::vector<cv::Rect2f> box_list;
                std::vector<float> stride = get_stride(netinfo);

                for (size_t i = 0; i < outputs.size(); i++) {
                    auto host_tensor = outputs[i].to(HostDevice::MemRegion());
                    int bits = outputs[i].dtype()->element_dtype.getStorageType().bits();
                    int obj_num = outputs[i].dtype()->shape[2];
                    int anchor_len = outputs[i].dtype()->shape[3];

                    if (bits == 16) {
                        auto data = (int16_t*)host_tensor.data().cptr();
                        for (int obj = 0; obj < obj_num; obj++) {
                            int base = obj * anchor_len;
                            Grid grid = get_grid(bits, data, base, anchor_len);
                            get_cls_bbox(id_list, score_list, box_list, data, base, grid, 
                                         netinfo.o_scale[i], stride[i], ANCHORS[i][grid.anchor_index], 
                                         N_CLASS, conf, MULTILABEL);
                        }
                    } else { // bits == 8
                        auto data = (int8_t*)host_tensor.data().cptr();
                        for (int obj = 0; obj < obj_num; obj++) {
                            int base = obj * anchor_len;
                            Grid grid = get_grid(bits, data, base, anchor_len);
                            get_cls_bbox(id_list, score_list, box_list, data, base, grid, 
                                         netinfo.o_scale[i], stride[i], ANCHORS[i][grid.anchor_index], 
                                         N_CLASS, conf, MULTILABEL);
                        }
                    }
                }
                if (fpga_nms && runBackend == "buyi") nms_res = nms_hard(box_list, score_list, id_list, iou_thresh, device);
                else nms_res = nms_soft(id_list, score_list, box_list, iou_thresh);
            }

            // 4. 画框与FPS
            draw_bboxes(frame, nms_res, lb_info, LABELS);

            auto t_end = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
            double fps = 1000.0 / (duration + 1e-5); 
            
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << fps;
            cv::putText(frame, "FPS: " + stream.str(), cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

            // --- [新增] 写入视频文件 ---
            if (writer.isOpened()) {
                writer.write(frame);
            }

            cv::imshow("Icraft Video Demo", frame);
            if (cv::waitKey(1) == 'q') break;
        }

        // 清理
        cap.release();
        writer.release(); // 关闭写入器，保存文件
        Device::Close(device);
        cv::destroyAllWindows();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << "[Exception] " << e.what() << std::endl;
        return -1;
    }
}