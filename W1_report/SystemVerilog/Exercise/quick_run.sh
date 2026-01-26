#!/bin/bash

# 快速编译和运行脚本
# 用法: ./quick_run.sh [command] [options]

cd "$(dirname "$0")"

# 检查是否存在源文件
if [ ! -f "run_simulation.sh" ]; then
    echo "错误：找不到 run_simulation.sh 脚本"
    exit 1
fi

# 显示帮助信息
show_help() {
    cat << 'EOF'
快速运行脚本 - quick_run.sh

用法:
  ./quick_run.sh [command] [files]

命令:
  build              编译并运行仿真（自动搜索所有 .sv 文件）
  rebuild, clean     清理后编译并运行
  compile, -o        仅编译
  run, -r            仅运行已编译的仿真
  help, -h           显示此帮助

高级用法（指定 SV 文件）:
  ./quick_run.sh Ex1.sv              # 编译 Ex1.sv（使用文件名作为输出名）
  ./quick_run.sh Ex1.sv Ex2.sv       # 编译多个文件
  ./quick_run.sh Ex1.sv out_name     # 编译 Ex1.sv 并指定输出名
    ./quick_run.sh -t top Ex1.sv       # 指定顶层模块
    ./quick_run.sh -tb tb.sv           # 指定 testbench 文件
    ./quick_run.sh -tb tb.sv --tb-top tb_top  # 指定 testbench 顶层模块
  ./quick_run.sh -c Ex1.sv out_name  # 清理后编译指定文件

快捷命令:
  ./quick_run.sh              - 自动编译运行
  ./quick_run.sh clean        - 清理后编译运行
  ./quick_run.sh compile      - 仅编译
  ./quick_run.sh run          - 仅运行
  ./quick_run.sh help         - 显示此帮助
EOF
}

# 处理快捷命令
case "$1" in
    help|-h|--help)
        show_help
        exit 0
        ;;
    build)
        echo "编译并运行仿真..."
        ./run_simulation.sh "${@:2}"
        ;;
    rebuild|clean|--clean|-c)
        echo "清理后编译并运行..."
        ./run_simulation.sh --clean "${@:2}"
        ;;
    compile|--compile|-o)
        echo "仅编译..."
        ./run_simulation.sh --compile-only "${@:2}"
        ;;
    run|--run|-r)
        echo "运行已编译的仿真..."
        ./run_simulation.sh --run-only
        ;;
    "")
        # 无参数，自动编译运行
        echo "自动编译并运行仿真..."
        ./run_simulation.sh
        ;;
    *)
        # 处理文件指定的用法
        # ./quick_run.sh [-c] [-t top] [-o out] [-tb tb.sv] [--tb-top tb_top] Ex1.sv [Ex2.sv ...]
        
        files=()
        output_name=""
        top_name=""
        tb_file=""
        tb_top=""
        clean_flag="false"
        
        args=("$@")
        i=0
        while [ $i -lt ${#args[@]} ]; do
            arg="${args[$i]}"
            case "$arg" in
                -c|--clean)
                    clean_flag="true"
                    ;;
                -t|--top)
                    i=$((i+1))
                    top_name="${args[$i]}"
                    ;;
                -o|--output|--name)
                    i=$((i+1))
                    output_name="${args[$i]}"
                    ;;
                -tb|--testbench)
                    i=$((i+1))
                    tb_file="${args[$i]}"
                    ;;
                --tb-top)
                    i=$((i+1))
                    tb_top="${args[$i]}"
                    ;;
                *.sv)
                    files+=("$arg")
                    ;;
                *)
                    # 兼容旧用法：把未识别的参数当作输出名
                    output_name="$arg"
                    ;;
            esac
            i=$((i+1))
        done
        
        if [ ${#files[@]} -eq 0 ]; then
            echo "错误：无法识别的命令 '$1'"
            echo "使用 './quick_run.sh help' 查看帮助"
            exit 1
        fi
        
        # 构建命令
        cmd="./run_simulation.sh"
        if [ "$clean_flag" = "true" ]; then
            cmd="$cmd --clean"
        fi
        for file in "${files[@]}"; do
            cmd="$cmd -f $file"
        done
        if [ -n "$tb_file" ]; then
            cmd="$cmd -tb $tb_file"
        fi
        
        if [ -n "$output_name" ]; then
            cmd="$cmd -o $output_name"
        else
            # 如果只有一个文件且没指定输出名，使用文件名作为输出名
            if [ ${#files[@]} -eq 1 ]; then
                default_output="${files[0]%.sv}"
                cmd="$cmd -o $default_output"
            fi
        fi

        if [ -n "$top_name" ]; then
            cmd="$cmd -t $top_name"
        fi
        if [ -n "$tb_top" ]; then
            cmd="$cmd --tb-top $tb_top"
        fi
        
        echo "执行: $cmd"
        eval "$cmd"
        ;;
esac

