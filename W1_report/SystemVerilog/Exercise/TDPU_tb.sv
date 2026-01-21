module tb_mission_1;
    // 信号声明
    import my_types_pkg::*; // 引入类型定义
    
    logic [7:0]  t_data;
    tern_t       t_weight;
    logic [15:0] t_curr;
    logic [15:0] t_res;
    
    // 实例化你的模块
    ternary_mac_unit u_dut (
        .i_data       (t_data),
        .i_weight     (t_weight),
        .i_current_sum(t_curr),
        .o_next_sum   (t_res)
    );
    
    initial begin
        $display("---------------------------------------");
        $display("   Mission 1 Verification Start");
        $display("---------------------------------------");
        
        // Case 1: 简单的加法 (10 * 1 + 5 = 15)
        t_data = 8'd10; t_weight = W_POS; t_curr = 16'd5;
        #10; // 等待 10ns 让电路跑出结果
        if (t_res === 16'd15) $display("[PASS] Case 1: 10 * 1 + 5 = 15");
        else                  $error("[FAIL] Case 1 Expected 15, Got %d", t_res);
        
        // Case 2: 减法 (20 * -1 + 100 = 80)
        t_data = 8'd20; t_weight = W_NEG; t_curr = 16'd100;
        #10;
        // TODO 4: 这里应该怎么写检查逻辑？
       if(t_res==16'd80) $display("[PASS] Case 2: 100-20=80");
       else              $error("[FAIL] Case Expected 80,Got %d",t_res);
        
        // Case 3: 乘以0 (50 * 0 + 33 = 33)
        t_data = 8'd50; t_weight = W_ZERO; t_curr = 16'd33;
        #10
        // TODO 5: 自己写一个测试用例
        
        if(t_res==16'd33) $display("[PASS] Case 3: 33=33");
        else          $error("[FAIL] Case Expected 33,Got %d",t_res);

        $display("---------------------------------------");
        $finish;
    end
endmodule