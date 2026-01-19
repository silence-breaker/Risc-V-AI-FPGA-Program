import torch
import time
import psutil
import os
import pandas as pd
import numpy as np
import re
import json
import platform
from datetime import datetime
from pathlib import Path
from transformers import AutoModelForCausalLM, AutoTokenizer

# ================= 配置区域 =================
SCRIPT_DIR = Path(__file__).parent.resolve()
PROJECT_ROOT = SCRIPT_DIR.parent
MODEL_PATH = PROJECT_ROOT / "models" / "microsoftbitnet-b1.58-2B-4T-bf16"
OUTPUT_DIR = PROJECT_ROOT / "docs"
PROMPT = "Microsoft is" 

# ================= 辅助工具 =================
def get_mem_mb():
    return psutil.Process(os.getpid()).memory_info().rss / 1024 / 1024

class AdvancedProfiler:
    def __init__(self):
        self.layer_stats = []
        self.temp_start = {}
        self.abs_mem_start = get_mem_mb()  # 记录初始绝对内存
        
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
                    'Mem Delta (MB)': mem_delta,
                    'Abs Mem (MB)': end_m,  # 记录绝对内存
                    'Input Shape': str(list(in_shape))
                })
                del self.temp_start[name]
        return hook

# ================= 主程序 =================
if __name__ == "__main__":
    # 创建输出目录
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    
    # 收集系统信息
    system_info = {
        'date': datetime.now().strftime('%Y年%m月%d日'),
        'platform': platform.system(),
        'processor': platform.processor(),
        'cpu_count': psutil.cpu_count(logical=True),
        'cpu_count_physical': psutil.cpu_count(logical=False),
        'memory_total_gb': round(psutil.virtual_memory().total / (1024**3), 2),
        'python_version': platform.python_version(),
        'torch_version': torch.__version__,
    }
    
    print(">>> 1. 加载模型...")
    mem_before_load = get_mem_mb()
    tokenizer = AutoTokenizer.from_pretrained(MODEL_PATH, trust_remote_code=False)
    model = AutoModelForCausalLM.from_pretrained(
        MODEL_PATH, device_map="cpu", torch_dtype=torch.float32, trust_remote_code=False
    )
    mem_after_load = get_mem_mb()
    
    # 获取模型结构信息
    model_structure = str(model)
    
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
    input_ids = inputs.input_ids
    seq_len = input_ids.shape[1]
    
    start_inference = time.perf_counter()
    with torch.no_grad():
        _ = model(input_ids)
    end_inference = time.perf_counter()
    total_inference_time = (end_inference - start_inference) * 1000  # ms
        
    # ================= 数据分析核心逻辑 =================
    print("\n>>> 4. 生成科学分析报告...")
    df = pd.DataFrame(profiler.layer_stats)
    
    # 保存完整的原始数据
    df.to_csv(OUTPUT_DIR / "raw_layer_data.csv", index=False)
    
    # 获取 Layer 0 数据 (包含初始化开销)
    df_layer0 = df[df['Layer Num'] == 0].copy()
    
    # 获取中间层数据（稳定运行）
    max_layer = df['Layer Num'].max()
    mid_layer = max_layer // 2
    df_mid_layer = df[df['Layer Num'] == mid_layer].copy()
    
    # 【关键步骤】剔除 Layer 0 (预热数据)
    df_stable = df[df['Layer Num'] > 0].copy()
    
    # 按算子类型分组统计 (取平均值)
    stats = df_stable.groupby('Submodule').agg({
        'Time (ms)': 'mean',
        'OPs': 'mean',
        'Mem Delta (MB)': 'mean'
    }).reset_index()
    
    # 计算衍生指标
    stats['Effective GOPS'] = (stats['OPs'] / 1e9) / (stats['Time (ms)'] / 1000)
    
    total_time = stats['Time (ms)'].sum()
    total_ops = stats['OPs'].sum()
    
    stats['Time Ratio (%)'] = (stats['Time (ms)'] / total_time) * 100
    stats['OPs Ratio (%)'] = (stats['OPs'] / total_ops) * 100
    
    stats = stats.sort_values(by='OPs', ascending=False)
    
    # MLP 和 Attention 分组统计
    mlp_ops = ['gate_proj', 'up_proj', 'down_proj']
    attn_ops = ['q_proj', 'k_proj', 'v_proj', 'o_proj']
    
    mlp_stats = stats[stats['Submodule'].isin(mlp_ops)]
    attn_stats = stats[stats['Submodule'].isin(attn_ops)]
    
    mlp_time = mlp_stats['Time (ms)'].sum()
    attn_time = attn_stats['Time (ms)'].sum()
    nonlinear_time = total_time - mlp_time - attn_time if total_time > (mlp_time + attn_time) else 0
    
    # 构建报告数据结构
    report_data = {
        'meta': {
            'report_title': 'BitNet b1.58 模型 CPU 推理性能分析报告',
            'date': system_info['date'],
            'framework': 'PyTorch (CPU only)',
            'model_path': str(MODEL_PATH),
            'prompt': PROMPT,
            'seq_len': int(seq_len),
        },
        'system_info': system_info,
        'model_info': {
            'structure': model_structure,
            'num_layers': int(max_layer + 1),
            'memory_loaded_mb': round(mem_after_load - mem_before_load, 2),
        },
        'inference_summary': {
            'total_time_ms': round(total_inference_time, 2),
            'total_ops_per_layer': int(total_ops),
            'avg_time_per_layer_ms': round(total_time, 2),
        },
        'layer_distribution': {
            'mlp_time_ms': round(mlp_time, 2),
            'mlp_time_ratio': round(mlp_time / total_time * 100, 1),
            'attn_time_ms': round(attn_time, 2),
            'attn_time_ratio': round(attn_time / total_time * 100, 1),
            'nonlinear_time_ms': round(nonlinear_time, 2),
            'nonlinear_time_ratio': round(nonlinear_time / total_time * 100, 1) if total_time > 0 else 0,
        },
        'operator_stats': stats.to_dict(orient='records'),
        'layer0_data': df_layer0.to_dict(orient='records'),
        'mid_layer_data': df_mid_layer.to_dict(orient='records'),
        'raw_data_file': 'raw_layer_data.csv'
    }
    
    # 保存 JSON 报告数据
    with open(OUTPUT_DIR / "inference_profile_report.json", 'w', encoding='utf-8') as f:
        json.dump(report_data, f, indent=2, ensure_ascii=False, default=str)
    
    # 格式化输出
    pd.options.display.float_format = '{:.4f}'.format
    
    print("\n" + "="*80)
    print(f"   BitNet 算子级性能剖析报告 (Stable Phase: Layers 1-{max_layer})")
    print("="*80)
    print(f"输入提示词: '{PROMPT}'")
    print(f"序列长度: {seq_len}")
    print(f"统计基准: 单个 Decoder Layer 的平均表现")
    print("-" * 80)
    
    cols = ['Submodule', 'Time (ms)', 'Time Ratio (%)', 'OPs', 'OPs Ratio (%)', 'Effective GOPS', 'Mem Delta (MB)']
    print(stats[cols].to_string(index=False))
    
    print("-" * 80)
    print(f"Total Time per Layer: {total_time:.2f} ms")
    print(f"Total OPs per Layer:  {total_ops:,.0f}")
    print("-" * 80)
    print(f"MLP Block 耗时: {mlp_time:.2f} ms ({mlp_time/total_time*100:.1f}%)")
    print(f"Attention Block 耗时: {attn_time:.2f} ms ({attn_time/total_time*100:.1f}%)")
    print("="*80)
    
    # 保存统计数据
    stats.to_csv(OUTPUT_DIR / "final_operator_benchmark.csv", index=False)
    
    print(f"\n✅ 报告数据已保存至 '{OUTPUT_DIR}':")
    print(f"   - inference_profile_report.json (完整报告数据)")
    print(f"   - raw_layer_data.csv (原始层数据)")
    print(f"   - final_operator_benchmark.csv (算子统计数据)")