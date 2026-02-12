
                  
  
# Icraft CLI

CLI仅由一个main.cpp组成，不提供头文件，也没有API
CLI的产物为icraft.exe（Windows）或icraft（Linux），但都可以使用icraft命令调用

## 一 使用示例

## 1.1 标准用法

CLI支持将输入的第一个命令行函数解析为Icraft组件
规则为：

```bash
icraft <command> [<--flag> [<args>]]
```

CLI会在环境变量中寻找可执行程序icraft-command，并将其它命令行参数传给它

## 1.2 配置文件

CLI支持将命令行存数储存在配置文件中
规则为：

```bash
icraft <command> [config.toml] [<--flag> [<args>]]
```

需要注意：

- 如果存在配置文件，那么它必须紧跟在command后

- 配置文件使用toml格式记录

- 命令行中输入的参数优先级高于配置文件中记录的参数

- CLI只解析toml中command对应的section

## 1.3 组合命令

CLI默认支持组合命令“compile”
规则为：

```bash
icraft compile [config.toml] [<--flag> [<args>]]
```

CLI会依次执行以下命令：

```bash
icraft parse [config.toml]
icraft optimize [config.toml]
icraft quantize [config.toml]
icraft adapt [config.toml]
icraft generate [config.toml]
```

该组合命令记录在“C:\Icraft\CLI\bin\comb.toml”或“/usr/bin/comb.toml”文件内
内容为：

```bash
[[compile]]
sequence = ["parse", "optimize", "quantize", "adapt", "generate"]
```

此处记录的组合命令对所有网络均生效
你可以模仿该形式自行添加自定义组合命令
组合命令的标志为双方括号[[]]
也可以将该[[section]]放置到具体网络的配置文件中，例如yolov5s.toml，那么它将只对改网络生效

## 1.4 多版本（仅限Windows）

3.0.0版本后的Icraft支持同时安装多个版本，并且在它们之间切换
该功能不兼容之前的版本

## 安装时

- 不同版本的之间可以同时安装

- 如果本机已经安装了一个版本，在卸载之前，不能安装相同版本

- icraft命令将指向最后安装的版本

## 卸载时

- 如果卸载后还有其它版本存在，那么icraft命令将指向最后安装的版本

## 运行时

使用以下命令可以查看本机当前已安装的所有Icraft版本：

```bash
icraft --version
# Icraft Version:
#  * Icraft v3.0.0
#    Icraft v3.0.1

# CLI Version:
# 0.11.6+59.develop.d3db7bf
```

使用以下命令可以将icraft重定向到指定版本：

```bash
icraft --version v3.0.1
# You have switched to Icraft v3.0.1
# Icraft Version:
#    Icraft v3.0.0
#  * Icraft v3.0.1

# CLI Version:
# 0.11.6+59.develop.d3db7bf
```

## 1.5 空跑

为了方便调试，CLI支持支持空跑
规则为：

```bash
icraft <command> [config.toml] [<--flag> [<args>]] [--dry_run]
```

CLI会将解析得到的待执行命令打印到屏幕上，但不真的执行

## 二 注意事项

CLI解析toml文件时最多支持二级数组嵌套，三级及以上会产生多余的引号导致错误

                