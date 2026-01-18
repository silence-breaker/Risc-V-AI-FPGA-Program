#!/bin/bash
# BitNet 模型推理性能分析运行脚本

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

echo "========================================"
echo "BitNet b1.58 推理性能分析"
echo "========================================"

# 检查虚拟环境
if [ ! -d "$PROJECT_DIR/venv" ]; then
    echo "错误: 虚拟环境不存在，请先运行 setup.sh"
    exit 1
fi

# 激活虚拟环境
source "$PROJECT_DIR/venv/bin/activate"

# 运行分析脚本
cd "$SCRIPT_DIR"
python inference_profiler.py \
    --model "microsoft/bitnet-b1.58-2B-4T-bf16" \
    --prompt "Hello, I am a language model and" \
    --max-tokens 50 \
    --output-dir "$PROJECT_DIR/docs" \
    --dtype float32

echo ""
echo "分析完成! 报告保存在 docs/inference_profile_report.json"
