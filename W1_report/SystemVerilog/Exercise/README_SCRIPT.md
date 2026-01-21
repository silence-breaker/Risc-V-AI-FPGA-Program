# SystemVerilog 一体化编译仿真脚本

## 功能说明

`run_simulation.sh` 是一个全自动的 SystemVerilog 编译和仿真脚本，能够：

- 灵活指定要编译的 .sv 文件（单个或多个）
- 自动搜索当前目录的 .sv 文件（无文件指定时）
- 生成指定名称的可执行仿真二进制
- 一键运行仿真并显示结果
- 支持灵活的命令行选项

## 快速开始

### 基本用法

```bash
# 自动编译当前目录所有 .sv 文件
./run_simulation.sh

# 指定 SV 文件和输出名称
./run_simulation.sh -f Ex1.sv -o test1

# 查看帮助信息
./run_simulation.sh --help
```

## 命令行选项

| 选项 | 全名 | 说明 | 示例 |
|------|------|------|------|
| `-h` | `--help` | 显示帮助信息 | `./run_simulation.sh -h` |
| `-c` | `--clean` | 清理旧的构建文件 | `./run_simulation.sh -c` |
| `-f FILE` | `--file FILE` | 指定要编译的 .sv 文件（可多次使用） | `./run_simulation.sh -f Ex1.sv` |
| `-t MODULE` | `--top MODULE` | 指定顶层模块名称 | `./run_simulation.sh -t my_module` |
| `-o NAME` | `--output NAME` | 指定输出仿真文件名 | `./run_simulation.sh -o test1` |
| `-n NAME` | `--name NAME` | 同 `-o`（别名） | `./run_simulation.sh -n test1` |
| `-v` | `--verbose` | 详细输出（显示编译细节） | `./run_simulation.sh -v` |
| | `--compile-only` | 仅编译，不运行仿真 | `./run_simulation.sh --compile-only` |
| | `--run-only` | 仅运行仿真（跳过编译） | `./run_simulation.sh --run-only` |
| | `--list-files` | 列出将要编译的所有文件 | `./run_simulation.sh -f Ex1.sv --list-files` |

## 使用示例

### 1. 自动编译和仿真（编译当前目录所有 .sv 文件）

```bash
./run_simulation.sh
```

### 2. 指定单个 SV 文件编译

```bash
./run_simulation.sh -f Ex1.sv
```

### 3. 指定 SV 文件和输出名称

```bash
./run_simulation.sh -f Ex1.sv -o test1
```

### 4. 编译多个 SV 文件

```bash
./run_simulation.sh -f Ex1.sv -f Ex2.sv -o combined
```

### 5. 清理并重新编译

```bash
./run_simulation.sh --clean -f Ex1.sv -o test1
```

### 6. 修改顶层模块名称

```bash
./run_simulation.sh -f Ex1.sv -t another_testbench -o test1
```

### 7. 仅编译不运行

```bash
./run_simulation.sh -f Ex1.sv -o test1 --compile-only
```

### 8. 仅运行已编译的仿真

```bash
./run_simulation.sh --run-only
```

### 9. 详细输出编译过程

```bash
./run_simulation.sh -f Ex1.sv -o test1 -v
```

### 10. 列出将要编译的文件

```bash
./run_simulation.sh -f Ex1.sv -f Ex2.sv --list-files
```

## 输出目录结构

```
Exercise/
├── Ex1.sv                    # SystemVerilog 源文件
├── Ex2.sv                    # 其他 SystemVerilog 源文件（可选）
├── run_simulation.sh         # 本脚本
├── build/                    # 构建目录（自动生成）
│   ├── test1                 # 指定输出名称的仿真可执行文件
│   ├── another_test          # 不同指定的输出文件
│   └── combined              # 从多个文件编译的输出文件
└── test_sim                  # 旧的仿真文件（可删除）
```

## 系统要求

- Linux 系统
- 已安装 `iverilog`（IcarusVerilog 编译器）
- 已安装 `vvp`（VVP 仿真器）

### 安装依赖

```bash
# Ubuntu/Debian
sudo apt-get install iverilog

# CentOS/RHEL
sudo yum install iverilog
```

## 故障排查

### 1. 找不到 iverilog 工具

```
[ERROR] 找不到工具: iverilog
```

**解决方案**：安装 IcarusVerilog

```bash
sudo apt-get install iverilog
```

### 2. 编译错误

**常见原因**：

- 模块名称错误：确保 `-t` 参数与 `.sv` 文件中的 `module` 名称一致
- 语法错误：检查 `.sv` 文件的 SystemVerilog 语法
- 文件路径错误：确保 `-f` 指定的文件存在

### 3. 仅运行模式失败

```
[ERROR] 仿真二进制文件不存在
```

**解决方案**：先运行编译过程

```bash
./run_simulation.sh -f Ex1.sv -o test1 --compile-only
# 然后
./run_simulation.sh --run-only
```

### 4. 未找到任何 .sv 文件

```
[ERROR] 未找到任何 .sv 文件
```

**解决方案**：确保：

- 当前目录有 `.sv` 文件，或
- 使用 `-f` 参数指定文件（相对或绝对路径）

## 高级用法

### 创建不同配置的多个仿真

```bash
# 配置 1：Ex1.sv 编译为 test1
./run_simulation.sh -f Ex1.sv -o test1

# 配置 2：Ex1.sv + Ex2.sv 编译为 combined
./run_simulation.sh -f Ex1.sv -f Ex2.sv -o combined

# 配置 3：Ex2.sv 编译为 test2
./run_simulation.sh -f Ex2.sv -o test2
```

### 指定不同的顶层模块

```bash
# 编译时指定特定的顶层模块
./run_simulation.sh -f Ex1.sv -t test_vars -o test1
./run_simulation.sh -f Ex1.sv -t another_module -o test2
```

### 脚本调用示例

```bash
#!/bin/bash
# 批量编译多个 SV 文件

for sv_file in *.sv; do
    # 去掉 .sv 后缀作为输出名称
    output_name="${sv_file%.sv}"
    echo "编译 $sv_file 为 $output_name"
    ./run_simulation.sh -f "$sv_file" -o "$output_name" --compile-only
done
```

## 脚本功能详解

### 1. 工具检查

- 验证系统中是否安装了必要的工具
- 工具不存在时立即退出并提示

### 2. 文件自动搜索

- 当未用 `-f` 指定文件时，自动搜索当前目录的所有 `.sv` 文件
- 用 `-f` 指定文件后，自动搜索功能自动禁用

### 3. 构建目录管理

- 自动创建 `build/` 目录
- 支持清理旧文件

### 4. 编译步骤

```
iverilog -g2009 -o <output> -s <top_module> <file1> <file2> ...
```

- `-g2009`：使用 SystemVerilog 2009 标准
- `-o`：指定输出文件
- `-s`：指定顶层模块

### 5. 仿真运行

```
vvp <binary>
```

- 运行已编译的仿真二进制
- 捕获 `$display` 等系统调用的输出

## 后续扩展

可以进一步扩展脚本功能：

1. 添加代码覆盖率分析
2. 添加波形文件生成 (VCD)
3. 添加性能指标收集
4. 支持多种仿真工具切换（Vivado、ModelSim 等）
5. 批量编译脚本生成工具

## 许可证

本脚本为项目配套工具，与项目使用相同的许可证。
