# SocketQL100AIUDevice 设备驱动文档

## 1. 概述
`SocketQL100AIUDevice` 是通过 TCP/IP 网络协议与远程 QL100 AIU 硬件进行通信的驱动类。它允许用户在宿主机（Host）上通过网络连接控制板端的 NPU 设备，执行模型推理、寄存器读写等操作。

该驱动适用于开发板与主机分离的场景，如通过以太网连接的嵌入式开发板。

---

## 2. URL 格式与参数

初始化设备时，需使用标准的 URL 字符串指定连接参数。

### URL 格式
```text
socket://<ip>:<port>/?npu=<npu_id>&dma=<dma_id>
```

### 参数说明

| 参数 | 必选/可选 | 默认值 | 描述 |
| :--- | :--- | :--- | :--- |
| **ip** | **必选** | - | 目标板卡的 IP 地址 (例如 `192.168.1.10`) |
| **port** | 可选 | `9981` | `icraft-serve` 服务监听的端口号 |
| **npu** | 可选 | `0` | 指定使用的 NPU 核心 ID |
| **dma** | 可选 | `0` | 指定使用的 DMA 通道 ID |

### 示例 URL
*   `socket://192.168.1.100` (使用默认端口 9981, NPU 0, DMA 0)
*   `socket://192.168.1.100:8080/?npu=1` (使用端口 8080, NPU 1)

---

## 3. API 接口说明

### 3.1 构造函数
```cpp
SocketQL100AIUDevice(const std::string& url);
```
*   **功能**: 解析 URL 并建立与远程设备的连接。
*   **异常**: 连接失败将抛出异常。

### 3.2 Open / Close
```cpp
void Open();
void Close();
```
*   **Open**: 显式打开设备连接（通常在构造函数中自动调用）。
*   **Close**: 关闭连接并释放资源。

### 3.3 寄存器操作 (WriteReg / ReadReg)
```cpp
void WriteReg(uint32_t addr, uint32_t value);
uint32_t ReadReg(uint32_t addr);
```
*   **功能**: 直接读写 NPU 硬件寄存器。主要用于底层调试或状态查询。
*   **addr**: 寄存器偏移地址。

### 3.4 模型推理 (Run)
```cpp
void Run(const void* instructions, size_t instr_size, 
         const void* inputs, size_t input_size, 
         void* outputs, size_t output_size);
```
*   **功能**: 发送指令流和输入数据，触发 NPU 执行，并等待回传输出结果。
*   **instructions**: 编译好的 NPU 指令二进制数据。
*   **inputs**: 输入 Tensor 数据。
*   **outputs**: 用于接收结果的缓冲区。

### 3.5 复位 (Reset)
```cpp
void Reset(int level = 0);
```
*   **level**: 
    *   `0`: 软复位 (Soft Reset)，仅复位 NPU 逻辑。
    *   `1`: 硬复位 (Hard Reset)，可能涉及板级复位。

---

## 4. 使用示例

### 4.1 Python 示例

```python
from icraft import SocketQL100AIUDevice

# 1. 连接设备
device_url = "socket://192.168.31.200:9981"
dev = SocketQL100AIUDevice(device_url)

# 2. 准备数据
with open("model.bin", "rb") as f:
    instr_data = f.read()
input_data = b'\x00' * 1024  # 假设输入 1KB 数据
output_buffer = bytearray(1024) # 假设输出 1KB 数据

# 3. 执行推理
try:
    dev.Run(instr_data, input_data, output_buffer)
    print("Inference finished successfully.")
    print("Output prefix:", output_buffer[:10])
except Exception as e:
    print(f"Error: {e}")

# 4. 关闭连接
dev.Close()
```

### 4.2 C++ 示例

```cpp
#include "icraft/device.h"
#include <vector>
#include <iostream>

int main() {
    try {
        // 1. 初始化
        std::string url = "socket://192.168.31.200";
        icraft::SocketQL100AIUDevice device(url);
        
        // 2. 准备数据 (伪代码)
        std::vector<uint8_t> instrs = load_file("model.bin");
        std::vector<uint8_t> inputs(1024, 0);
        std::vector<uint8_t> outputs(1024);

        // 3. 运行
        device.Run(instrs.data(), instrs.size(), 
                   inputs.data(), inputs.size(), 
                   outputs.data(), outputs.size());

        std::cout << "Run success!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
```

---

## 5. 错误排查
*   **Connection Refused**: 检查板卡 IP 是否可达，检查板卡上 `icraft-serve` 进程是否已启动。
*   **Timeout**: 网络延迟过高或 NPU 程序陷入死循环。
*   **Protocol Error**: 客户端与服务端版本不匹配。
