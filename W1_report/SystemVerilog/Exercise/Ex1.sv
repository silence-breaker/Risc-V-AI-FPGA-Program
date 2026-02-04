// 这是一个简单的测试模块，用于演示 SystemVerilog 的赋值特性
module test_vars;

    // 定义变量
    // 在 SystemVerilog 中，推荐使用 logic 代替 reg，但 reg 依然有效
    reg [7:0]  m_var1;
    reg [15:0] m_var2;

    initial begin
        // '1 是 SystemVerilog 的全 1 赋值语法
        // 它会根据左侧变量的位宽自动填充
        m_var1 = '1; // 结果为 8'hff
        m_var2 = '1; // 结果为 16'hffff

        // 打印结果
        // 注意：原代码中的 $$display 修正为 $display
        $display("----------------------------------------");
        $display("Simulation Result:");
        $display("m_var1 = 0x%0h", m_var1);
        $display("m_var2 = 0x%0h", m_var2);
        $display("----------------------------------------");
        
        // 结束仿真
        $finish;
    end

endmodule