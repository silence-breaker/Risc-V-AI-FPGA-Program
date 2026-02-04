#!/bin/bash

# 1. 格式化 SystemVerilog 代码（保持良好的代码风格）
verible-verilog-format --inplace vec_multi_core.sv

# 2. 运行 Verilator 编译
# --cc: 产生C++模型
# --exe: 包含用户编写的 sim_main.cpp
# --build: 自动调用 make 编译出二进制文件
# --trace: 开启波形追踪
# -Wno-IMPORTSTAR: 忽略你之前遇到的包导入警告
verilator --cc vec_multi_core.sv --exe sim_main.cpp --build -Wall --trace -Wno-IMPORTSTAR

# 3. 执行仿真
if [ -f "./obj_dir/Vvec_multi_core" ]; then
    ./obj_dir/Vvec_multi_core
else
    echo "编译失败，请检查报错信息。"
fi