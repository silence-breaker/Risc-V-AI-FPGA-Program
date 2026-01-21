# SV learn report

[SV基本语法网站](https://www.chipverify.com/systemverilog/systemverilog-datatypes)

## 语法总结

### 数据类型

具体值只说最重要的四种：0，1，x(未知态),z(高阻态)

- wire: 只能被连续赋值语句（assign）驱动，不能在过程块中赋值。适用于组合逻辑连接。可以有多个驱动源，然后根据驱动强度来决定最终值（比如IIC里面的总线，多个器件可以同时驱动SDA线）
- reg: 可以在过程块（initial/always）中赋值，适用于存储元素和组合逻辑。
- logic: SystemVerilog 引入的新类型，既可以被连续赋值语句驱动，也可以在过程块中赋值。推荐使用 logic 替代 reg。只能有一个驱动源
- bit: 只能存储 0 和 1，不能表示 x 和 z。适用于不需要三态逻辑的场景，提高仿真性能

### 格式字符串用法归纳

下面总结 `$display/$write/$sformatf` 等常用格式字符串及用法示例：

- `%d` / `%0d`：十进制（有符号）显示。`%0d` 不填充空格。
- `%u`：十进制（无符号）显示。
- `%b` / `%0b`：二进制显示。
- `%o` / `%0o`：八进制显示。
- `%h` / `%0h`：十六进制显示（常用于总线/寄存器）。
- `%x` / `%0x`：十六进制显示（小写）。
- `%c`：按 ASCII 字符显示单个字节。
- `%s`：字符串显示。
- `%f`：实数显示（real/shortreal）。
- `%e` / `%g`：科学计数法显示实数。
- `%t`：仿真时间显示（配合 `$timeformat` 可控制单位/精度）。
- `%m`：层次化名称（当前模块/实例路径）。
- `%%`：打印百分号。

常见用法示例：

```systemverilog
logic [7:0]  a = 8'hA5;
integer      i = -12;
real         r = 3.14159;

$display("a=0x%0h b=%0b i=%0d", a, a, i);
$display("r=%0.3f time=%0t", r, $time);
$display("scope=%m");
```

补充说明：

- 宽度与补零：`%0h` 表示不填充空格；`%04h` 表示宽度 4、不足补零。
- `$timeformat(unit, precision, suffix, minwidth)` 可统一控制 `%t` 的显示格式。

### 结构体使用

```systemverilog
typedef struct packed {
    logic [7:0]  coins;   // 明确 8 位
    logic [31:0] dollars; // 明确 32 位
} s_money_packed;
s_money_packed my_money_packed='{coins: 8'hFF, dollars: 32'h12345678};

```

'{}是结构体的赋值符号，`'{3{1'b0}}`表示结构体内的每个字段都赋值为3个0。

### 数组

- 打包数组和非打包数组

```systemverilog
logic [7:0] packed_element;
//硬件上一根8位的总线
logic unpacked_element [7:0];
//可能对应分散的8个寄存器（不一定是挨着的）
logic [7:0] unpacked_array [3:0];
//4根8位的总线或者一块RAM，只能分开unpacked_array[i]去赋值，不可以[i:j]，因为物理上他们是不连续的
logic [3:0][7:0] my_bus;
//一根32位宽的大粗线，可一次性赋值，可以展平来看
```

### tb中的延迟时间

写testbench时，initial块中可以使用`#`延迟语句来模拟时间延迟。如果不加延迟时间，tb的结果很可能因为组合逻辑的瞬时变化而无法正确反映设计的实际行为。通过添加适当的延迟，可以确保信号有足够的时间稳定下来，从而获得准确的仿真结果。

### package和import

在 SystemVerilog 中，`package` 用于定义一组相关的类型、参数和函数，以便在多个模块或文件中共享。使用 `import` 语句可以将包中的内容引入到当前作用域，从而方便地访问包中定义的元素。这样可以提高代码的模块化和可维护性，避免重复定义相同的类型或参数。在模块开头用 import 包名::*;，表示导入包内所有内容。

### &&与==

在SV中，逻辑与运算符`&&`用于连接两个布尔表达式，而相等运算符`==`用于比较两个值是否相等。需要注意的是，`&&`返回一个布尔值（true或false），而`==`返回一个布尔值表示两个操作数是否相等。在条件判断中，使用`&&`来组合多个条件，而使用`==`来检查变量的具体值。

### assign与always_comb

在SV中，`assign`语句用于连续赋值，适用于组合逻辑电路的描述。而`always_comb`块则是一种更高级的方式来描述组合逻辑，它自动处理敏感列表，确保在任何输入变化时都会重新计算输出。相比之下，`always_comb`提供了更清晰和简洁的语法，减少了人为错误的可能性。

### logic与assign

先定义logic类型变量，然后再与输出端口相连。输出是汇集口，本身不存储数据。
下面是典型错误:

```systemverilog
assign logic [3:0] ones = q[3:0];  // 1. 定义 ones 是 q 的连线（读取 q）
// ...
always_ff @(posedge clk) begin
    ones <= ones + 1'b1;           // 2. 试图在触发器里给 ones 赋值（写入 ones）
end
```

上面代码中，ones 既被定义为 q 的连线（读取 q），又试图在触发器里给 ones 赋值（写入 ones），这是不允许的。正确的做法是先定义 logic 变量，然后再把它和输出端口相连:

```systemverilog
logic [3:0] ones;                  // 1. 定义 ones 作为一个独立的变量
assign q[3:0] = ones;              // 2. 把输出和 ones 连起来
// ...
always_ff @(posedge clk) begin
    ones <= ones + 1'b1;           // 3. 现在可以在触发器里给 ones 赋值了
end
```

### 函数和任务区分

在 SystemVerilog 中，函数（function）和任务（task）都是用于封装可重用代码块的结构，但它们有一些关键区别：

```systemverilog
function void display ();
 $display ("Am not going to return any value");
endfunction

task void display ();
 #10 $display ("Me neither");// #10 是延时语句（延迟10个时间单位），函数中不能使用
endtask
```

### SV的填充字面量特性

1. 在 Verilog 中，如果你想给 16 位变量全赋 1，你得写 16'hFFFF。如果你后来把变量改成了 32 位，你还得改代码。
2. 在 SV 中，'1 表示 “无论位宽是多少，全部填 1”。同理还有 '0 (全 0), 'z (全高阻), 'x (全未知)。这极大地增强了代码的参数化能力和可维护性。

### Intial begin

在 SV 中，`initial begin` 块用于在仿真开始时执行一次性的初始化操作。它通常用于设置初始条件、变量赋值或启动仿真过程。与 Verilog 相比，SV 的 `initial` 块可以包含更复杂的逻辑和控制结构，使得初始化过程更加灵活和强大。此外，SV 允许在 `initial` 块中使用延迟语句，以便在特定时间点执行操作，从而更好地模拟实际硬件行为。

## 练习

1. Build a 4-digit BCD (binary-coded decimal) counter. Each decimal digit is encoded using 4 bits: q[3:0] is the ones digit, q[7:4] is the tens digit, etc. For digits [3:1], also output an enable signal indicating when each of the upper three digits should be incremented.

```systemverilog
module top_module (
    input clk,
    input reset,   // Synchronous active-high reset
    output [3:1] ena,
    output [15:0] q);
    logic [3:0] ones,tens,huns,thous;
    assign q = {thous,huns,tens,ones};//把输出和内在的四位连起来
    //定义进位信号
    logic ones_full,tens_full,huns_full,thous_full;
    assign ones_full = (ones == 4'd9);
    assign tens_full = (tens == 4'd9)&&ones_full;
    assign huns_full = (huns == 4'd9)&&tens_full;
    assign thous_full = (thous == 4'd9)&&huns_full;
    always_comb begin
        ena = {huns_full,tens_full,ones_full};
               
    end
    always_ff @(posedge clk) begin
        if(reset) begin
            ones <= 0;
            tens <= 0;
            huns<= 0;
            thous <= 0;
        end
        else begin
        //个位
         if(ones_full) 
            ones <= 0;          
         else 
            ones <= ones + 1'd1;
        //十位
         if(ones_full) begin
           tens <= tens + 1'd1;
             if(tens_full)
                tens <= 0;
         end
        
        //百位
         if(tens_full) begin
             huns <= huns + 1'd1; 
             if(huns_full)
                huns <= 0;
         end
        
        //千位
         if(huns_full) begin
             thous <= thous + 1'd1; 
             if(thous_full)
                thous <= 0;
         end
           
     end 
    end
endmodule


```
