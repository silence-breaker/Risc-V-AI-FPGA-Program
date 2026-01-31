`timescale 1ns / 1ps
`include "package_def.sv"  //引入包定义文件

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
  import package_def::*;
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


  //2.加法树 Part1
  logic signed [3:0][31:0] sum_temp;  //中间和
  logic o_valid_stage1;//由于加法树分了两层，所以valid信号也要分两段传递，否则时许不收敛

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      for (int k = 0; k < 4; k++) sum_temp[k] <= '0;
      o_valid_stage1 <= 1'b0;
    end else begin
      if (product_ready) begin

        sum_temp[0] <= (product[0] + product[1]) + (product[2] + product[3]);
        sum_temp[1] <= (product[4] + product[5]) + (product[6] + product[7]);
        sum_temp[2] <= (product[8] + product[9]) + (product[10] + product[11]);
        sum_temp[3] <= (product[12] + product[13]) + (product[14] + product[15]);


      end
      o_valid_stage1 <= product_ready;
    end
  end

  //3.加法树 Part2 & 输出寄存器
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      o_result <= '0;  //复位不可放到加法树part1,否则会计算错误
      o_data_ready <= 1'b0;
    end else begin
      o_data_ready <= o_valid_stage1;
      o_result <= sum_temp[0] + sum_temp[1] + sum_temp[2] + sum_temp[3];
    end
  end


endmodule
