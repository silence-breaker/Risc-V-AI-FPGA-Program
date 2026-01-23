
**项目**: Microsoft/BitNet (`bitnet.cpp`)

**核心目标**: 理解 1.58-bit LLM 的 C++ 实现，并将其逻辑映射到 FPGA 硬件模块设计。

**阅读时间**: 2025年（假定）

**关键词**: `ggml`, `ternary weights`, `quantization`, `FPGA`, `Verilog`

---
## 💡 第一章：初探——1.58 bit 到底存在哪里？

打开项目，既然是基于 `llama.cpp`，核心肯定在 `ggml` 库里。传统的 FP16 模型，权重直接就是 `float16`。INT4 模型则是打包的整数。那 1.58 bit 呢？计算机里没有 1.58 个 bit。
### 1.1 寻找数据结构

我在 `ggml-quants.c` (或者 `ggml-common.h` 类似的头文件) 里寻找线索。
BitNet b1.58 的核心逻辑是权重只有三态：`{-1, 0, 1}`。

$$\log_2(3) \approx 1.58$$

所以在内存中，它实际上**必须**用 **2-bit** 来存储一个权重（因为 1-bit 只能存 2 个状态，3 个状态需要 2-bit）。

**👀 代码阅读发现：**

看到了一些新的 Quantization Type，比如 `GGML_TYPE_TQ1_0` 或 `GGML_TYPE_TQ2_0`（Ternary Quantization）。

在底层的 packing 逻辑里：

- 它是把权重压缩得很紧凑。
    
- 最简单的实现方式：一个 `uint8_t` (8 bit) 可以存 4 个权重（每个 2 bit）。
    
- 映射关系可能是：
    
    - `00` -> `0`
        
    - `01` -> `1`
        
    - `10` -> `-1` (或者 `11` -> `-1`)
        
    - `11` -> 未使用/保留
        

**🧠 思考与笔记：**

> C++ 里需要位运算（shift & mask）来解压这些数。
> 
> **FPGA 映射思考**：这对 FPGA 太友好了！
> 
> 在 FPGA 上，我不需要像 CPU 那样用 `>>` 和 `&` 指令去取值。我可以写一个 `Bit Unpacker` 模块，直接用 `wire [1:0] weight = raw_data[i*2 +: 2];` 这种语法并在一个时钟周期内把 128 bit 的总线数据瞬间“炸”开成 64 个权重。完全没有 CPU 的指令开销。

---
## ⚡ 第二章：算力核心——消失的乘法器

这是最精彩的部分。通常 LLM 的推理核心是 `GEMM` (通用矩阵乘法) 或者 `GEMV` (矩阵向量乘法)。

公式是：$Y = W \times X$

其中 $W$ 是权重，$X$ 是激活值（Input Tokens）。

### 2.1 这里的 Kernel 怎么写？

我找到了 `ggml_vec_dot_...` 这种函数。

在 BitNet 中，$W$ 只有 {-1, 0, 1}。

$W \times X$ 变成了：

- 如果 $W = 1$，结果是 $+X$
    
- 如果 $W = -1$，结果是 $-X$
    
- 如果 $W = 0$，结果是 $0$ (Skip)
    

**👀 代码阅读发现：**

在 CPU 的 SIMD (AVX2/AVX512) 代码里，我没看到 `vfmadd` (浮点乘加) 或者 `pmaddubsw` (整型乘加)。

取而代之的是 `vpadd` (加法) 和 `vpsub` (减法)，以及一些 shuffle/blend 指令来处理 `0` 的情况。

微软的代码里可能还用了 T-MAC (LUT-based) 算法，查表法来进一步加速。

**🧠 思考与笔记：**

> 这简直是硬件的福音。
> 
> 传统的 INT8 量化需要 DSP (Digital Signal Processing) 模块来做乘法。FPGA 上的 DSP 资源是很昂贵的，数量有限（几百到几千个）。
> 
> **FPGA 映射思考**：
> 
> 我不需要 DSP 了！
> 
> 我只需要 LUT (Look-Up Table) 和 Adder (加法器)。
> 
> 我可以构建一个巨大的 **Systolic Array (脉动阵列)**，里面的 PE (Processing Element) 非常简单：
> 
> - 输入：2-bit Weight, 8-bit Activation
>     
> - 逻辑：`case(Weight) 0: out=0; 1: out=acc+act; -1: out=acc-act;`
>     
> - 这只是一个多路选择器 (MUX) 加上一个累加器。
>     
>     这意味着在同样的芯片面积下，我可以塞进去比传统架构多 5-10 倍的算力单元。
>     

---

## 💾 第三章：内存管理的“野性”——没有 Python 的世界

没有 PyTorch 的 `malloc`，没有 Garbage Collection。`llama.cpp` (以及 BitNet) 使用的是一种静态图的内存分配方式。

### 3.1 `ggml_cgraph` 与内存池

**👀 代码阅读发现：**

在推理开始前，它会建立一个 `ggml_cgraph`。它预先计算了所有 tensor 的形状。

然后它分配了一大块 `void* buffer`。

所有的 tensor 数据都只是这个 buffer 里的偏移量 (offset)。

**🧠 思考与笔记：**

> 这就是 C++ 的极致控制。
> 
> 这种“静态分配”的思想和 FPGA 设计完全一致。FPGA 最怕动态内存分配（DDR碎片化、指针跳转）。
> 
> **FPGA 映射思考**：
> 
> 1. **Instruction Dispatcher**: 我需要一个模块来解析 `cgraph`，把它变成指令序列。
>     
> 2. **Memory Map**: 由于地址是静态的，我可以在编译 bitstream 之前或者运行时初始化阶段，就把所有权重的物理地址算好。
>     
> 3. **No Malloc**: FPGA 运行时绝对不需要 `malloc`。DDR 的读写地址生成器 (Address Generator) 可以是完全确定性的线性计数器。
>     

---

## 🏗️ 第四章：FPGA 架构蓝图 (最终产出)

根据对 C++ 源码的阅读，我现在可以画出 FPGA 加速器的顶层模块图了。这个架构专门为 BitNet b1.58 优化。

### 模块 1: The Ternary Weight Fetcher (三值权重提取器)

- **C++ 对应逻辑**: 指针移动，位解压。
    
- **FPGA 实现**:
    
    - **DDR4/HBM Controller Interface**: 突发读取 (Burst Read) 512-bit 宽的数据。
        
    - **Unpacker**: 纯组合逻辑。输入 512 bit，输出 256 个 2-bit 的符号 (Symbols)。
        
    - **FIFO**: 缓冲这些符号，以匹配计算阵列的速度。
        

### 模块 2: Activation Streamer (激活流管理器)

- **C++ 对应逻辑**: 读取输入向量 `x`，通常是 INT8 量化后的。
    
- **FPGA 实现**:
    
    - **On-chip SRAM (BRAM/URAM)**: 存储当前的 Context/Token 的激活值。
        
    - BitNet b1.58 的激活值是 INT8，所以这里还是需要一定带宽，但比 FP16 减半。
        

### 模块 3: The "Bit-Adder" Array (位加法阵列 - 核心创新)

- **C++ 对应逻辑**: `acc += w * x` (实际上是 `acc += (sign) ? x : 0`)。
- **FPGA 实现**:
    - 这是一个巨大的并行计算阵列。
    - **输入**: 广播(Broadcast) 一个 INT8 的激活值 $X$ 给一列 PE。
    - **每个 PE**:
        - 接收一个 2-bit 权重 $W$。
        - 控制逻辑：
            - `W == 00 (0)` -> 累加器保持不变。    
            - `W == 01 (+1)` -> 累加器 `+ X`。  
            - `W == 10 (-1)` -> 累加器 `- X`。  
    - **优势**: 无需 DSP block，仅消耗 LUT 逻辑资源。
        
### 模块 4: Post-Processing Unit (后处理单元)

- **C++ 对应逻辑**: Dequantization (反量化), RMSNorm, Softmax。
    
- **FPGA 实现**:
    
    - 这里可能需要少量的 DSP。因为累加结果是 INT32，最后可能需要乘上一个 FP16 的 scaling factor 变回 logits。
        
    - 可以用流水线化的浮点乘法器实现。
        
---

## 📝 总结：从软件到硬件的映射表

|**C++ (BitNet.cpp)**|**核心操作**|**FPGA 对应模块**|**关键优势**|
|---|---|---|---|
|`ggml_type`|数据封装 (Packing)|**Combinational Unpacker**|零周期解压，带宽利用率极高|
|`ggml_vec_dot`|向量点积|**Adder Tree / Accumulator**|彻底抛弃乘法器，节省 DSP|
|`ggml_cgraph`|静态图调度|**State Machine / Sequencer**|确定性延时，无操作系统开销|
|Loop / Iterator|循环遍历|**Pipelining (流水线)**|吞吐量最大化|

**最后感想：**

阅读 BitNet 的源码让我意识到，算法的革新（1-bit/1.58-bit）正在重塑底层计算架构。在通用 GPU 上，我们还得用位运算指令模拟“去乘法化”，但在 FPGA 上，这是原生的、物理级别的优势。这可能是 FPGA 在 LLM 推理领域反超 GPU 的一个关键机会。