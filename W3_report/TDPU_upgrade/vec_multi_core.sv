`timescale 1ns / 1ps
`include "package_def.sv"  //引入包定义文件
import package_def::*;
//在一个时间周期内并行计算默认参数为16对数据的TDPU核心
//该核心先进行权重锁存，然后以脉动形式输出结果
//logic [数量-1 : 0] [位宽-1 : 0] 变量名;
module vec_multi_core #(
    parameter int LEN = 16,  //并行度
    parameter int DATA_WIDTH = 8
) (

    input logic clk,
    input logic rst_n,  //异步复位
    input logic i_data_valid,  //输入数据有效信号（同步）
    input logic i_load_weight,  //加载权重信号（同步）
    input logic signed [LEN-1:0][DATA_WIDTH-1:0] i_data,  //输入激活值数组
    input weight_t [LEN-1:0] i_weight,  //输入权重数组
    output logic o_data_ready,  //输出结果有效信号（同步）
    output logic signed [31:0] o_result  //输出累加结果，选择32位以防溢出
);

  //0.权重寄存器(收到加载信号时锁存权重)
  weight_t [LEN-1:0] weight_reg;
  always_ff @(posedge clk or negedge rst_n) begin : core
    if (!rst_n) begin
      weight_reg <= '{default: W_ZERO};
    end else begin
      if (i_load_weight) begin
        weight_reg <= i_weight;//如果没有收到权重加载信号则保持原来的数据不变
      end
    end

  end

  //1.PE计算层
  //中间信号：用于处理符号扩展
  logic signed [LEN-1:0][31:0] product;
  logic product_ready;
  //计算每个激活值和权重点积的结果（并行生成）
  //根据权重值决定是加、减 还是 不变
  generate
    for (genvar i = 0; i < LEN; i++) begin : gen_PE  // genvar是生成循环专用变量
      always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
          product[i] <= 32'sd0;  // 每个元素独立复位
          product_ready <= 1'b0;
        end else begin
          if (i_data_valid) begin
            unique case (weight_reg[i])
              W_POS: begin
                product[i] <= 32'(i_data[i]);  // 符号扩展到32位
              end
              W_NEG: begin
                product[i] <= -32'(i_data[i]);  // 符号扩展并取负
              end
              W_ZERO: begin
                product[i] <= 32'sd0;
              end
              default: product[i] <= 32'sd0;
            endcase
          end else begin
            // 补充i_data_valid为低时的赋值，避免锁存器
            product[i] <= product[i];  // 保持原值（显式写，消除警告）

          end
          product_ready <= i_data_valid;
        end
      end
    end
  endgenerate


  //2. 参数化加法树
  // 计算加法树的层数: $clog2(LEN)
  localparam int TREE_DEPTH = $clog2(LEN);
  
  // 定义加法树的中间信号
  // tree_data[level][index]
  // 第0层是 product 结果 (LEN个)
  // 第1层是 LEN/2 个结果
  // ...
  // 第TREE_DEPTH层是 1 个结果
  logic signed [31:0] tree_data [TREE_DEPTH:0][LEN-1:0];
  logic [TREE_DEPTH:0] tree_valid;

  // 将PE层的输出连接到加法树第0层
  always_comb begin
    for (int i = 0; i < LEN; i++) begin
      tree_data[0][i] = product[i];
    end
    tree_valid[0] = product_ready;
  end

  // 生成加法树流水线
  generate
    for (genvar level = 0; level < TREE_DEPTH; level++) begin : gen_tree_level
      // 当前层节点数
      localparam int NUM_NODES = LEN >> (level + 1);
      
      for (genvar k = 0; k < NUM_NODES; k++) begin : gen_adder
        always_ff @(posedge clk or negedge rst_n) begin
          if (!rst_n) begin
            tree_data[level+1][k] <= 32'sd0;
          end else begin
            if (tree_valid[level]) begin
              // 相邻两个节点相加
              tree_data[level+1][k] <= tree_data[level][2*k] + tree_data[level][2*k+1];
            end
          end
        end
      end
      
      // Valid信号流水线传递
      always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
          tree_valid[level+1] <= 1'b0;
        end else begin
          tree_valid[level+1] <= tree_valid[level];
        end
      end
    end
  endgenerate

  //3. 输出处理
  // 最终结果在 tree_data[TREE_DEPTH][0]
  assign o_result = tree_data[TREE_DEPTH][0];
  assign o_data_ready = tree_valid[TREE_DEPTH];


endmodule
