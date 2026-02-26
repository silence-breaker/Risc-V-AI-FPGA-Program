# AXIZG330AIUDevice 设备驱动文档

## 1. 概述
`AXIZG330AIUDevice` 是 FMQL30TAI (Zhuge 330) 平台的本地 AXI 总线驱动。这是在该平台上运行高性能 AI 应用的首选方式。它直接通过 SoC 的 AXI 总线控制 NPU IP 核，配合 Linux UIO 或 Reserved Memory 机制工作。

---

## 2. 硬件架构适配

### 2.1 内存空间 (Memory Map)
ZG330 通常包含两类可访问空间：
1.  **Register Space (CSR)**: 控制状态寄存器，用于启动停止 NPU、中断屏蔽等。通常映射大小为 4KB 或 64KB。
2.  **Data Space (DDR & OCM)**:
    *   **DDR**: 通过 CMA (Contiguous Memory Allocator) 分配物理连续内存。
    *   **OCM**: 直接映射片内 SRAM 物理地址，提供极高的读写带宽。

`AXIZG330AIUDevice` 自动处理这些复杂的地址映射关系。

---

## 3. 驱动配置

在 Linux 系统中初始化该设备通常依赖设备树 (Device Tree, DTS) 信息。

### 3.1 URL / 初始化参数
通常不需要复杂的 URL，构造函数会自动扫描系统设备节点（如 `/dev/uioX`）。

```cpp
// C++ 初始化
icraft::AXIZG330AIUDevice device; // 自动查找默认设备
```

### 3.2 环境变量
可以通过环境变量覆盖默认行为：
*   `ICRAFT_UIO_DEV`: 指定使用的 UIO 设备文件 (e.g., `/dev/uio0`).
*   `ICRAFT_MEM_SIZE`: 强制指定保留内存大小。

---

## 4. 性能优化特性

### 4.1 Zero-Copy (零拷贝)
当输入数据已经位于预留的物理内存中时（例如由视频采集模块直接写入），`AXIZG330AIUDevice` 支持传入物理地址指针，避免 CPU 二次拷贝。

### 4.2 中断驱动 (Interrupt Driven)
驱动使用阻塞读取 (`read()`) 等待 UIO 中断，确保在等待 NPU 计算完成时 CPU 占用率为 0。

### 4.3 Cache Coherency
Zhuge 平台可能需要手动维护 Cache 一致性。驱动在 `Run()` 前后会自动执行 `SimdFlush` 或调用内核 IOCTL 进行 Cache 刷新与无效化。

---

## 5. 用于服务器后端
`AXIZG330AIUDevice` 是 `icraft-serve` 在 FMQL30TAI 上的默认后端实现。
当用户运行：
```bash
icraft-serve --port 9981
```
系统内部实例化的即为 `AXIZG330AIUDevice`，对外提供 Socket 服务。

---

## 6. 开发建议
*   **调试**: 使用 `dmesg` 查看内核日志中是否有 NPU 相关的 IO 错误或 IOMMU 报错。
*   **多进程**: 通常 NPU 是独占设备，同一时间只能有一个进程（或 `AXIZG330AIUDevice` 实例）打开设备，否则会发生资源冲突。
