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
            # 处理不同类型的输入
            if isinstance(input, tuple) and len(input) > 0:
                first_input = input[0]
            else:
                first_input = input
            
            input_shape = None
            if hasattr(first_input, 'shape'):
                input_shape = first_input.shape
            
            self.temp_start[name] = {
                'start_t': time.perf_counter(),
                'start_m': get_mem_mb(),
                'input_shape': input_shape
            }
        return hook
        
    def post_hook(self, name, layer_type, category='other'):
        def hook(module, input, output):
            if name in self.temp_start:
                start_data = self.temp_start[name]
                end_t = time.perf_counter()
                end_m = get_mem_mb()
                
                duration = (end_t - start_data['start_t']) * 1000 # ms
                mem_delta = max(0, end_m - start_data['start_m'])
                
                # 自动推断维度
                in_shape = start_data['input_shape']
                ops = 0
                input_shape_str = "N/A"
                
                if in_shape is not None and len(in_shape) >= 3:
                    B, S, K = in_shape[0], in_shape[1], in_shape[2]
                    input_shape_str = str(list(in_shape))
                    
                    # 推断输出维度 N (仅对 Linear 层)
                    N = 0
                    if hasattr(module, 'out_features'):
                        N = module.out_features
                    elif hasattr(module, 'weight') and len(module.weight.shape) >= 2:
                        N = module.weight.shape[0]
                    
                    # 计算运算量
                    if category == 'linear':
                        # Linear: OPs = 2 * M * K * N
                        ops = 2 * (B * S) * K * N if N > 0 else 0
                    elif category == 'norm':
                        # RMSNorm: 需要计算均方根，约 3*N 操作（平方、求和、开方、除法）
                        ops = 3 * B * S * K
                    elif category == 'activation':
                        # ReLU²: 2*N 操作（ReLU + 平方）
                        ops = 2 * B * S * K
                    elif category == 'embedding':
                        # Embedding: 查表操作，主要是内存访问
                        ops = B * S * K  # 近似
                elif in_shape is not None and len(in_shape) == 2:
                    # 处理 2D 输入 (如 Embedding 的输入)
                    B, S = in_shape[0], in_shape[1]
                    input_shape_str = str(list(in_shape))
                    if category == 'embedding' and hasattr(module, 'embedding_dim'):
                        ops = B * S * module.embedding_dim
                
                # 解析层号
                layer_num = -1
                match = re.search(r'layers\.(\d+)', name)
                if match:
                    layer_num = int(match.group(1))

                self.layer_stats.append({
                    'Layer Name': name,
                    'Layer Num': layer_num,
                    'Submodule': name.split('.')[-1],
                    'Type': layer_type,
                    'Category': category,
                    'Time (ms)': duration,
                    'OPs': ops,
                    'Mem Delta (MB)': mem_delta,
                    'Abs Mem (MB)': end_m,
                    'Input Shape': input_shape_str
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
    
    # 注册 Hooks - 监控所有关键层
    print(">>> 2. 注册性能探针 (监控 Linear、Norm、Activation、Embedding 层)...")
    
    # 定义需要监控的层类型
    linear_types = ['Linear', 'BitLinear', 'AutoBitLinear']
    norm_types = ['RMSNorm', 'LayerNorm', 'BitNetRMSNorm']
    activation_types = ['ReLU', 'GELU', 'SiLU', 'Activation', 'ReLUSquaredActivation']
    embedding_types = ['Embedding']
    rotary_types = ['RotaryEmbedding', 'BitNetRotaryEmbedding']
    
    for name, module in model.named_modules():
        class_name = module.__class__.__name__
        
        # Linear 层
        if any(t in class_name for t in linear_types):
            module.register_forward_pre_hook(profiler.pre_hook(name))
            module.register_forward_hook(profiler.post_hook(name, class_name, 'linear'))
        # Norm 层
        elif any(t in class_name for t in norm_types):
            module.register_forward_pre_hook(profiler.pre_hook(name))
            module.register_forward_hook(profiler.post_hook(name, class_name, 'norm'))
        # 激活函数层
        elif any(t in class_name for t in activation_types):
            module.register_forward_pre_hook(profiler.pre_hook(name))
            module.register_forward_hook(profiler.post_hook(name, class_name, 'activation'))
        # Embedding 层
        elif any(t in class_name for t in embedding_types):
            module.register_forward_pre_hook(profiler.pre_hook(name))
            module.register_forward_hook(profiler.post_hook(name, class_name, 'embedding'))
        # Rotary Embedding
        elif any(t in class_name for t in rotary_types):
            module.register_forward_pre_hook(profiler.pre_hook(name))
            module.register_forward_hook(profiler.post_hook(name, class_name, 'rotary'))

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
    max_layer = df[df['Layer Num'] >= 0]['Layer Num'].max()
    mid_layer = max_layer // 2
    df_mid_layer = df[df['Layer Num'] == mid_layer].copy()
    
    # 【关键步骤】剔除 Layer 0 (预热数据) 和非层内数据 (Layer Num == -1 表示非 decoder layer 内)
    df_stable = df[(df['Layer Num'] > 0) & (df['Layer Num'] <= max_layer)].copy()
    
    # 分离 Linear 和 Non-Linear 层数据
    df_linear = df_stable[df_stable['Category'] == 'linear'].copy()
    df_nonlinear = df_stable[df_stable['Category'].isin(['norm', 'activation'])].copy()
    
    # Linear 层统计 (按 Submodule 分组)
    linear_stats = df_linear.groupby('Submodule').agg({
        'Time (ms)': 'mean',
        'OPs': 'mean',
        'Mem Delta (MB)': 'mean'
    }).reset_index()
    linear_stats['Category'] = 'linear'
    linear_stats['Effective GOPS'] = (linear_stats['OPs'] / 1e9) / (linear_stats['Time (ms)'] / 1000)
    
    # Non-Linear 层统计 (按 Submodule 分组)
    nonlinear_stats = df_nonlinear.groupby('Submodule').agg({
        'Time (ms)': 'mean',
        'OPs': 'mean',
        'Mem Delta (MB)': 'mean'
    }).reset_index()
    nonlinear_stats['Category'] = 'nonlinear'
    nonlinear_stats['Effective GOPS'] = nonlinear_stats.apply(
        lambda row: (row['OPs'] / 1e9) / (row['Time (ms)'] / 1000) if row['Time (ms)'] > 0 else 0, axis=1
    )
    
    # 合并统计
    all_stats = pd.concat([linear_stats, nonlinear_stats], ignore_index=True)
    
    # 计算总时间和占比
    total_linear_time = linear_stats['Time (ms)'].sum()
    total_nonlinear_time = nonlinear_stats['Time (ms)'].sum() if len(nonlinear_stats) > 0 else 0
    total_time = total_linear_time + total_nonlinear_time
    total_ops = all_stats['OPs'].sum()
    
    # 为每个统计表添加占比列
    linear_stats['Time Ratio (%)'] = (linear_stats['Time (ms)'] / total_time) * 100
    linear_stats['OPs Ratio (%)'] = linear_stats.apply(
        lambda row: (row['OPs'] / total_ops) * 100 if total_ops > 0 else 0, axis=1
    )
    
    if len(nonlinear_stats) > 0:
        nonlinear_stats['Time Ratio (%)'] = (nonlinear_stats['Time (ms)'] / total_time) * 100
        nonlinear_stats['OPs Ratio (%)'] = nonlinear_stats.apply(
            lambda row: (row['OPs'] / total_ops) * 100 if total_ops > 0 else 0, axis=1
        )
    
    all_stats['Time Ratio (%)'] = (all_stats['Time (ms)'] / total_time) * 100
    all_stats['OPs Ratio (%)'] = all_stats.apply(
        lambda row: (row['OPs'] / total_ops) * 100 if total_ops > 0 else 0, axis=1
    )
    
    # 按时间排序
    all_stats = all_stats.sort_values(by='Time (ms)', ascending=False)
    
    # MLP 和 Attention 分组统计
    mlp_ops = ['gate_proj', 'up_proj', 'down_proj']
    attn_ops = ['q_proj', 'k_proj', 'v_proj', 'o_proj']
    norm_ops = ['input_layernorm', 'post_attention_layernorm', 'attn_sub_norm', 'ffn_sub_norm']
    activation_ops = ['act_fn']
    
    mlp_time = linear_stats[linear_stats['Submodule'].isin(mlp_ops)]['Time (ms)'].sum()
    attn_time = linear_stats[linear_stats['Submodule'].isin(attn_ops)]['Time (ms)'].sum()
    norm_time = nonlinear_stats[nonlinear_stats['Submodule'].isin(norm_ops)]['Time (ms)'].sum()
    activation_time = nonlinear_stats[nonlinear_stats['Submodule'].isin(activation_ops)]['Time (ms)'].sum()
    
    # Embedding 层数据（全局层，不在 decoder layer 内）
    df_embedding = df[df['Category'] == 'embedding'].copy()
    df_rotary = df[df['Category'] == 'rotary'].copy()
    
    embedding_time = df_embedding['Time (ms)'].sum() if len(df_embedding) > 0 else 0
    rotary_time = df_rotary['Time (ms)'].sum() if len(df_rotary) > 0 else 0
    
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
            'mlp_time_ratio': round(mlp_time / total_time * 100, 1) if total_time > 0 else 0,
            'attn_time_ms': round(attn_time, 2),
            'attn_time_ratio': round(attn_time / total_time * 100, 1) if total_time > 0 else 0,
            'norm_time_ms': round(norm_time, 2),
            'norm_time_ratio': round(norm_time / total_time * 100, 1) if total_time > 0 else 0,
            'activation_time_ms': round(activation_time, 2),
            'activation_time_ratio': round(activation_time / total_time * 100, 1) if total_time > 0 else 0,
            'linear_total_time_ms': round(total_linear_time, 2),
            'linear_total_ratio': round(total_linear_time / total_time * 100, 1) if total_time > 0 else 0,
            'nonlinear_total_time_ms': round(total_nonlinear_time, 2),
            'nonlinear_total_ratio': round(total_nonlinear_time / total_time * 100, 1) if total_time > 0 else 0,
        },
        'global_layers': {
            'embedding_time_ms': round(embedding_time, 2),
            'rotary_time_ms': round(rotary_time, 2),
        },
        'linear_operator_stats': linear_stats.to_dict(orient='records'),
        'nonlinear_operator_stats': nonlinear_stats.to_dict(orient='records'),
        'all_operator_stats': all_stats.to_dict(orient='records'),
        'layer0_data': df_layer0.to_dict(orient='records'),
        'mid_layer_data': df_mid_layer.to_dict(orient='records'),
        'embedding_data': df_embedding.to_dict(orient='records'),
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
    
    print("\n【Linear 层统计】")
    cols = ['Submodule', 'Time (ms)', 'Time Ratio (%)', 'OPs', 'OPs Ratio (%)', 'Effective GOPS', 'Mem Delta (MB)']
    print(linear_stats.sort_values(by='Time (ms)', ascending=False)[cols].to_string(index=False))
    
    print("\n【Non-Linear 层统计】")
    print(nonlinear_stats.sort_values(by='Time (ms)', ascending=False)[cols].to_string(index=False))
    
    print("\n" + "-" * 80)
    print(f"Total Time per Layer: {total_time:.4f} ms")
    print(f"Total OPs per Layer:  {total_ops:,.0f}")
    print("-" * 80)
    print(f"【模块分布】")
    print(f"  MLP Block (Linear):      {mlp_time:.4f} ms ({mlp_time/total_time*100:.2f}%)")
    print(f"  Attention Block (Linear): {attn_time:.4f} ms ({attn_time/total_time*100:.2f}%)")
    print(f"  Normalization (Non-Lin): {norm_time:.4f} ms ({norm_time/total_time*100:.2f}%)")
    print(f"  Activation (Non-Lin):    {activation_time:.4f} ms ({activation_time/total_time*100:.2f}%)")
    print("-" * 80)
    print(f"  Linear 层总计:     {total_linear_time:.4f} ms ({total_linear_time/total_time*100:.2f}%)")
    print(f"  Non-Linear 层总计: {total_nonlinear_time:.4f} ms ({total_nonlinear_time/total_time*100:.2f}%)")
    print("="*80)
    
    if embedding_time > 0 or rotary_time > 0:
        print(f"\n【全局层耗时】(不在 Decoder Layer 内)")
        print(f"  Embedding:        {embedding_time:.4f} ms")
        print(f"  Rotary Embedding: {rotary_time:.4f} ms")
    
    # 保存统计数据
    all_stats.to_csv(OUTPUT_DIR / "final_operator_benchmark.csv", index=False)
    linear_stats.to_csv(OUTPUT_DIR / "linear_operator_stats.csv", index=False)
    nonlinear_stats.to_csv(OUTPUT_DIR / "nonlinear_operator_stats.csv", index=False)
    
    print(f"\n✅ 报告数据已保存至 '{OUTPUT_DIR}':")
    print(f"   - inference_profile_report.json (完整报告数据)")
    print(f"   - raw_layer_data.csv (原始层数据)")
    print(f"   - final_operator_benchmark.csv (全部算子统计)")
    print(f"   - linear_operator_stats.csv (Linear 层统计)")
    print(f"   - nonlinear_operator_stats.csv (Non-Linear 层统计)")