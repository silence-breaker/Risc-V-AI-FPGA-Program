module tb_stream_accumulator;

  // 信号声明
  logic clk;
  logic rst_n;
  logic signed [15:0] t_data;
  logic t_valid;
  logic t_last;
  logic signed [31:0] t_result;
  logic t_res_valid;

  // 实例化设计模块
  stream_accumulator u_dut (
      .clk           (clk),
      .rst_n         (rst_n),
      .i_data        (t_data),
      .i_valid       (t_valid),
      .i_last        (t_last),
      .o_result      (t_result),
      .o_result_valid(t_res_valid)
  );

  // 时钟生成 (10ns 周期)
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end

  // 定义发送任务
  task send_packet(input int length, input int start_value, input int step);
    integer i;
    begin
      $display("[Time %0t] Sending Packet: Len=%0d, Start=%0d, Step=%0d", $time, length,
               start_value, step);
      for (i = 0; i < length; i++) begin
        @(posedge clk);  // 等待时钟上升沿
        t_valid <= 1'b1;
        t_data  <= 16'(start_value + i * step);

        if (i == length - 1) t_last <= 1'b1;
        else t_last <= 1'b0;
      end

      @(posedge clk);
      t_valid <= 1'b0;
      t_last  <= 1'b0;
      t_data  <= '0;
    end
  endtask

  // 主测试流程
  initial begin
    $display("===========================================");
    $display("   Testbench: Stream Accumulator Start");
    $display("===========================================");

    $dumpfile("stream_acc.vcd");
    $dumpvars(0, tb_stream_accumulator);

    rst_n   = 0;
    t_valid = 0;
    t_last  = 0;
    t_data  = 0;

    #30;
    rst_n = 1;
    #20;

    // --- Case 1: 标准测试 ---
    send_packet(4, 10, 10);

    // 修改检测逻辑：不再用 wait，而是等待时钟并在 valid 有效时检查
    // 这样可以避免仿真器的 delta-cycle 竞争问题
    while (t_res_valid == 0) @(posedge clk);

    if (t_result == 100) $display("[PASS] Case 1 (Standard): Result = 100");
    else $error("[FAIL] Case 1: Expected 100, Got %0d", t_result);

    #20;

    // --- Case 2: 单数据测试 ---
    send_packet(1, 55, 0);

    while (t_res_valid == 0) @(posedge clk);

    if (t_result == 55) $display("[PASS] Case 2 (Single): Result = 55");
    else $error("[FAIL] Case 2: Expected 55, Got %0d", t_result);

    #20;

    // --- Case 3: 背靠背传输 ---
    $display("[Time %0t] Starting Back-to-Back Test...", $time);

    // 包 A
    @(posedge clk);
    t_valid <= 1;
    t_data  <= 1;
    t_last  <= 0;
    @(posedge clk);
    t_valid <= 1;
    t_data  <= 1;
    t_last  <= 1;

    // 包 B
    @(posedge clk);
    t_valid <= 1;
    t_data  <= 10;
    t_last  <= 0;

    // 此时应该能检测到包A的结果 (Result=2)
    // 注意：因为我们是背靠背发，所以在发包B数据的同时，包A的结果有效
    if (t_res_valid && t_result == 2) $display("[PASS] Back-to-Back Part A: Result = 2");

    @(posedge clk);
    t_valid <= 1;
    t_data  <= 10;
    t_last  <= 1;

    @(posedge clk);
    t_valid <= 0;
    t_last  <= 0;

    // 检查包B的结果
    while (t_res_valid == 0) @(posedge clk);
    if (t_result == 20) $display("[PASS] Back-to-Back Part B: Result = 20");
    else $error("[FAIL] Back-to-Back Part B: Expected 20, Got %0d", t_result);

    #50;
    $display("===========================================");
    $finish;
  end

endmodule
