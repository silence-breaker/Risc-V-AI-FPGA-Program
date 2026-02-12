
# FMQL30TAI YOLOv5 视频流推理仿真工作总结报告

**项目名称：** 基于 FMQL30TAI 的 YOLOv5s 视频流实时推理仿真
**运行环境：** Windows 11 (Host Simulation) / WSL (Cross-Compile)
**开发语言：** Python / C++
**模型架构：** YOLOv5s (Int8 Quantized, ZG330 Backend)

---

## 一、 工作概述

在完成了 YOLOv5s 模型的量化编译与交叉编译环境搭建后，为了在硬件板卡（悟净开发板）到位前充分验证模型精度、预处理逻辑及后处理算法的正确性，我们在 PC 端（Windows）实现了基于视频流的实时推理仿真。

本工作分别完成了 **Python 原型验证** 和 **C++ 工程仿真验证**，成功将原本仅支持单张图片的官方示例改造为支持 `mp4` 视频输入、实时画框显示及结果保存的完整应用。

---

## 二、 技术原理 

* **原理**：Icraft 工具链提供了 `HostBackend` 模式。在此模式下，PC 的 CPU 会模拟 NPU（神经网络处理器）的行为，逐条执行编译后的 NPU 指令。
* **目的**：虽然 CPU 模拟执行速度较慢，但其计算逻辑与真实的 NPU 完全一致（Bit-exact），因此可以用来验证量化模型的精度和程序的业务逻辑。

---

## 三、 代码实现 

### 1. Python 实现 (`video_demo_v2.py`)

Python 版本利用其动态特性，快速验证了模型加载、视频读取和 DetPost 解码逻辑。

**核心功能**：
* 使用 `cv2.VideoCapture` 读取视频流。
* 强制指定 `run_backend = "host"` 进行 CPU 仿真。
* 通过 `netinfo.DetPost_on` 自动判断是否启用硬件解码逻辑。
* 利用 `get_det_results_hard` 解析 NPU 输出数据。

**操作过程**
- 在`...\modelzoo\yolov5_7.0\yolov5_7.0_icraft\3_deploy\pyrt`文件夹下放入基于官方` yolov5_psin.py `修改后的`video_demo_v2.py`
- 找一段 MP4 格式的视频，重命名为 `my_test_video.mp4`，放到 `pyrt`文件夹下
- 运行仿真： pyrt 目录下运行命令`uv run video_demo.py`（安装了UV）

**Python原型验证效果**
![alt text](result_video_py.gif)


### 2. C++ 实现 (`src/video_yolov5s_psin.cpp`)

C++ 版本完全模拟了最终上板运行的代码结构，验证了内存管理和编译链路。

 **核心功能**：
* **CMake 集成**：通过修改 `CMakeLists.txt` 添加新的编译目标。
* **OpenCV 集成**：引入 OpenCV C++ 库处理视频 IO。
* **独立预处理**：实现了不依赖官方库的 `letterbox` 函数。

**操作过程**
- 在`...\modelzoo\yolov5_7.0\yolov5_7.0_icraft\3_deploy\src`文件夹下放入基于官方` yolov5s_psin.cpp `修改后的`video_yolov5s_psin.cpp`
- 找一段 MP4 格式的视频，重命名为 `my_test_video.mp4`，放到 `3_deploy\build_win`文件夹下
- 在` CMakeLists.txt `中添加：
```CMake
add_executable(video_yolov5s_psin src/video_yolov5s_psin.cpp)
target_link_libraries(video_yolov5s_psin PRIVATE Icraft::HostBackend Icraft::BuyiBackend Icraft::ZG330Backend)
```
- 在` Developer PowerShell for VS 2022 `中执行以下命令

1. 进入 `build_win` 目录

2. 重新生成工程 (Cmake)：

```powershell
cmake ..
```
3. 开始编译：
```powershell
cmake --build . --config Release
```
4. 运行：
```powershell
.\Release\video_yolov5s_psin.exe ..\cfg\yolov5s_ZG_int8_demo.yaml
```
**C++工程仿真验证效果**
![alt text](cpp_result.gif)


## 四、 仿真总结

### 1. 功能验证

* **画面**：成功加载了 `my_test_video.mp4`，并生成了带有检测框的 `cpp_result.mp4`。
* **检测目标**：能够基本准确识别视频中的行人（Person）、车辆（Car）等目标。
* **坐标精度**：检测框位置贴合物体边缘，较为精准

### 2. 性能表现 (Host 仿真)

* **帧率 (FPS)**：约 **0.2 ~ 0.4 FPS**。
* **原因**：
  PC 的 CPU (x86) 需要模拟执行 NPU (ZG330) 的专用指令集。
  每一层卷积计算都需要通过软件模拟，没有硬件并行加速。



---

## 五、 上板性能评估与展望

既然我们在 PC 上已经跑通了全流程，那么当我们将编译好的程序（`yolov5s_psin` ARM版）部署到真实的 **FMQL30TAI 悟净开发板** 上时，性能将会有质的飞跃：

| 指标 | PC 仿真 (Host Backend) | 开发板实测 (ZG330 Backend) | 提升原因 |
| --- | --- | --- | --- |
| **计算核心** | CPU (软件模拟指令) | NPU (硬件加速) | NPU 专为卷积运算设计，拥有数百个并行计算单元。 |
| **数据类型** | FP32 模拟 Int8 | Int8 (硬件直算) | 8位整数运算速度远快于浮点模拟，且内存占用减半。 |
| **推理速度** | < 0.5 FPS | 预计加速数十倍 | 硬件流水线处理，无需 CPU 模拟开销。 |
| **CPU 负载** | 较高 | 较低 | 大部分计算卸载到 NPU，CPU 仅负责预处理和后处理。 |

