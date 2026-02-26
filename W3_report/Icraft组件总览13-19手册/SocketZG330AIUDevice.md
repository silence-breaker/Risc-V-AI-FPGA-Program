# SocketZG330AIUDevice 设备驱动文档

## 1. 概述
`SocketZG330AIUDevice` 是专为 FMQL30TAI (Zhuge 330) 平台设计的网络驱动类。它继承自标准 Socket 设备接口，但针对 Zhuge 架构的特性进行了扩展，特别是对片上存储 (OCM) 的支持和特定的状态查询机制。

该驱动用于通过网络连接控制 FMQL30TAI 评估板或产品板。

---

## 2. URL 格式

```text
socket://<ip>:<port>/?npu=<npu_id>&dma=<dma_id>
```
参数含义与 QL100 版本一致。

---

## 3. 核心差异与特性

相比通用的 QL100 设备，ZG330 设备具有以下特有功能：

### 3.1 OCM (On-Chip Memory) 映射
Zhuge 架构拥有较大的片上 SRAM (OCM)。`SocketZG330AIUDevice` 支持识别和操作 OCM 区域。
在内存映射定义中，通常会包含：
*   **DDR 区域**: 常规大容量内存。
*   **OCM 区域**: 高带宽、低延迟的片上内存。

### 3.2 复位机制 (Reset Levels)
`Reset(int level)` 方法支持特定的复位等级：
*   **Level 0 (Soft Reset)**: 清除 NPU 内部状态机，不影响 PCIe/AXI 总线配置。
*   **Level 1 (Hard Reset)**: 触发子系统复位，可能需要重新加载固件。

### 3.3 设备信息查询
支持查询扩展的设备版本字符串：
*   **Version Format**: `FMSHZGV3TECH-AID` (示例)
*   可以通过驱动接口获取固件版本号和硬件 ID。

---

## 4. API 汇总

| 方法 | 说明 |
| :--- | :--- |
| `Run(...)` | 执行推理，支持 ZG330 特有的指令集格式。 |
| `WriteReg/ReadReg` | 访问 Zhuge CSR (Control Status Registers)。 |
| `LoadInputs` | 将输入数据搬运到指定的 DDR 或 OCM 地址。 |
| `GetOutputs` | 从指定地址取回数据。 |

---

## 5. Python 使用示例

```python
from icraft import SocketZG330AIUDevice
import numpy as np

# 连接到 Zhuge 板卡
# 假设板卡 IP 为 192.168.10.99
dev = SocketZG330AIUDevice("socket://192.168.10.99")

print("Device connected successfully.")

# 检查设备状态 (读取 0x00 状态寄存器)
status = dev.ReadReg(0x00)
print(f"Current NPU Status: 0x{status:08X}")

# 运行推理 (假设已有 binary_code)
# dev.Run(...) 

dev.Close()
```

---

## 6. 常见问题
*   **OCM 访问错误**: 如果模型使用了 OCM 优化，但物理地址被非法访问，可能会导致 Bus Error。确保编译器生成的地址映射与硬件配置一致。
*   **版本不兼容**: 宿主机的 SDK 版本必须与板端的 `icraft-serve` 版本严格对应，否则协议握手可能失败。
