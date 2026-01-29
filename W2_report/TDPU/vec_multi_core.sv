`include "package_def.sv"  //引入包定义文件
import package_def::*;
//在一个时间周期内并行计算默认参数为16对数据的TDPU核心
//logic [数量-1 : 0] [位宽-1 : 0] 变量名;
module vec_multi_core #(
    parameter int LEN = 16  //并行度
) (
    input  logic signed [LEN-1:0][7:0] i_data,    //输入激活值数组
    input  weight_t     [LEN-1:0]      i_weight,  //输入权重数组
    output logic signed [   31:0]      o_result   //输出累加结果，选择32位以防溢出
);
  //中间信号：用于处理符号扩展
  logic signed [31:0] product[LEN];
  //计算每个激活值和权重点积的结果（并行生成）
  genvar i;
  generate
    for (i = 0; i < LEN; i++) begin : gen_PE

      //根据权重值决定是加、减 还是 不变
      always_comb begin
        unique case (i_weight[i])
          W_POS: begin
            product[i] = 32'(i_data[i]);  //符号扩展到32位
          end
          W_NEG: begin
            product[i] = -32'(i_data[i]);  //符号扩展到32位并取负
          end
          W_ZERO: begin
            product[i] = 32'sd0;  //权重为0，结果为0
          end
          default: product[i] = 32'sd0;  // 安全保底
        endcase
      end
    end
  endgenerate

  //累加所有PE的输出结果
  int j = 0;
  always_comb begin
    o_result = 32'sd0;  //初始化累加结果
    for (j = 0; j < LEN; j++) begin
      o_result += product[j];  //累加每个PE的结果
    end
  end

endmodule
