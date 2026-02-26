# AXIQL100AIUDevice 设备驱动文档

## 1. 概述

`AXIQL100AIUDevice` 是用于在本地直接访问 QL100 AIU 硬件的驱动类。它通常运行在搭载 NPU 的嵌入式 Linux 系统（如 PetaLinux）上，通过 `/dev/mem` 或特定的内核驱动接口（UIO/VFIO）直接映射 AXI 总线地址空间，以实现高性能的低延迟控制。

与 `Socket` 版本不同，该驱动不涉及网络传输，适用于部署在边缘设备本机的应用。

---

## 2. URL 格式与参数

`AXIQL100AIUDevice` 使用 `axi://` 协议头。

### URL 格式
```text
axi://<address>/?range=<size>&mode=<mode>
```
*(注：通常情况下，AXI 设备可能不需要复杂的 URL 参数，直接使用 `axi://0` 或默认构造即可，具体取决于底层库实现)*

### 常见参数

| 参数 | 描述 |
| :--- | :--- |
| **address** | NPU 基地址 (Base Address)，通常由 Vivado 硬件设计决定。 |
| **range** | 映射内存空间的大小。 |
| **device_id** | 若系统存在多个设备，指定设备 ID。 |

---

## 3. 功能特性

1.  **直接内存访问 (DMA)**: 驱动直接管理物理内存（CMA - Contiguous Memory Allocator），实现零拷贝或极低拷贝的数据传输。
2.  **中断处理**: 支持等待 NPU 完成中断（Interrupt），释放 CPU 资源，而非忙轮询（Polling）。
3.  **高性能**: 相比 Socket 方式，没有网络协议栈开销，延迟最低。

---

## 4. API 接口

接口定义与 `InstructionDevice` 基类一致：

### 4.1 Run
```cpp
virtual void Run(const void* instr, size_t instr_len,
                 const void* input, size_t input_len,
                 void* output, size_t output_len) override;
```
直接向物理地址写入指令和数据，启动 NPU 寄存器，等待中断，然后从物理地址读取结果。

### 4.2 Reset
```cpp
virtual void Reset(int level = 0) override;
```
复位硬件状态机。

---

## 5. 使用场景

### 场景 A: 嵌入式板卡本机部署
在 QL100 开发板上运行 C++ 推理程序，直接调用 `AXIQL100AIUDevice` 进行视频流实时处理。

### 场景 B: `icraft-serve` 后端
`icraft-serve` 工具实际上是 `AXIQL100AIUDevice` 的一个包装器。它在板端创建 AXI 设备实例，并通过 TCP 网络暴露给远端 Socket 客户端。

---

## 6. 注意事项
*   **权限**: 运行该驱动通常需要 **root 权限** (`sudo`)，因为它涉及到底层 `/dev/mem` 或 UIO 设备的读写。
*   **内核驱动**: 必须确保系统已加载正确的内核模块（如 `uio_pdrv_genirq` 或厂商提供的 `ql100_driver.ko`），且设备树（Device Tree）配置正确。
*   **内存一致性**: 驱动内部会自动处理 Cache Flush/Invalidate，确保 CPU 与 NPU 看到的主存数据一致。
