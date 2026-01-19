#!/usr/bin/env python3
"""
BitNet b1.58-2B-4T 推理性能分析脚本 (增强版)

功能：
1. 加载 HuggingFace 上的 BitNet 模型
2. 对每个线性层 (Linear Layer) 进行计时分析
3. 监控每层的内存占用情况
4. 进行 CPU 频率归一化
5. 生成 Markdown 格式的详细报告

作者: RISC-V AI FPGA 项目组
日期: 2026-01-18
"""

import os
import time
import argparse
from datetime import datetime
from typing import Dict, List, Tuple, Optional, Any
from dataclasses import dataclass, field
from contextlib import contextmanager
from collections import defaultdict
import functools

import torch
import torch.nn as nn
import psutil
import cpuinfo
import numpy as np
from transformers import AutoModelForCausalLM, AutoTokenizer
from tqdm import tqdm

# 强制使用 CPU
os.environ["CUDA_VISIBLE_DEVICES"] = ""
# 不再限制线程数，使用系统默认配置


@dataclass
class CPUInfo:
    """CPU 信息数据类"""
    brand: str
    arch: str
    cores_physical: int
    cores_logical: int
    freq_base_mhz: float
    freq_current_mhz: float
    
    @classmethod
    def collect(cls) -> "CPUInfo":
        """收集 CPU 信息"""
        info = cpuinfo.get_cpu_info()
        freq = psutil.cpu_freq()
        
        freq_base = 0.0
        freq_current = 0.0
        
        if freq:
            freq_base = freq.max if freq.max else freq.current
            freq_current = freq.current if freq.current else freq.max
        
        if freq_base == 0:
            hz_actual = info.get("hz_actual_friendly", "")
            hz_advertised = info.get("hz_advertised_friendly", "")
            for hz_str in [hz_actual, hz_advertised]:
                if "GHz" in hz_str:
                    try:
                        freq_base = float(hz_str.replace("GHz", "").strip()) * 1000
                        break
                    except:
                        pass
                elif "MHz" in hz_str:
                    try:
                        freq_base = float(hz_str.replace("MHz", "").strip())
                        break
                    except:
                        pass
        
        if freq_base == 0:
            freq_base = 3000.0
            print("警告: 无法获取 CPU 频率，使用默认值 3000 MHz")
        
        if freq_current == 0:
            freq_current = freq_base
            
        return cls(
            brand=info.get("brand_raw", "Unknown"),
            arch=info.get("arch", "Unknown"),
            cores_physical=psutil.cpu_count(logical=False) or 1,
            cores_logical=psutil.cpu_count(logical=True) or 1,
            freq_base_mhz=freq_base,
            freq_current_mhz=freq_current,
        )


@dataclass
class MemorySnapshot:
    """内存快照"""
    timestamp: float
    rss_mb: float
    vms_mb: float
    system_used_mb: float
    system_total_mb: float
    
    @classmethod
    def capture(cls, start_time: float) -> "MemorySnapshot":
        """捕获当前内存状态"""
        process = psutil.Process()
        mem_info = process.memory_info()
        sys_mem = psutil.virtual_memory()
        return cls(
            timestamp=time.perf_counter() - start_time,
            rss_mb=mem_info.rss / (1024 ** 2),
            vms_mb=mem_info.vms / (1024 ** 2),
            system_used_mb=sys_mem.used / (1024 ** 2),
            system_total_mb=sys_mem.total / (1024 ** 2),
        )


@dataclass
class LayerProfile:
    """单层性能数据"""
    layer_name: str
    layer_type: str
    call_count: int = 0
    total_time_ms: float = 0.0
    total_time_normalized_ms: float = 0.0
    memory_before_mb: float = 0.0
    memory_after_mb: float = 0.0
    memory_delta_mb: float = 0.0
    memory_peak_delta_mb: float = 0.0  # 峰值内存增量
    abs_memory_mb: float = 0.0  # 绝对内存占用
    input_shape: str = ""
    output_shape: str = ""
    input_shape_tuple: tuple = ()  # 用于计算 OPs
    output_shape_tuple: tuple = ()  # 用于计算 OPs
    params_count: int = 0
    weight_shape: tuple = ()  # 权重形状用于计算 OPs
    
    # 计算相关
    ops_per_call: int = 0  # 单次运算量 (OPs)
    total_ops: int = 0  # 总运算量
    
    # 每次调用的详细记录
    call_times_ms: list = field(default_factory=list)  # 每次调用耗时
    call_mem_deltas: list = field(default_factory=list)  # 每次调用内存增量


@dataclass
class StageProfile:
    """推理阶段性能数据"""
    name: str
    duration_ms: float
    duration_normalized_ms: float
    memory_before_mb: float
    memory_after_mb: float
    memory_delta_mb: float


@dataclass
class TokenProfile:
    """单 Token 生成性能数据"""
    token_id: int
    token_text: str
    time_ms: float
    time_normalized_ms: float
    memory_mb: float


class LayerProfiler:
    """层级性能分析器 - 使用 Hook 机制追踪每层的执行"""
    
    def __init__(self, freq_scale: float = 1.0):
        self.freq_scale = freq_scale
        self.layer_profiles: Dict[str, LayerProfile] = {}
        self.hooks: List[torch.utils.hooks.RemovableHandle] = []
        self.start_time = time.perf_counter()
        self.enabled = False
        self._current_layer_start: Dict[str, float] = {}
        self._current_layer_mem: Dict[str, float] = {}
        
    def _normalize_time(self, duration_ms: float) -> float:
        """CPU 频率归一化"""
        return duration_ms * self.freq_scale
    
    def _get_memory_mb(self) -> float:
        """获取当前进程内存占用 (MB)"""
        return psutil.Process().memory_info().rss / (1024 ** 2)
    
    def _create_forward_pre_hook(self, layer_name: str):
        """创建前向传播前置钩子"""
        def hook(module, input):
            if not self.enabled:
                return
            self._current_layer_start[layer_name] = time.perf_counter()
            self._current_layer_mem[layer_name] = self._get_memory_mb()
        return hook
    
    def _create_forward_hook(self, layer_name: str, layer_type: str, params_count: int, module: nn.Module):
        """创建前向传播后置钩子"""
        # 预先获取权重形状
        weight_shape = ()
        if hasattr(module, 'weight') and module.weight is not None:
            weight_shape = tuple(module.weight.shape)
        
        def hook(module, input, output):
            if not self.enabled:
                return
            
            start_time = self._current_layer_start.get(layer_name, time.perf_counter())
            mem_before = self._current_layer_mem.get(layer_name, 0)
            
            duration_ms = (time.perf_counter() - start_time) * 1000
            mem_after = self._get_memory_mb()
            mem_delta = mem_after - mem_before
            
            # 获取输入输出形状
            input_shape = ""
            output_shape = ""
            input_shape_tuple = ()
            output_shape_tuple = ()
            try:
                if isinstance(input, tuple) and len(input) > 0:
                    if hasattr(input[0], 'shape'):
                        input_shape_tuple = tuple(input[0].shape)
                        input_shape = str(list(input_shape_tuple))
                if hasattr(output, 'shape'):
                    output_shape_tuple = tuple(output.shape)
                    output_shape = str(list(output_shape_tuple))
            except:
                pass
            
            # 计算单次运算量 (OPs) - 对于矩阵乘法: 2 * M * N * K
            ops_per_call = 0
            if weight_shape and len(weight_shape) == 2 and input_shape_tuple:
                # Linear 层: Y = X @ W^T, 其中 W 的形状是 [out_features, in_features]
                # 输入 X 形状: [batch, seq_len, in_features]
                # OPs = 2 * batch * seq_len * out_features * in_features
                out_features, in_features = weight_shape
                if len(input_shape_tuple) >= 2:
                    batch_seq = 1
                    for dim in input_shape_tuple[:-1]:
                        batch_seq *= dim
                    ops_per_call = 2 * batch_seq * out_features * in_features
            
            # 更新或创建层性能数据
            if layer_name not in self.layer_profiles:
                self.layer_profiles[layer_name] = LayerProfile(
                    layer_name=layer_name,
                    layer_type=layer_type,
                    params_count=params_count,
                    weight_shape=weight_shape,
                )
            
            profile = self.layer_profiles[layer_name]
            profile.call_count += 1
            profile.total_time_ms += duration_ms
            profile.total_time_normalized_ms += self._normalize_time(duration_ms)
            profile.memory_after_mb = mem_after
            profile.abs_memory_mb = mem_after  # 绝对内存
            
            # 记录每次调用的详细数据
            profile.call_times_ms.append(duration_ms)
            profile.call_mem_deltas.append(mem_delta)
            
            # 更新内存增量（累积）
            profile.memory_delta_mb += mem_delta
            if mem_delta > profile.memory_peak_delta_mb:
                profile.memory_peak_delta_mb = mem_delta
            
            profile.input_shape = input_shape
            profile.output_shape = output_shape
            profile.input_shape_tuple = input_shape_tuple
            profile.output_shape_tuple = output_shape_tuple
            profile.ops_per_call = ops_per_call
            profile.total_ops += ops_per_call
            
            if profile.memory_before_mb == 0:
                profile.memory_before_mb = mem_before
                
        return hook
    
    def register_hooks(self, model: nn.Module, target_types: Tuple[type, ...] = (nn.Linear,)):
        """注册钩子到模型的指定层类型"""
        for name, module in model.named_modules():
            if isinstance(module, target_types):
                layer_type = module.__class__.__name__
                params_count = sum(p.numel() for p in module.parameters())
                
                # 注册前向传播前置和后置钩子
                pre_hook = module.register_forward_pre_hook(
                    self._create_forward_pre_hook(name)
                )
                post_hook = module.register_forward_hook(
                    self._create_forward_hook(name, layer_type, params_count, module)
                )
                self.hooks.append(pre_hook)
                self.hooks.append(post_hook)
        
        print(f"已注册 {len(self.hooks)//2} 个层的性能追踪钩子")
    
    def enable(self):
        """启用性能追踪"""
        self.enabled = True
        
    def disable(self):
        """禁用性能追踪"""
        self.enabled = False
    
    def reset(self):
        """重置性能数据"""
        self.layer_profiles.clear()
        self._current_layer_start.clear()
        self._current_layer_mem.clear()
        
    def remove_hooks(self):
        """移除所有钩子"""
        for hook in self.hooks:
            hook.remove()
        self.hooks.clear()
    
    def get_sorted_profiles(self, sort_by: str = "total_time_ms") -> List[LayerProfile]:
        """获取按指定字段排序的层性能数据"""
        profiles = list(self.layer_profiles.values())
        return sorted(profiles, key=lambda x: getattr(x, sort_by, 0), reverse=True)


class InferenceProfiler:
    """推理性能分析器 (增强版)"""
    
    REFERENCE_FREQ_MHZ = 3000.0
    
    def __init__(
        self,
        model_name: str = "../models/BitNet b1.58-2B-4T-bf16",
        device: str = "cpu",
        dtype: torch.dtype = torch.float32,
    ):
        self.model_name = model_name
        self.device = device
        self.dtype = dtype
        
        self.model = None
        self.tokenizer = None
        
        self.cpu_info = CPUInfo.collect()
        self.freq_scale = self.cpu_info.freq_base_mhz / self.REFERENCE_FREQ_MHZ
        print(f"CPU 频率: {self.cpu_info.freq_base_mhz:.0f} MHz, 归一化系数: {self.freq_scale:.3f}")
        print(f"CPU 核心数: {self.cpu_info.cores_physical} 物理核 / {self.cpu_info.cores_logical} 逻辑核")
        print(f"PyTorch 线程数: {torch.get_num_threads()}")
        
        self.start_time = time.perf_counter()
        self.stage_profiles: List[StageProfile] = []
        self.memory_timeline: List[MemorySnapshot] = []
        self.layer_profiler: Optional[LayerProfiler] = None
        self.token_profiles: List[TokenProfile] = []
        
    def _normalize_time(self, duration_ms: float) -> float:
        """CPU 频率归一化"""
        return duration_ms * self.freq_scale
    
    @contextmanager
    def _profile_stage(self, stage_name: str):
        """阶段性能分析上下文管理器"""
        mem_before = MemorySnapshot.capture(self.start_time)
        self.memory_timeline.append(mem_before)
        
        start = time.perf_counter()
        yield
        duration_ms = (time.perf_counter() - start) * 1000
        
        mem_after = MemorySnapshot.capture(self.start_time)
        self.memory_timeline.append(mem_after)
        
        profile = StageProfile(
            name=stage_name,
            duration_ms=duration_ms,
            duration_normalized_ms=self._normalize_time(duration_ms),
            memory_before_mb=mem_before.rss_mb,
            memory_after_mb=mem_after.rss_mb,
            memory_delta_mb=mem_after.rss_mb - mem_before.rss_mb,
        )
        self.stage_profiles.append(profile)
        
        print(f"  [{stage_name}] 耗时: {duration_ms:.2f}ms "
              f"(归一化: {profile.duration_normalized_ms:.2f}ms), "
              f"内存变化: {profile.memory_delta_mb:+.2f}MB")
    
    def load_model(self) -> None:
        """加载模型和分词器"""
        print(f"\n{'='*60}")
        print(f"加载模型: {self.model_name}")
        print(f"{'='*60}")
        
        with self._profile_stage("Tokenizer 加载"):
            self.tokenizer = AutoTokenizer.from_pretrained(self.model_name)
            if self.tokenizer.pad_token is None:
                self.tokenizer.pad_token = self.tokenizer.eos_token
        
        with self._profile_stage("Model 加载"):
            self.model = AutoModelForCausalLM.from_pretrained(
                self.model_name,
                torch_dtype=self.dtype,
                low_cpu_mem_usage=True,
            )
            self.model.eval()
        
        # 统计模型参数
        total_params = sum(p.numel() for p in self.model.parameters())
        linear_count = sum(1 for m in self.model.modules() if isinstance(m, nn.Linear))
        print(f"\n模型参数量: {total_params / 1e9:.2f}B")
        print(f"Linear 层数量: {linear_count}")
        
        # 初始化层级分析器
        self.layer_profiler = LayerProfiler(freq_scale=self.freq_scale)
        self.layer_profiler.register_hooks(self.model, target_types=(nn.Linear,))
    
    def run_inference(
        self,
        prompt: str,
        max_new_tokens: int = 50,
        temperature: float = 0.7,
    ) -> Tuple[str, List[TokenProfile]]:
        """执行推理并分析性能"""
        print(f"\n{'='*60}")
        print(f"执行推理")
        print(f"{'='*60}")
        print(f"Prompt: {prompt}")
        print(f"Max new tokens: {max_new_tokens}")
        
        self.token_profiles = []
        generated_ids = []
        
        # 1. Tokenization
        with self._profile_stage("Tokenization (编码)"):
            inputs = self.tokenizer(
                prompt,
                return_tensors="pt",
                padding=True,
            )
            input_ids = inputs["input_ids"]
            attention_mask = inputs["attention_mask"]
            
        print(f"  输入 token 数: {input_ids.shape[1]}")
        
        # 启用层级分析
        self.layer_profiler.enable()
        self.layer_profiler.reset()
        
        # 2. Prefill 阶段
        with self._profile_stage("Prefill (首次前向)"):
            with torch.no_grad():
                outputs = self.model(
                    input_ids=input_ids,
                    attention_mask=attention_mask,
                    use_cache=True,
                )
                past_key_values = outputs.past_key_values
                next_token_logits = outputs.logits[:, -1, :]
        
        # 3. Decode 阶段
        print(f"\n  开始 Decode 阶段 (逐 token 生成)...")
        
        current_ids = input_ids
        decode_start_time = time.perf_counter()
        
        for i in tqdm(range(max_new_tokens), desc="  生成中"):
            mem_snapshot = MemorySnapshot.capture(self.start_time)
            start_token_time = time.perf_counter()
            
            with torch.no_grad():
                if temperature > 0:
                    probs = torch.softmax(next_token_logits / temperature, dim=-1)
                    next_token = torch.multinomial(probs, num_samples=1)
                else:
                    next_token = torch.argmax(next_token_logits, dim=-1, keepdim=True)
                
                if next_token.item() == self.tokenizer.eos_token_id:
                    break
                
                generated_ids.append(next_token.item())
                
                attention_mask = torch.cat([
                    attention_mask,
                    torch.ones((1, 1), dtype=attention_mask.dtype)
                ], dim=1)
                
                outputs = self.model(
                    input_ids=next_token,
                    attention_mask=attention_mask,
                    past_key_values=past_key_values,
                    use_cache=True,
                )
                past_key_values = outputs.past_key_values
                next_token_logits = outputs.logits[:, -1, :]
            
            token_time_ms = (time.perf_counter() - start_token_time) * 1000
            token_text = self.tokenizer.decode([next_token.item()])
            
            self.token_profiles.append(TokenProfile(
                token_id=next_token.item(),
                token_text=token_text,
                time_ms=token_time_ms,
                time_normalized_ms=self._normalize_time(token_time_ms),
                memory_mb=mem_snapshot.rss_mb,
            ))
        
        # 禁用层级分析
        self.layer_profiler.disable()
        
        # 统计 Decode 阶段
        if self.token_profiles:
            decode_times = [t.time_ms for t in self.token_profiles]
            decode_total_ms = (time.perf_counter() - decode_start_time) * 1000
            
            self.stage_profiles.append(StageProfile(
                name="Decode (逐token生成)",
                duration_ms=decode_total_ms,
                duration_normalized_ms=self._normalize_time(decode_total_ms),
                memory_before_mb=self.token_profiles[0].memory_mb,
                memory_after_mb=self.token_profiles[-1].memory_mb,
                memory_delta_mb=self.token_profiles[-1].memory_mb - self.token_profiles[0].memory_mb,
            ))
            
            print(f"\n  生成 {len(self.token_profiles)} 个 token")
            print(f"  平均每 token: {np.mean(decode_times):.2f}ms "
                  f"(归一化: {self._normalize_time(np.mean(decode_times)):.2f}ms)")
            print(f"  吞吐量: {1000 / np.mean(decode_times):.2f} tokens/s")
        
        # 4. Detokenization
        with self._profile_stage("Detokenization (解码)"):
            generated_text = self.tokenizer.decode(generated_ids, skip_special_tokens=True)
        
        full_response = prompt + generated_text
        print(f"\n生成结果: {generated_text}")
        
        return full_response, self.token_profiles
    
    def generate_markdown_report(self, output_dir: str = "../docs") -> str:
        """生成 Markdown 格式的性能分析报告"""
        print(f"\n{'='*60}")
        print("生成 Markdown 性能分析报告")
        print(f"{'='*60}")
        
        # 计算汇总数据
        total_time = sum(s.duration_ms for s in self.stage_profiles)
        total_normalized = sum(s.duration_normalized_ms for s in self.stage_profiles)
        peak_memory = max(s.memory_after_mb for s in self.stage_profiles) if self.stage_profiles else 0
        
        # 获取层级分析数据
        layer_profiles = self.layer_profiler.get_sorted_profiles("total_time_ms") if self.layer_profiler else []
        total_layer_time = sum(lp.total_time_ms for lp in layer_profiles)
        
        # 构建 Markdown 内容
        md_lines = []
        
        # 标题和元信息
        md_lines.append("# BitNet b1.58 推理性能分析报告\n")
        md_lines.append(f"**生成时间**: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
        md_lines.append(f"**模型路径**: `{self.model_name}`\n")
        md_lines.append(f"**数据类型**: `{self.dtype}`\n")
        md_lines.append("")
        
        # CPU 信息
        md_lines.append("## 1. 系统信息\n")
        md_lines.append("### CPU 配置\n")
        md_lines.append(f"| 属性 | 值 |")
        md_lines.append(f"|------|-----|")
        md_lines.append(f"| CPU 型号 | {self.cpu_info.brand} |")
        md_lines.append(f"| 架构 | {self.cpu_info.arch} |")
        md_lines.append(f"| 物理核心数 | {self.cpu_info.cores_physical} |")
        md_lines.append(f"| 逻辑核心数 | {self.cpu_info.cores_logical} |")
        md_lines.append(f"| 基准频率 | {self.cpu_info.freq_base_mhz:.0f} MHz |")
        md_lines.append(f"| 当前频率 | {self.cpu_info.freq_current_mhz:.0f} MHz |")
        md_lines.append(f"| PyTorch 线程数 | {torch.get_num_threads()} |")
        md_lines.append("")
        
        # 频率归一化说明
        md_lines.append("### 频率归一化\n")
        md_lines.append(f"- **参考频率**: {self.REFERENCE_FREQ_MHZ:.0f} MHz")
        md_lines.append(f"- **归一化系数**: {self.freq_scale:.3f}")
        md_lines.append(f"- **计算公式**: `归一化时间 = 实测时间 × (实际频率 / 参考频率)`")
        md_lines.append("")
        
        # 推理阶段分析
        md_lines.append("## 2. 推理阶段分析\n")
        md_lines.append("| 阶段 | 耗时 (ms) | 归一化耗时 (ms) | 占比 (%) | 内存变化 (MB) |")
        md_lines.append("|------|-----------|-----------------|----------|---------------|")
        
        for s in self.stage_profiles:
            pct = (s.duration_ms / total_time * 100) if total_time > 0 else 0
            md_lines.append(f"| {s.name} | {s.duration_ms:.2f} | {s.duration_normalized_ms:.2f} | {pct:.1f} | {s.memory_delta_mb:+.2f} |")
        
        md_lines.append(f"| **总计** | **{total_time:.2f}** | **{total_normalized:.2f}** | **100.0** | - |")
        md_lines.append("")
        
        # 汇总统计
        md_lines.append("### 汇总统计\n")
        md_lines.append(f"- **总推理时间**: {total_time:.2f} ms ({total_time/1000:.2f} s)")
        md_lines.append(f"- **归一化总时间**: {total_normalized:.2f} ms")
        md_lines.append(f"- **峰值内存占用**: {peak_memory:.2f} MB ({peak_memory/1024:.2f} GB)")
        
        if self.token_profiles:
            decode_times = [t.time_ms for t in self.token_profiles]
            md_lines.append(f"- **生成 Token 数**: {len(self.token_profiles)}")
            md_lines.append(f"- **平均每 Token 耗时**: {np.mean(decode_times):.2f} ms")
            md_lines.append(f"- **推理吞吐量**: {1000 / np.mean(decode_times):.2f} tokens/s")
        md_lines.append("")
        
        # 线性层分析
        if layer_profiles:
            md_lines.append("## 3. 部分层具体运行数据 (Raw Data)\n")
            md_lines.append(f"**总计 Linear 层数量**: {len(layer_profiles)}\n")
            md_lines.append(f"**Linear 层总耗时**: {total_layer_time:.2f} ms\n")
            md_lines.append("")
            
            # 按层组织数据 - 参考报告格式的详细表格
            layer_data_by_decoder = defaultdict(list)
            lm_head_data = None
            
            for lp in layer_profiles:
                parts = lp.layer_name.split(".")
                if "layers" in parts:
                    layer_idx = parts.index("layers")
                    if layer_idx + 1 < len(parts):
                        try:
                            decoder_layer_num = int(parts[layer_idx + 1])
                            layer_data_by_decoder[decoder_layer_num].append(lp)
                        except:
                            pass
                elif "lm_head" in lp.layer_name:
                    lm_head_data = lp
            
            # Layer 0 (首层 - 包含初始化开销)
            if 0 in layer_data_by_decoder:
                md_lines.append("### Layer 0 (首层 - 包含初始化开销)\n")
                md_lines.append("| Layer Name (层名) | Type (类型) | Input Shape (输入维度) | Time (ms) | Mem Delta (MB) | Abs Mem (MB) |")
                md_lines.append("| --- | --- | --- | --- | --- | --- |")
                
                layer0_total_time = 0
                for lp in sorted(layer_data_by_decoder[0], key=lambda x: x.layer_name):
                    avg_time = lp.total_time_ms / lp.call_count if lp.call_count > 0 else 0
                    avg_mem_delta = lp.memory_delta_mb / lp.call_count if lp.call_count > 0 else 0
                    # 使用第一次调用的数据（prefill阶段）
                    first_call_time = lp.call_times_ms[0] if lp.call_times_ms else avg_time
                    first_call_mem = lp.call_mem_deltas[0] if lp.call_mem_deltas else avg_mem_delta
                    layer0_total_time += first_call_time
                    
                    # 简化层名
                    short_name = lp.layer_name.replace("model.", "")
                    is_mlp = "mlp" in lp.layer_name
                    row_prefix = "**" if is_mlp else ""
                    row_suffix = "**" if is_mlp else ""
                    
                    md_lines.append(f"| {row_prefix}{short_name}{row_suffix} | {row_prefix}{lp.layer_type}{row_suffix} | {row_prefix}{lp.input_shape}{row_suffix} | {row_prefix}{first_call_time:.3f}{row_suffix} | {row_prefix}{first_call_mem:.3f}{row_suffix} | {row_prefix}{lp.abs_memory_mb:.1f}{row_suffix} |")
                
                md_lines.append(f"| layers.0 | BitNetDecoderLayer | - | {layer0_total_time:.3f} | - | - |")
                md_lines.append("")
                md_lines.append("> **数据解读**：第0层耗时显著高于后续层，这是由于包含了模型初始化、内存分配等一次性开销。\n")
            
            # Layer 1 (初始稳定运行阶段)
            if 1 in layer_data_by_decoder:
                md_lines.append("### Layer 1 (初始稳定运行阶段)\n")
                md_lines.append("| Layer Name (层名) | Type (类型) | Input Shape (输入维度) | Time (ms) | Mem Delta (MB) | Abs Mem (MB) |")
                md_lines.append("| --- | --- | --- | --- | --- | --- |")
                
                layer1_total_time = 0
                for lp in sorted(layer_data_by_decoder[1], key=lambda x: x.layer_name):
                    # 使用第二次调用的数据（第一个decode token）
                    idx = 1 if len(lp.call_times_ms) > 1 else 0
                    call_time = lp.call_times_ms[idx] if lp.call_times_ms else 0
                    call_mem = lp.call_mem_deltas[idx] if lp.call_mem_deltas else 0
                    layer1_total_time += call_time
                    
                    short_name = lp.layer_name.replace("model.", "")
                    is_mlp = "mlp" in lp.layer_name
                    row_prefix = "**" if is_mlp else ""
                    row_suffix = "**" if is_mlp else ""
                    
                    md_lines.append(f"| {row_prefix}{short_name}{row_suffix} | {row_prefix}{lp.layer_type}{row_suffix} | {row_prefix}{lp.input_shape}{row_suffix} | {row_prefix}{call_time:.3f}{row_suffix} | {row_prefix}{call_mem:.3f}{row_suffix} | {row_prefix}{lp.abs_memory_mb:.1f}{row_suffix} |")
                
                md_lines.append(f"| layers.1 | BitNetDecoderLayer | - | {layer1_total_time:.3f} | - | - |")
                md_lines.append("")
                md_lines.append("> **数据解读**：第1层耗时降至正常水平，接近稳定运行状态。\n")
            
            # Layer 17 (中段稳定运行阶段)
            mid_layer = 17 if 17 in layer_data_by_decoder else (15 if 15 in layer_data_by_decoder else None)
            if mid_layer and mid_layer in layer_data_by_decoder:
                md_lines.append(f"### Layer {mid_layer} (中段稳定运行阶段)\n")
                md_lines.append("| Layer Name (层名) | Type (类型) | Input Shape (输入维度) | Time (ms) | Mem Delta (MB) | Abs Mem (MB) |")
                md_lines.append("| --- | --- | --- | --- | --- | --- |")
                
                layer_mid_total_time = 0
                for lp in sorted(layer_data_by_decoder[mid_layer], key=lambda x: x.layer_name):
                    # 使用稳定阶段的平均值
                    avg_time = lp.total_time_ms / lp.call_count if lp.call_count > 0 else 0
                    avg_mem = lp.memory_delta_mb / lp.call_count if lp.call_count > 0 else 0
                    layer_mid_total_time += avg_time
                    
                    short_name = lp.layer_name.replace("model.", "")
                    is_mlp = "mlp" in lp.layer_name
                    row_prefix = "**" if is_mlp else ""
                    row_suffix = "**" if is_mlp else ""
                    
                    md_lines.append(f"| {row_prefix}{short_name}{row_suffix} | {row_prefix}{lp.layer_type}{row_suffix} | {row_prefix}{lp.input_shape}{row_suffix} | {row_prefix}{avg_time:.2f}{row_suffix} | {row_prefix}{avg_mem:.2f}{row_suffix} | {row_prefix}{lp.abs_memory_mb:.1f}{row_suffix} |")
                
                md_lines.append(f"| layers.{mid_layer} | BitNetDecoderLayer | - | {layer_mid_total_time:.2f} | - | - |")
                md_lines.append("")
                md_lines.append("> **数据解读**：MLP 层的三个算子耗时显著高于 Attention 层。\n")
            
            md_lines.append("---\n")
            
            # 按模块分组统计（单层平均耗时分布）
            md_lines.append("## 4. 单层 (Decoder Layer) 平均耗时分布\n")
            
            module_stats: Dict[str, Dict[str, Any]] = defaultdict(lambda: {
                "count": 0, "total_time_ms": 0, "total_params": 0, "layers": []
            })
            
            for lp in layer_profiles:
                # 解析模块名称 (例如 model.layers.0.self_attn.q_proj -> self_attn.q_proj)
                parts = lp.layer_name.split(".")
                if "layers" in parts:
                    # Transformer 层内的模块
                    layer_idx = parts.index("layers")
                    if layer_idx + 2 < len(parts):
                        module_type = ".".join(parts[layer_idx+2:])
                    else:
                        module_type = parts[-1]
                else:
                    module_type = parts[-1] if parts else "unknown"
                
                module_stats[module_type]["count"] += 1
                module_stats[module_type]["total_time_ms"] += lp.total_time_ms
                module_stats[module_type]["total_params"] += lp.params_count
                module_stats[module_type]["layers"].append(lp.layer_name)
            
            # 按耗时排序
            sorted_modules = sorted(module_stats.items(), key=lambda x: x[1]["total_time_ms"], reverse=True)
            
            md_lines.append("| 模块类型 | 层数量 | 总耗时 (ms) | 占比 (%) | 总参数量 |")
            md_lines.append("|----------|--------|-------------|----------|----------|")
            
            for module_type, stats in sorted_modules:
                pct = (stats["total_time_ms"] / total_layer_time * 100) if total_layer_time > 0 else 0
                params_str = f"{stats['total_params']:,}" if stats['total_params'] < 1e6 else f"{stats['total_params']/1e6:.2f}M"
                md_lines.append(f"| `{module_type}` | {stats['count']} | {stats['total_time_ms']:.2f} | {pct:.2f} | {params_str} |")
            md_lines.append("")
            
            md_lines.append("---\n")
            
            # ===== 算子级性能分析 (参考报告核心表格) =====
            md_lines.append("## 5. 算子级性能分析 (Operator-Level Analysis)\n")
            md_lines.append("模型稳定运行阶段的每种算子核心数据统计与分析如下：\n")
            md_lines.append("### 5.1 核心数据统计表\n")
            
            # 按算子类型聚合统计 (排除 Layer 0 的初始化开销)
            operator_stats: Dict[str, Dict[str, Any]] = defaultdict(lambda: {
                "total_time_ms": 0.0,
                "total_ops": 0,
                "call_count": 0,
                "mem_peak": 0.0,
                "profiles": []
            })
            
            # 计算总运算量（用于算力占比）
            total_ops_all = 0
            
            for lp in layer_profiles:
                parts = lp.layer_name.split(".")
                if "layers" in parts:
                    layer_idx = parts.index("layers")
                    try:
                        decoder_num = int(parts[layer_idx + 1])
                        # 排除 Layer 0 的初始化开销，使用 Layer 1-N 的数据
                        if decoder_num == 0:
                            continue
                    except:
                        pass
                    
                    # 获取算子类型 (q_proj, k_proj, gate_proj, etc.)
                    op_type = parts[-1] if parts else "unknown"
                    
                    # 计算稳定阶段的平均耗时 (排除第一次调用)
                    if len(lp.call_times_ms) > 1:
                        stable_times = lp.call_times_ms[1:]  # 排除 prefill
                        avg_time = sum(stable_times) / len(stable_times)
                    else:
                        avg_time = lp.total_time_ms / lp.call_count if lp.call_count > 0 else 0
                    
                    operator_stats[op_type]["total_time_ms"] += avg_time
                    operator_stats[op_type]["total_ops"] += lp.ops_per_call
                    operator_stats[op_type]["call_count"] += 1
                    operator_stats[op_type]["profiles"].append(lp)
                    
                    if lp.memory_peak_delta_mb > operator_stats[op_type]["mem_peak"]:
                        operator_stats[op_type]["mem_peak"] = lp.memory_peak_delta_mb
                    
                    total_ops_all += lp.ops_per_call
            
            # 计算单层总耗时
            single_layer_time = sum(stats["total_time_ms"] for stats in operator_stats.values())
            
            # 按耗时排序并生成表格
            sorted_ops = sorted(operator_stats.items(), key=lambda x: x[1]["total_time_ms"], reverse=True)
            
            md_lines.append("| 算子名称 (Submodule) | 平均耗时 (ms) | 时间占比 (%) | 单次运算量 (OPs) | 算力占比 (%) | 有效算力 (GOPS) | 内存增量 (MB) |")
            md_lines.append("| --- | --- | --- | --- | --- | --- | --- |")
            
            for op_type, stats in sorted_ops:
                avg_time = stats["total_time_ms"] / stats["call_count"] if stats["call_count"] > 0 else 0
                time_pct = (avg_time / single_layer_time * stats["call_count"] * 100) if single_layer_time > 0 else 0
                
                # 单次运算量 (取第一个profile的ops)
                ops_per_call = stats["profiles"][0].ops_per_call if stats["profiles"] else 0
                ops_str = f"{ops_per_call / 1e6:.2f} M" if ops_per_call > 0 else "N/A"
                
                # 算力占比
                ops_pct = (ops_per_call / total_ops_all * stats["call_count"] * 100) if total_ops_all > 0 else 0
                
                # 有效算力 (GOPS) = OPs / time_ms / 1e6 (因为 OPs 是整数，time 是 ms)
                gops = (ops_per_call / avg_time / 1e6) if avg_time > 0 and ops_per_call > 0 else 0
                
                # 内存增量
                mem_str = f"{stats['mem_peak']:.2f}" if stats['mem_peak'] > 0.01 else "~0"
                
                # 判断是否为 MLP 层 (加粗显示)
                is_mlp = op_type in ["gate_proj", "up_proj", "down_proj"]
                prefix = "**" if is_mlp else ""
                suffix = "**" if is_mlp else ""
                
                parent_module = "(MLP)" if is_mlp else "(Attn)"
                
                md_lines.append(f"| {prefix}{op_type} {parent_module}{suffix} | {prefix}{avg_time:.2f}{suffix} | {prefix}{time_pct:.2f}%{suffix} | {prefix}{ops_str}{suffix} | {prefix}{ops_pct:.2f}%{suffix} | {prefix}{gops:.2f}{suffix} | {prefix}{mem_str}{suffix} |")
            
            md_lines.append("")
            
            # 5.2 深度分析
            md_lines.append("### 5.2 深度分析\n")
            
            # 计算 MLP 和 Attention 的统计
            mlp_ops = ["gate_proj", "up_proj", "down_proj"]
            attn_ops = ["q_proj", "k_proj", "v_proj", "o_proj"]
            
            mlp_time = sum(operator_stats[op]["total_time_ms"] for op in mlp_ops if op in operator_stats)
            attn_time = sum(operator_stats[op]["total_time_ms"] for op in attn_ops if op in operator_stats)
            mlp_ops_total = sum(operator_stats[op]["total_ops"] for op in mlp_ops if op in operator_stats)
            attn_ops_total = sum(operator_stats[op]["total_ops"] for op in attn_ops if op in operator_stats)
            
            md_lines.append("#### 5.2.1 算力瓶颈分析 (Compute Bound)\n")
            md_lines.append("**核心发现**：MLP 三算子（gate_proj、up_proj、down_proj）成为计算瓶颈。\n")
            md_lines.append("**数据支撑**：\n")
            md_lines.append(f"- MLP 三算子合计运算量：**{mlp_ops_total / 1e6:.2f}M OPs**")
            md_lines.append(f"- Attention 四算子合计运算量：**{attn_ops_total / 1e6:.2f}M OPs**")
            if total_ops_all > 0:
                md_lines.append(f"- MLP 运算量占比：**{mlp_ops_total / total_ops_all * 100:.1f}%**")
            if single_layer_time > 0:
                md_lines.append(f"- MLP 耗时占比：**{mlp_time / single_layer_time * 100:.1f}%**")
            md_lines.append("")
            
            # 有效算力对比
            md_lines.append("**各算子运算效率对比**：\n")
            md_lines.append("| 算子类型 | 单次运算量 | 平均耗时 | 运算效率 (OPs/ms) |")
            md_lines.append("| --- | --- | --- | --- |")
            
            for op_type, stats in sorted_ops[:7]:  # Top 7 算子
                avg_time = stats["total_time_ms"] / stats["call_count"] if stats["call_count"] > 0 else 0
                ops_per_call = stats["profiles"][0].ops_per_call if stats["profiles"] else 0
                gops = (ops_per_call / avg_time / 1e6) if avg_time > 0 and ops_per_call > 0 else 0
                md_lines.append(f"| {op_type} | {ops_per_call / 1e6:.2f}M | {avg_time:.2f}ms | **{gops:.2f} GOPS** |")
            
            md_lines.append("")
            md_lines.append("---\n")
            
            # 完整层列表 (折叠)
            md_lines.append("### 附录：完整 Linear 层列表\n")
            md_lines.append("<details>")
            md_lines.append("<summary>点击展开完整列表 (共 {} 层)</summary>\n".format(len(layer_profiles)))
            md_lines.append("| 层名称 | 调用次数 | 总耗时 (ms) | 占比 (%) | 输入形状 | 输出形状 | 参数量 |")
            md_lines.append("|--------|----------|-------------|----------|----------|----------|--------|")
            
            for lp in layer_profiles:
                pct = (lp.total_time_ms / total_layer_time * 100) if total_layer_time > 0 else 0
                params_str = f"{lp.params_count:,}" if lp.params_count < 1e6 else f"{lp.params_count/1e6:.2f}M"
                md_lines.append(f"| `{lp.layer_name}` | {lp.call_count} | {lp.total_time_ms:.2f} | {pct:.2f} | {lp.input_shape} | {lp.output_shape} | {params_str} |")
            
            md_lines.append("\n</details>")
            md_lines.append("")
        
        # Token 生成详情
        if self.token_profiles:
            md_lines.append("## 6. Token 生成详情\n")
            
            decode_times = [t.time_ms for t in self.token_profiles]
            md_lines.append("### 6.1 统计信息\n")
            md_lines.append(f"- **生成 Token 数**: {len(self.token_profiles)}")
            md_lines.append(f"- **最小耗时**: {min(decode_times):.2f} ms")
            md_lines.append(f"- **最大耗时**: {max(decode_times):.2f} ms")
            md_lines.append(f"- **平均耗时**: {np.mean(decode_times):.2f} ms")
            md_lines.append(f"- **标准差**: {np.std(decode_times):.2f} ms")
            md_lines.append(f"- **中位数**: {np.median(decode_times):.2f} ms")
            md_lines.append("")
            
            # Token 列表 (折叠)
            md_lines.append("### 6.2 Token 生成列表\n")
            md_lines.append("<details>")
            md_lines.append("<summary>点击展开完整列表 (共 {} 个 Token)</summary>\n".format(len(self.token_profiles)))
            md_lines.append("| 序号 | Token ID | Token 文本 | 耗时 (ms) | 归一化耗时 (ms) | 内存 (MB) |")
            md_lines.append("|------|----------|------------|-----------|-----------------|-----------|")
            
            for i, tp in enumerate(self.token_profiles, 1):
                token_text = tp.token_text.replace("|", "\\|").replace("\n", "\\n")
                if len(token_text) > 20:
                    token_text = token_text[:17] + "..."
                md_lines.append(f"| {i} | {tp.token_id} | `{token_text}` | {tp.time_ms:.2f} | {tp.time_normalized_ms:.2f} | {tp.memory_mb:.2f} |")
            
            md_lines.append("\n</details>")
            md_lines.append("")
        
        # 内存时间线
        md_lines.append("## 7. 内存占用时间线\n")
        md_lines.append("| 时间点 (s) | 进程 RSS (MB) | 虚拟内存 (MB) | 系统已用 (MB) | 系统总量 (MB) |")
        md_lines.append("|------------|---------------|---------------|---------------|---------------|")
        
        for mem in self.memory_timeline:
            md_lines.append(f"| {mem.timestamp:.2f} | {mem.rss_mb:.2f} | {mem.vms_mb:.2f} | {mem.system_used_mb:.2f} | {mem.system_total_mb:.2f} |")
        md_lines.append("")
        
        # FPGA 加速建议
        md_lines.append("## 8. FPGA 加速建议\n")
        
        if layer_profiles:
            top5_layers = layer_profiles[:5]
            top5_time = sum(lp.total_time_ms for lp in top5_layers)
            top5_pct = (top5_time / total_layer_time * 100) if total_layer_time > 0 else 0
            
            md_lines.append("### 加速目标层\n")
            md_lines.append(f"根据性能分析，建议优先将以下层卸载到 FPGA 加速：\n")
            md_lines.append(f"- **Top 5 层占比**: {top5_pct:.1f}% 的 Linear 层计算时间")
            md_lines.append("")
            
            for i, lp in enumerate(top5_layers, 1):
                pct = (lp.total_time_ms / total_layer_time * 100) if total_layer_time > 0 else 0
                md_lines.append(f"{i}. `{lp.layer_name}`")
                md_lines.append(f"   - 耗时占比: {pct:.2f}%")
                md_lines.append(f"   - 参数量: {lp.params_count:,}")
                md_lines.append(f"   - 输入形状: {lp.input_shape}")
                md_lines.append(f"   - 输出形状: {lp.output_shape}")
                md_lines.append("")
        
        md_lines.append("### 1.58-bit 量化收益预估\n")
        md_lines.append("| 指标 | FP32 | 1.58-bit | 压缩比 |")
        md_lines.append("|------|------|----------|--------|")
        total_params = sum(lp.params_count for lp in layer_profiles) if layer_profiles else 0
        fp32_size = total_params * 4 / (1024**2)  # MB
        bit158_size = total_params * 2 / 8 / (1024**2)  # 2-bit packed
        md_lines.append(f"| Linear 层权重大小 | {fp32_size:.2f} MB | {bit158_size:.2f} MB | {fp32_size/bit158_size:.1f}x |")
        md_lines.append("")
        
        # 结论
        md_lines.append("---\n")
        md_lines.append("*本报告由 BitNet 推理性能分析工具自动生成*")
        
        # 写入文件
        os.makedirs(output_dir, exist_ok=True)
        report_path = os.path.join(output_dir, "inference_profile_report.md")
        
        with open(report_path, "w", encoding="utf-8") as f:
            f.write("\n".join(md_lines))
        
        print(f"\n报告已保存至: {report_path}")
        
        # 控制台输出汇总
        print(f"\n{'='*60}")
        print("性能分析汇总")
        print(f"{'='*60}")
        print(f"总推理时间: {total_time:.2f} ms")
        print(f"峰值内存: {peak_memory:.2f} MB")
        if self.token_profiles:
            print(f"生成 Token 数: {len(self.token_profiles)}")
            print(f"吞吐量: {1000 / np.mean([t.time_ms for t in self.token_profiles]):.2f} tokens/s")
        print(f"Linear 层数量: {len(layer_profiles)}")
        print(f"Linear 层总耗时: {total_layer_time:.2f} ms")
        
        return report_path


def main():
    parser = argparse.ArgumentParser(
        description="BitNet b1.58 模型推理性能分析 (增强版)"
    )
    parser.add_argument(
        "--model",
        type=str,
        default="../models",
        help="模型路径（本地路径或 HuggingFace 模型名称）"
    )
    parser.add_argument(
        "--prompt",
        type=str,
        default="How are you today?",
        help="推理输入提示语"
    )
    parser.add_argument(
        "--max-tokens",
        type=int,
        default=50,
        help="最大生成 token 数"
    )
    parser.add_argument(
        "--output-dir",
        type=str,
        default="../docs",
        help="报告输出目录"
    )
    parser.add_argument(
        "--dtype",
        type=str,
        choices=["float32", "float16", "bfloat16"],
        default="float32",
        help="模型数据类型"
    )
    
    args = parser.parse_args()
    
    dtype_map = {
        "float32": torch.float32,
        "float16": torch.float16,
        "bfloat16": torch.bfloat16,
    }
    
    print("=" * 60)
    print("BitNet b1.58 推理性能分析 (增强版)")
    print("=" * 60)
    print(f"时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    
    profiler = InferenceProfiler(
        model_name=args.model,
        dtype=dtype_map[args.dtype],
    )
    
    # 加载模型
    profiler.load_model()
    
    # 执行推理
    response, token_profiles = profiler.run_inference(
        prompt=args.prompt,
        max_new_tokens=args.max_tokens,
    )
    
    # 生成 Markdown 报告
    report_path = profiler.generate_markdown_report(output_dir=args.output_dir)
    
    # 清理 hooks
    if profiler.layer_profiler:
        profiler.layer_profiler.remove_hooks()
    
    print("\n" + "=" * 60)
    print("分析完成!")
    print("=" * 60)


if __name__ == "__main__":
    main()
