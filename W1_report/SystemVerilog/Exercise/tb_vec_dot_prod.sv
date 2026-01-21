module tb_mission_2;
    import my_types_pkg::*;

    // 1. 定义参数
    localparam VECTOR_LEN = 4;

    // 2. 信号声明
    // 注意：这里的位宽定义必须和模块对应
    logic [VECTOR_LEN-1:0][7:0] t_vec_data;
    tern_t [VECTOR_LEN-1:0]     t_vec_weight;
    logic signed [15:0]         t_result;

    // 3. 实例化：修改参数为 4
    vector_dot_product #(.LEN(VECTOR_LEN)) u_dut (
        .i_vec_data   (t_vec_data),
        .i_vec_weight (t_vec_weight),
        .o_dot_result   (t_result)
    );

    initial begin
        $display("--- Mission 2 Start (Parallelism = 4) ---");

        // Case 1: 全 1 测试
        // Data:   [ 1,  1,  1,  1]
        // Weight: [+1, +1, +1, +1]
        // Expect: 4
        
        // 这种赋值方式叫 Aggregate Assignment，非常方便
        t_vec_data   = '{8'd1, 8'd1, 8'd1, 8'd1};
        t_vec_weight = '{W_POS, W_POS, W_POS, W_POS};
        
        #10;
        if (t_result === 16'd4) $display("Case 1 PASS: 1+1+1+1 = 4");
        else                    $error("Case 1 FAIL: Got %d", t_result);

        // Case 2: 混合测试
        // Data:   [ 10,   20,   30,    40 ]
        // Weight: [+1,   -1,    0,    +1 ]
        // Calc:   10 + (-20) +  0  +  40 = 30
        
        // TODO 5: 请依据上面的注释，给 data 和 weight 赋值
        t_vec_data   = '{8'd10, 8'd20, 8'd30, 8'd40};
        t_vec_weight = '{W_POS, W_NEG, W_ZERO, W_POS};

        #10;
        if (t_result === 16'd30) $display("Case 2 PASS: 10-20+0+40 = 30");
        else                     $error("Case 2 FAIL: Got %d", t_result);

        $finish;
    end

endmodule
