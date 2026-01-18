#!/usr/bin/env python3
"""
BitNet b1.58-2B-4T-bf16 推理性能分析脚本

功能：
1. 加载 HuggingFace 上的 BitNet 模型
2. 分析纯 CPU 推理各阶段的时间开销
3. 监控内存占用情况
4. 进行 CPU 频率归一化

作者: RISC-V AI FPGA 项目组
日期: 2026-01-17
"""

import os
import time
import json
import argparse
from datetime import datetime
from typing import Dict, List, Tuple, Optional
from dataclasses import dataclass, asdict
from contextlib import contextmanager

import torch
import psutil
import cpuinfo
import numpy as np
from transformers import AutoModelForCausalLM, AutoTokenizer
from tqdm import tqdm

# 强制使用 CPU
os.environ["CUDA_VISIBLE_DEVICES"] = ""
torch.set_num_threads(1)  # 单线程便于分析


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
        
        # 尝试从多个来源获取 CPU 频率
        freq_base = 0.0
        freq_current = 0.0
        
        if freq:
            freq_base = freq.max if freq.max else freq.current
            freq_current = freq.current if freq.current else freq.max
        
        # 如果 psutil 获取失败，尝试从 cpuinfo 获取
        if freq_base == 0:
            hz_actual = info.get("hz_actual_friendly", "")
            hz_advertised = info.get("hz_advertised_friendly", "")
            # 尝试解析如 "2.4000 GHz" 格式
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
        
        # 最后的备选：使用合理的默认值
        if freq_base == 0:
            freq_base = 3000.0  # 假设 3.0 GHz 作为默认值
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
    rss_mb: float        # 进程常驻内存
    vms_mb: float        # 虚拟内存
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
class StageProfile:
    """单阶段性能数据"""
    name: str
    duration_ms: float
    duration_normalized_ms: float  # 频率归一化后的时间
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


class InferenceProfiler:
    """推理性能分析器"""
    
    # 参考 CPU 频率（用于归一化，选择 3.0 GHz 作为基准）
    REFERENCE_FREQ_MHZ = 3000.0
    
    def __init__(
        self,
        model_name: str = "../models/BitNet b1.58-2B-4T-bf16",  # 本地模型路径
        device: str = "cpu",
        dtype: torch.dtype = torch.bfloat16,  # BitNet 推荐使用 bfloat16
    ):
        self.model_name = model_name
        self.device = device
        self.dtype = dtype
        
        self.model = None
        self.tokenizer = None
        
        self.cpu_info = CPUInfo.collect()
        # 频率归一化: 实测时间 × (实际频率 / 参考频率)
        # 这样高频 CPU 的归一化时间会更短，反映其真实性能优势
        self.freq_scale = self.cpu_info.freq_base_mhz / self.REFERENCE_FREQ_MHZ
        print(f"CPU 频率: {self.cpu_info.freq_base_mhz:.0f} MHz, 归一化系数: {self.freq_scale:.3f}")
        
        self.start_time = time.perf_counter()
        self.stage_profiles: List[StageProfile] = []
        self.memory_timeline: List[MemorySnapshot] = []
        
    def _normalize_time(self, duration_ms: float) -> float:
        """
        CPU 频率归一化
        
        将实测时间转换为参考频率（3.0 GHz）下的等效时间
        归一化时间 = 实测时间 × (实际频率 / 参考频率)
        
        这样可以在不同 CPU 之间公平比较性能
        """
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
                low_cpu_mem_usage=True,  # 低内存模式，逐层加载
            )
            self.model.eval()
        
        # 统计模型参数
        total_params = sum(p.numel() for p in self.model.parameters())
        print(f"\n模型参数量: {total_params / 1e9:.2f}B")
    
    def run_inference(
        self,
        prompt: str,
        max_new_tokens: int = 50,
        temperature: float = 0.7,
    ) -> Tuple[str, List[TokenProfile]]:
        """
        执行推理并分析性能
        
        返回:
            - 生成的文本
            - 每个 token 的性能数据
        """
        print(f"\n{'='*60}")
        print(f"执行推理")
        print(f"{'='*60}")
        print(f"Prompt: {prompt}")
        print(f"Max new tokens: {max_new_tokens}")
        
        token_profiles: List[TokenProfile] = []
        generated_ids = []
        
        # 1. Tokenization（编码阶段）
        with self._profile_stage("Tokenization (编码)"):
            inputs = self.tokenizer(
                prompt,
                return_tensors="pt",
                padding=True,
            )
            input_ids = inputs["input_ids"]
            attention_mask = inputs["attention_mask"]
            
        print(f"  输入 token 数: {input_ids.shape[1]}")
        
        # 2. Prefill 阶段（首次前向传播，处理整个 prompt）
        with self._profile_stage("Prefill (首次前向)"):
            with torch.no_grad():
                outputs = self.model(
                    input_ids=input_ids,
                    attention_mask=attention_mask,
                    use_cache=True,
                )
                past_key_values = outputs.past_key_values
                next_token_logits = outputs.logits[:, -1, :]
        
        # 3. Decode 阶段（逐 token 生成）
        print(f"\n  开始 Decode 阶段 (逐 token 生成)...")
        
        current_ids = input_ids
        
        for i in tqdm(range(max_new_tokens), desc="  生成中"):
            mem_snapshot = MemorySnapshot.capture(self.start_time)
            start_token_time = time.perf_counter()
            
            with torch.no_grad():
                # 采样下一个 token
                if temperature > 0:
                    probs = torch.softmax(next_token_logits / temperature, dim=-1)
                    next_token = torch.multinomial(probs, num_samples=1)
                else:
                    next_token = torch.argmax(next_token_logits, dim=-1, keepdim=True)
                
                # 检查是否结束
                if next_token.item() == self.tokenizer.eos_token_id:
                    break
                
                generated_ids.append(next_token.item())
                
                # 更新 attention mask
                attention_mask = torch.cat([
                    attention_mask,
                    torch.ones((1, 1), dtype=attention_mask.dtype)
                ], dim=1)
                
                # 前向传播获取下一个 token 的 logits
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
            
            token_profiles.append(TokenProfile(
                token_id=next_token.item(),
                token_text=token_text,
                time_ms=token_time_ms,
                time_normalized_ms=self._normalize_time(token_time_ms),
                memory_mb=mem_snapshot.rss_mb,
            ))
        
        # 统计 Decode 阶段
        if token_profiles:
            decode_times = [t.time_ms for t in token_profiles]
            self.stage_profiles.append(StageProfile(
                name="Decode (逐token生成)",
                duration_ms=sum(decode_times),
                duration_normalized_ms=self._normalize_time(sum(decode_times)),
                memory_before_mb=token_profiles[0].memory_mb,
                memory_after_mb=token_profiles[-1].memory_mb,
                memory_delta_mb=token_profiles[-1].memory_mb - token_profiles[0].memory_mb,
            ))
            
            print(f"\n  生成 {len(token_profiles)} 个 token")
            print(f"  平均每 token: {np.mean(decode_times):.2f}ms "
                  f"(归一化: {self._normalize_time(np.mean(decode_times)):.2f}ms)")
            print(f"  吞吐量: {1000 / np.mean(decode_times):.2f} tokens/s")
        
        # 4. Detokenization（解码阶段）
        with self._profile_stage("Detokenization (解码)"):
            generated_text = self.tokenizer.decode(generated_ids, skip_special_tokens=True)
        
        full_response = prompt + generated_text
        print(f"\n生成结果: {generated_text}")
        
        return full_response, token_profiles
    
    def generate_report(self, output_dir: str = "../docs") -> Dict:
        """生成性能分析报告"""
        print(f"\n{'='*60}")
        print("性能分析报告")
        print(f"{'='*60}")
        
        report = {
            "meta": {
                "model_name": self.model_name,
                "timestamp": datetime.now().isoformat(),
                "reference_freq_mhz": self.REFERENCE_FREQ_MHZ,
            },
            "cpu_info": asdict(self.cpu_info),
            "freq_normalization": {
                "actual_freq_mhz": self.cpu_info.freq_base_mhz,
                "reference_freq_mhz": self.REFERENCE_FREQ_MHZ,
                "scale_factor": self.freq_scale,
                "explanation": "归一化时间 = 实测时间 × (实际频率 / 参考频率)",
            },
            "stage_profiles": [asdict(s) for s in self.stage_profiles],
            "summary": {},
        }
        
        # 汇总统计
        total_time = sum(s.duration_ms for s in self.stage_profiles)
        total_normalized = sum(s.duration_normalized_ms for s in self.stage_profiles)
        peak_memory = max(s.memory_after_mb for s in self.stage_profiles)
        
        report["summary"] = {
            "total_time_ms": total_time,
            "total_time_normalized_ms": total_normalized,
            "peak_memory_mb": peak_memory,
            "stages_breakdown": {
                s.name: {
                    "time_ms": s.duration_ms,
                    "time_percent": s.duration_ms / total_time * 100,
                    "time_normalized_ms": s.duration_normalized_ms,
                    "memory_delta_mb": s.memory_delta_mb,
                }
                for s in self.stage_profiles
            },
        }
        
        # 打印汇总
        print(f"\nCPU: {self.cpu_info.brand}")
        print(f"基准频率: {self.cpu_info.freq_base_mhz:.0f} MHz")
        print(f"频率归一化系数: {self.freq_scale:.3f}")
        
        print(f"\n{'阶段':<25} {'耗时(ms)':<12} {'归一化(ms)':<12} {'占比':<10} {'内存变化(MB)':<12}")
        print("-" * 75)
        for s in self.stage_profiles:
            pct = s.duration_ms / total_time * 100
            print(f"{s.name:<25} {s.duration_ms:<12.2f} {s.duration_normalized_ms:<12.2f} "
                  f"{pct:<10.1f}% {s.memory_delta_mb:<+12.2f}")
        print("-" * 75)
        print(f"{'总计':<25} {total_time:<12.2f} {total_normalized:<12.2f} {'100.0':<10}%")
        print(f"\n峰值内存占用: {peak_memory:.2f} MB")
        
        # 保存报告
        os.makedirs(output_dir, exist_ok=True)
        report_path = os.path.join(output_dir, "inference_profile_report.json")
        with open(report_path, "w", encoding="utf-8") as f:
            json.dump(report, f, ensure_ascii=False, indent=2)
        print(f"\n报告已保存至: {report_path}")
        
        return report


def main():
    parser = argparse.ArgumentParser(
        description="BitNet b1.58 模型推理性能分析"
    )
    parser.add_argument(
        "--model",
        type=str,
        default="../models",  # 本地模型路径
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
        default=250,
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
    print("BitNet b1.58 推理性能分析")
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
    
    # 生成报告
    report = profiler.generate_report(output_dir=args.output_dir)
    
    print("\n" + "=" * 60)
    print("分析完成!")
    print("=" * 60)


if __name__ == "__main__":
    main()
