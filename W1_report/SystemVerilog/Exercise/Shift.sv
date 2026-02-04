module Shift (
    input logic clk,
    input logic load,
    input logic ena,
    input logic [1:0] amount,
    input logic [63:0] data,
    output logic [63:0] q
);

  always_ff @(posedge clk) begin
    if (load) begin
      q <= data;
    end else if (ena) begin
      unique case (amount)
        2'b00:   q <= {q[62:0], 1'b0};  //逻辑左移1位
        2'b01:   q <= {q[55:0], 8'd0};  //逻辑左移8位
        2'b10:   q <= {q[63], q[63:1]};  //算术右移1位
        2'b11:   q <= {{8{q[63]}}, q[63:8]};  //算术右移8位
        default: q <= q;  //安全保底
      endcase
    end

  end

endmodule
