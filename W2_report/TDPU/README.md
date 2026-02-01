# TDPU核心模块报告

## 文件夹结构

- obj_dir: Verilator生成的中间文件
- run_sim.sh: 运行仿真的脚本（直接./run_sim.sh即可）
- wave.vcd: 生成的波形文件
- sim_main.cpp: 仿真主程序
- vec_multi_core.sv: 可配置并行度和数据深度的向量乘法核心模块
- package_def.sv: TDPU相关宏包定义
