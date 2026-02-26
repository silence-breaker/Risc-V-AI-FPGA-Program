# Icraft Show 可视化工具

## 1. 简介
`Icraft Show` 是一款强大的可视化分析工具，用于展示神经网络模型结构、分析量化精度损失以及查看内存优化策略。它支持 JSON 模型文件导入、各阶段 FTMP (Feature Map) 数据对比分析。

---

## 2. 命令行参数

使用命令行启动工具时，可指定以下参数：

| 参数 | 描述 | 功能 |
| :--- | :--- | :--- |
| `--json <path>` | 模型结构 JSON 文件路径 | 直观显示网络拓扑结构 |
| `--raw <path>` | 模型权重 RAW 文件路径 | 辅助显示权重详情（需配合 json 使用） |
| `--analyse <dir>` | 分析结果文件夹 | 加载量化误差分析结果 |
| `--ftmp_dir1 <dir>` | 待对比 FTMP 文件夹 A | 用于 `diff` 模式 |
| `--ftmp_dir2 <dir>` | 待对比 FTMP 文件夹 B | 用于 `diff` 模式 |
| `--log_path <dir>` | 日志输出路径 | 默认为 `.icraft/log` |

---

## 3. 功能模块详解

### 3.1 网络参数可视化 (Net View)
*   **输入**: 支持 `JSON` (结构) 和 `RAW` (权重) 文件导入，或 `Snapshot` 快照包。
*   **界面**: 
    *   **全局信息**: 左上角显示网络名称、框架来源、算子总数。
    *   **拓扑图**: 节点代表算子 (Conv, Relu 等)，边代表 Tensor (ftmp)。
    *   **详情页**: 点击算子，右侧侧边栏显示详细属性（Stride, Pad 等）。
*   **权重查看**: 如加载了 RAW 文件，可查看具体权重的十进制/十六进制数值，并支持导出 CSV。
*   **搜索**: `Ctrl+F` 呼出搜索框，支持按算子类型 `Conv`、算子 ID `op_123` 或 Tensor ID `ftmp_456` 进行定位。

### 3.2 量化分析 (Quantization Analysis)
该模块用于分析浮点模型与量化模型之间的精度差异 (Accuracy Loss)。

#### 工作模式
1.  **XRUN 独立前向**: 
    *   输入完整的 JSON/RAW 模型。
    *   配置 Input 图片或数据集 TXT。
    *   工具自动运行前向推理，生成每一层的输出。
2.  **逐层对比 (Layer-wise Analysis)**:
    *   输入 **Golden Model** (基准，通常是 Float) 和 **Test Model** (待测，通常是 Quantized)。
    *   **原理**: 将 Golden 模型的中间输出作为 Test 模型对应层的输入，消除累积误差，精确定位引入误差的单层算子。
    *   **指标**: 计算余弦相似度 (Cosine Similarity)、欧氏距离 (Euclidean Distance)、平均绝对误差 (MAE)。

#### 结果展示
*   **折线图**: 横轴为算子执行序，纵轴为相似度/误差值。点击表头可隐藏/显示特定曲线。
*   **数据采样**: 点击某个数据点，可查看该层输出 Tensor 的具体数值波形图（支持前1000个点采样）。

### 3.3 内存优化分析 (Memory Optimization)
用于分析 CodeGen 编译器的内存分配策略。

*   **输入**: `_generate_memopt.log` (由 Compiler Generate 阶段生成)。
*   **视图**: 
    *   **时间-空间图**: 横轴为时间周期，纵轴为内存地址空间。
    *   **矩形块**:代表一个 FTMP 的生命周期。
    *   **存储类型**: 支持切换查看 **ETM** (External Memory / DDR) 和 **OCM** (On-Chip Memory)。
*   **交互**: 鼠标滚轮缩放，拖拽平移。用途是检查内存复用是否紧凑，以及 OCM 利用率是否充分。
