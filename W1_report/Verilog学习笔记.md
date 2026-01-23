```
2026年1月19日
```
## Basic
### Zero
```
module top_module(
    output zero
);
	// Module body starts after semicolon
	assign zero = 1'b0;
endmodule
```
简单来说，这段代码的功能是：**创建一个模块，它的输出端口 `zero` 被永久固定为低电平（逻辑 0）。**
下面是详细的代码拆解，特别是 `1'b0` 的含义：
**1. 核心语句：`assign zero = 1'b0;`**
这行代码的意思是：把数值 `0` 持续地赋值给输出端口 `zero`。
最关键的是右边的 **`1'b0`**，这是 Verilog 中表示数字的标准格式，读作 **"1 bit binary 0"**（1位二进制的0）。它的结构如下：
- **`1` (位宽)**: 表示这个数占用 **1个比特** (1 bit) 的宽度。
- **`'` (分隔符)**: 固定写法，用来隔开位宽和进制。
- **`b` (进制)**: 表示 **二进制 (binary)**。如果是 `d` 则是十进制，`h` 是十六进制。
- **`0` (数值)**: 表示具体的数值是 **0**。
**举一反三：**
- `1'b1`：表示 1位的二进制数 1（高电平）。
- `3'b101`：表示 3位的二进制数 101（十进制的5）。

###  Simple wire
```
module top_module( input in, output out );
	//这里是你要写的代码
	  assign out = in; 
endmodule
```
**语法解释**
1. **`assign`**: 这是 Verilog 中用于描述组合逻辑（Combinational Logic）最基础的关键字。它表示“连续赋值”，只要右边的值发生变化，左边的值会立刻跟着变化，就像物理上的一根导线一样。
2. **方向性**: Verilog 的赋值是有方向的。
    - **左边 (`out`)**: 是接收端（Sink），也就是输出端口。    
    - **右边 (`in`)**: 是驱动源（Source/Driver），也就是输入端口。    
    - **逻辑**: 把 `in` 的信号驱动到 `out` 上。    
3. **分号 `;`**: 千万别忘了每条语句结束都要加分号。

### Wire4
```
module top_module( 
    input a,b,c,
    output w,x,y,z );
	assign w=a;
    assign x=b;
    assign y=b;
    assign z=c;
endmodule
```
简单的赋值语句

### Inverter
```
module top_module( input in, output out );
    assign out = ~in;
endmodule
```
~表示反向

### Andgate
```
module top_module( 
    input a, 
    input b, 
    output out );
	assign out = a & b;
endmodule
```

### Norgate
```
module top_module( 
    input a, 
    input b, 
    output out );
    assign out = ~(a | b);
endmodule
```

### XNORgate(同或门)
```
module top_module( 
    input a, 
    input b, 
    output out );
    assign out = ~(a ^ b);
endmodule
```

### Declare wires（从这里开始有SV和verilog的区分）
```
//verilog的语法

`default_nettype none
module top_module(
    input a,
    input b,
    input c,
    input d,
    output out,
    output out_n   ); 
    
    wire wire1, wire2, wire3;
    assign wire1 = a & b;
    assign wire2 = c & d;
    assign wire3 = wire1 | wire2;
    assign out = wire3;
    assign out_n = ~wire3;
    
endmodule

//system verilog的语法

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
    // 2. 内部信号：用 logic 替代 wire
    logic wire1, wire2, wire3;
    
    // 3. 逻辑赋值：assign 语句在 SV 中依然完全适用
    assign wire1 = a & b;
    assign wire2 = c & d;
    assign wire3 = wire1 | wire2;
    
    assign out   = wire3;
    assign out_n = ~wire3;
endmodule
```


## Vectors
### vector0
```
module top_module ( 
    input wire [2:0] vec,
    output wire [2:0] outv,
    output wire o2,
    output wire o1,
    output wire o0  ); // Module body starts after module declaration

    assign outv = vec;
    assign o0 = outv[0];
    assign o1 = outv[1];
    assign o2 = outv[2];
    
endmodule
```
输出的图片为：
![[Pasted image 20260120160407.png]]

**1. 向量定义 `[2:0]`**
Verilog
```
input wire [2:0] vec
```
- 这表示 `vec` 不是一根线，而是 **3根线捆在一起**。
- `[2:0]` 表示位宽是 3 位，下标从 2 到 0（即 `vec[2]`, `vec[1]`, `vec[0]`）。 
- 通常 `[0]` 是最低位（LSB），`[2]` 是最高位（MSB）。
**2. 整体赋值**
```
assign outv = vec;
```
- **含义**：把输入总线 `vec` 原封不动地传给输出总线 `outv`。
- **比喻**：相当于把一根 3 芯的电缆直接延长出去了。

**3. 位选择（Bit-select）/ 拆分**
```
assign o0 = outv[0];
assign o1 = outv[1];
assign o2 = outv[2];
```
- **含义**：这是把“一束线”拆开。
    - `outv[0]` 取出第 0 位，连到单根线 `o0`。    
    - `outv[1]` 取出第 1 位，连到单根线 `o1`。    
    - `outv[2]` 取出第 2 位，连到单根线 `o2`。


### Vector in more details
构建一个组合电路，将输入半字（16位，[15：0]）拆分为低[7：0]和高[15：8]字节。
```
`default_nettype none     // Disable implicit nets. Reduces some types of bugs.
module top_module( 
    input wire [15:0] in,
    output wire [7:0] out_hi,
    output wire [7:0] out_lo );

    assign out_hi = in[15:8];
    assign out_lo = in[7:0];
    
endmodule
```

### Vector part select
```
module top_module( 
    input [31:0] in,
    output [31:0] out );//

    // assign out[31:24] = ...;
    assign out = {in[7:0], in[15:8], in[23:16], in[31:24]};

endmodule
```
**代码逻辑拆解**
让我们假设输入信号 `in` 是一个 32 位的十六进制数： `in = 32'h11223344`
这个数由 4 个字节组成：
- **Byte 3 (高位)**: `in[31:24]` = `0x11`
    
- **Byte 2**: `in[23:16]` = `0x22`
    
- **Byte 1**: `in[15:8]` = `0x33`
    
- **Byte 0 (低位)**: `in[7:0]` = `0x44`
- 
代码中的赋值语句是：
```
assign out = { in[7:0], in[15:8], in[23:16], in[31:24] };
```
这意味着 `out` 的构造顺序如下：
1. **最高 8 位 (out[31:24])** 变成了 `in[7:0]` (原来的最低字节，即 `0x44`)。
2. **次高 8 位 (out[23:16])** 变成了 `in[15:8]` (原来的次低字节，即 `0x33`)。
3. **次低 8 位 (out[15:8])** 变成了 `in[23:16]` (原来的次高字节，即 `0x22`)。
4. **最低 8 位 (out[7:0])** 变成了 `in[31:24]` (原来的最高字节，即 `0x11`)。

### Vectorgates
```
module top_module( 
    input [2:0] a,
    input [2:0] b,
    output [2:0] out_or_bitwise,
    output out_or_logical,
    output [5:0] out_not
);

    assign out_or_bitwise = a | b;
    assign out_or_logical = a || b;
    assign out_not[5:3] = ~b;
    assign out_not[2:0] = ~a;
    
endmodule
```
![[Pasted image 20260120163311.png]]
- **`|`** 是搞**硬件**的（每一位都算）。
- **`||`** 是搞**逻辑**的（只看是不是0，结果只有1位）。
- **`out_not`** 展示了如何分别给一个长向量的高位和低位赋值。

### Gates4
```
module top_module( 
    input [3:0] in,
    output out_and,
    output out_or,
    output out_xor
);

    assign out_and = in[0] & in[1] & in[2] & in[3];
    assign out_or = in[0] | in[1] | in[2] | in[3];
    assign out_xor = in[0] ^ in[1] ^ in[2] ^ in[3];
    
endmodule
```


### Vector concatenation operator
"{}"这个符号的意思是把输入的不同信号进行拼接
```
module top_module (
    input [4:0] a, b, c, d, e, f,
    output [7:0] w, x, y, z );//

    // assign { ... } = { ... };
    // assign {w[7:0], x[7:0], y[7:0], z[7:0]} = {a[4:0], b[4:0], c[4:0], d[4:0], e[4:0], f[4:0], 2'b11};
    assign {w, x, y, z} = {a, b, c, d, e, f, 2'b11};
    
endmodule
```
**右边 (Right-Hand Side): 数据的来源**
`{a, b, c, d, e, f, 2'b11}`
这一步将所有输入信号按顺序首尾相连，并在最后加上二进制的 `11`。
- `a` (5位)  
- `b` (5位)  
- `c` (5位)   
- `d` (5位)   
- `e` (5位)  
- `f` (5位)  
- `2'b11` (2位常数)   
- **总计:** $5 + 5 + 5 + 5 + 5 + 5 + 2 = \mathbf{32} \text{ 位}$。
 **左边 (Left-Hand Side): 数据的去向**
`{w, x, y, z}`
这一步将右边生成的 32 位数据流，从高位到低位依次“灌入”到输出信号中。
- `w` (8位) - 接收最高的 8 位
- `x` (8位) - 接收接下来的 8 位  
- `y` (8位) - 接收接下来的 8 位 
- `z` (8位) - 接收最后的 8 位 
- **总计:** $8 + 8 + 8 + 8 = \mathbf{32} \text{ 位}$。
---
由于输入是 5 位一组，输出是 8 位一组，**边界是不对齐的**。数据会跨越信号边界。具体的对应关系如下：

|**输出信号 (8位)**|**数据来源 (具体的位)**|**组成说明**|
|---|---|---|
|**w [7:0]**|**a[4:0]**, **b[4:2]**|`a` 的全部 5 位 + `b` 的高 3 位|
|**x [7:0]**|**b[1:0]**, **c[4:0]**, **d[4]**|`b` 的剩 2 位 + `c` 的全部 5 位 + `d` 的最高位|
|**y [7:0]**|**d[3:0]**, **e[4:1]**|`d` 的剩 4 位 + `e` 的高 4 位|
|**z [7:0]**|**e[0]**, **f[4:0]**, **2'b11**|`e` 的剩 1 位 + `f` 的全部 5 位 + 常数 `11`|

### vector reversal1
```
module top_module( 
    input [7:0] in,
    output [7:0] out
);
    assign out = {in[0], in[1], in[2], in[3], in[4], in[5], in[6], in[7]};
endmodule
```
![[Pasted image 20260123140835.png]]
简单来说，它把输入的 8 位二进制数“颠倒”了过来。原来的最低位（LSB）变成了最高位（MSB），原来的最高位变成了最低位。

- **右侧 (源数据):** `{in[0], in[1], ..., in[7]}`
    - 它按照从 `in[0]` 到 `in[7]` 的顺序提取位。
    - 注意：在 Verilog 中，写在最左边的是**最高位 (MSB)**。
    - 因此，这里强制把 `in[0]`（原本的最低位）放在了结果的最高位位置。  
- **左侧 (目标数据):** `out` (即 `out[7:0]`)
    - 拼接后的结果直接赋值给 `out`。    
    - 这意味着：    
        - `out[7]` (最高位) 获取了 `in[0]` (最低位)      
        - `out[6]` 获取了 `in[1]`       
        - ...      
        - `out[0]` (最低位) 获取了 `in[7]` (最高位)        

波形图中的数字通常是 **16进制 (Hexadecimal)** 表示的。
 **案例 A: 输入 `in = 1`**
- **二进制 (in):** `0000 0001` (注意最右边是 `in[0]`)
- **翻转后 (out):** `1000 0000` (原来的 `1` 跑到了最左边)
- **16进制 (out):** `80`
- **波形图结果:** 图中可以看到当 `in` 为 `1` 时，`out` 确实是 `80`。

### Replication operator
```
module top_module (
    input [7:0] in,
    output [31:0] out );//

    // assign out = { replicate-sign-bit , the-input };
    assign out = {{24{in[7]}}, in};

endmodule
```
这是通过复制左侧较小数字的符号位（最高有效位）来实现的。例如，符号扩展为4'b**0**101 （5）为8位得到8'b**0000**0101 （5），而符号扩展为4'b**1**101 （-3）为8位则为8'b**1111**1101 （-3）。

构建一个电路，将8位数字符号扩展到32位。这需要将24个符号位的复制件串接起来（即复制位[7]24次），然后是8位编号本身。

### more replication
```
module top_module (
    input a, b, c, d, e,
    output [24:0] out );//

    assign out[24:20] = ~ {5{a}} ^ {a, b, c, d, e};
    assign out[19:15] = ~ {5{b}} ^ {a, b, c, d, e};
    assign out[14:10] = ~ {5{c}} ^ {a, b, c, d, e};
    assign out[9:5] = ~ {5{d}} ^ {a, b, c, d, e};
    assign out[4:0] = ~ {5{e}} ^ {a, b, c, d, e};

endmodule
```
简单来说，它的功能是：**对比 5 个输入信号（a,b,c,d,e）中的每一个信号，与其他所有信号是否相等。**

代码中的核心逻辑是 `~ ( ... ^ ... )`。
- `^` 是 **异或 (XOR)**：两个位**不同**时为 1。
- `~` 是 **取反 (NOT)**
- `~ (... ^ ...)` 组合起来就是 **同或 (XNOR)**：两个位**相同**时为 1，不同为 0。

代码利用了 **位复制运算符 `{n{...}}`** 和 **位拼接运算符 `{...}`** 来构造向量进行并行比较。
以第一行 `assign out[24:20] = ~ {5{a}} ^ {a, b, c, d, e};` 为例：
1. **左操作数 `{5{a}}`**：将 `a` 复制 5 次。
    - 结果：`[a, a, a, a, a]`    
2. **右操作数 `{a, b, c, d, e}`**：将 5 个输入拼接。
    - 结果：`[a, b, c, d, e]`    
3. **运算**：对这两个 5 位向量进行按位同或（XNOR）。
    - `out[24]` = `a` XNOR `a` (结果恒为 1)    
    - `out[23]` = `a` XNOR `b` (如果 a==b，则为 1)    
    - `out[22]` = `a` XNOR `c`    
    - ...以此类推


## Modules Hierarchy
### modules
```
module top_module ( input a, input b, output out );
    mod_a instance1(.out(out), .in1(a), .in2(b));
endmodule
```
简单来说，它的意思是：**在当前的电路（`top_module`）里，放入了一个现成的子电路（`mod_a`），并把线接好。**
所有的输出都取决于
你可以把这段代码想象成在设计一块电路板：
- **`top_module` (顶层模块)**：这是你正在设计的**主板**。它有两个外部接口插槽 `a` 和 `b`，以及一个输出接口 `out`。
- **`mod_a` (子模块)**：这是一个现成的**芯片型号**（比如一个 CPU 或加法器芯片）。它的内部设计定义在别的地方，这里我们只需要用它。
- **`instance1` (实例名)**：这是你给焊在板子上的这块具体芯片起的**名字**（就像给变量命名一样）。
- **`.out(out), .in1(a)...` (连线)**：这是你在**画电路走线**，把主板上的线路连接到芯片的管脚上。

### Connecting ports by position
```
	mod_a instance1(out1, out2, a, b, c, d);
	只通过逗号进行信号输入的间隔
```
上一段代码里，我们看到了 `.out(out)` 这种写法，那是“指名道姓”的连接。 而这段代码里：
```
mod_a instance1(out1, out2, a, b, c, d);
```
括号里只有信号的名字，没有“点号”。这意味着：**连线的正确性完全依赖于顺序**。
Verilog 编译器会拿着 `mod_a` 的定义，和这里括号里的信号**一一对应**，像排队报数一样：
- 这里的 **第1个** 信号，自动连到 `mod_a` 定义时的 **第1个** 端口。
- 这里的 **第2个** 信号，自动连到 `mod_a` 定义时的 **第2个** 端口。
- ...以此类推。

### Connecting ports by name
```
    mod_a instance1(.in1(a), .in2(b), .in3(c), .in4(d), .out1(out1), .out2(out2),);
```
直接通过名字直接指定输入信号和输出信号的端口，这样可以不需要注重顺序。

### Three modules 
```
module top_module ( input clk, input d, output q );
    wire q1, q2;
    my_dff instance1(.clk(clk), .d(d), .q(q1));
    my_dff instance2(.clk(clk), .d(q1), .q(q2));
    my_dff instance3(.clk(clk), .d(q2), .q(q));
endmodule
```
你会得到一个有两个输入和一个输出的模块（实现一个D触发器）。实例化三个，然后将它们串联起来，形成长度为3的移位寄存器。端口需要连接到所有实例。
提供的模块如下：`module my_dff ( input clk, input d, output q );`
注意，要进行内部连接，你需要申报一些线缆。请谨慎为线路和模块实例命名：名称必须是唯一的。

  

[![](https://hdlbits.01xz.net/mw/images/6/60/Module_shift.png)](https://hdlbits.01xz.net/wiki/File:Module_shift.png)

### modules and vectors
```完整代码
module top_module ( 
    input clk, 
    input [7:0] d, 
    input [1:0] sel, 
    output [7:0] q 
);
    
    wire [7:0] q1, q2, q3;
    my_dff8 instance1(.clk(clk), .d(d), .q(q1));
    my_dff8 instance2(.clk(clk), .d(q1), .q(q2));
    my_dff8 instance3(.clk(clk), .d(q2), .q(q3));
    
    always @(*) begin
        case(sel)
            0 : q = d;
            1 : q = q1;
            2 : q = q2;
            3 : q = q3;
        endcase
    end
endmodule
```

```
always @(*) begin
    case(sel)
        0 : q = d;
        1 : q = q1;
        2 : q = q2;
        3 : q = q3;
    endcase
end
```

这段代码描述了一个标准的 **4选1 多路选择器 (4-to-1 Multiplexer)**。
- **`always @(*)`**：
    - 这表示这是一个**组合逻辑**电路。
    - `*` 是通配符，意思是“只要括号里用到的任何输入信号（如 `sel`, `d`, `q1`, `q2`, `q3`）发生变化，就立即执行一遍这个代码块”。  
    - 它就像一个实时的开关，没有记忆功能，信号变了输出马上变。    
- **`case(sel)`**：
    - 这就是开关的控制旋钮。它根据 `sel` 的值（0, 1, 2, 3）来决定电路的通路。  
- **具体逻辑**：
    - **`sel == 0`**：输出 `q` 直接连通输入 `d`（**无延迟**，直通）。
    - **`sel == 1`**：输出 `q` 连通 `q1`（**延迟 1 个周期**的数据）。   
    - **`sel == 2`**：输出 `q` 连通 `q2`（**延迟 2 个周期**的数据）。   
    - **`sel == 3`**：输出 `q` 连通 `q3`（**延迟 3 个周期**的数据）。

### Adder1
```
module top_module(
    input [31:0] a,
    input [31:0] b,
    output [31:0] sum
);
    
    wire cin1, cout1,cout2;
    wire [15:0] sum1, sum2;
    assign cin1 = 0;
    
    add16 instance1(.a(a[15:0]), .b(b[15:0]), .cin(cin1), .cout(cout1), .sum(sum1));
    add16 instance2(.a(a[31:16]), .b(b[31:16]), .cin(cout1), .cout(cout2), .sum(sum2));
    
    assign sum = {sum2, sum1};

endmodule
```
对于加法器来说，需要提前定义wire和cin1的内容，通过add16这个模块进行具体的计算
核心假发语句即为{}进行前后位数的连接

### Adder2
```
module top_module (
    input [31:0] a,
    input [31:0] b,
    output [31:0] sum
);//
    wire cin1, cout1, cout2;
    wire [15:0] sum1, sum2;
    assign cin1 = 0;
    add16 instance1(.a(a[15:0]), .b(b[15:0]), .cin(cin1), .cout(cout1), .sum(sum1));
    add16 instance2(.a(a[31:16]), .b(b[31:16]), .cin(cout1), .cout(cout2), .sum(sum2));
    
    assign sum = {sum2, sum1};

endmodule

module add1 ( input a, input b, input cin,   output sum, output cout );

// Full adder module here
    assign {cout, sum} = a + b + cin;

endmodule
```
有点类似于把前面的部分进行拆解，加入进位的计算

### Carry-select adder
```
module top_module(
    input [31:0] a,
    input [31:0] b,
    output [31:0] sum
);

    wire cin1, cout1, cin2, cout2, cin3, cout3;
    wire [15:0] sum1, sum2, sum3, sum_h;
    assign cin1 = 0;
    assign cin2 = 0;
    assign cin3 = 1;
    
    add16 instance1(.a(a[15:0]), .b(b[15:0]), .cin(cin1), .cout(cout1), .sum(sum1));
    add16 instance2(.a(a[31:16]), .b(b[31:16]), .cin(cin2), .cout(cout2), .sum(sum2));
    add16 instance3(.a(a[31:16]), .b(b[31:16]), .cin(cin3), .cout(cout3), .sum(sum3));
    
    always @(*) begin
        case(cout1)
            0 : sum_h = sum2;
            1 : sum_h = sum3;
        endcase
    end
    
    assign sum = {sum_h, sum1};
    
endmodule
```
它将两个带进位输入的16位数字相加，并得到一个进位输出和16位的和。你必须实例_化三个_这样的加法器，使用你自己的16位2对1复用器来构建进位选择加法器。

### Adder-subtractor
```
module top_module(
    input [31:0] a,
    input [31:0] b,
    input sub,
    output [31:0] sum
);
    wire cout1, cout2;
    wire [15:0] sum1, sum2;
    wire [31:0] b_xor;
    
    always @(*) begin
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
这里的 `.cin(sub)` 完成了公式中 **“+1”** 的操作：
- **当 `sub = 0` (加法) 时：**
    - `b_xor` 是 $B$。
    - `cin` 是 $0$。
    - 运算结果：$A + B + 0$。**(标准的加法)**
- **当 `sub = 1` (减法) 时：**
    - `b_xor` 是 $\text{~}B$（反码）。
    - `cin` 是 $1$。
    - 运算结果：$A + \text{~}B + 1$。
    - 根据补码定义，这等价于 $A - B$。**(标准的减法)**

## Procedures
### Alwaysblock1(combinational)
```
module top_module(
    input a, 
    input b,
    output wire out_assign,
    output reg out_alwaysblock
);

    assign out_assign = a & b;
    always @(*) out_alwaysblock = a & b;
    
endmodule
```
 **方式一：连续赋值 (Continuous Assignment)**
```
output wire out_assign;
assign out_assign = a & b;
```
- **语法：** `assign`
- **数据类型：** 必须是 **`wire`**（线网型）。
- **原理：**
    - 这就像你在电路板上焊了一根线。    
    - 只要右边的 `a` 或 `b` 发生变化，左边的 `out_assign` **立即、实时**地更新。    
    - 这是描述组合逻辑最直观、最简单的方法。
 **方式二：过程赋值 (Procedural Assignment)**
```
output reg out_alwaysblock;
always @(*) out_alwaysblock = a & b;
```
- **语法：** `always @(*)`
- **数据类型：** 必须是 **`reg`**（寄存器型）。
    - **注意：** 这里的 `reg` **并不代表**它是一个物理上的“寄存器”或“触发器”！这只是 Verilog 的语法规则：**在 `always` 块里被赋值的信号，必须定义为 `reg`**。      
- **原理：** 
    - **`@(*)`**：这叫做敏感列表。星号 `*` 的意思是“只要代码块里用到的任何输入信号（这里是 `a` 或 `b`）发生变化，就执行一遍下面的语句”。    
    - 因为没有时钟信号（`posedge clk`），所以这个 `always` 块生成的依然是**纯组合逻辑**。

### Alwaysblock2(clocked)
```
// synthesis verilog_input_version verilog_2001
module top_module(
    input clk,
    input a,
    input b,
    output wire out_assign,
    output reg out_always_comb,
    output reg out_always_ff   );

    assign out_assign = a ^ b;
    always @(*) out_always_comb = a ^ b;
    always @(posedge clk) out_always_ff <= a ^ b;
    ![[BitNet_Performance_Report]]
endmodule
```
**1. `out_assign`：组合逻辑 (Combinational Logic)**

```
assign out_assign = a ^ b;
```
- **硬件原型**：这就是一个纯粹的 **异或门 (XOR Gate)**。
- **特点**：**即时响应**。
    - 只要输入 `a` 或 `b` 发生变化，输出 `out_assign` 会**立即**（在仿真时间上是 0 延迟）跟着变化。        
- **语法**：使用 `assign` 关键字，左边必须是 `wire` 类型。 
---
**2. `out_always_comb`：也是组合逻辑**
```
always @(*) out_always_comb = a ^ b;
```
- **硬件原型**：生成的电路和上面那个**完全一样**，也是一个纯粹的 **异或门**。
- **特点**：**即时响应**。
    - `@(*)` 的意思是“敏感列表是所有输入”。只要 `a` 或 `b` 变了，这个块就执行一次。    
- **语法差异**：
    - 在 `always` 块里赋值，左边的变量必须定义为 `reg` 类型。    
    - **注意**：这里的 `reg` 只是语法要求，**并不代表**它真的生成了一个物理上的寄存器（Flip-Flop）。这是初学者最容易晕的地方：**写着 reg，但实际是 wire**。    
    - 组合逻辑的 `always` 块里通常使用阻塞赋值 `=`。    
---
**3. `out_always_ff`：时序逻辑 (Sequential Logic)**
```
always @(posedge clk) out_always_ff <= a ^ b;
```
- **硬件原型**：这是一个 **D触发器 (D Flip-Flop)**，触发器的输入端连着一个异或门。
- **特点**：**慢半拍（有时钟节拍）**。
    - 它**看不见** `a` 和 `b` 的实时变化。   
    - 它**只盯着**时钟 `clk` 的上升沿（`posedge`）。  
    - 只有当时钟信号从 0 变到 1 的那一瞬间，它才会去看一眼 `a ^ b` 等于多少，并把结果存下来输出。 
    - 如果在两个时钟沿之间，`a` 和 `b` 变乱了套，只要时钟没来，`out_always_ff` 就纹丝不动。    
- **语法**：
    - 敏感列表必须是时钟沿（如 `posedge clk`）。
    - 必须使用非阻塞赋值 `<=`。
    - 生成的电路具有**记忆性**（存储上一拍的结果）。    
**总结与对比表**

|**信号名**|**逻辑类型**|**硬件电路**|**什么时候变？**|**赋值符号**|
|---|---|---|---|---|
|**out_assign**|组合逻辑|纯导线/逻辑门|`a` 或 `b` 变了，立马就变|`=` (assign)|
|**out_always_comb**|组合逻辑|纯导线/逻辑门|`a` 或 `b` 变了，立马就变|`=` (阻塞)|
|**out_always_ff**|**时序逻辑**|**寄存器 (DFF)**|**只有在 `clk` 上升沿那一刻变**|`<=` (非阻塞)|

### IF statement
```
// synthesis verilog_input_version verilog_2001
module top_module(
    input a,
    input b,
    input sel_b1,
    input sel_b2,
    output wire out_assign,
    output reg out_always   ); 

    assign out_assign = (sel_b1 && sel_b2) ? b : a;
    always @(*) out_always = (sel_b1 && sel_b2) ? b : a;
    
endmodule
```
代码的核心在于 `(sel_b1 && sel_b2) ? b : a`。这是 C 语言和 Verilog 中通用的**三元运算符**。
- **语法格式：** `条件 ? 真时取值 : 假时取值`
- **在本例中：**
    - **条件**：`sel_b1 && sel_b2` (即 `sel_b1` 和 `sel_b2` **同时为 1**)。   
    - **真 (True)**：如果条件成立，输出 **`b`**。
    - **假 (False)**：如果条件不成立（任意一个为 0），输出 **`a`**。

这段代码描述的电路包含两个部分：
3. **一个 AND 门（与门）**：用来判断 `sel_b1` 和 `sel_b2` 是否同时为高电平。
4. **一个 2选1 多路选择器 (MUX)**：根据与门的结果来切换通道。
5. 真值表 (Truth Table)

|**sel_b1**|**sel_b2**|**逻辑判断 (&&)**|**输出结果**|
|---|---|---|---|
|0|0|0 (假)|**a**|
|0|1|0 (假)|**a**|
|1|0|0 (假)|**a**|
|**1**|**1**|**1 (真)**|**b**|

###  IF statement latches
```
// synthesis verilog_input_version verilog_2001
module top_module (
    input      cpu_overheated,
    output reg shut_off_computer,
    input      arrived,
    input      gas_tank_empty,
    output reg keep_driving  ); //

    always @(*) begin
        if (cpu_overheated)
           shut_off_computer = 1;
        else
            shut_off_computer = 0;
    end

    always @(*) begin
        if (~arrived)
            keep_driving = ~gas_tank_empty;
        else
            keep_driving = 0;
    end

endmodule这个代码是什么意思
```
设计**组合逻辑**（Combinational Logic）时，必须遵守一个黄金法则：
 **输出在任何情况下都必须有明确的值。**
**1. 第一个逻辑块（CPU 控制）**
Verilog
```
always @(*) begin
    if (cpu_overheated)
       shut_off_computer = 1;
    else
        shut_off_computer = 0;
end
```
- **功能**：当输入信号 `cpu_overheated` 为 **1** 时，输出 `shut_off_computer` 为 **1**；当输入为 **0** 时，输出为 **0**。
- **实质**：输出信号完全跟随输入信号的变化（逻辑上等价于 `assign shut_off_computer = cpu_overheated;`）。
    
**2. 第二个逻辑块（驾驶控制）**
```
always @(*) begin
    if (~arrived)
        keep_driving = ~gas_tank_empty;
    else
        keep_driving = 0;
end
```
- **功能**：这是一个带有优先级的条件判断。
    - **情况 A（未到达）**：如果 `arrived` 为 **0**（即 `~arrived` 为真），输出 `keep_driving` 取决于油箱状态：油箱不空（`gas_tank_empty` 为 0）则输出 1，否则输出 0。    
    - **情况 B（已到达）**：如果 `arrived` 为 **1**（即进入 `else` 分支），无论油箱状态如何，输出 `keep_driving` 强制为 **0**。    
- **实质**：逻辑表达式为 `keep_driving = (!arrived) && (!gas_tank_empty)`。

