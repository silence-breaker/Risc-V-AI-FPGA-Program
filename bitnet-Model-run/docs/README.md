# 共同任务一：BitNet b1.58 模型 CPU 推理性能分析

## 任务目标

分析 `microsoft/bitnet-b1.58-2B-4T-bf16` 模型在 PyTorch 框架下纯 CPU 环境的推理性能：

1. **时间开销分析**：各推理阶段（Tokenization、Prefill、Decode、Detokenization）的耗时
2. **内存占用分析**：模型加载、推理过程中的内存变化
3. **频率归一化**：将实测时间归一化到参考 CPU 频率（3.0 GHz），便于跨机器比较

## 项目结构

```
bitnet-Model-run/
├── setup.sh                    # 环境配置脚本
├── requirements.txt            # Python 依赖
├── src/
│   ├── inference_profiler.py   # 主分析脚本
│   └── run_analysis.sh         # 运行脚本
└── docs/
    ├── README.md               # 本文档
    └── inference_profile_report.json  # 分析报告（运行后生成）
```

## 快速开始

### 1. 配置环境

```bash
cd bitnet-Model-run
chmod +x setup.sh
./setup.sh
```

### 2. 运行分析

```bash
# 方式一：使用运行脚本
chmod +x src/run_analysis.sh
./src/run_analysis.sh

# 方式二：手动运行
source venv/bin/activate
cd src
python inference_profiler.py --help  # 查看参数
python inference_profiler.py
```

### 3. 查看报告

分析完成后，报告将保存在 `docs/inference_profile_report.json`。

## 推理阶段说明

### Transformer 模型推理流程

```
用户输入 → [Tokenization] → Token IDs
                              ↓
                         [Prefill]  ← 处理整个 prompt，生成 KV Cache
                              ↓
                         [Decode]   ← 逐 token 生成（自回归）
                              ↓
Token IDs → [Detokenization] → 输出文本
```

| 阶段 | 说明 | 计算特性 |
|------|------|----------|
| **Tokenization** | 文本编码为 Token ID | CPU 字符串处理 |
| **Prefill** | 首次前向传播，处理完整 prompt | Compute-bound（计算密集） |
| **Decode** | 逐 token 生成，每步读取全部权重 | Memory-bound（访存密集） |
| **Detokenization** | Token ID 解码为文本 | CPU 字符串处理 |

### 为什么 Decode 是瓶颈？

在 Decode 阶段，每生成一个 token 都需要：

1. 从内存读取全部模型权重（~500MB for 2-bit packed）
2. 执行一次完整的前向传播

这导致 **内存带宽成为主要瓶颈**，而非计算能力。

## 频率归一化说明

不同 CPU 的主频不同，直接比较耗时不公平。我们采用以下归一化方法：

$$\text{归一化时间} = \text{实测时间} \times \frac{\text{实际 CPU 频率}}{\text{参考频率 (3.0 GHz)}}$$

例如：

- 某 CPU 频率为 2.4 GHz，实测 Prefill 耗时 1000ms
- 归一化时间 = 1000 × (2400 / 3000) = 800ms

这样可以估算在"标准" 3.0 GHz CPU 上的等效耗时。

## 报告格式说明

`inference_profile_report.json` 包含：

```json
{
  "meta": {
    "model_name": "模型名称",
    "timestamp": "运行时间",
    "reference_freq_mhz": 3000
  },
  "cpu_info": {
    "brand": "CPU 型号",
    "freq_base_mhz": "基准频率"
  },
  "freq_normalization": {
    "scale_factor": "归一化系数",
    "explanation": "计算公式"
  },
  "stage_profiles": [
    {
      "name": "阶段名称",
      "duration_ms": "实测耗时",
      "duration_normalized_ms": "归一化耗时",
      "memory_before_mb": "阶段前内存",
      "memory_after_mb": "阶段后内存",
      "memory_delta_mb": "内存变化"
    }
  ],
  "summary": {
    "total_time_ms": "总耗时",
    "peak_memory_mb": "峰值内存"
  }
}
```

## 团队成员结果汇总

> LCJ 负责汇总三人的分析结果

| 成员 | CPU 型号 | 基准频率 | Prefill (ms) | Decode (ms/token) | 峰值内存 (MB) |
|------|----------|----------|--------------|-------------------|---------------|
| WJ   |          |          |              |                   |               |
| WYC  |          |          |              |                   |               |
| LCJ  |          |          |              |                   |               |

## 参考资料

- [BitNet b1.58 论文](https://arxiv.org/abs/2402.17764)
- [HuggingFace 模型页面](https://huggingface.co/microsoft/bitnet-b1.58-2B-4T-bf16)
- [Roofline Model 性能分析](https://en.wikipedia.org/wiki/Roofline_model)
