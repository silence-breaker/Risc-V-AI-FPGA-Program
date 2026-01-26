package my_types_pkg;
    typedef enum logic [1:0] {
        W_ZERO = 2'b00,
        W_POS  = 2'b01,
        W_NEG  = 2'b11
    } tern_t;
endpackage

import my_types_pkg::*; 

module vector_dot_product #(
    parameter int LEN = 4 //列可变参数的时候不需要分号
)(
    //输入端口：使用Packed Array
    //这是一个总线包含LEN个8位数据（拼在一起）
    input logic [LEN-1:0][7:0] i_vec_data,
    input tern_t [LEN-1:0] i_vec_weight,//数据类型不要搞错
    //输出端口：16位结果
    output logic signed [15:0] o_dot_result//考虑点积加和之后会变大
);
    
    always_comb begin

        //点积初始化为0
        o_dot_result = '0;
        for(i=0;i<LEN;i++) begin : dot_parr
            unique case(i_vec_weight[i]) 
                W_NEG: o_dot_result = o_dot_result - $signed(i_vec_data[i]);
                W_POS: o_dot_result = o_dot_result + $signed(i_vec_data[i]);
                W_ZERO: o_dot_result = o_dot_result;
            endcase
        end

    end

endmodule


