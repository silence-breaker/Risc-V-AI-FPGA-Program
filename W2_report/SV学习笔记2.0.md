```
1.26日开始
```
## Procedures
### Case Statement
```
// synthesis verilog_input_version verilog_2001
module top_module ( 
    input [2:0] sel, 
    input [3:0] data0,
    input [3:0] data1,
    input [3:0] data2,
    input [3:0] data3,
    input [3:0] data4,
    input [3:0] data5,
    output reg [3:0] out   );//

    always@(*) begin  // This is a combinational circuit
        case(sel)
            0 : out = data0;
            1 : out = data1;
            2 : out = data2;
            3 : out = data3;
            4 : out = data4;
            5 : out = data5;
            default : out = 0;
        endcase
    end

endmodule
```
为什么要加入default这个语句？
是 6、7 或其他非法值，输出一律设为 **0**。 这样消除了不确定性，避免了生成锁存器。

1. 端口定义分析
- **控制信号 (`sel`)**: `input [2:0] sel`
    - 这是一个 3 位宽的信号，可以表示 $0 \sim 7$ 共 8 种数值。    
- **数据输入 (`data0` ~ `data5`)**: `input [3:0] ...`
    - 共有 6 个输入通道。    
    - 每个通道宽 4 位（例如，可以传输十进制 0-15 的数）。  
- **数据输出 (`out`)**: `output reg [3:0] out`
    - 这是最终选中的结果。   
    - 定义为 `reg` 类型是因为它在 `always` 块中被赋值（这是 Verilog 语法规则，实际上生成的是组合逻辑电路，而非触发器）。    
 2. 核心逻辑分析 (`case` 语句)
代码使用了 `always @(*)` 配合 `case` 结构来描述选择逻辑：
- **选择逻辑**:
    - 当 `sel = 0` 时，电路连通 `data0` -> `out`。
    - 当 `sel = 1` 时，电路连通 `data1` -> `out`。
    - ...以此类推，直到 `sel = 5` 连通 `data5`。

### Priority Encoder
```
// synthesis verilog_input_version verilog_2001
module top_module (
    input [3:0] in,
    output reg [1:0] pos  );
    
    always @(*) begin
        case(in)
            4'b0000 : pos = 0;
            4'b0001 : pos = 0;
            4'b0010 : pos = 1;
            4'b0011 : pos = 0;
            4'b0100 : pos = 2;
            4'b0101 : pos = 0;
            4'b0110 : pos = 1;
            4'b0111 : pos = 0;
            4'b1000 : pos = 3;
            4'b1001 : pos = 0;
            4'b1010 : pos = 1;
            4'b1011 : pos = 0;
            4'b1100 : pos = 2;
            4'b1101 : pos = 0;
            4'b1110 : pos = 1;
            4'b1111 : pos = 0;
        endcase
    end

endmodule
```
4-2位优先编码器
- **只要第 0 位是 1 (`xxxx1`)**：
    - 看代码：`0001`, `0011`, `0101`, `0111`, `1001`, `1011`, `1101`, `1111`
    - 输出全是 `pos = 0`。
    - **含义**：不管高位是什么，只要最低位（第0位）是 1，就输出 0。
- **第 0 位是 0，且第 1 位是 1 (`xxx10`)**：
    - 看代码：`0010`, `0110`, `1010`, `1110`
    - **含义**：第 0 位没“抢答”，轮到第 1 位“抢答”。    
- **第 0、1 位都是 0，且第 2 位是 1 (`xx100`)**：
    - 看代码：`0100`, `1100`    
    - 输出全是 `pos = 2`。    
- **只有第 3 位是 1 (`1000`)**：
    - 输出 `pos = 3`。

### Priority Encoder With casez
```
module top_module (
    input [7:0] in,
    output reg [2:0] pos  );

    always @(*) begin
        casez(in)
            8'bzzzzzzz1 : pos = 0;
            8'bzzzzzz1z : pos = 1;
            8'bzzzzz1zz : pos = 2;
            8'bzzzz1zzz : pos = 3;
            8'bzzz1zzzz : pos = 4;
            8'bzz1zzzzz : pos = 5;
            8'bz1zzzzzz : pos = 6;
            8'b1zzzzzzz : pos = 7;
            default : pos = 0;
        endcase
    end
    
endmodule
```
通常的 `case` 语句要求完全匹配（0匹配0，1匹配1）。
`case` 语句（包括 `casez`）是**按顺序执行**的，也就是**从上往下**进行匹配，一旦找到第一个匹配项，就会执行并跳出，不再看后面的项。
让我们看看代码的顺序：
1. **第一行**：`8'bzzzzzzz1 : pos = 0;`
    - **含义**：它只看最低位 (`in[0]`) 是否为 `1`。前面的 7 位 (`zzzzzzz`) 是什么完全不关心。 
    - **结果**：只要 `in[0]` 是 1，不管高位有多少个 1，`pos` 都会被锁定为 `0`。   
2. **第二行**：`8'bzzzzzz1z : pos = 1;`
    - **含义**：如果代码执行到这一行，说明**第一行没匹配上**（即 `in[0]` 肯定是 0）。此时，它检查 `in[1]` 是否为 `1`。
    - **结果**：如果 `in[0]` 是 0 且 `in[1]` 是 1，`pos` 输出 `1`。

### Avoiding Latches（case的语句写法）
```
// synthesis verilog_input_version verilog_2001
module top_module (
    input [15:0] scancode,
    output reg left,
    output reg down,
    output reg right,
    output reg up  ); 
    
    always @(*) begin
        left = 0; down = 0; right = 0; up = 0;
        case(scancode)
            16'he06b : left = 1;
            16'he072 : down = 1;
            16'he074 : right = 1;
            16'he075 : up = 1;
            default : ;
        endcase
    end

endmodule
注意case的语句写法
```
![[Pasted image 20260130153505.png]]
![[Pasted image 20260130153543.png]]

## More Verilog features
### Conditional Ternary Operator
```
module top_module (
    input [7:0] a, b, c, d,
    output [7:0] min);//

    // assign intermediate_result1 = compare? true: false;
    wire [7:0] min_mid, min_mid1, min_mid2;
    assign min_mid = (a < b) ? a : b;
    assign min_mid1 = (c < min_mid) ? c : min_mid;
    assign min_mid2 = (d < min_mid1) ? d : min_mid1;
    assign min = min_mid2;

endmodule
```
它的功能是：比较四个 8位输入数 `a, b, c, d`，并输出其中**最小**的那个数。
**目前的链式结构（串行）：** 比较路径长度 = 3 个比较器延迟 (a/b -> c -> d)
**树形结构（并行 - 推荐写法）：**
```
wire [7:0] min_ab, min_cd;
assign min_ab = (a < b) ? a : b; // a,b 比较
assign min_cd = (c < d) ? c : d; // c,d 比较 (这里可以并行发生)
assign min    = (min_ab < min_cd) ? min_ab : min_cd; // 最后的胜者决赛
```
比较路径长度 = 2 个比较器延迟。当输入数据很多时，树形结构速度更快

### Reduction Operators
```
module top_module (

    input [7:0] in,

    output parity); 

    assign parity = ^ in[7:0];

endmodule
```

这段代码实现了一个 **8位奇偶校验位计算器 (8-bit Parity Generator/Checker)**。
它的核心功能是：计算输入 `in` 中有多少个 `1`，如果是**奇数个**，输出 `1`；如果是**偶数个**，输出 `0`
代码中的关键符号是 `^`（异或符），但注意它放在了变量的**前面**：
```
assign parity = ^ in[7:0];
```
这叫做 **单目归约异或 (Unary Reduction XOR)**。
它的意思不是“两个数做异或”，而是**把向量里所有的位，从头到尾进行异或操作**。

### Reduction: Even wider gates
```
module top_module( 
    input [99:0] in,
    output out_and,
    output out_or,
    output out_xor 
);
    assign out_and = & in[99:0];检查是否全为1
    assign out_or = | in[99:0];检查是否全为0
    assign out_xor = ^ in[99:0];检查1的个数是奇数个还是偶数个
endmodule
```

### Combinational for-loop: Vector reversal 2
```
module top_module( 
    input [99:0] in,
    output [99:0] out
);

    always @(*) begin
         for(integer i = 0; i < 100; i++)
            out[i] = in[99 - i];
    end
    
endmodule
```
- **当 i = 0 时**： `out[0] = in[99 - 0]` -> `out[0] = in[99]` (输入的**最高位**，变成了输出的**最低位**)
- **当 i = 1 时**： `out[1] = in[99 - 1]` -> `out[1] = in[98]`
- ... (中间过程) ...
- **当 i = 99 时**： `out[99] = in[99 - 99]` -> `out[99] = in[0]` (输入的**最低位**，变成了输出的**最高位**)

### Combinational for-loop: 255-bit population counts
```
module top_module( 
    input [254:0] in,
    output [7:0] out );

    always @(*) begin
        out = 0;
        for(int i = 0; i < 255; i++) begin
            if(in[i])
                out = out + 1;
            else
                out = out + 0;
        end
    end
    
endmodule
```

- **`input [254:0] in`**： 这是一个 255 位宽的巨大输入向量
- **`always @(*)`**： 这表示这是一个**组合逻辑**电路。只要输入 `in` 变了，里面的代码就会立即重新计算一遍。
- **`out = 0;`**： **初始化**。在每次计算开始前，先把计数器清零。这是组合逻辑循环累加的标准写法，防止生成锁存器。
- **`for(int i = 0; i < 255; i++)`**： 循环遍历输入的每一位（从第 0 位到第 254 位）。
- **`if(in[i]) out = out + 1;`**： 如果当前位 `in[i]` 是 `1`，就把结果 `out` 加 1。

### Combinational for-loop: 100-bit binary adder 2
```
module top_module(
    input [99:0] a,
    input [99:0] b,
    input cin,
    output reg [99:0] cout,
    output reg [99:0] sum
);

    integer i;

    always @(*) begin
        // 第 0 位的处理（使用外部输入 cin）
        // 对应原代码中的 assign 语句，但在 always 块中改为阻塞赋值
        cout[0] = a[0] & b[0] | a[0] & cin | b[0] & cin;
        sum[0]  = a[0] ^ b[0] ^ cin;

        // 第 1 到 99 位的处理（使用上一位的进位 cout[i-1]）
        for (i = 1; i < 100; i = i + 1) begin
            cout[i] = a[i] & b[i] | a[i] & cout[i-1] | b[i] & cout[i-1];
            sum[i]  = a[i] ^ b[i] ^ cout[i-1];
        end
    end

endmodule
```
 **核心逻辑：全加器 (Full Adder)**
代码中的每一位计算都遵循全加器的公式：
- **Sum (和)** = $A \oplus B \oplus C_{in}$
    - 代码对应：`sum[i] = a[i] ^ b[i] ^ cout[i-1];` 
- **Cout (进位)** = $(A \cdot B) + (A \cdot C_{in}) + (B \cdot C_{in})$
    - 代码对应：`cout[i] = a[i] & b[i] | a[i] & cout[i-1] | b[i] & cout[i-1];`

### Combinational for-loop: 100-bit BCD adder 
```
module top_module( 
    input [399:0] a, b,
    input cin,
    output cout,
    output [399:0] sum );
    
    wire [399:0] cout_tmp;
    bcd_fadd fadd(.a(a[3:0]), .b(b[3:0]), .cin(cin), .cout(cout_tmp[0]),.sum(sum[3:0]));
    assign cout = cout_tmp[396];
    
    generate
        genvar i;
        for(i = 4; i < 400; i=i+4) begin : adder
            bcd_fadd fadd(.a(a[i+3:i]), .b(b[i+3:i]), .cin(cout_tmp[i-4]), .cout(cout_tmp[i]),.sum(sum[i+3:i]));
        end
    endgenerate

endmodule
```

这个模块实际上是在做 **100 个十进制数字** 的加法运算。

```
generate
    genvar i;
    for(i = 4; i < 400; i=i+4) begin : adder
        bcd_fadd fadd(.a(a[i+3:i]), ... .cin(cout_tmp[i-4]), .cout(cout_tmp[i]), ...);
    end
endgenerate
```
- **`generate`**：这是 Verilog 中用来批量生成硬件的语法。
- **`i=i+4`**：步长为 4，因为每个 BCD 数字占 4 位。
- **连接逻辑（进位链）**：
    - 当前模块的输入进位 `.cin` 来自上一模块的输出 `.cin(cout_tmp[i-4])`。
    - 当前模块的输出进位 `.cout` 存入当前索引 `.cout(cout_tmp[i])`。
- **作用**：这就像搭积木一样，把剩下 99 个加法器一个接一个地串联起来。

## Basic Gates
### GND
```
直接将对应的端口赋值到0就可以了
```



