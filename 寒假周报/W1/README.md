# 第一周周报

## 整体完成情况

1. 三人均完成了在本地跑通1.58-bit大模型的源代码，并分析了量化模型在Pytorch框架下纯CPU环境下推理各个阶段的时间开销和内存占用情况，形成了详实的性能分析报告。
2. 三人均阅读了微软基于1.58bit改造的llama.cpp（BitNet）项目源码，理解了在没有Python自动调度的情况下，用最基础的C++代码去管理内存、搬运比特位、执行计算的实现方式。
3. 三人均学习了SystemVerilog的基本语法，练习了简单的组合逻辑和时序逻辑设计。（还在持续学习中）
4. WJ和WYC成功搭建了Vivado开发环境，LCJ暂时还在HDLbits等在线资源写代码，未配置Vivado。

## 详细报告链接

[基于Pytorch框架下纯CPU推理1.58bit大模型的性能分析报告](bitnet-Model-run/docs/BitNet_b1.58_CPU推理性能分析报告.md)

[基于BitNet项目源码的分析报告](Bitnetcpp_analysis/README.md)
(点进去之后看BitNet.cpp 优化后 CPU 推理性能分析报告即可，其他报告是中间产物)

[WJ的SystemVerilog学习笔记](https://github.com/silence-breaker/Risc-V-AI-FPGA-Program/tree/WJ/W1_report/SystemVerilog)

[WYC的SystemVerilog学习笔记](https://github.com/silence-breaker/Risc-V-AI-FPGA-Program/blob/WYC/W1_report/Verilog%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0.md)

[LCJ的SystemVerilog学习笔记](https://github.com/silence-breaker/Risc-V-AI-FPGA-Program/tree/LCJ/W1/SV%E5%AD%A6%E4%B9%A0%E6%8A%A5%E5%91%8A)

## 归纳总结

1. 本周的任务完成情况良好，三人均按计划完成了各自的任务，并形成了相关报告和学习笔记，没有拖沓和懈怠。
2. 通过本周的任务，大家对1.58bit模型的transformer架构有了更加具体深入的理解（LCJ在第一份pytorch版报告中绘制了一个很形象的流程图）。然后通过对bitnet.cpp源码的阅读发现他们KV存储的方式是环形缓冲区，这和我们原来想的KV分页式管理不同。 通过对比两种方式的优缺点，我们认为环形缓冲区更适合FPGA实现，因为它能更好地利用连续内存，减少内存碎片，提高数据访问效率，而且对于我们初学者更简单易实现。
3. SystemVerilog的学习还在继续，下周打算全员完成vscode+vivado的环境搭建，并完成一些基于TDPU简化设计的练习。
