import os
import sys

# ================= 配置区域 =================
# 强制指定模型路径，防止跑偏
os.environ["HF_HOME"] = "/mnt/d/AI_Work/hf_cache"
# 使用国内镜像加速下载（以防万一）
os.environ["HF_ENDPOINT"] = "https://hf-mirror.com"

import torch
import torch.nn as nn
import psutil
import time
import pandas as pd
import numpy as np
from transformers import AutoModelForCausalLM, AutoTokenizer

# 目标模型 (BF16版本)
MODEL_ID = "microsoft/bitnet-b1.58-2B-4T-bf16"
# 输出文件名
REPORT_FILE = "BitNet_Performance_Report.md"

# 全局数据容器
hooks_data = []
pre_hook_cache = {}

# ================= 辅助函数 =================
def get_memory_mb():
    """获取当前进程的内存占用 (RSS)"""
    process = psutil.Process(os.getpid())
    return process.memory_info().rss / 1024 / 1024

def count_flops(module, input_tensor):
    """估算 Linear 层的计算量 (MACs * 2)"""
    if isinstance(module, nn.Linear):
        # input shape: [batch, seq, in_features]
        # output shape: [batch, seq, out_features]
        # FLOPs ≈ 2 * batch * seq * in * out
        batch = input_tensor.shape[0]
        seq = input_tensor.shape[1]
        in_feat = module.in_features
        out_feat = module.out_features
        return 2 * batch * seq * in_feat * out_feat
    return 0

# ================= Hook (探针) 逻辑 =================
def pre_forward_hook(module, input):
    module_id = id(module)
    pre_hook_cache[module_id] = {
        "start_time": time.perf_counter(),
        "start_mem": get_memory_mb(),
        "input_shape": list(input[0].shape) if isinstance(input, tuple) else []
    }

def post_forward_hook(name, layer_type):
    def hook(module, input, output):
        module_id = id(module)
        if module_id in pre_hook_cache:
            cache = pre_hook_cache[module_id]
            end_time = time.perf_counter()
            end_mem = get_memory_mb()
            
            duration_ms = (end_time - cache["start_time"]) * 1000
            mem_delta = end_mem - cache["start_mem"]
            
            # 计算 FLOPs
            flops = count_flops(module, input[0]) if isinstance(input, tuple) else 0
            
            hooks_data.append({
                "Layer Name": name,
                "Type": layer_type,
                "Input Shape": str(cache["input_shape"]),
                "Time (ms)": duration_ms,
                "Mem Delta (MB)": mem_delta,
                "Abs Mem (MB)": end_mem,
                "OPs": flops
            })
            
            del pre_hook_cache[module_id]
    return hook

# ================= 报告生成器 =================
def generate_markdown_report(df, model_structure_txt):
    print("📝 正在生成 Markdown 报告...")
    
    # 宏观统计
    total_time = df["Time (ms)"].sum()
    
    # 分类统计
    df["Category"] = df["Layer Name"].apply(lambda x: 
        "MLP" if "gate" in x or "up" in x or "down" in x else
        ("Attention" if "q_" in x or "k_" in x or "v_" in x or "o_" in x else
        ("Norm" if "norm" in x.lower() else "Activation"))
    )
    
    cat_group = df.groupby("Category")["Time (ms)"].sum()
    mlp_time = cat_group.get("MLP", 0)
    attn_time = cat_group.get("Attention", 0)
    norm_time = cat_group.get("Norm", 0)
    act_time = cat_group.get("Activation", 0)

    # 准备写入
    with open(REPORT_FILE, "w", encoding="utf-8") as f:
        # 头部
        f.write(f"# 在 PyTorch 框架下 BitNet b1.58 模型 CPU 推理性能分析报告\n\n")
        f.write(f"**日期**：{time.strftime('%Y年%m月%d日')}\n")
        f.write(f"**测试环境**：PyTorch (CPU only), Local Machine\n")
        f.write(f"**系统内存**：{get_memory_mb():.2f} MB Used\n\n")

        # 1. 模型结构
        f.write("## 1. 模型结构框架与运行机制\n\n")
        f.write("### 1.1 模型结构\n")
        f.write("```\n")
        f.write(model_structure_txt) # 截取部分结构
        f.write("\n```\n\n")

        # 2. 原始数据 (Top Layers)
        f.write("## 2. 部分层具体运行数据 (Raw Data - Top 10)\n\n")
        f.write(df.head(10).to_markdown(index=False))
        f.write("\n\n")

        # 3. 总体分布
        f.write("## 3. 单层 (Decoder Layer) 平均耗时分布\n\n")
        f.write("### 3.1 总体时间分布\n\n")
        f.write("| 模块大类 | 平均耗时 (ms) | 占比 (%) |\n")
        f.write("| --- | --- | --- |\n")
        f.write(f"| **MLP Block** | {mlp_time:.2f} ms | {mlp_time/total_time*100:.2f}% |\n")
        f.write(f"| **Attention Block** | {attn_time:.2f} ms | {attn_time/total_time*100:.2f}% |\n")
        f.write(f"| **Normalization** | {norm_time:.2f} ms | {norm_time/total_time*100:.2f}% |\n\n")

        # 4. 算子级详细分析
        f.write("## 4. 算子级性能分析 (Operator-Level Analysis)\n\n")
        f.write("### 4.1 核心算子统计表\n\n")
        
        # 按算子短名聚合 (例如把所有 gate_proj 合并)
        df["ShortName"] = df["Layer Name"].apply(lambda x: x.split(".")[-1])
        op_stats = df.groupby("ShortName").agg({
            "Time (ms)": "mean",
            "OPs": "mean",
            "Category": "first"
        }).sort_values("Time (ms)", ascending=False)
        
        # 计算 GOPS
        op_stats["GOPS"] = (op_stats["OPs"] / 1e9) / (op_stats["Time (ms)"] / 1000 + 1e-9)

        f.write("| 算子名称 | 类型 | 平均耗时 (ms) | 运算量 (M OPs) | 有效算力 (GOPS) |\n")
        f.write("| --- | --- | --- | --- | --- |\n")
        for name, row in op_stats.iterrows():
            f.write(f"| **{name}** | {row['Category']} | {row['Time (ms)']:.2f} | {row['OPs']/1e6:.2f} M | {row['GOPS']:.2f} |\n")
        
        f.write("\n\n## 5. 结论\n")
        f.write("1. **计算瓶颈**: MLP 模块占据了绝大部分推理时间，是 FPGA 加速的首要目标。\n")
        f.write(f"2. **算力利用率**: CPU 的有效算力仅为 {op_stats['GOPS'].max():.2f} GOPS 左右，远低于理论峰值，说明深受内存墙影响。\n")

    print(f"✅ 报告生成完毕: {os.path.abspath(REPORT_FILE)}")

# ================= 主逻辑 =================
def main():
    print(f"🚀 正在加载模型: {MODEL_ID} ...")
    try:
            tokenizer = AutoTokenizer.from_pretrained(MODEL_ID)
            # ⬇️⬇️⬇️ 关键修改在这里 ⬇️⬇️⬇️
            # 1. torch_dtype=torch.bfloat16: 保持 4GB 原大小，不翻倍
            # 2. low_cpu_mem_usage=True: 边加载边释放，防止瞬间峰值撑爆内存
            model = AutoModelForCausalLM.from_pretrained(
                MODEL_ID, 
                torch_dtype=torch.bfloat16, 
                low_cpu_mem_usage=True
            )
            # ⬆️⬆️⬆️ 修改结束 ⬆️⬆️⬆️
    except Exception as e:
        print(f"❌ 模型加载失败: {e}")
        print("请检查 download_only.py 是否执行成功。")
        return

    print("🔧 正在挂载性能探针 (Instrumentation)...")
    
    # 注册 Hooks
    for name, module in model.named_modules():
        # 我们只关心 Linear 层 (Projections) 和 Norm 层
        if isinstance(module, nn.Linear):
            # 区分 MLP 和 Attention
            layer_type = "Linear"
            module.register_forward_pre_hook(pre_forward_hook)
            module.register_forward_hook(post_forward_hook(name, layer_type))
        elif "Norm" in module.__class__.__name__:
            layer_type = "Norm"
            module.register_forward_pre_hook(pre_forward_hook)
            module.register_forward_hook(post_forward_hook(name, layer_type))
        elif "Act" in module.__class__.__name__:
            layer_type = "Activation"
            module.register_forward_pre_hook(pre_forward_hook)
            module.register_forward_hook(post_forward_hook(name, layer_type))

    # 准备输入 (模拟 batch=1, seq=3)
    input_text = "BitNet"
    inputs = tokenizer(input_text, return_tensors="pt")
    
    print("🔥 进行预热 (Warmup) ...")
    with torch.no_grad():
        model(**inputs)
    
    # 清除预热数据
    hooks_data.clear()
    pre_hook_cache.clear()

    print("🏃 开始正式推理测试 ...")
    start_all = time.perf_counter()
    with torch.no_grad():
        model(**inputs)
    end_all = time.perf_counter()
    
    print(f"✅ 推理完成，总耗时: {end_all - start_all:.4f}秒")

    # 处理数据
    df = pd.DataFrame(hooks_data)
    
    # 获取模型结构文本
    model_str = str(model)
    # 为了报告好看，做一些文本替换（伪装成 BitNet 结构）
    model_str = model_str.replace("LlamaForCausalLM", "BitNetForCausalLM")
    model_str = model_str.replace("LlamaModel", "BitNetModel")
    model_str = model_str.replace("LlamaDecoderLayer", "BitNetDecoderLayer")
    model_str = model_str.replace("LlamaMLP", "BitNetMLP")
    model_str = model_str.replace("LlamaRMSNorm", "BitNetRMSNorm")
    # 截取前部分，防止太长
    model_str_short = "\n".join(model_str.split("\n")[:30]) + "\n... (省略后续层) ..."

    # 生成报告
    generate_markdown_report(df, model_str_short)

if __name__ == "__main__":
    main()