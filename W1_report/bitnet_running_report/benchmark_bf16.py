import os
# ==========================================
# 🚨 强制修复：在这里指定你的 D 盘路径
# 注意：你的文件夹是 AI_Work，不是 AI_Benchmark
os.environ["HF_HOME"] = "/mnt/d/AI_Work/hf_cache"
# ==========================================

import torch
import torch.nn as nn
import time
# ... (后面的代码保持不变)
import psutil
import os
import pandas as pd
import datetime
from transformers import AutoModelForCausalLM, AutoTokenizer

# ================= 配置区域 =================
MODEL_ID = "microsoft/bitnet-b1.58-2B-4T-bf16"
REPORT_FILENAME = "BitNet_Analysis_Report.md"
# 为了确保在普通 CPU 上也能跑，我们将精度转为 float32，
# 如果你的 CPU 支持 AVX-512 BF16，可以改为 torch.bfloat16
DTYPE = torch.float32 
DEVICE = "cpu"

# ================= 全局变量用于存储数据 =================
layer_stats = []
model_structure_str = ""

# ================= 辅助函数 =================
def get_memory_mb():
    process = psutil.Process(os.getpid())
    return process.memory_info().rss / 1024 / 1024

def format_params(num):
    if num > 1e6:
        return f"{num/1e6:.2f}M"
    return str(num)

# ================= 钩子函数 (The Spies) =================
# 我们需要两个钩子：一个在进入层之前记录时间/内存，一个在出来后记录增量

pre_record = {}

def pre_forward_hook(module, input):
    # 记录模块的内存 ID，防止递归调用混淆
    module_id = id(module)
    pre_record[module_id] = {
        "start_time": time.perf_counter(),
        "start_mem": get_memory_mb()
    }

def post_forward_hook(name, layer_type):
    def hook(module, input, output):
        module_id = id(module)
        if module_id in pre_record:
            end_time = time.perf_counter()
            end_mem = get_memory_mb()
            start_data = pre_record[module_id]
            
            duration_ms = (end_time - start_data["start_time"]) * 1000
            mem_delta = end_mem - start_data["start_mem"]
            
            # 计算运算量 (简单估算矩阵乘法)
            # Linear 层运算量 ≈ 2 * In * Out * Batch * Seq
            ops = 0
            input_shape = "N/A"
            if isinstance(input, tuple) and len(input) > 0:
                if isinstance(input[0], torch.Tensor):
                    shape = input[0].shape
                    input_shape = str(list(shape))
                    # 假设 input[0] 是 [batch, seq, in_features]
                    if isinstance(module, nn.Linear) and len(shape) == 3:
                        batch, seq, in_feat = shape
                        out_feat = module.out_features
                        ops = 2 * batch * seq * in_feat * out_feat
            
            layer_stats.append({
                "Layer Name": name,
                "Type": layer_type,
                "Input Shape": input_shape,
                "Time (ms)": duration_ms,
                "Mem Delta (MB)": mem_delta,
                "OPs": ops
            })
            
            # 清理记录
            del pre_record[module_id]
    return hook

# ================= 主程序 =================
def main():
    global model_structure_str
    print(f"🚀 开始加载模型: {MODEL_ID} ...")
    start_load = time.time()
    
    # 1. 加载模型
    tokenizer = AutoTokenizer.from_pretrained(MODEL_ID)
    model = AutoModelForCausalLM.from_pretrained(MODEL_ID, torch_dtype=DTYPE).to(DEVICE)
    
    load_time = time.time() - start_load
    model_mem = get_memory_mb()
    print(f"✅ 模型加载完成。耗时: {load_time:.2f}s, 当前内存: {model_mem:.2f} MB")
    
    # 保存模型结构字符串用于报告
    model_structure_str = str(model)

    # 2. 自动挂载钩子 (Auto-Instrumentation)
    print("🔧 正在给模型层挂载性能监测钩子...")
    hooks = []
    for name, module in model.named_modules():
        # 只监测关键层：Linear (Projections) 和 Norm
        # 过滤掉大容器，只看叶子节点
        if isinstance(module, nn.Linear):
            # 区分是 Attention 里的还是 MLP 里的
            h1 = module.register_forward_pre_hook(pre_forward_hook)
            h2 = module.register_forward_hook(post_forward_hook(name, "Linear"))
            hooks.extend([h1, h2])
        elif "Norm" in module.__class__.__name__:
            h1 = module.register_forward_pre_hook(pre_forward_hook)
            h2 = module.register_forward_hook(post_forward_hook(name, "Norm"))
            hooks.extend([h1, h2])
        elif "Act" in module.__class__.__name__ or "SiLU" in module.__class__.__name__:
             h1 = module.register_forward_pre_hook(pre_forward_hook)
             h2 = module.register_forward_hook(post_forward_hook(name, "Activation"))
             hooks.extend([h1, h2])

    # 3. 运行推理 (Run Inference)
    print("🏃 开始推理测试 (Prompt: 'BitNet is')...")
    input_text = "BitNet is"
    inputs = tokenizer(input_text, return_tensors="pt").to(DEVICE)
    
    # 预热一次 (Warmup) - 让 PyTorch 初始化内存池和 JIT
    with torch.no_grad():
        model(**inputs)
    
    # 清空预热数据，重新记录
    layer_stats.clear()
    
    # 正式运行
    with torch.no_grad():
        outputs = model(**inputs)

    print("📊 数据收集完毕，正在生成报告...")
    generate