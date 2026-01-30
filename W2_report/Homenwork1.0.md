### 4-digit decimal counter
```
module top_module (
    input reset,
    input clk, 
    output [3:1] ena,
    output [15:0] d
    );
    
    always @(posedge clk) begin
        if(reset) begin
            d = 0;
            ena = 0;
        end
        else begin
            d[3:0] = d[3:0] + 1;
            ena[1] = (d[3:0] == 9) ? 1 : 0;
            if(d[3:0] == 10) begin
                d[3:0] = 0;
                d[7:4] = d[7:4] + 1;
            end
            ena[2] = ((d[7:4] == 9) && (d[3:0] == 9)) ? 1 : 0;
            if(d[7:4] == 10) begin
                d[7:4] = 0;
                d[11:8] = d[11:8] + 1;
            end
            ena[3] = ((d[11:8] == 9) && (d[7:4] == 9) && (d[3:0] == 9)) ? 1 : 0;
            if(d[11:8] == 10) begin
                d[11:8] = 0;
                d[15:12] = d[15:12] + 1;
            end
            if(d[15:12] == 10) begin
                d = 0;
            end
        end
    end

endmodule
```
问题一：忘记初始化d与ena

### Left/Right arithmetic shift by 1 or 8
```
module top_module(
    input clk,
    input ena,
    input load,
    input [1:0] amount,
    input [63:0] data,
    output reg [63:0] d
    ); 

    always @(posedge clk) begin
        if(load == 1)begin
            d = data;
        end
        else begin
            if(ena == 1) begin
                case(amount)
                    2'b00: d <= d << 1;
                    2'b01: d <= d << 8;
                    2'b10: begin
                        d <= d >> 1;  //先逻辑右移，高位变为0
                        if(d[63] == 1) begin
                            d[63] <= 1; //强制把新的最高位改为1
                        end
                    end
                    2'b11: begin
                        d <= d >> 8;
                        if(d[63] == 1) begin
                            d[63:56] <= {8{1'b1}};
                        end
                    end
                endcase
            end
        end
    end
    
endmodule
```
问题一：endcase漏写case
问题二：关于非阻塞赋值的注意事项
- **时序逻辑（Sequential Logic）**：凡是在 `always @(posedge clk)` 块里，**必须使用非阻塞赋值 (`<=`)**。
- **组合逻辑（Combinational Logic）**：凡是在 `always @(*)` 块里，**必须使用阻塞赋值 (`=`)**。

### Simple FSM 2 (synchronous reset)
```
module top_module(
    input clk,
    input reset,    
    input j,
    input k,
    output out
    ); //  

    parameter OFF = 0, ON = 1; 
    reg state, next_state;

    always @(*) begin
        // State transition logic
        case (state)
            ON: next_state <= k ? OFF : ON;
            OFF: next_state <= j ? ON : OFF;
        endcase
    end

    always @(posedge clk) begin
        // State flip-flops with synchronous reset
        if (reset) begin
            state <= OFF;
        end
        else begin
            state <= next_state;
        end
    end

    // Output logic
    // assign out = (state == ...);
    assign out = (state == ON);

endmodule
```
- **当前是 ON (1) 时**：
    - **看 K 输入**。
    - 如果 `k=1`，跳转到 `OFF`（清零/翻转）。
    - 如果 `k=0`，保持 `ON`（保持）。
        
- **当前是 OFF (0) 时**：
    - **看 J 输入**。
    - 如果 `j=1`，跳转到 `ON`（置位/翻转）。
    - 如果 `j=0`，保持 `OFF`（保持）。