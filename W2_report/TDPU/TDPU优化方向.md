# TDPU优化方向

## 一、当前TDPU架构分析

### 1.1 设计概述

| 特性 | 当前TDPU | 参考TPU |
|------|----------|---------|
| **量化方式** | 三值权重{-1,0,+1} | 8-bit整数 |
| **计算阵列** | 1D向量乘法器 (16并行) | 2D脉动阵列 (16×16) |
| **流水线** | 3级 (PE→加法树1→加法树2) | 多级脉动数据流 |
| **存储** | 无片上SRAM | 多级缓冲 (10KB×3 + 128KB) |
| **控制** | 简单握手信号 | 完整状态机 (9状态) |
| **输出** | 单累加器 | 16×16输出块 |

### 1.2 核心代码结构

```
vec_multi_core (单一模块)
├── weight_reg (权重锁存)
├── gen_PE (16个并行PE)
│   └── 三值乘法器 (通过选择+1/-1/0实现)
├── sum_temp (两级加法树)
└── o_result (32位累加输出)
```

**优势**：

- ✅ 简单直接，易于验证
- ✅ 1.58-bit量化减少存储带宽
- ✅ 支持权重锁存后的多次复用
- ✅ 流水线化设计

## 二、专业级优化建议

### 2.1 架构升级：从1D向量到2D脉动阵列

**问题**：当前设计只能做向量点积，无法高效映射卷积

**方案**：

```systemverilog
// 参考TPU的2D脉动阵列设计
module TDPU_array #(
    parameter ROWS = 16,
    parameter COLS = 16
) (
    input logic clk, rst_n,
    input logic [127:0] activation_in,  // 16×8bit
    input weight_t [COLS-1:0] weight_in,  // 16个权重列
    output logic [31:0] output_col [COLS]  // 16列累加结果
);
    // 2D PE网格实现脉动数据流
endmodule
```

**优势**：

- 256个并行三值乘法器 (vs 当前16个)
- 天然支持卷积映射
- 脉动数据流减少布线开销

### 2.2 存储层次结构

**问题**：无片上缓冲，依赖外部数据供给

**方案**：添加三级缓冲

```systemverilog
// 添加片上SRAM层次
module TDPU_with_memory (
    input logic [127:0] sram_data_in,
    output logic [127:0] sram_data_out,
    // ... 控制信号
);

// 1. 共享缓冲区 (128KB) - 主SRAM接口
// 2. 权重缓冲区 (16KB) - 权重预取
// 3. 激活缓冲区 (16KB) - 激活值流水线
// 4. 输出缓冲区 (32KB) - 结果汇集
```

**容量计算**：

- 三值权重：2bit/权重 vs 8bit → **4×存储效率提升**
- 16×16阵列权重 = 256 × 2bit = 64B
- 可支持更大阵列：64×64阵列 = 1024B

### 2.3 卷积映射引擎

**问题**：无法直接处理2D卷积

**方案**：添加卷积参数

```systemverilog
module conv_controller #(
    parameter IN_CH = 64,
    parameter OUT_CH = 64,
    parameter KERNEL_H = 3,
    parameter KERNEL_W = 3,
    parameter STRIDE = 1,
    parameter PAD = 1
) (
    input logic [15:0] feature_h,    // 输入特征图高度
    input logic [15:0] feature_w,     // 输入特征图宽度
    output logic [31:0] tiling_ctrl   // Tiling控制
);
    // 自动计算tiling策略
    // 生成权重/激活地址序列
endmodule
```

### 2.4 流水线与双缓冲优化

**当前问题**：CALCULATE状态下无数据预取

**优化方案**：

```systemverilog
// 双缓冲实现计算与加载重叠
always_ff @(posedge clk) begin
    case (state)
        CALCULATE: begin
            // PE计算使用 buffer_A
            // 同时加载下一块数据到 buffer_B
        end
        LOAD_NEXT: begin
            // 交换 buffer_A 和 buffer_B
        end
    endcase
end
```

### 2.5 精度与量化增强

**当前**：固定三值量化

**扩展方案**：

```systemverilog
typedef enum logic [2:0] {
    QUANT_TERNARY = 3'b001,    // {-1,0,+1}
    QUANT_INT4    = 3'b010,    // 4-bit
    QUANT_INT8   = 3'b011,    // 8-bit  
    QUANT_BINARY = 3'b100     // {-1,+1}
} quant_mode_t;

module adaptive_PE (
    input quant_mode_t mode,
    input logic [7:0] weight_8bit,
    input weight_t weight_ternary,
    // ... 自动选择计算路径
);
```

### 2.6 状态机扩展

**当前**：3状态 (LOAD_WEIGHT → PROCESS → IDLE)

**参考TPU的9状态扩展**：

| 状态 | 功能 | 周期数 |
|------|------|--------|
| IDLE | 空闲 | - |
| LOAD_W | 加载权重 | 16 |
| LOAD_A | 加载激活 | 16 |
| CALC | 脉动计算 | 可变 |
| DRAIN | 排出结果 | 16 |
| WRITE_BACK | 写回SRAM | 16 |

### 2.7 接口标准化

**当前**：Verilator仿真接口

**生产化方案**：

```systemverilog
// AXI4-Stream接口
module TDPU_AXI (
    // AXI Slave Interface
    input  logic s_axis_tvalid,
    output logic s_axis_tready,
    input  logic [127:0] s_axis_tdata,
    input  logic s_axis_tlast,
    
    // AXI Master Interface (输出)
    output logic m_axis_tvalid,
    input  logic m_axis_tready,
    output logic [31:0] m_axis_tdata,
    
    // 控制寄存器
    input  logic [31:0] ctrl_reg,  // 启动/复位
    output logic [31:0] status_reg // 完成/错误
);
```

## 三、优化优先级建议

| 优先级 | 优化项 | 难度 | 收益 | 建议 |
|--------|--------|------|------|------|
| **P0** | 添加片上缓冲 | 中 | 高 | 解决带宽瓶颈 |
| **P1** | 2D脉动阵列 | 高 | 极高 | 支持卷积运算 |
| **P2** | 双缓冲流水线 | 中 | 高 | 提升吞吐 |
| **P3** | 卷积参数接口 | 低 | 高 | 自动化映射 |
| **P4** | AXI接口 | 中 | 中 | FPGA集成 |
| **P5** | 多精度支持 | 高 | 中 | 灵活性 |

## 四、代码级改进建议

### 4.1 当前代码问题

```systemverilog
// 问题1：加法树硬编码为16输入
logic signed [3:0][31:0] sum_temp;  // 固定4组

// 问题2：无溢出保护
output logic signed [31:0] o_result

// 问题3：product_ready信号位置不当
always_ff @(posedge clk or negedge rst_n)
  product_ready <= i_data_valid;  // 与product并行
```

### 4.2 改进代码

```systemverilog
// 参数化加法树
localparam ADDER_LEVELS = $clog2(LEN);
logic signed [ADDER_LEVELS:0][LEN-1:0][31:0] adder_tree;

// 溢出检测
logic overflow_flag;
assign overflow_flag = |o_result[31:16] & ~o_result[31];  // MSB不一致

// 更好的流水线控制
logic [2:0] pipeline_valid;
always_ff @(posedge clk) begin
    pipeline_valid <= {pipeline_valid[1:0], i_data_valid};
end
```

## 五、总结

| 对比维度 | 当前TDPU | 优化后TDPU |
|----------|----------|------------|
| **峰值性能** | 16×200MHz = 3.2 GOPS | 256×200MHz = 51.2 GOPS |
| **运算类型** | 向量点积 | 卷积+矩阵乘 |
| **存储** | 外部SRAM | 64KB+片上缓冲 |
| **接口** | 仿真信号 | AXI4-Stream |
| **量化** | 固定三值 | 多精度自适应 |

**推荐路线图**：

1. **Phase 1**: 添加输入/输出缓冲，引入双缓冲机制
2. **Phase 2**: 扩展为2D脉动阵列，实现卷积支持
3. **Phase 3**: 添加AXI接口和状态机，实现完整TPU-like架构

这样可以将TDPU从一个简单的向量乘法器升级为具有竞争力的AI推理加速器。
