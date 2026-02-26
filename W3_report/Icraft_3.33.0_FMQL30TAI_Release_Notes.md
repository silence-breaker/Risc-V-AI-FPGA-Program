# Icraft v3.33.0 FMQL30TAI Release Notes

## 1. 概述
**发布版本**: v3.33.0  
**发布日期**: 2024-04-12  
**硬件平台**: FMQL30TAI (Zhuge)

本版本主要针对 Icraft 工具链在 FMQL30TAI 平台上的功能增强与优化，提供了对更多算子、网络模型的支持，并改进了量化策略与编译流程。

---

## 2. 支持算子列表 (Supported Operators)

Icraft v3.33.0 支持以下算子操作，覆盖了常见的数学运算、逻辑控制及神经网络层：

| 算子类别 | 算子名称 | 描述 |
| :--- | :--- | :--- |
| **基础数学运算** | `Abs` | 绝对值运算 |
| | `Add` | 加法运算 |
| | `Sub` | 减法运算 |
| | `Mul` | 乘法运算 |
| | `Div` | 除法运算 |
| | `Neg` | 取负运算 |
| | `Exp` | 指数运算 |
| | `Log` | 对数运算 |
| | `Sqrt` | 平方根运算 |
| | `Pow` | 幂运算 |
| **激活函数** | `Relu` | Rectified Linear Unit |
| | `Relu6` | Relu6 激活函数 |
| | `LeakyRelu` | Leaky Relu 激活函数 |
| | `Sigmoid` | Sigmoid 全连接 |
| | `Tanh` | 双曲正切函数 |
| | `HardSigmoid` | Hard Sigmoid |
| | `HardSwish` | Hard Swish |
| | `Softmax` | Softmax 归一化 |
| **卷积与池化** | `Conv` | 卷积层 |
| | `ConvTranspose` | 转置卷积 (反卷积) |
| | `AveragePool` | 平均池化 |
| | `MaxPool` | 最大池化 |
| | `GlobalAveragePool`| 全局平均池化 |
| **形状变换** | `Reshape` | 形状重塑 |
| | `Transpose` |不仅支持常规转置，也支持特殊维度变换 |
| | `Flatten` | 展平操作 |
| | `Squeeze` | 压缩维度 |
| | `Unsqueeze` | 增加维度 |
| | `Concat` | 张量拼接 |
| | `Split` | 张量分割 |
| | `Slice` | 张量切片 |
| | `Pad` | 填充操作 |
| | `Resize` | 图像缩放 (Nearest, Linear) |
| **逻辑与归一化** | `BatchNormalization` | 批归一化 |
| | `InstanceNormalization` | 实例归一化 |
| | `LayerNormalization` | 层归一化 |
| | `Clip` | 数值截断 |
| | `Cast` | 数据类型转换 |
| | `Gemm` | 通用矩阵乘法 (全连接层) |
| | `MatMul` | 矩阵乘法 |
| | `Where` | 条件选择 |
| **其他** | `Constant` | 常量节点 |
| | `Shape` | 获取形状 |
| | `Gather` | 数据收集 |
| | `ScatterND` | 稀疏数据分散 |
| | `TopK` | 取前K个最大/小值 |
| | `ReduceMean/Max/Min` | 归约操作 |

> *注：部分算子支持特定的属性配置（如 `dilations`, `pads`, `strides` 等），具体请参考算子详细约束文档。*

---

## 3. 支持网络模型 (Supported Networks)

以下网络模型在 FMQL30TAI 平台上经过验证，可正常编译与运行：

### 3.1 目标检测 (Object Detection)
- **YOLO 系列**: 
  - `Yolov5s`
  - `Yolov3`
  - `Yolov3-tiny`
- **SSD**: Single Shot MultiBox Detector
- **RetinaNet**: 基于 ResNet50 backbone

### 3.2 图像分类 (Image Classification)
- **ResNet 系列**: `ResNet18`, `ResNet50`
- **MobileNet 系列**: `MobileNetV1`, `MobileNetV2`
- **Inception 系列**: `InceptionV3`
- **VGG**: `VGG16`
- **SqueezeNet**: `SqueezeNet1.1`

### 3.3 语义分割 (Semantic Segmentation)
- **UNet**: 医学图像分割常用网络
- **FCN**: Fully Convolutional Networks

### 3.4 关键点检测与姿态估计
- **OpenPose**: 人体姿态估计

---

## 4. 编译与量化配置说明

为在 FMQL30TAI 硬件上达到最佳性能，编译配置推荐如下：

### 4.1 量化配置 (Quantization)

FMQL30TAI 使用 8-bit / 16-bit 混合量化方案。

*   **Calibration Method**: `MinMax` 或 `KL-Divergence` (推荐用于激活值分布不均匀的层)
*   **Weight Quantization**: Per-Channel (推荐) 或 Per-Tensor
*   **Activation Quantization**: Per-Tensor

示例配置文件 (`config.toml`):

```toml
[quantization]
method = "minmax"  # options: minmax, kl, mse
weight_granularity = "per_channel"
activation_type = "int8"
weight_type = "int8"
calibration_dataset = "./calib_data"
```

### 4.2 编译优化 (Compilation)

*   **Optimization Level**: `O3` (推荐，开启图融合与指令调度优化)
*   **Target**: `FMQL30TAI`

---

## 5. 已知问题与限制

1.  **动态形状**: 当前版本暂不支持动态 Input Shape，编译时需指定静态 Input Dimensions。
2.  **算子限制**: `Resize` 算子在某些特定插值模式下可能 fallback 到 CPU 执行。
3.  **内存管理**: 对于超大模型（> 几百 MB），需确保除去权重外有足够的系统内存用于中间激活值存储。
