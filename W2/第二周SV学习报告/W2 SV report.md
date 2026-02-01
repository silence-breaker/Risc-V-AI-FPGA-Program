# 从零开始的SystemVerilog学习报告
2026/1/30 updated by LCJ
第一周学习平台：HDLBits

---

## 第一部分 入门 SV 核心基础语法
### 1.1 SV 的基本单元：模块（Module）
模块是 SV 中描述硬件的最小独立单元，所有逻辑设计都必须写在模块内，类比编程中的 “函数 / 类”，但模块描述的是硬件电路的结构和行为。

> **在 SV 中**：SV 中推荐用 `logic` 替代 Verilog 的 `wire`/`reg`，统一逻辑信号类型（仅双向端口仍需 `wire`/`inout`）。

```SystemVerilog
// SV 模块定义（兼容Verilog，但推荐logic类型）
module basic_module(
    input  logic clk,       // 输入时钟（logic替代wire/reg）
    input  logic rst,       // 输入复位
    input  logic [3:0] in,  // 4位宽输入（位宽[高位:低位]）
    output logic [3:0] out  // 4位宽输出
);

// ------------ 核心逻辑描述区 ------------
// 组合逻辑：SV推荐always_comb（替代Verilog的always @(*)）
// 时序逻辑：SV推荐always_ff（替代Verilog的always @(posedge clk)）

endmodule
```

---

### 1.2 连续赋值（assign）：组合逻辑专属
- **语法：** `assign 目标信号 = 表达式;`
- **特点：** “实时赋值”，只要右边表达式的任意信号变化，左边立即更新
- **适用：** 简单组合逻辑（门电路、多路选择器、加法器）
- **赋值符：只能用阻塞赋值`=`**

> **在 SV 中**：assign 支持 `logic` 类型（Verilog中assign左侧仅支持wire），无需区分wire/reg，简化语法。

示例：assign 实现与非门
```SystemVerilog
module nand_gate(
    input  logic a, b,
    output logic out
);
    // SV中logic类型兼容assign赋值
    assign out = ~(a & b);
endmodule
```

#### 1.2.1 位拼接写法
- 基础语法：`{信号1, 信号2, ..., 信号N}`
- 进阶：重复拼接 `{n{signal}}`

```SystemVerilog
// SV 增强示例：符号扩展拼接（4位有符号数扩展为8位）
logic [3:0] s_data;
logic [7:0] ext_data;
assign ext_data = {{4{s_data[3]}}, s_data}; // 算术扩展（保持符号位）
```

---

### 1.3 SystemVerilog 字面量
#### 1.3.1 核心结构
SV 完全兼容 Verilog 字面量格式，同时新增**无符号/有符号标记**、**二进制负数值**等增强：
```
[位宽]'[进制符号][数值]  // Verilog基础格式
[位宽]'s[进制符号][数值] // SV新增：有符号字面量
[位宽]'u[进制符号][数值] // SV新增：无符号字面量
```

#### 1.3.2 常用进制字面量对照表（补充 SV 增强）
| 进制   | 符号 | Verilog写法       | SV 增强写法          | 含义                     |
|--------|------|------------------|---------------------|--------------------------|
| 二进制 | `b`  | `1'b1`、`4'b1010` | `4'sb1101`（有符号） | 1位二进制1 / 4位有符号二进制1101（-3） |
| 十进制 | `d`  | `3'd5`、`10`      | `5'sd-3`（有符号）  | 3位十进制5 / 5位有符号十进制-3 |
| 十六进制 | `h` | `8'hA`、`16'h1234` | `8'uhFF`（无符号） | 8位无符号十六进制FF（255） |

#### 1.3.3 硬件特有的特殊值（完全兼容 Verilog）
| 符号 | 含义                     | 示例         | 场景                     |
|------|--------------------------|--------------|--------------------------|
| `x`  | 未知值（硬件未初始化）   | `1'bx`、`4'bxx00` | 未赋值的寄存器、故障信号 |
| `z`  | 高阻态（三态门输出）     | `1'bz`、`8'hzz`   | 总线驱动、三态缓冲器     |
| `?`  | `z`的别名（仅在case中用） | `4'b1??0`        | case语句的模糊匹配       |

#### 1.3.4 SV 字面量避坑指南（补充）
1. 有符号字面量需显式加 `s` 标记，否则默认无符号；
2. 二进制负数直接写 `4'sb1101`（等价于-3），而非 `4'b-3`（非法）；
3. 位宽不足时，有符号字面量会**符号截断**，无符号会**零截断**。

---

### 1.4 基本逻辑门的实现
SV 完全兼容 Verilog 逻辑门写法，同时推荐：
1. 用 `logic` 替代 `wire/reg`；
2. 复杂逻辑用 `always_comb` 替代多段 assign（可读性更高）；
3. 新增**逻辑运算符增强**（`===`/`!==` 支持 x/z 比较）。

```SystemVerilog
// SV 优化版同或门（支持x/z值比较）
module xnorgate( 
    input  logic a, b,
    output logic out
);
    always_comb begin // SV推荐：组合逻辑用always_comb
        out = ~(a ^ b);
        // SV增强：检测x/z值并告警
        if (a === 1'bx || b === 1'bx) begin
            $warning("Input signal has unknown value!");
        end
    end
endmodule
```

---

### 1.5 声明线
#### 1.5.1 显式声明 vs 隐式声明
SV 推荐保留 `default_nettype none禁用隐式线网，同时：
- 用 `logic` 统一替代 `wire`，无需区分“线网/变量”；
- 新增 `var` 关键字显式声明变量（兼容 Verilog 老代码）。

```SystemVerilog
`default_nettype none
module top_module (
    input  logic a, b, c, d,
    output logic out, out_n
);
    logic w1, w2; // SV：logic替代wire
    // var reg w3; // 兼容Verilog：显式声明reg变量
    
    assign w1 = a & b;
    assign w2 = c & d;
    assign out = w1 | w2;
    assign out_n = ~out;
endmodule
```

#### 1.5.2 向量
SV 兼容 Verilog 向量语法，同时新增：
- **向量位序统一**：推荐 `[N-1:0]` 小端序，SV 支持 `$bits(vector)` 获取向量位宽；
- **合并/拆分增强**：`packed/unpacked` 数组支持更灵活的位操作；
- **动态向量**：`dynamic array`（运行时调整长度）。

```SystemVerilog
// SV 增强：动态数组（未打包数组，运行时分配长度）
logic [7:0] dyn_arr[]; // 动态数组（8位元素，长度可变）

initial begin
    dyn_arr = new[4]; // 分配4个元素
    dyn_arr[0] = 8'h11;
    dyn_arr[1] = 8'h22;
    dyn_arr.delete(); // 清空数组
end
```

---

### 1.6 模块（Module）
#### 1.6.1 连接信号到模块端口
SV 兼容 Verilog 的“按位置/按名称”实例化，同时新增：
- **通配符端口连接**：`.name(*)` 自动匹配端口名（减少代码量）；
- **接口连接**：用 `interface` 替代多根独立线网（后文详细讲）。

```SystemVerilog
// SV 增强：通配符端口连接（端口名完全匹配时）
mod_a instance2 ( .* ); // 等价于 .in1(in1), .in2(in2), .out(out)
```

#### 1.6.2 Always 块的 SV 标准化
Verilog 的 `always` 块无明确语义，SV 拆分出 3 个语义明确的块：

| Verilog 写法          | SV 标准化写法 | 语义                 | 适用场景       | 赋值规则       |
|-----------------------|---------------|----------------------|----------------|----------------|
| `always @(*)`         | `always_comb` | 纯组合逻辑           | 组合电路       | 阻塞赋值 `=`    |
| `always @(posedge clk)` | `always_ff`  | 纯时序逻辑（触发器） | 寄存器/计数器  | 非阻塞赋值 `<=` |
| `always @(*) if(...)` | `always_latch` | 锁存器逻辑          | 锁存器（慎用） | 阻塞赋值 `=`    |

> **关键区别**：
> - `always_comb` 会自动检测所有输入信号（无需手动列敏感列表），且仿真时会在0时刻执行一次；
> - `always_ff` 强制检查“仅时钟/复位触发”，避免组合逻辑混入时序块；
> - `always_latch` 显式标记锁存器，工具会告警“是否有意生成锁存器”。

示例：SV 标准化 Always 块
```SystemVerilog
// 组合逻辑（SV推荐）
always_comb begin
    if (sel) out = a;
    else     out = b;
end

// 时序逻辑（SV推荐）
always_ff @(posedge clk or posedge areset) begin
    if (areset) q <= '0; // SV：'0 表示全0赋值（任意位宽）
    else        q <= d;
end
```

#### 1.6.3 过程式语句
1. **if 语句**：SV 支持 `else if` 连续判断，且 `always_comb` 中遗漏分支会告警（避免隐式锁存）；
2. **case 语句**：SV 新增 `case inside`（范围匹配）、`unique case`（唯一性检查）、`priority case`（优先级检查）；
3. **for 语句**：SV 支持 `foreach` 遍历数组（无需手动写索引）。

```SystemVerilog
// SV 增强：case inside 范围匹配
logic [3:0] val;
always_comb begin
    unique case (val) // unique：检查分支是否无重叠/无遗漏
        inside {[1:5]}: out = 1'b1; // 范围匹配1-5
        6,8,10:         out = 1'b0;
        default:        out = 1'bx;
    endcase
end

// SV 增强：foreach 遍历数组
logic [7:0] arr[4]; // 未打包数组（4个8位元素）
always_comb begin
    sum = '0;
    foreach (arr[i]) begin // 自动遍历所有索引
        sum += arr[i];
    end
end
```

#### 1.6.4 generate 语句
SV 兼容 Verilog 的 generate 循环，同时新增：
- `generate if`（条件生成硬件）；
- `generate case`（多分支生成硬件）；
- 无需显式 `genvar`（可直接用 `int` 作为循环变量）。

```SystemVerilog
// SV 增强：条件生成硬件
generate
    if (WIDTH == 8) begin : gen_8bit
        logic [7:0] data;
    end else if (WIDTH == 16) begin : gen_16bit
        logic [15:0] data;
    end
endgenerate
```

---

### 1.7 时序逻辑
#### 1.7.1 D 触发器
```SystemVerilog
module top_module (
    input  logic clk,    
    input  logic [7:0] d,
    output logic [7:0] q
);
    // SV推荐：always_ff + 非阻塞赋值 + '0 全0初始化
    always_ff @(posedge clk) begin
        q <= d;
    end
endmodule
```

#### 1.7.2 异步/同步复位
- SV 推荐用 `'0` 替代 `8'd0`（适配任意位宽，无需硬编码）；
- 新增 `sync_accept_on` 等复位属性（仿真用）。

```SystemVerilog
// SV 异步复位优化版
module top_module (
    input  logic clk,
    input  logic areset,   // active high asynchronous reset
    input  logic [7:0] d,
    output logic [7:0] q
);
    always_ff @(posedge clk or posedge areset) begin
        if (areset) 
            q <= '0; // SV：'0 自动匹配q的位宽，全0赋值
        else
            q <= d;
    end
endmodule
```

#### 1.7.3 边缘检测
SV 新增 `$rose`/`$fell`/`$stable` 系统函数，简化边缘检测：
- `$rose(signal)`：检测信号从0→1（正边缘）；
- `$fell(signal)`：检测信号从1→0（负边缘）；
- `$stable(signal)`：检测信号无变化。

```SystemVerilog
// SV 简化版8位正边缘检测
module top_module (
    input  logic clk,
    input  logic [7:0] in,
    output logic [7:0] pedge
);
    always_ff @(posedge clk) begin
        pedge <= $rose(in); // SV：$rose自动检测每一位的正边缘
    end
endmodule
```

#### 1.7.4 移位寄存器
SV 支持 `>>>` 算术右移运算符（替代手动符号扩展），且支持动态移位（结合变量）：
```SystemVerilog
// SV 64位算术移位寄存器优化版
module top_module(
    input  logic clk,
    input  logic load,
    input  logic ena,
    input  logic [1:0] amount,
    input  logic [63:0] data,
    output logic [63:0] q
);
    always_ff @(posedge clk) begin
        if (load)
            q <= data;
        else if (ena) begin
            case (amount)
                2'b00: q <= q << 1;
                2'b01: q <= q << 8;
                2'b10: q <= q >>> 1; // SV：算术右移（自动保持符号位）
                2'b11: q <= q >>> 8;
            endcase
        end
    end
endmodule
```

#### 1.7.5 有限状态机（FSM）
Verilog 用`parameter`定义状态（易出错），SV 推荐用`enum`枚举类型定义状态（类型安全、可读性高）：

```SystemVerilog
// SV 枚举类型实现FSM（JK触发器状态机）
module top_module(
    input  logic clk,
    input  logic areset,    // Asynchronous reset to OFF
    input  logic j,
    input  logic k,
    output logic out
);
    // SV：枚举类型定义状态（类型安全，避免状态值写错）
    enum logic {OFF=1'b0, ON=1'b1} state, next_state;

    // 时序段（状态寄存器）
    always_ff @(posedge clk or posedge areset) begin
        if (areset)
            state <= OFF;
        else
            state <= next_state;
    end

    // 组合段（下一状态逻辑）
    always_comb begin
        case (state)
            OFF: next_state = j ? ON : OFF;
            ON:  next_state = k ? OFF : ON;
            default: next_state = OFF;
        endcase
    end

    // 输出段
    assign out = (state == ON);
endmodule
```

---

## 第二部分 SystemVerilog 核心增强特性
### 2.1 高级数据类型
#### 2.1.1 统一逻辑类型：logic
| 类型    | Verilog 语义       | SV 语义                  | 适用场景                  |
|---------|--------------------|--------------------------|---------------------------|
| `wire`  | 线网（被动赋值）   | 仅双向端口/三态总线使用  | inout 端口、三态总线      |
| `reg`   | 变量（主动赋值）   | 废弃（用logic替代）      | 无                        |
| `logic` | 无（Verilog无此类型） | 统一逻辑类型（支持assign/always赋值） | 所有单方向端口、内部信号 |

> **核心规则**：
> 1. 单方向端口（input/output）优先用 `logic`；
> 2. 双向端口（inout）必须用 `wire`（logic不支持三态驱动）；
> 3. `logic` 支持连续赋值（assign）和过程赋值（always），无需区分wire/reg。

#### 2.1.2 定宽整数类型
Verilog 只有 `integer`（32位有符号），SV 新增多种定宽整数，无需手动定义位宽：

| 类型       | 位宽 | 符号性 | 取值范围                  | 适用场景               |
|------------|------|--------|---------------------------|------------------------|
| `bit`      | 1    | 无符号 | 0/1                       | 单比特标志位           |
| `byte`     | 8    | 有符号 | -128 ~ 127                | 字节数据、ASCII字符    |
| `shortint` | 16   | 有符号 | -32768 ~ 32767            | 短整型数据             |
| `int`      | 32   | 有符号 | -2^31 ~ 2^31-1            | 常规整数、循环索引     |
| `longint`  | 64   | 有符号 | -2^63 ~ 2^63-1            | 大整数、时间戳         |
| `uint`     | 32   | 无符号 | 0 ~ 2^32-1                | 无符号计数、地址       |

示例：
```SystemVerilog
bit flag;          // 1位无符号
byte char_data;    // 8位有符号
uint addr;         // 32位无符号地址
longint timestamp; // 64位有符号时间戳

initial begin
    char_data = -128; // 合法（byte的最小值）
    addr = 4294967295; // 合法（uint的最大值）
end
```

#### 2.1.3 枚举类型（enum）
枚举类型将“名称”与“数值”绑定，避免硬编码数值

```SystemVerilog
// 定义枚举类型（显式指定数值，默认从0开始递增）
enum logic [3:0] {
    IDLE  = 4'b0001,
    READ  = 4'b0010,
    WRITE = 4'b0100,
    ERROR = 4'b1000
} fsm_state;

// 枚举类型操作
always_comb begin
    case (fsm_state)
        IDLE:  next_state = READ;
        READ:  next_state = WRITE;
        WRITE: next_state = IDLE;
        ERROR: next_state = IDLE;
    endcase
end

// 枚举类型转换（名称→数值/数值→名称）
initial begin
    $display("IDLE = %0b", IDLE); // 输出：IDLE = 0001
    $display("State name: %s", fsm_state.name()); // 输出当前状态名称
end
```

#### 2.1.4 结构体（struct）与联合体（union）
- **结构体（struct）**：将不同类型的变量打包成一个整体（如数据包、控制字）；
- **联合体（union）**：同一内存空间存储不同类型的数据（节省资源，如高低位复用）。

```SystemVerilog
// 结构体：定义数据包格式
struct packed { // packed：打包成连续比特（硬件可综合）
    logic [7:0] addr;
    logic [31:0] data;
    logic [1:0] cmd;
} pkt;

// 联合体：高低位复用（32位整体 / 4个8位字节）
union packed {
    logic [31:0] word;
    logic [7:0] byte[4];
} data_bus;

initial begin
    pkt.addr = 8'h10;
    pkt.data = 32'h12345678;
    pkt.cmd = 2'b01;

    data_bus.word = 32'hAABBCCDD;
    $display("Byte 0 = %0h", data_bus.byte[0]); // 输出：DD
end
```

#### 2.1.5 动态数据结构（SV 独有，主要用于验证）
SV 新增 3 种动态数据结构（运行时调整长度，**设计代码慎用，验证代码首选**）：

| 类型         | 语法          | 特点                          | 适用场景               |
|--------------|---------------|-------------------------------|------------------------|
| 动态数组     | `type arr[]`  | 长度可变，连续内存            | 可变长度数据缓存       |
| 队列         | `type q[$]`   | 头部/尾部增删高效，连续内存   | 事务队列、FIFO         |
| 关联数组     | `type aa[key]`| 键值对存储，稀疏内存          | 地址映射、查表         |

示例：
```SystemVerilog
// 动态数组
int dyn_arr[];
initial begin
    dyn_arr = new[5]; // 分配5个元素
    dyn_arr[0] = 10;
    dyn_arr = new[10](dyn_arr); // 扩容到10个元素，保留原有数据
    dyn_arr.delete(); // 清空
end

// 队列
int q[$] = {1,2,3}; // 初始化
initial begin
    q.push_back(4); // 尾部添加：q = {1,2,3,4}
    q.push_front(0); // 头部添加：q = {0,1,2,3,4}
    q.pop_front(); // 头部删除：q = {1,2,3,4}
end

// 关联数组（键为地址，值为数据）
logic [31:0] mem[int]; // 键为int，值为32位逻辑
initial begin
    mem[32'h1000] = 32'h1234; // 地址0x1000存入0x1234
    mem[32'h2000] = 32'h5678;
    $display("Mem[0x1000] = %0h", mem[32'h1000]); // 输出0x1234
end
```

---

### 2.2 接口（interface）
Verilog 用多根线网连接模块，易出错且代码冗余；SV 用 `interface` 将“信号+协议”封装成一个整体，简化模块交互（尤其适用于总线、协议接口如AXI、SPI）。

#### 2.2.1 接口定义与使用
```SystemVerilog
// 1. 定义接口（封装SPI协议信号）
interface spi_if (input logic clk, rst);
    // 信号声明
    logic sclk;
    logic mosi;
    logic miso;
    logic cs_n;

    // 协议方法（可选，封装协议逻辑）
    task spi_write(logic [7:0] data);
        cs_n = 0;
        for (int i=7; i>=0; i--) begin
            mosi = data[i];
            @(posedge sclk);
        end
        cs_n = 1;
    endtask
endinterface

// 2. 模块使用接口（替代多根端口）
module spi_master(spi_if ifc); // 接口作为端口
    always_ff @(posedge ifc.clk) begin
        if (!ifc.rst) begin
            ifc.sclk <= 0;
        end else begin
            ifc.sclk <= ~ifc.sclk;
        end
    end
endmodule

// 3. 顶层实例化接口+模块
module top;
    logic clk, rst;
    spi_if ifc(clk, rst); // 实例化接口
    spi_master m(ifc);    // 模块连接接口

    initial begin
        rst = 1;
        #10 rst = 0;
        ifc.spi_write(8'h55); // 调用接口的方法
    end
endmodule
```

#### 2.2.2 接口的优势
1. 减少端口数量（一根接口替代多根线网）；
2. 封装协议逻辑（方法/任务），代码复用；
3. 支持 `modport`（端口方向约束），避免连接错误。

---

### 2.3 面向对象编程（OOP）
SV 引入类（class）、对象（object）、继承、多态等OOP特性，**主要用于验证（UVM）**，设计代码极少使用。

#### 2.3.1 类与对象基础
```SystemVerilog
// 定义类（封装数据+方法）
class Packet;
    // 成员变量
    rand logic [7:0] addr; // rand：随机化变量
    rand logic [31:0] data;
    logic [1:0] cmd;

    // 成员方法
    function new(logic [1:0] init_cmd); // 构造函数（创建对象时调用）
        cmd = init_cmd;
    endfunction

    function void print(); // 打印数据包信息
        $display("Addr: %0h, Data: %0h, Cmd: %0b", addr, data, cmd);
    endfunction
endclass

// 创建对象并使用
initial begin
    Packet pkt1; // 声明类句柄（类似指针）
    pkt1 = new(2'b01); // 实例化对象（调用构造函数）
    pkt1.addr = 8'h10;
    pkt1.data = 32'h1234;
    pkt1.print(); // 调用方法：输出Addr:10, Data:1234, Cmd:01
end
```

#### 2.3.2 约束随机化
`rand` 变量 + `constraint` 约束，实现自动化测试用例生成：
```SystemVerilog
class Packet;
    rand logic [7:0] addr;
    rand logic [31:0] data;

    // 约束：addr在0x10~0xFF之间，data为偶数
    constraint c_addr {
        addr inside {[8'h10:8'hFF]};
        data % 2 == 0;
    }
endclass

initial begin
    Packet pkt;
    pkt = new();
    for (int i=0; i<5; i++) begin
        pkt.randomize(); // 随机化（满足约束）
        pkt.print(); // 输出5个符合约束的随机数据包
    end
end
```

---

### 2.4 系统断言（SVA）
SVA（SystemVerilog Assertion）是SV新增的断言语言，用于**检查设计是否符合规格**（如协议时序、信号约束），是验证的核心工具。

#### 2.4.1 基本断言语法
```SystemVerilog
// 即时断言（立即检查）
initial begin
    assert (pkt.addr != 8'h00) else $error("Addr is zero!");
end

// 时序断言（检查时钟域的时序关系）
logic req, ack;
assert property (
    @(posedge clk) req |-> ##1 ack // 规则：req拉高后，下一个时钟ack必须拉高
) else $error("Req without ack!");
```

#### 2.4.2 常用SVA算子
| 算子       | 含义                 | 示例                  |
|------------|----------------------|-----------------------|
| `\|->`      | 重叠蕴含             | `req \|-> ack`（req和ack同时有效） |
| `\|=>`      | 非重叠蕴含           | `req \|=> ack`（req后下一拍ack有效） |
| `##n`      | 延迟n个时钟          | `##2 ack`（延迟2拍ack有效） |
| `throughout` | 全程满足         | `req throughout (##3 ack)`（req在3拍内一直有效） |
| `within`   | 在区间内满足         | `ack within (##1 ##2 req)`（ack在req的1-2拍内有效） |

---

### 2.5 功能覆盖率
功能覆盖率用于**验证测试用例是否覆盖所有设计场景**（如所有状态、所有指令、所有边界值），确保验证的完整性。

```SystemVerilog
// 定义覆盖率组
covergroup cg_packet @(posedge clk);
    // 覆盖点：addr的取值范围
    cp_addr: coverpoint pkt.addr {
        bins low = {[0:31]};
        bins mid = {[32:63]};
        bins high = {[64:255]};
    }
    // 覆盖点：cmd的所有取值
    cp_cmd: coverpoint pkt.cmd {
        bins all_cmds[] = {[0:3]}; // 自动拆分所有取值
    }
    // 交叉覆盖：addr范围 + cmd取值（验证所有组合）
    cp_cross: cross cp_addr, cp_cmd;
endgroup

// 使用覆盖率组
initial begin
    cg_packet cg = new(); // 实例化覆盖率组
    forever @(posedge clk) begin
        cg.sample(); // 采样覆盖率（每拍更新）
    end
end
```

---

### 2.6 模块化编程：Package 与 Import
Verilog 用`include`复制代码（易冲突），SV 用`package`封装可复用代码（如枚举、结构体、方法），通过`import`导入使用，避免命名冲突。

```SystemVerilog
// 定义package
package spi_pkg;
    enum logic {IDLE, TRANS} spi_state;
    struct packed {
        logic [7:0] addr;
        logic [31:0] data;
    } spi_pkt;
    function void spi_print(spi_pkt pkt);
        $display("SPI Pkt: %0h %0h", pkt.addr, pkt.data);
    endfunction
endpackage

// 导入并使用package
module spi_module;
    import spi_pkg::*; // 导入package的所有内容
    spi_pkt pkt;
    initial begin
        pkt.addr = 8'h10;
        spi_print(pkt); // 调用package中的方法
    end
endmodule
```

---

## 附录：SV 常用系统函数/任务
| 函数/任务       | 功能                          | 示例                          |
|-----------------|-------------------------------|-------------------------------|
| `$bits(var)`    | 获取变量位宽                  | $bits(pkt) → 40（addr8+data32） |
| `$rose(signal)` | 检测信号正边缘                | $rose(req)                    |
| `$fell(signal)` | 检测信号负边缘                | $fell(ack)                    |
| `$random()`     | 生成随机数                    | $random % 100 → 0-99的随机数  |
| `$display()`    | 打印信息                      | $display("Time: %0t", $time)  |
| `$finish()`     | 结束仿真                      | $finish(1) → 带错误码结束     |