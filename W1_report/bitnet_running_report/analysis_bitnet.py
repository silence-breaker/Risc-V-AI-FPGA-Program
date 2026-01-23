import torch
import time
import psutil
import os
import numpy as np
# 增加导入 LlamaTokenizer
from transformers import AutoModelForCausalLM, AutoTokenizer, LlamaTokenizer    

# === 配置区域 ===
# 微软官方发布的 PyTorch 版本模型
MODEL_ID = "1bitLLM/bitnet_b1_58-3B"

# 强制使用 CPU 进行分析
device = torch.device("cpu")
os.environ["CUDA_VISIBLE_DEVICES"] = ""

def print_memory(stage):
    """打印当前进程的内存占用"""
    process = psutil.Process(os.getpid())
    mem_mb = process.memory_info().rss / 1024 / 1024
    print(f"[{stage}] Memory Usage: {mem_mb:.2f} MB")
    return mem_mb

# === 1. 加载模型与分词器 ===
print(">>> Step 1: Loading Model (This pulls source code from HuggingFace)...")
print_memory("Before Load")

start_load = time.time()
# trust_remote_code=True 是关键，它允许加载微软自定义的 1.58bit 模型结构代码
# 强制使用 LlamaTokenizer，无视配置文件里错误的 BitnetTokenizer
tokenizer = LlamaTokenizer.from_pretrained(MODEL_ID, trust_remote_code=True)
model = AutoModelForCausalLM.from_pretrained(MODEL_ID, trust_remote_code=True).to(device)

# 将模型设为评估模式
model.eval()
print(f"Model loaded in {time.time() - start_load:.2f} seconds.")
base_memory = print_memory("After Load")

# === 2. 注册性能分析钩子 (Hooks) ===
# 用于存储每一层的耗时
layer_timings = {}

def get_time_hook(layer_name):
    """创建一个钩子，记录该层的运行时间"""
    def hook(module, input, output):
        start = time.time()
        # 这里只是为了触发计算，实际耗时需要在外部做更精细的 profiling
        # 但为了简单模拟“每一层占比”，我们记录调用时间戳（近似值）
        if layer_name not in layer_timings:
            layer_timings[layer_name] = []
        layer_timings[layer_name].append(time.time())
    return hook

# 为模型中的每一层 Linear 注册钩子
# 注意：BitNet 的核心层通常叫 BitLinear
print(">>> Step 2: Registering Hooks for Profiling...")
for name, module in model.named_modules():
    # 过滤出主要计算层（BitLinear 或 普通 Linear）
    if "Linear" in module.__class__.__name__ or "Bit" in module.__class__.__name__:
        module.register_forward_hook(get_time_hook(name))

# === 3. 运行推理 ===
print(">>> Step 3: Running Inference...")
input_text = "BitNet is a 1-bit Transformer architecture that"
inputs = tokenizer(input_text, return_tensors="pt").to(device)

# 使用 PyTorch Profiler 获取精确的算子级耗时
with torch.profiler.profile(
    activities=[torch.profiler.ProfilerActivity.CPU],
    record_shapes=True,
    profile_memory=True,
    with_stack=True
) as prof:
    with torch.no_grad():
        outputs = model.generate(**inputs, max_new_tokens=20)

print_memory("After Inference")

# === 4. 输出分析报告 ===
print("\n" + "="*40)
print("       ANALYSIS REPORT (CPU)       ")
print("="*40)

# 打印最耗时的前 15 个操作
print(prof.key_averages().table(sort_by="cpu_time_total", row_limit=15))

# 导出详细数据（可选）
# prof.export_chrome_trace("bitnet_trace.json")
# print("\nTrace file saved as 'bitnet_trace.json'")

generated_text = tokenizer.decode(outputs[0], skip_special_tokens=True)
print(f"\nGenerated Text: {generated_text}")