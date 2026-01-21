// ---------------------------------------------------------
// 步骤 1: 定义数据类型
// ---------------------------------------------------------
package my_types_pkg;
    // TODO 1: 使用 typedef enum 定义一个叫 tern_t 的类型
    // 包含 W_ZERO, W_POS, W_NEG 三个成员
    // 提示：enum logic [1:0] { ... } ...;
    
    typedef enum logic [1:0] {
        // 在这里填空
        W_ZERO = 2'b00,
        W_POS  = 2'b01,
        W_NEG  = 2'b10
    } tern_t;
endpackage

// 引入刚才定义的包，这样下面就能直接用 tern_t 了
import my_types_pkg::*;

module ternary_mac_unit (
    // 输入端口
    input  logic [7:0]  i_data,       // 输入激活值 (比如 int8)
    input  tern_t       i_weight,     // 1.58-bit 权重 (使用我们定义的类型)
    input  logic [15:0] i_current_sum,// 当前的累加和
    
    // 输出端口
    output logic [15:0] o_next_sum    // 下一拍的累加和
);

    // 中间信号：用于处理符号扩展
    logic signed [15:0] data_extended;

    // ---------------------------------------------------------
    // 步骤 2: 组合逻辑实现
    // ---------------------------------------------------------
    always_comb begin
        // TODO 2: 符号扩展
        // 这里的 i_data 是 8位的，但加法结果是 16位的。
        // 如果 i_data 是负数(比如 -5)，直接补0扩展会变成正的大数。
        // 必须用符号扩展。
        // 提示：使用 $signed()
        
        data_extended = $signed(i_data);

        // TODO 3: 实现无乘法逻辑
        // 根据 i_weight 的值，决定是加、减 还是 不变
        // 提示：使用 unique case (i_weight)
        
        unique case (i_weight)
            W_POS: begin
                // 如果权重是 +1: 结果 = 当前和 + 数据
                o_next_sum = i_current_sum + data_extended;
            end
            
            W_NEG: begin
                // TODO 3.1: 如果权重是 -1: 结果 = ?
                o_next_sum = i_current_sum-data_extended;
            end
            
            W_ZERO: begin
                // TODO 3.2: 如果权重是 0: 结果 = ?
                o_next_sum = i_current_sum;
            end
            
            default: o_next_sum = i_current_sum; // 安全保底
        endcase
    end
//实际上这个累加的过程就是矩阵乘法
endmodule