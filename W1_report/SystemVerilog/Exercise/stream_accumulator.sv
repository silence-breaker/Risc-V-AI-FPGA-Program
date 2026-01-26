module stream_accumulator (
    input logic signed [15:0] i_data,
    input logic i_valid,
    input logic i_last,
    input logic clk,
    input logic rst_n,
    output logic signed [31:0] o_result,
    output logic o_result_valid
);
  logic signed [31:0] accumulator;
  always_ff @(posedge clk) begin : accu
    if (!rst_n) begin
      o_result <= '0;
      o_result_valid <= 1'b0;
      accumulator <= '0;
    end else begin
      o_result_valid <= 1'b0;  //默认输出无效
      if (i_valid) begin

        if (i_last) begin
          o_result_valid <= 1'b1;
          o_result <= accumulator + 32'(i_data);  //输出最终结果
          accumulator <= '0;  //清零累加器
        end else begin
          accumulator <= accumulator + 32'(i_data);  //累加
        end
      end
    end
  end
  //有一个问题最后一个信号valid和last同时是高电平，两个if语句分支会出现冲突，所以必须要加中间的寄存器保存状态
  //相当于内部计算，收到last信号后计算完成再刷新输出，否则输出不变
endmodule
