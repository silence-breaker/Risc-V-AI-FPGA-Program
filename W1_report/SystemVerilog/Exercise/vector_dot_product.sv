`include "my_types_pkg.sv"  //引入包定义文件这样就不会报错了
module vector_dot_product
  import my_types_pkg::*;  // import 放在模块声明内部（SV 标准写法）
#(
    parameter int LEN = 4  //列可变参数的时候不需要分号
) (
    //输入端口：使用Packed Array
    //这是一个总线包含LEN个8位数据（拼在一起）
    input logic [LEN-1:0][7:0] i_vec_data,
    input tern_t [LEN-1:0] i_vec_weight,  //数据类型不要搞错
    //输出端口：16位结果
    output logic signed [15:0] o_dot_result  //考虑点积加和之后会变大
);
  always_comb begin

    //点积初始化为0
    o_dot_result = '0;
    for (int i = 0; i < LEN; i++) begin : dot_parr
      unique case (i_vec_weight[i])
        W_NEG:   o_dot_result = o_dot_result - 16'($signed(i_vec_data[i]));
        W_POS:   o_dot_result = o_dot_result + 16'($signed(i_vec_data[i]));
        W_ZERO:  o_dot_result = o_dot_result;
        default: o_dot_result = o_dot_result;  //防止综合报错
      endcase
    end
  end

endmodule


