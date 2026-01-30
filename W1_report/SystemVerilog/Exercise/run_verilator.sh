#!/bin/bash

################################################################################
# Verilator SystemVerilog 仿真脚本
# 支持完整的 SystemVerilog 特性（package, typedef 等）
################################################################################

set -e

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_info()    { echo -e "${BLUE}[INFO]${NC} $1"; }
print_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
print_error()   { echo -e "${RED}[ERROR]${NC} $1"; }

# 默认值
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"
OUTPUT_NAME="sim_verilator"
SV_FILES=()
TB_FILE=""
TOP_MODULE=""
CLEAN=false
COMPILE_ONLY=false
RUN_ONLY=false

# 帮助信息
print_help() {
    cat << EOF
用法: $0 [选项]

Verilator SystemVerilog 仿真脚本 - 支持完整 SV 特性

选项:
  -h, --help              显示帮助信息
  -c, --clean             清理构建文件
  -f, --file FILE         指定 DUT .sv 文件（可多次使用）
  -tb, --testbench FILE   指定 testbench 文件
  -t, --top MODULE        指定顶层模块名（默认从 tb 文件推断）
  -o, --output NAME       指定输出名称（默认: $OUTPUT_NAME）
  --compile-only          仅编译
  --run-only              仅运行

示例:
  $0 -f vector_dot_product.sv -tb tb_vec_dot_prod.sv
  $0 -f my_types_pkg.sv -f vector_dot_product.sv -tb tb_vec_dot_prod.sv -o my_sim
EOF
}

# 解析参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)      print_help; exit 0 ;;
        -c|--clean)     CLEAN=true; shift ;;
        -f|--file)      SV_FILES+=("$2"); shift 2 ;;
        -tb|--testbench) TB_FILE="$2"; shift 2 ;;
        -t|--top)       TOP_MODULE="$2"; shift 2 ;;
        -o|--output)    OUTPUT_NAME="$2"; shift 2 ;;
        --compile-only) COMPILE_ONLY=true; shift ;;
        --run-only)     RUN_ONLY=true; shift ;;
        *)              print_error "未知选项: $1"; exit 1 ;;
    esac
done

# 清理
if $CLEAN; then
    print_info "清理构建目录..."
    rm -rf "${BUILD_DIR}/obj_dir_${OUTPUT_NAME}"
    print_success "清理完成"
fi

# 仅运行模式
if $RUN_ONLY; then
    EXEC="${BUILD_DIR}/obj_dir_${OUTPUT_NAME}/V${TOP_MODULE:-tb}"
    if [[ -x "$EXEC" ]]; then
        print_info "运行仿真..."
        "$EXEC"
        exit 0
    else
        print_error "找不到可执行文件，请先编译"
        exit 1
    fi
fi

# 检查文件
if [[ ${#SV_FILES[@]} -eq 0 ]] && [[ -z "$TB_FILE" ]]; then
    print_error "请至少指定一个 .sv 文件 (-f) 或 testbench (-tb)"
    print_help
    exit 1
fi

# 自动检测顶层模块
if [[ -z "$TOP_MODULE" ]] && [[ -n "$TB_FILE" ]]; then
    TOP_MODULE=$(grep -oP '(?<=^module\s)\w+' "$TB_FILE" | head -1)
    print_info "自动检测顶层模块: $TOP_MODULE"
fi

if [[ -z "$TOP_MODULE" ]]; then
    print_error "无法确定顶层模块，请使用 -t 指定"
    exit 1
fi

# 创建构建目录
mkdir -p "$BUILD_DIR"
OBJ_DIR="${BUILD_DIR}/obj_dir_${OUTPUT_NAME}"

# 构建文件列表（package 文件需要在最前面）
ALL_FILES=()

# 检查是否有 package 文件需要加入
for f in "${SV_FILES[@]}"; do
    # 检查文件中的 include
    if grep -q '`include' "$f" 2>/dev/null; then
        includes=$(grep -oP '(?<=`include\s")[^"]+' "$f")
        for inc in $includes; do
            if [[ -f "$inc" ]] && [[ ! " ${ALL_FILES[*]} " =~ " ${inc} " ]]; then
                ALL_FILES+=("$inc")
            fi
        done
    fi
done

# 添加 DUT 文件
for f in "${SV_FILES[@]}"; do
    if [[ ! " ${ALL_FILES[*]} " =~ " ${f} " ]]; then
        ALL_FILES+=("$f")
    fi
done

# 检查 testbench 的 include
if [[ -n "$TB_FILE" ]]; then
    if grep -q '`include' "$TB_FILE" 2>/dev/null; then
        includes=$(grep -oP '(?<=`include\s")[^"]+' "$TB_FILE")
        for inc in $includes; do
            if [[ -f "$inc" ]] && [[ ! " ${ALL_FILES[*]} " =~ " ${inc} " ]]; then
                # 插入到最前面
                ALL_FILES=("$inc" "${ALL_FILES[@]}")
            fi
        done
    fi
    ALL_FILES+=("$TB_FILE")
fi

print_info "========== Verilator 仿真脚本 =========="
print_info "待编译文件:"
for f in "${ALL_FILES[@]}"; do
    echo "  - $f"
done
print_info "顶层模块: $TOP_MODULE"

# 编译
print_info "开始 Verilator 编译..."

# Verilator 5.x 编译
verilator --binary --timing \
    -Wall -Wno-fatal \
    --top-module "$TOP_MODULE" \
    -Mdir "$OBJ_DIR" \
    -o "V${TOP_MODULE}" \
    "${ALL_FILES[@]}" 2>&1

VERILATOR_EXIT=$?

if [[ $VERILATOR_EXIT -ne 0 ]]; then
    print_error "Verilator 编译失败"
    exit 1
fi

print_success "编译成功"

# 运行
if ! $COMPILE_ONLY; then
    print_info "运行仿真..."
    echo "----------------------------------------"
    "${OBJ_DIR}/V${TOP_MODULE}"
    echo "----------------------------------------"
    print_success "仿真完成"
fi
