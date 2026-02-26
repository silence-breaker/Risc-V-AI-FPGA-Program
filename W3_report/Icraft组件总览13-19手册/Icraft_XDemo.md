# Icraft XDemo 示例工程说明

## 1. 简介
`XDemo` 是 Icraft SDK 提供的自定义算子 (Custom Operator) 示例工程。它展示了如何利用 Icraft 的 API 实现特定的后处理或预处理功能，并将其集成到神经网络推理流程中。

主要包含以下示例算子：
*   **DetPost**: Detection Post-processing (检测后处理)
*   **ImageMake**: 图像预处理/生成
*   **NearestUpsample**: 最近邻上采样
*   **SegPost**: Segmentation Post-processing (分割后处理)

---

## 2. 算子使用注意事项

### 2.1 ImageMake 算子
*   **全局初始化特性**: `ImageMake` 算子的初始化参数是全局生效的。
*   **陷阱**: 如果网络中包含多个 `ImageMake` 算子，且每个算子需要不同的初始化参数，必须确保存储和执行顺序是交替的（Init -> Forward -> Init -> Forward）。
*   **错误模式**: 若先批量执行所有 Init，再批量执行 Forward，则所有算子都会使用最后一次 Init 的参数，导致计算错误。

### 2.2 SegPost 算子 (语义分割后处理)
该算子通常插入在神经网络的 Output 之后，利用硬件加速完成 ArgMax 和 UpSampling 操作，直接输出类别索引图。

#### 关键配置参数
| 参数名 | 描述 | 取值说明 |
| :--- | :--- | :--- |
| **mode** | 工作模式 | `1`: SegPost模式 (Argmax + Upsample)<br>`0`: Argmax模式 (仅 Argmax) |
| **dst_xsize** | 目标宽度 | 输出特征图的宽度 (不能为0/1, max <= 32*src) |
| **dst_ysize** | 目标高度 | 输出特征图的高度 |
| **align_corner** | 对齐方式 | `1`: 边角对齐<br>`0`: 中心对齐 (双线性插值相关) |
| **sleep_time** | 休眠时间 | 算子工作时的等待/休眠微秒数 |
| **out_index** | 输出索引 | 指定第几个输出端口连接此硬算子，默认 `"0"` |

#### 输出数据格式
输出按 **4字节 (32-bit)** 为单位对齐：

1.  **Mode = 0 (Argmax Only)**:
    *   Byte 0: **Channel Index** (类别索引)
    *   Byte 1-2: **Channel Value** (具体数值，8bit高位补符号)
    *   Byte 3: `0x00` (无效/保留)

2.  **Mode = 1 (Argmax + Upsample)**:
    *   Byte 0: **Channel Index** (类别索引)
    *   Byte 1-3: **Channel Value** (具体数值，需 /16 还原为实际值)

---

## 3. 构建与运行
`XDemo` 依赖本地安装的 `Icraft` 库。编译通常通过 CMake 进行：

```bash
mkdir build && cd build
cmake ..
make
./xdemo_app
```
(具体编译步骤请参考工程根目录下的 `README` 或 `CMakeLists.txt`)
