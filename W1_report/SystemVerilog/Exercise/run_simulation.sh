#!/bin/bash

################################################################################
# SystemVerilog 编译运行一体化脚本
# 功能：编译指定的 .sv 文件 -> 生成指定名称的仿真文件 -> 运行仿真
# 使用方式: ./run_simulation.sh [选项]
################################################################################

set -e  # 任何命令失败则立即退出

# 配置变量
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_NAME="sv_simulation"
SV_FILES=()  # 待编译的 SV 文件列表
BUILD_DIR="${SCRIPT_DIR}/build"
OUTPUT_BINARY="${BUILD_DIR}/${PROJECT_NAME}"
OUTPUT_NAME="${PROJECT_NAME}"  # 输出文件名（不含路径）
TOP_MODULE="test_vars"  # 默认顶层模块
TOP_MODULE_AUTO="true"  # 是否自动推断顶层模块
TB_FILE=""              # testbench 文件
TB_TOP=""               # testbench 顶层模块名
AUTO_SEARCH="true"  # 是否自动搜索 SV 文件

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

################################################################################
# 函数定义
################################################################################

# 打印帮助信息
print_help() {
    cat << EOF
用法: $0 [选项]

选项:
  -h, --help              显示此帮助信息
  -c, --clean             清理构建文件
  -f, --file FILE         指定要编译的 .sv 文件（可多次使用，自动禁用自动搜索）
    -tb, --testbench FILE   指定 testbench 文件（会加入编译列表）
    --tb-top MODULE         指定 testbench 顶层模块名（优先级最高）
  -t, --top MODULE        指定顶层模块名称 (默认: $TOP_MODULE)
  -o, --output NAME       指定输出仿真文件名（不含路径，默认: $PROJECT_NAME）
  -n, --name NAME         同 -o（别名）
  -v, --verbose           详细输出
  --compile-only          仅编译，不运行仿真
  --run-only              仅运行仿真（跳过编译）
  --list-files            列出将要编译的所有文件

示例:
  $0                                          # 自动编译当前目录所有 .sv 文件
  $0 -f Ex1.sv -o test1                      # 编译 Ex1.sv，输出为 test1
  $0 -f Ex1.sv -f Ex2.sv -o combined         # 编译多个文件
    $0 -f TDPU_core.sv -tb TDPU_tb.sv          # 编译 DUT + testbench
    $0 -f TDPU_core.sv -tb TDPU_tb.sv --tb-top TDPU_tb  # 指定 testbench 顶层
  $0 --clean -f Ex1.sv -t my_module          # 清理后编译指定文件和模块
  $0 -f Ex1.sv --compile-only                # 仅编译
  $0 --run-only                              # 仅运行
EOF
}

# 打印带颜色的信息
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 检查必要的工具
check_tools() {
    local tools=("iverilog" "vvp")
    for tool in "${tools[@]}"; do
        if ! command -v "$tool" &> /dev/null; then
            print_error "找不到工具: $tool"
            print_info "请安装: sudo apt-get install iverilog"
            exit 1
        fi
    done
    print_success "工具检查通过"
}

# 自动推断顶层模块
detect_top_module() {
    local file
    local module_name
    for file in "${SV_FILES[@]}"; do
        module_name=$(grep -E -h -m 1 "^\s*module\s+[a-zA-Z_][a-zA-Z0-9_$]*" "$file" \
            | sed -E "s/^\s*module\s+([a-zA-Z_][a-zA-Z0-9_$]*).*/\1/")
        if [ -n "$module_name" ]; then
            TOP_MODULE="$module_name"
            return 0
        fi
    done
    return 1
}

detect_tb_top_module() {
    if [ -z "$TB_FILE" ]; then
        return 1
    fi
    local module_name
    module_name=$(grep -E -h -m 1 "^\s*module\s+[a-zA-Z_][a-zA-Z0-9_$]*" "$TB_FILE" \
        | sed -E "s/^\s*module\s+([a-zA-Z_][a-zA-Z0-9_$]*).*/\1/")
    if [ -n "$module_name" ]; then
        TOP_MODULE="$module_name"
        return 0
    fi
    return 1
}

# 清理构建文件
clean() {
    if [ -d "$BUILD_DIR" ]; then
        print_info "清理构建文件..."
        rm -rf "$BUILD_DIR"
        print_success "清理完成"
    fi
}

# 创建构建目录
setup_build_dir() {
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir -p "$BUILD_DIR"
        print_info "创建构建目录: $BUILD_DIR"
    fi
}

# 编译 SystemVerilog
compile() {
    print_info "开始编译 SystemVerilog 文件..."
    
    # 如果没有指定文件，则自动搜索
    if [ "$AUTO_SEARCH" = "true" ] && [ ${#SV_FILES[@]} -eq 0 ]; then
        print_info "自动搜索 .sv 文件..."
        mapfile -t SV_FILES < <(find "$SCRIPT_DIR" -maxdepth 1 -name "*.sv" -type f)
    fi
    
    # 检查是否有 .sv 文件
    if [ ${#SV_FILES[@]} -eq 0 ]; then
        print_error "未找到任何 .sv 文件"
        exit 1
    fi

    # 顶层模块选择优先级：--tb-top > -t > 自动检测(优先从 tb 文件) > 默认
    if [ -n "$TB_TOP" ]; then
        TOP_MODULE="$TB_TOP"
        print_info "使用 testbench 顶层模块: $TOP_MODULE"
    elif [ "$TOP_MODULE_AUTO" = "true" ]; then
        if [ -n "$TB_FILE" ] && detect_tb_top_module; then
            print_info "自动检测 testbench 顶层模块: $TOP_MODULE"
        elif detect_top_module; then
            print_info "自动检测顶层模块: $TOP_MODULE"
        else
            print_warning "未能自动检测顶层模块，使用默认: $TOP_MODULE"
        fi
    else
        print_info "顶层模块: $TOP_MODULE"
    fi
    
    if [ "$VERBOSE" = "true" ]; then
        print_info "待编译文件:"
        for file in "${SV_FILES[@]}"; do
            echo "  - $file"
        done
    fi
    
    # 使用 iverilog 编译
    if [ "$VERBOSE" = "true" ]; then
        iverilog -g2009 -o "$OUTPUT_BINARY" -s "$TOP_MODULE" "${SV_FILES[@]}"
    else
        iverilog -g2009 -o "$OUTPUT_BINARY" -s "$TOP_MODULE" "${SV_FILES[@]}" 2>&1 | grep -i "error\|warning" || true
    fi
    
    if [ ! -f "$OUTPUT_BINARY" ]; then
        print_error "编译失败"
        exit 1
    fi
    
    print_success "编译完成: $OUTPUT_BINARY"
}

# 运行仿真
run_simulation() {
    print_info "开始运行仿真..."
    echo ""
    echo -e "${BLUE}═══════════════════════════════════════════════════${NC}"
    
    # 运行 vvp 仿真
    vvp "$OUTPUT_BINARY"
    
    echo -e "${BLUE}═══════════════════════════════════════════════════${NC}"
    echo ""
    print_success "仿真完成"
}

# 生成报告
generate_report() {
    local report_file="${BUILD_DIR}/simulation_report.txt"
    cat > "$report_file" << EOF
================================
SystemVerilog 仿真报告
================================
生成时间: $(date)
顶层模块: $TOP_MODULE
输出文件: $OUTPUT_BINARY
编译文件:
EOF
    for file in "${SV_FILES[@]}"; do
        echo "  - $(basename "$file")" >> "$report_file"
    done
    cat >> "$report_file" << EOF
================================
EOF
    print_success "报告已保存到: $report_file"
}

################################################################################
# 主程序流程
################################################################################

# 默认值
VERBOSE="false"
COMPILE_ONLY="false"
RUN_ONLY="false"
CLEAN_FIRST="false"

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            print_help
            exit 0
            ;;
        -c|--clean)
            CLEAN_FIRST="true"
            shift
            ;;
        -f|--file)
            AUTO_SEARCH="false"  # 手动指定文件时禁用自动搜索
            SV_FILES+=("$2")
            shift 2
            ;;
        -tb|--testbench)
            AUTO_SEARCH="false"
            TB_FILE="$2"
            # 确保 tb 文件加入编译列表
            SV_FILES+=("$2")
            shift 2
            ;;
        --tb-top)
            TB_TOP="$2"
            TOP_MODULE_AUTO="false"
            shift 2
            ;;
        -t|--top)
            TOP_MODULE="$2"
            TOP_MODULE_AUTO="false"
            shift 2
            ;;
        -o|-n|--output|--name)
            OUTPUT_NAME="$2"
            OUTPUT_BINARY="${BUILD_DIR}/${OUTPUT_NAME}"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE="true"
            shift
            ;;
        --compile-only)
            COMPILE_ONLY="true"
            shift
            ;;
        --run-only)
            RUN_ONLY="true"
            shift
            ;;
        --list-files)
            AUTO_SEARCH="false"
            # 显示将要编译的文件
            if [ ${#SV_FILES[@]} -eq 0 ]; then
                echo "未指定任何文件，使用 -f 选项指定"
                print_help
                exit 0
            fi
            echo "将要编译的文件:"
            for file in "${SV_FILES[@]}"; do
                echo "  - $file"
            done
            exit 0
            ;;
        *)
            print_error "未知选项: $1"
            print_help
            exit 1
            ;;
    esac
done

# 主流程
print_info "========== SystemVerilog 一体化仿真脚本 =========="

# 检查工具
check_tools

# 清理旧文件
if [ "$CLEAN_FIRST" = "true" ]; then
    clean
fi

# 创建构建目录
setup_build_dir

# 仅运行模式
if [ "$RUN_ONLY" = "true" ]; then
    if [ ! -f "$OUTPUT_BINARY" ]; then
        print_error "仿真二进制文件不存在: $OUTPUT_BINARY"
        exit 1
    fi
    run_simulation
    exit 0
fi

# 正常流程：编译
compile

# 如果指定了仅编译模式，则退出
if [ "$COMPILE_ONLY" = "true" ]; then
    exit 0
fi

# 运行仿真
run_simulation

# 可选：生成报告
# generate_report

print_success "=================================================="
print_success "所有操作完成！"
