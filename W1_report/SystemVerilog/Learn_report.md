# SV learn report

[SV基本语法网站](https://www.chipverify.com/systemverilog/systemverilog-datatypes)

## 语法总结

### 区分压缩与非压缩数组

SV定义和Verilog不同，SV中数组分为压缩数组和非压缩数组两种。压缩数组是指数组的维度定义在变量名的左侧，而非压缩数组是指数组的维度定义在变量名的右侧。压缩数组通常用于表示多维数据结构，而非压缩数组则更适合表示一维数据流。一般都采用压缩数组，这样可以进行一些数值的比较和加减。只有在RAM、ROM 或者寄存器堆等场景下才使用非压缩数组。

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
