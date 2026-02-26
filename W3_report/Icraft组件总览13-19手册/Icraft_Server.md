# Icraft Server 使用指南

## 1. 简介
`Icraft Server` (`icraft-serve`) 是一个轻量级的代理服务器程序。它运行在搭载 NPU 硬件的嵌入式设备（服务端）上，将本地的 AXI 设备（如 `AXIQL100AIUDevice` 或 `AXIZG330AIUDevice`）封装并通过 TCP/IP 网络暴露出来。

远端的 PC 开发机（客户端）可以通过 `SocketDevice` 类连接此服务器，实现远程模型加载、调试与推理。

---

## 2. 启动命令

### 基本用法
```bash
icraft-serve [options]
```

### 常用参数

| 参数 | 简写 | 描述 | 默认值 |
| :--- | :--- | :--- | :--- |
| `--port <port>` | `-p` | 指定监听的 TCP 端口号 | `9981` |
| `--device <name>` | `-d` | 指定要绑定的底层设备名称 | 自动检测 |
| `--help` | `-h` | 显示帮助信息 | - |
| `--verbose` | `-v` | 开启详细日志模式（调试用） | false |

### 示例
```bash
# 在默认端口 9981启动服务
icraft-serve

# 在端口 8080启动，并开启详细日志
icraft-serve -p 8080 -v
```

---

## 3. 工作原理

1.  **初始化**: `icraft-serve` 启动后，会尝试初始化本地的 NPU 硬件驱动（AXI 设备）。
2.  **监听**: 在指定端口开启 TCP 监听 (`0.0.0.0:<port>`)，等待客户端连接。
3.  **连接处理**: 
    *   当 PC 端创建 `Socket...Device` 时，建立 Socket 连接。
    *   服务端接管连接，解析网络包协议。
4.  **指令转发**:
    *   客户端发送 "WriteReg" -> 服务端执行本地 WriteReg -> 返回结果。
    *   客户端发送 "Run" -> 服务端接收指令流和数据 -> 调用本地 Run -> 等待中断 -> 回传结果数据。

---

## 4. 部署与维护

### 4.1 开机自启 (Systemd)
建议将 server 配置为系统服务。创建 `/etc/systemd/system/icraft-serve.service`:

```ini
[Unit]
Description=Icraft NPU Server
After=network.target

[Service]
Type=simple
ExecStart=/usr/bin/icraft-serve --port 9981
Restart=always
User=root

[Install]
WantedBy=multi-user.target
```

启用服务：
```bash
systemctl enable icraft-serve
systemctl start icraft-serve
```

### 4.2 日志查看
如果服务启动失败，查看日志：
```bash
journalctl -u icraft-serve -f
```

### 4.3 常见报错
*   **Bind failed**: 端口已被占用。检查是否有另一个 `icraft-serve` 实例在运行。
*   **Device open failed**: 缺少内核驱动（如 `.ko` 未加载）或权限不足（非 root 用户运行）。
*   **Version mismatch**: 客户端 SDK 版本与服务端版本不一致，连接时会报错。请保持两端版本同步。
