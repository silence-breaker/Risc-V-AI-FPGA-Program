module FSM2 (
    input  logic clk,
    input  logic reset,  // Synchronous reset to OFF
    input  logic j,
    input  logic k,
    output logic out
);

  //状态定义
  typedef enum logic [1:0] {
    OFF = 2'b00,
    ON  = 2'b01
  } state_t;
  state_t current_state, next_state;

  //时许逻辑
  always_ff @(posedge clk) begin
    if (reset) begin
      current_state <= OFF;
    end else begin
      current_state <= next_state;
    end
  end

  //组合逻辑决定下一个状态是什么
  always_comb begin
    unique case (current_state)
      OFF: begin
        if (j) begin
          next_state = ON;
        end else begin
          next_state = OFF;
        end
      end

      ON: begin
        if (k) begin
          next_state = OFF;
        end else begin
          next_state = ON;
        end
      end
      default: begin
        next_state = OFF;  //安全保底
      end
    endcase
  end

  //输出逻辑
  assign out = (current_state == ON) ? 1'b1 : 1'b0;

endmodule
