# Icraft 组件总览

本文档汇总了 Icraft 套件中包含的各个组件及其对应的用户手册链接。

## 基础工具与库

| 组件名称 | 说明 |
| :--- | :--- |
| **Utils** | Icraft Utils 用户手册，提供通用工具函数和辅助功能。 |
| **XIR** | Icraft XIR (Xilinx Intermediate Representation) 用户手册，核心中间表示层。 |
| **XRT** | Icraft XRT (Xilinx Runtime) 用户手册，提供运行时支持。 |
| **CLI** | Icraft CLI 命令行工具用户手册，提供核心编译和操作接口。 |

## 编译流程组件

| 组件名称 | 说明 |
| :--- | :--- |
| **Parse (解析)** | 模型解析组件用户手册，负责将原始模型转换为内部表示。 |
| **Quantizer (量化)** | 模型量化工具用户手册，负责将浮点模型转换为定点模型。 |
| **Adapt (适配)** | 适配器/优化器用户手册，负责图层面的优化和硬件适配。 |
| **CodeGen (指令生成)** | 指令生成器用户手册，负责生成最终的可执行指令流。 |

## 运行与后端

| 组件名称 | 说明 |
| :--- | :--- |
| **Running (运行)** | ICraft XRun 运行用户手册，指导如何在目标平台上运行模型。 |
| **HostBackend** | 主机端后端支持手册。 |
| **BuyiBackend** | Buyi 自定义架构后端支持手册。 |
| **ZG330Backend** | ZG330 芯片后端支持手册。 |

## 设备模型 (Devices)

| 组件名称 | 类型 | 说明 |
| :--- | :--- | :--- |
| **SocketQL100AIU** | Socket | 基于 Socket 通信的 QL100AIU 设备模型。 |
| **AXIQL100AIU** | AXI | 基于 AXI 总线的 QL100AIU 设备模型。 |
| **SocketZG330AIU** | Socket | 基于 Socket 通信的 ZG330AIU 设备模型。 |
| **AXIZG330AIU** | AXI | 基于 AXI 总线的 ZG330AIU 设备模型。 |

## 扩展工具

| 组件名称 | 说明 |
| :--- | :--- |
| **Server** | Icraft Server 用户手册，提供服务端推理能力。 |
| **Icraft-Show** | 可视化工具 Icraft-Show 用户手册，用于模型分析和展示。 |
| **XDemo** | 示例工程 XDemo 用户手册，包含自定义算子和完整流程示例。 |
