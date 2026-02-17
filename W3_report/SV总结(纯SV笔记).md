# SV笔记汇总

```
2026年1月19日
```

## Basic

### Zero

```systemverilog
module top_module(
    output logic zero
);
	// Module body starts after semicolon
	assign zero = 1'b0;
endmodule
```

**SystemVerilog (SV) 改进点：**
- **`logic` 类型**: SV 引入了 unified 数据类型 `logic`。在 Verilog 中，你必须区分 `wire`（用于 assign）和 `reg`（用于 always）。在 SV 中，除了多驱动信号（如双向总线）必须用 `wire` 外，其他情况一律推荐使用 `logic`。它既可以被 `assign` 赋值，也可以在 `always` 块中赋值。

### Simple wire

```systemverilog
module top_module( input logic in, output logic out );
	//这里是你要写的代码
	  assign out = in; 
endmodule
```

**语法解释**
- **`input/output logic`**: 显式声明端口类型为 logic，这是一种良好的编码习惯。

### Wire4

```systemverilog
module top_module( 
    input logic a,b,c,
    output logic w,x,y,z );
	assign w=a;
    assign x=b;
    assign y=b;
    assign z=c;
endmodule
```

### Inverter

```systemverilog
module top_module( input logic in, output logic out );
    assign out = ~in;
endmodule
```

### Andgate

```systemverilog
module top_module( 
    input logic a, 
    input logic b, 
    output logic out );
	assign out = a & b;
endmodule
```

### Norgate

```systemverilog
module top_module( 
    input logic a, 
    input logic b, 
    output logic out );
    assign out = ~(a | b);
endmodule
```

### XNORgate(同或门)

```systemverilog
module top_module( 
    input logic a, 
    input logic b, 
    output logic out );
    assign out = ~(a ^ b);
endmodule
```

### Declare wires

```systemverilog
`default_nettype none
module top_module(
    // 1. 端口声明：显式使用 logic 类型
    input  logic a,
    input  logic b,
    input  logic c,
    input  logic d,
    output logic out,
    output logic out_n
);  
    // 2. 内部信号：用 logic 替代 wire/reg
    logic wire1, wire2, wire3;
  
    // 3. 逻辑赋值：assign 语句在 SV 中依然完全适用
    assign wire1 = a & b;
    assign wire2 = c & d;
    assign wire3 = wire1 | wire2;
  
    assign out   = wire3;
    assign out_n = ~wire3;
endmodule
```

**SV 与 Verilog 的区别：**
- **`logic` vs `wire`**: 在 Verilog 中，内部连线通常声明为 `wire`，而在 SV 中，内部信号通常声明为 `logic`。这避免了你需要思考"这个信号是在 always 块里赋值还是用 assign 赋值"的麻烦。

## Vectors

### vector0

```systemverilog
module top_module ( 
    input logic [2:0] vec,
    output logic [2:0] outv,
    output logic o2,
    output logic o1,
    output logic o0  ); 

    assign outv = vec;
    assign o0 = outv[0];
    assign o1 = outv[1];
    assign o2 = outv[2];
  
endmodule
```

**SV 特性**
- **类型声明**: `input logic [2:0]` 替代了 `input wire [2:0]`。

### Vector in more details

构建一个组合电路，将输入半字（16位，[15：0]）拆分为低[7：0]和高[15：8]字节。

```systemverilog
`default_nettype none     
module top_module( 
    input logic [15:0] in,
    output logic [7:0] out_hi,
    output logic [7:0] out_lo );

    assign out_hi = in[15:8];
    assign out_lo = in[7:0];
  
endmodule
```

### Vector part select

```systemverilog
module top_module( 
    input logic [31:0] in,
    output logic [31:0] out );

    assign out = {in[7:0], in[15:8], in[23:16], in[31:24]};

endmodule
```

### Vectorgates

```systemverilog
module top_module( 
    input logic [2:0] a,
    input logic [2:0] b,
    output logic [2:0] out_or_bitwise,
    output logic out_or_logical,
    output logic [5:0] out_not
);

    assign out_or_bitwise = a | b;
    assign out_or_logical = a || b;
    assign out_not[5:3] = ~b;
    assign out_not[2:0] = ~a;
  
endmodule
```

### Gates4

```systemverilog
module top_module( 
    input logic [3:0] in,
    output logic out_and,
    output logic out_or,
    output logic out_xor
);

    assign out_and = &in; // SV 也可以使用归约运算符简化书写
    assign out_or = |in;
    assign out_xor = ^in;
  
endmodule
```

### Vector concatenation operator

"{}"这个符号的意思是把输入的不同信号进行拼接

```systemverilog
module top_module (
    input logic [4:0] a, b, c, d, e, f,
    output logic [7:0] w, x, y, z );

    assign {w, x, y, z} = {a, b, c, d, e, f, 2'b11};
  
endmodule
```

### vector reversal1

```systemverilog
module top_module( 
    input logic [7:0] in,
    output logic [7:0] out
);
    // 也可以使用流操作符(streaming operator) {<<{}} 来实现翻转（高级SV用法）
    // assign out = {<<{in}}; 
    assign out = {in[0], in[1], in[2], in[3], in[4], in[5], in[6], in[7]};
endmodule
```

### Replication operator

```systemverilog
module top_module (
    input logic [7:0] in,
    output logic [31:0] out );

    // 符号扩展
    assign out = {{24{in[7]}}, in};

endmodule
```

### more replication

```systemverilog
module top_module (
    input logic a, b, c, d, e,
    output logic [24:0] out );

    assign out[24:20] = ~ {5{a}} ^ {a, b, c, d, e};
    assign out[19:15] = ~ {5{b}} ^ {a, b, c, d, e};
    assign out[14:10] = ~ {5{c}} ^ {a, b, c, d, e};
    assign out[9:5] = ~ {5{d}} ^ {a, b, c, d, e};
    assign out[4:0] = ~ {5{e}} ^ {a, b, c, d, e};

endmodule
```

## Modules Hierarchy

### modules

```systemverilog
module top_module ( input logic a, input logic b, output logic out );
    
    // SV 允许 .name 的隐式连接方式，如果端口名和信号名一致
    // mod_a instance1(.*); // 自动匹配所有同名端口
    
    mod_a instance1(.out(out), .in1(a), .in2(b));
endmodule
```

### Connecting ports by position

```systemverilog
	mod_a instance1(out1, out2, a, b, c, d);
```
注：SV 中通常强烈建议使用按名称连接 (`.name`) 以避免顺序错误，且 SV 提供了 `.name` 和 `.*` 的简便写法。

### Connecting ports by name

```systemverilog
    mod_a instance1(.in1(a), .in2(b), .in3(c), .in4(d), .out1(out1), .out2(out2));
```

### Three modules

```systemverilog
module top_module ( input logic clk, input logic d, output logic q );
    logic q1, q2;
    my_dff instance1(.clk(clk), .d(d), .q(q1));
    my_dff instance2(.clk(clk), .d(q1), .q(q2));
    my_dff instance3(.clk(clk), .d(q2), .q(q));
endmodule
```

### modules and vectors

```systemverilog
module top_module ( 
    input logic clk, 
    input logic [7:0] d, 
    input logic [1:0] sel, 
    output logic [7:0] q 
);
  
    logic [7:0] q1, q2, q3;
    my_dff8 instance1(.clk(clk), .d(d), .q(q1));
    my_dff8 instance2(.clk(clk), .d(q1), .q(q2));
    my_dff8 instance3(.clk(clk), .d(q2), .q(q3));
  
    always_comb begin
        case(sel)
            0 : q = d;
            1 : q = q1;
            2 : q = q2;
            3 : q = q3;
        endcase
    end
endmodule
```

**SV 改进：always_comb**
- **`always_comb`**: 替代了 `always @(*)`。
    - 它显式告诉工具这是一个组合逻辑块。
    - 它会自动处理敏感列表。
    - 它会在仿真 0 时刻自动执行一次，防止未初始化。

### Adder1

```systemverilog
module top_module(
    input logic [31:0] a,
    input logic [31:0] b,
    output logic [31:0] sum
);
  
    logic cin1, cout1, cout2;
    logic [15:0] sum1, sum2;
    assign cin1 = '0; // '0 是 SV 中表示全0的一种简便写法，适配任意位宽
  
    add16 instance1(.a(a[15:0]), .b(b[15:0]), .cin(cin1), .cout(cout1), .sum(sum1));
    add16 instance2(.a(a[31:16]), .b(b[31:16]), .cin(cout1), .cout(cout2), .sum(sum2));
  
    assign sum = {sum2, sum1};

endmodule
```

### Adder2

```systemverilog
module top_module (
    input logic [31:0] a,
    input logic [31:0] b,
    output logic [31:0] sum
);
    logic cin1, cout1, cout2;
    logic [15:0] sum1, sum2;
    assign cin1 = '0;
    add16 instance1(.a(a[15:0]), .b(b[15:0]), .cin(cin1), .cout(cout1), .sum(sum1));
    add16 instance2(.a(a[31:16]), .b(b[31:16]), .cin(cout1), .cout(cout2), .sum(sum2));
  
    assign sum = {sum2, sum1};

endmodule

module add1 ( input logic a, input logic b, input logic cin, output logic sum, output logic cout );
    assign {cout, sum} = a + b + cin;
endmodule
```

### Carry-select adder

```systemverilog
module top_module(
    input logic [31:0] a,
    input logic [31:0] b,
    output logic [31:0] sum
);

    logic cin1, cout1, cin2, cout2, cin3, cout3;
    logic [15:0] sum1, sum2, sum3, sum_h;
    
    assign cin1 = '0;
    assign cin2 = '0;
    assign cin3 = '1; // '1 表示全1，这里即 1位1
  
    add16 instance1(.a(a[15:0]), .b(b[15:0]), .cin(cin1), .cout(cout1), .sum(sum1));
    add16 instance2(.a(a[31:16]), .b(b[31:16]), .cin(cin2), .cout(cout2), .sum(sum2));
    add16 instance3(.a(a[31:16]), .b(b[31:16]), .cin(cin3), .cout(cout3), .sum(sum3));
  
    always_comb begin
        case(cout1)
            0 : sum_h = sum2;
            1 : sum_h = sum3;
        endcase
    end
  
    assign sum = {sum_h, sum1};
  
endmodule
```

### Adder-subtractor

```systemverilog
module top_module(
    input logic [31:0] a,
    input logic [31:0] b,
    input logic sub,
    output logic [31:0] sum
);
    logic cout1, cout2;
    logic [15:0] sum1, sum2;
    logic [31:0] b_xor;
  
    always_comb begin
        if(sub)
            b_xor = ~b;
        else
            b_xor = b;
    end
  
    add16 instance1(.a(a[15:0]), .b(b_xor[15:0]), .cin(sub), .cout(cout1), .sum(sum1));
    add16 instance2(.a(a[31:16]), .b(b_xor[31:16]), .cin(cout1), .cout(cout2), .sum(sum2));
  
    assign sum = {sum2, sum1};
  
endmodule
```

## Procedures

### Alwaysblock1(combinational)

```systemverilog
module top_module(
    input logic a, 
    input logic b,
    output logic out_assign,
    output logic out_alwaysblock
);

    assign out_assign = a & b;
    always_comb out_alwaysblock = a & b;
  
endmodule
```

**SV 核心对比：**

1.  **Continuous Assignment (`assign`)**:
    - 适用于简单的组合逻辑。
    - 左侧只能是 `wire` (Verilog) 或 `logic` (SV)。

2.  **Procedural Assignment (`always_comb`)**:
    - 替代了 `always @(*)`。
    - **优点**: 语义更清晰，工具会自动检查是否偶然生成了 latch（锁存器），如果有会报错。
    - 左侧在 SV 中使用 `logic`。

### Alwaysblock2(clocked)

```systemverilog
module top_module(
    input logic clk,
    input logic a,
    input logic b,
    output logic out_assign,
    output logic out_always_comb,
    output logic out_always_ff   );

    assign out_assign = a ^ b;
    always_comb out_always_comb = a ^ b;
    always_ff @(posedge clk) out_always_ff <= a ^ b;
    
endmodule
```

**SV 的三大 Always 块：**
- **`always_comb`**: 组合逻辑。替代 `always @(*)`。
- **`always_ff`**: 时序逻辑（触发器）。替代 `always @(posedge clk)`。如果这里面的逻辑不能被综合成触发器（例如没有时钟沿控制），编译器会报错。
- **`always_latch`**: 锁存器逻辑。替代 `always @(*)`（当需要 latch 时）。

### IF statement

```systemverilog
module top_module(
    input logic a,
    input logic b,
    input logic sel_b1,
    input logic sel_b2,
    output logic out_assign,
    output logic out_always   ); 

    assign out_assign = (sel_b1 && sel_b2) ? b : a;
    always_comb out_always = (sel_b1 && sel_b2) ? b : a;
  
endmodule
```

### IF statement latches

```systemverilog
module top_module (
    input logic cpu_overheated,
    output logic shut_off_computer,
    input logic arrived,
    input logic gas_tank_empty,
    output logic keep_driving  ); 

    always_comb begin
        if (cpu_overheated)
           shut_off_computer = 1;
        else
            shut_off_computer = 0;
    end

    always_comb begin
        if (~arrived)
            keep_driving = ~gas_tank_empty;
        else
            keep_driving = 0;
    end

endmodule
```

**避免 Latch 的黄金法则：**
在 `always_comb` 块中，**输出在任何 `if/else` 分支下都必须被赋值**。如果使用了 `always_comb` 而代码逻辑产生了锁存器（例如漏掉了 else），优秀的 SV 编译器会发出警告或错误。

### Case Statement

```systemverilog
module top_module ( 
    input logic [2:0] sel, 
    input logic [3:0] data0,
    input logic [3:0] data1,
    input logic [3:0] data2,
    input logic [3:0] data3,
    input logic [3:0] data4,
    input logic [3:0] data5,
    output logic [3:0] out   );

    always_comb begin  
        case(sel)
            0 : out = data0;
            1 : out = data1;
            2 : out = data2;
            3 : out = data3;
            4 : out = data4;
            5 : out = data5;
            default : out = '0; 
        endcase
    end

endmodule
```
注意：使用 `always_comb`。

### Priority Encoder

```systemverilog
module top_module (
    input logic [3:0] in,
    output logic [1:0] pos  );
  
    // unique case 或 priority case 是 SV 的新特性
    // priority case 显式告诉工具这是一个有优先级的匹配（虽然 case 本身就是顺序的）
    always_comb begin
        priority case(in)
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

### Priority Encoder With casez

```systemverilog
module top_module (
    input logic [7:0] in,
    output logic [2:0] pos  );

    always_comb begin
        priority casez(in)
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

### Avoiding Latches（case的语句写法）

```systemverilog
module top_module (
    input logic [15:0] scancode,
    output logic left,
    output logic down,
    output logic right,
    output logic up  ); 
  
    always_comb begin
        // 推荐做法：在 case 前设置默认值，这样最安全，不用写 default 也不会生成 latch
        left = 0; down = 0; right = 0; up = 0;
        
        case(scancode)
            16'he06b : left = 1;
            16'he072 : down = 1;
            16'he074 : right = 1;
            16'he075 : up = 1;
        endcase
    end

endmodule
```

## More Verilog features

### Conditional Ternary Operator

```systemverilog
module top_module (
    input logic [7:0] a, b, c, d,
    output logic [7:0] min);

    logic [7:0] min_ab, min_cd;
    
    // SV 同样支持三元运算符
    assign min_ab = (a < b) ? a : b; 
    assign min_cd = (c < d) ? c : d; 
    assign min    = (min_ab < min_cd) ? min_ab : min_cd; 

endmodule
```

### Reduction Operators

```systemverilog
module top_module (
    input logic [7:0] in,
    output logic parity); 

    assign parity = ^in; // 对整个向量进行归约异或

endmodule
```

### Reduction: Even wider gates

```systemverilog
module top_module( 
    input logic [99:0] in,
    output logic out_and,
    output logic out_or,
    output logic out_xor 
);
    assign out_and = &in;
    assign out_or = |in;
    assign out_xor = ^in;
endmodule
```

### Combinational for-loop: Vector reversal 2

```systemverilog
module top_module( 
    input logic [99:0] in,
    output logic [99:0] out
);

    always_comb begin
         // SV 允许在 for 循环内部直接声明循环变量
         for(int i = 0; i < 100; i++)
            out[i] = in[99 - i];
    end
  
endmodule
```

### Combinational for-loop: 255-bit population counts

```systemverilog
module top_module( 
    input logic [254:0] in,
    output logic [7:0] out );

    always_comb begin
        out = '0; 
        for(int i = 0; i < 255; i++) begin
            if(in[i])
                out++; // SV 支持自增运算符 ++
        end
    end
  
endmodule
```

**SV 特性：**
- **自增/自减**: `out++`。
- **循环变量**: `for(int i...)`。

### Combinational for-loop: 100-bit binary adder 2

```systemverilog
module top_module(
    input logic [99:0] a,
    input logic [99:0] b,
    input logic cin,
    output logic [99:0] cout,
    output logic [99:0] sum
);

    always_comb begin
        // 第 0 位
        cout[0] = a[0] & b[0] | a[0] & cin | b[0] & cin;
        sum[0]  = a[0] ^ b[0] ^ cin;

        for (int i = 1; i < 100; i++) begin
            cout[i] = a[i] & b[i] | a[i] & cout[i-1] | b[i] & cout[i-1];
            sum[i]  = a[i] ^ b[i] ^ cout[i-1];
        end
    end

endmodule
```

### Combinational for-loop: 100-bit BCD adder

```systemverilog
module top_module( 
    input logic [399:0] a, b,
    input logic cin,
    output logic cout,
    output logic [399:0] sum );
  
    logic [399:0] cout_tmp;
    
    // 初始化第一个
    bcd_fadd fadd(.a(a[3:0]), .b(b[3:0]), .cin(cin), .cout(cout_tmp[0]),.sum(sum[3:0]));
    assign cout = cout_tmp[396];
    
    // SV 中的 generate 块，通常可以直接写 for 循环（如果编译器支持），
    // 但标准的 generate 语法依然推荐保留以增强兼容性
    generate
        for(genvar i = 4; i < 400; i=i+4) begin : adder
            bcd_fadd fadd(.a(a[i+3:i]), .b(b[i+3:i]), .cin(cout_tmp[i-4]), .cout(cout_tmp[i]),.sum(sum[i+3:i]));
        end
    endgenerate

endmodule
```

## Basic Gates

### GND

```systemverilog
// 赋值为 '0 即可
assign out = '0;
```
