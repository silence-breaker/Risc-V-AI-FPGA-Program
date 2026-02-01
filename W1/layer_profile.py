import torch
import time
import psutil
import os
import pandas as pd
import numpy as np
import re
from transformers import AutoModelForCausalLM, AutoTokenizer

# ================= 配置区域 =================
MODEL_PATH = "D:/BitNet_Model_Local"
PROMPT = "Microsoft is" 

# ================= 辅助工具 =================
def get_mem_mb():
    return psutil.Process(os.getpid()).memory_info().rss / 1024 / 1024

class AdvancedProfiler:
    def __init__(self):
        self.layer_stats = []
        self.temp_start = {}
        
    def pre_hook(self, name):
        def hook(module, input):
            self.temp_start[name] = {
                'start_t': time.perf_counter(),
                'start_m': get_mem_mb(),
                'input_shape': input[0].shape  # 捕获输入形状 [Batch, Seq, Hidden]
            }
        return hook
        
    def post_hook(self, name, layer_type):
        def hook(module, input, output):
            if name in self.temp_start:
                start_data = self.temp_start[name]
                end_t = time.perf_counter()
                end_m = get_mem_mb()
                
                duration = (end_t - start_data['start_t']) * 1000 # ms
                mem_delta = max(0, end_m - start_data['start_m'])
                
                # 自动推断维度
                in_shape = start_data['input_shape']
                B, S, K = in_shape[0], in_shape[1], in_shape[2]
                
                # 推断输出维度 N
                # 对于 Linear 层: Weight shape is [N, K], Output is [B, S, N]
                N = 0
                if hasattr(module, 'out_features'):
                    N = module.out_features
                elif hasattr(module, 'weight'):
                    N = module.weight.shape[0]
                
                # 计算运算量 (OPs = 2 * M * K * N)
                # M = Batch * Seq
                ops = 2 * (B * S) * K * N if N > 0 else 0
                
                # 解析层号
                layer_num = -1
                match = re.search(r'layers\.(\d+)', name)
                if match:
                    layer_num = int(match.group(1))

                self.layer_stats.append({
                    'Layer Name': name,
                    'Layer Num': layer_num,
                    'Submodule': name.split('.')[-1], # e.g., q_proj, gate_proj
                    'Type': layer_type,
                    'Time (ms)': duration,
                    'OPs': ops,
                    'Mem Delta (MB)': mem_delta
                })
                del self.temp_start[name]
        return hook

# ================= 主程序 =================
if __name__ == "__main__":
    print(">>> 1. 加载模型...")
    tokenizer = AutoTokenizer.from_pretrained(MODEL_PATH, trust_remote_code=False)
    model = AutoModelForCausalLM.from_pretrained(
        MODEL_PATH, device_map="cpu", torch_dtype=torch.float32, trust_remote_code=False
    )
    
    profiler = AdvancedProfiler()
    
    # 注册 Hooks
    print(">>> 2. 注册性能探针 (监控所有 Linear 层)...")
    for name, module in model.named_modules():
        # 只监控 Linear 相关层
        if "Linear" in module.__class__.__name__:
            module.register_forward_pre_hook(profiler.pre_hook(name))
            module.register_forward_hook(profiler.post_hook(name, module.__class__.__name__))

    # 运行推理
    print(">>> 3. 运行推理 (收集数据)...")
    inputs = tokenizer(PROMPT, return_tensors="pt")
    with torch.no_grad():
        _ = model(inputs.input_ids)
        
    # ================= 数据分析核心逻辑 =================
    print("\n>>> 4. 生成科学分析报告...")
    df = pd.DataFrame(profiler.layer_stats)
    
    # 【关键步骤】剔除 Layer 0 (预热数据)
    df_stable = df[df['Layer Num'] > 0].copy()
    
    # 按算子类型分组统计 (取平均值)
    # 我们关心的是：对于任意一个标准的 Decoder Layer，里面的各个算子表现如何
    stats = df_stable.groupby('Submodule').agg({
        'Time (ms)': 'mean',
        'OPs': 'mean',        # 理论上每层OPs应该一样，取平均即可
        'Mem Delta (MB)': 'mean'
    }).reset_index()
    
    # 计算衍生指标
    # 1. Effective GOPS (有效算力) = (OPs / 1e9) / (Time_s)
    stats['Effective GOPS'] = (stats['OPs'] / 1e9) / (stats['Time (ms)'] / 1000)
    
    # 2. Total Metrics (用于计算占比)
    total_time = stats['Time (ms)'].sum()
    total_ops = stats['OPs'].sum()
    
    # 3. Ratios (占比)
    stats['Time Ratio (%)'] = (stats['Time (ms)'] / total_time) * 100
    stats['OPs Ratio (%)'] = (stats['OPs'] / total_ops) * 100 # 算力占总算力(运算量)之比
    
    # 4. 排序 (按运算量大小排序，突出重点)
    stats = stats.sort_values(by='OPs', ascending=False)
    
    # 格式化输出
    pd.options.display.float_format = '{:.4f}'.format
    
    print("\n" + "="*80)
    print(f"   BitNet 算子级性能剖析报告 (Stable Phase: Layers 1-{df['Layer Num'].max()})")
    print("="*80)
    print(f"输入提示词: '{PROMPT}'")
    print(f"统计基准: 单个 Decoder Layer 的平均表现")
    print("-" * 80)
    
    # 重新排列列顺序，符合人类阅读习惯
    cols = ['Submodule', 'Time (ms)', 'Time Ratio (%)', 'OPs', 'OPs Ratio (%)', 'Effective GOPS', 'Mem Delta (MB)']
    print(stats[cols].to_string(index=False))
    
    print("-" * 80)
    print(f"Total Time per Layer: {total_time:.2f} ms")
    print(f"Total OPs per Layer:  {total_ops:,.0f}")
    print("="*80)
    
    # 保存
    stats.to_csv("final_operator_benchmark.csv", index=False)
    print("\n✅ 详细数据已保存至 'final_operator_benchmark.csv'")