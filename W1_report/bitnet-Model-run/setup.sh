#!/bin/bash
# BitNet 模型分析项目环境配置脚本

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "========================================"
echo "BitNet 模型分析环境配置"
echo "========================================"

# 检查 Python 版本
PYTHON_CMD=""
if command -v python3.10 &> /dev/null; then
    PYTHON_CMD="python3.10"
elif command -v python3.11 &> /dev/null; then
    PYTHON_CMD="python3.11"
elif command -v python3 &> /dev/null; then
    PYTHON_CMD="python3"
else
    echo "错误: 未找到 Python3，请先安装 Python 3.10+"
    exit 1
fi

echo "使用 Python: $PYTHON_CMD ($($PYTHON_CMD --version))"

# 创建虚拟环境
VENV_DIR="$SCRIPT_DIR/venv"
if [ -d "$VENV_DIR" ]; then
    echo "虚拟环境已存在: $VENV_DIR"
    read -p "是否重新创建? (y/N) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        rm -rf "$VENV_DIR"
        $PYTHON_CMD -m venv "$VENV_DIR"
        echo "虚拟环境已重新创建"
    fi
else
    $PYTHON_CMD -m venv "$VENV_DIR"
    echo "虚拟环境已创建: $VENV_DIR"
fi

# 激活虚拟环境
source "$VENV_DIR/bin/activate"

# 升级 pip
pip install --upgrade pip

# 安装依赖
echo ""
echo "安装依赖包..."
pip install -r "$SCRIPT_DIR/requirements.txt"

echo ""
echo "========================================"
echo "环境配置完成!"
echo "========================================"
echo ""
echo "使用方法:"
echo "  1. 激活虚拟环境: source venv/bin/activate"
echo "  2. 运行分析脚本: cd src && python inference_profiler.py"
echo "  或者直接运行:   ./src/run_analysis.sh"
echo ""
echo "注意: 首次运行会自动下载模型 (~4GB)，请确保网络通畅"
