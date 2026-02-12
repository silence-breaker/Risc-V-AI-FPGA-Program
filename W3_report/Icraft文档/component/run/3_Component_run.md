# Icraft XRun

新组件XRun将取代旧的Run（在线运行用）、Simulator（离线仿真用），同时具备两者的功能。

XRun基于XRT实现，相当于是XRT的可执行程序外壳。

XRun仅有一个main.cpp组成，不提供头文件，也没有API。

XRun的产物为icraft-run.exe（Windows）或icraft-run（Linux），但都可以使用icraft-run调用

## 一 命令行参数

本章节主要介绍XRun组件的参数说明。
XRun组件在使用时必须配置的参数有：待运行的网络文件路径、网络输入文件路径。
其中待运行的网络文件路径可通过json + raw、jr\_path + network、load\_snapshot三种方式配置。

Table.必须配置的命令行参数[#](#id12 "此表格的永久链接")

| 参数 | 说明 |
| --- | --- |
| json | 待运行的json文件路径 |
| raw | 待运行的raw文件路径 |
| jr\_path | 待运行的json和raw文件夹路径 |
| network | 待运行的json和raw文件名 |
| input | 网络输入文件路径，支持图片或ftmp，支持多输入，多输入以“;”分隔 |
| load\_snapshot | 快照文件路径，由快照文件反序列化得到session |

XRun组件在使用时可选配置的参数有：

Table.可选配置的命令行参数[#](#id13 "此表格的永久链接")

| 参数 | 说明 |
| --- | --- |
| log\_path | log存放路径，默认为.logs；完整路径为log\_path/network/\*.log |
| backends | 指定后端，默认为Host，布衣后端为BY，诸葛后端为ZG330 |
| dump\_format | 指定dump特征图使用的格式；支持SFB/SFT/SQB/SQT/HQB/HQT等；默认为空，即不dump |
| dump\_ftmp | 指定dump哪些特征图；默认为空，即dump所有特征图 |
| dump\_output | 只dump网络的输出特征图，默认不打开 |
| dump\_hidden | dump合并算子中的中间层结果，仅针对BYBackend且开启合并算子的网络有效。 |
| fake\_qf | 打开fake\_qf模式，仅针对HostBackend有效，默认不打开 |
| compress | 打开内存压缩模式，仅针对BYBackend/ZG330Backend有效，默认不打开； |
| log\_time | 记录每个算子的执行时间信息到屏幕和run\_time.log文件中，默认不记录 |
| log\_io | 记录每个算子的输入输出信息到屏幕和run\_io.log文件中，默认不记录 |
| merge\_hardop | 打开合并硬算子模式，仅对BYBackend/ZG330Backend有效，默认不打开； |
| lazy\_load | 开启惰性加载，仅对输入模型文件为json和raw时有效，默认不开启 |
| precheck | 开启device预检，包括dma读写检查、寄存器读写检查、位流是否打patch，默认不开启 |
| frequency | 设置ICore的时钟频率，单位为MHz |
| decode\_dll | 指定网络输入预处理所使用的动态链接库，默认为空 |
| close\_mmu | 关闭mmu模式，仅针对BYBackend有效，默认是不关闭，即开启mmu |
| save\_snapshot | 序列化session生成快照文件，保存在log\_path目录下，默认为不开启 |
| wait\_time | 设置前向等待的时间上限，单位毫秒，默认值为10000 |
| ocmopt | 选择ocm优化方案，仅针对ZG330Backend有效，默认为-1，可选择-1，0，1，2，3，分别为选择方案一~三中评分最高的方案、不开启ocm优化、选择方案一、选择方案二、选择方案三 |

## 二 使用示例

### 2.1 三种输入方式

待运行的网络文件路径可通过json + raw、jr\_path + network、load\_snapshot三种方式配置，均支持绝对路径和相对路径。

### 2.1.1 json + raw

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./images/cat.png"
lazy_load = true
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1//BY
2icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./images/cat.png" --lazy_load
3icraft-run --json "E:/jsonraw/yolov2_BY.json" --raw "E:/jsonraw/yolov2_BY.raw" --input "E:/images/cat.png" --lazy_load
4
5//ZG
6icraft-run --json "./jsonraw/yolov2_ZG.json" --raw "./jsonraw/yolov2_ZG.raw" --input "./images/cat.png" --lazy_load
7icraft-run --json "E:/jsonraw/yolov2_ZG.json" --raw "E:/jsonraw/yolov2_ZG.raw" --input "E:/images/cat.png" --lazy_load
```

### 2.1.2 jr\_path + network

toml文件中的参数配置示例如下：

```
[run]
jr_path = "./"
network = "./yolov2_BY"
input = "./images/cat.png"
lazy_load = true
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

### 2.1.3 load\_snapshot

使用快照文件作为输入文件，mmu模式、合并算子和内存优化等配置无效，而是与生成快照文件时的配置一致。

toml文件中的参数配置示例如下：

```
[run]
load_snapshot = "./snapshot/yolov2.snapshot"
input = "./images/cat.png"
backends = "BY,socket://ql100aiu@192.168.125.141:9981?npu=0x40000000&dma=0x80000000;Host"
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

### 2.2 后端指定

Xrun目前支持三种后端，
后端HostBackend支持CPU、Cuda等多种Device，
后端BYBackend、ZG330Backend支持Socket、AXI等多种Device，
不指定后端时，默认为HostCPU。

以下具体介绍BYBackend、ZG330Backend后端的参数配置，包含socket、axi、mock三种模式：

### 2.2.1 Socket

socket模式对应的url包含板子IP地址、npu起始地址、dma起始地址，对应连接的板子需开启icraft-serve。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./images/cat.png"
backends = "BY,socket://ql100aiu@192.168.125.141:9981?npu=0x40000000&dma=0x80000000;Host"
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1//BY
2icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --backends "BY,socket://ql100aiu@192.168.125.141:9981?npu=0x40000000&dma=0x80000000;Host" --input "./images/cat.png"
3
4//ZG
5icraft-run --json "./jsonraw/yolov2_ZG.json" --raw "./jsonraw/yolov2_ZG.raw" --backends "ZG330,socket://haps-zg330@192.168.124.24:5001;Host" --input "./images/cat.png"
```

### 2.2.2 Axi

axi模式对应的url包含npu起始地址、dma起始地址。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./images/cat.png"
backends = "BY,axi://ql100aiu?npu=0x40000000&dma=0x80000000;Host"
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --backends "BY,axi://ql100aiu?npu=0x40000000&dma=0x80000000;Host" --input "./images/cat.png"
```

### 2.2.3 Mock

mock模式对应的url包含npu起始地址、dma起始地址，使用该模式无需上板，
目前仅用于快照功能，与参数–save\_snapshot配合使用。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./images/cat.png"
backends = "BY,mock://ql100ai?npu=0x40000000&dma=0x80000000;Host"
save_snapshot = true
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1//BY
2icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --save_snapshot --backends "BY,mock://ql100ai?npu=0x40000000&dma=0x80000000;Host" --input "./images/cat.png"
3
4//ZG
5icraft-run --json "./jsonraw/yolov2_ZG.json" --raw "./jsonraw/yolov2_ZG.raw" --save_snapshot --backends "ZG330,mock://zg330;Host" --input "./images/cat.png"
```

### 2.3 多输入

input为必填参数,
如果输入文件为ftmp，则其格式、大小必须与json中记录的一致,
多输入有两种配置方式：通过分号隔开，通过文本文件输入。

### 2.3.1 通过分号隔开

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./images/cat.png;./images/elephant.ftmp"
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./images/cat.png;./images/elephant.ftmp"
```

### 2.3.2 通过文本文件输入

文本文件中记录所有输入文件的路径，用换行符隔开。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./img_list.txt"
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./img_list.txt"
```

### 2.4 记录时间

记录时间功能由各backend负责实现，有问题可向其开发者反馈。
目前提供四种时间wall、mem、hard、other，记录结果保存至log\_path路径下。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./img_list.txt"
log_time = true
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./img_list.txt" --log_time
```

### 2.5 记录io

目前只记录每个算子的所有输入和输出特征图,
不记录HardOp这种算子内部隐藏了的特征图，记录结果保存至log\_path路径下。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./img_list.txt"
log_io = true
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./img_list.txt" --log_io
```

### 2.6 dump特征图

dump功能由XRT的Tensor提供，有问题可向其开发者反馈。

Xrun会在指定的log路径下创建ftmp+dump\_format的文件夹，将各特征图保存其中，
无论是二进制还是文本文件，后缀名均为ftmp，用户需要根据文件夹名称判断是否可读。
若配置了–dump\_ftmp，则只会保存指定vid的特征图，用户需自行保证特征图v\_id有效，不存在的v\_id不会被dump。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./img_list.txt"
dump_format = "SFB"
dump_ftmp = "5,12,75"
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./img_list.txt" --dump_format SFB --dump_ftmp "5,12,75"
```

### 2.7 Device配置

Device配置主要是针对BuyiDevice的配置，需绑定Buyibackend后端,
包括设置ICore的时钟频率、device预检和设置mmu模式，用户可按需配置。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./img_list.txt"
frequency = 860
precheck = true
close_mmu = false
backends = "BY,axi://ql100aiu?npu=0x40000000&dma=0x80000000;Host"
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./img_list.txt" --frequency 860 --precheck --backends "BY,axi://ql100aiu?npu=0x40000000&dma=0x80000000;Host"
```

### 2.8 Backend配置

Backend配置是针对HostBackend、Buyibackend的配置，包括fake\_qf、内存压缩、合并算子，用户可按需配置。
使用限制和注意事项详见各组件文档说明。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./img_list.txt"
fake_qf = true
compress = true
merge_hardop = true
close_mmu = true
backends = "BY,axi://ql100aiu?npu=0x40000000&dma=0x80000000;Host"
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./img_list.txt" --fake_qf --compress --merge_hardop --close_mmu --backends "BY,axi://ql100aiu?npu=0x40000000&dma=0x80000000;Host"
```

### 2.9 快照

快照功能对当前session进行序列化，并保存快照文件至log\_path下。
目前只支持BY/ZG阶段的网络。

toml文件中的参数配置示例如下：

```
[run]
json = "./jsonraw/yolov2_BY.json"
raw = "./jsonraw/yolov2_BY.raw"
input = "./img_list.txt"
backends = "BY,mock://ql100ai?npu=0x40000000&dma=0x80000000;Host"
save_snapshot = true
```

配置完毕后，在命令行输入 `icraft run ./sample.toml` 即可启动XRun。

在命令行里使用XRun时，其参数配置如下：

```
1//BY
2icraft-run --json "./jsonraw/yolov2_BY.json" --raw "./jsonraw/yolov2_BY.raw" --input "./img_list.txt" --save_snapshot --backends "BY,mock://ql100ai?npu=0x40000000&dma=0x80000000;Host"
3
4//ZG
5icraft-run --json "./jsonraw/yolov2_ZG.json" --raw "./jsonraw/yolov2_ZG.raw" --input "./img_list.txt" --save_snapshot --backends "ZG330,mock://zg330;Host"
```

## 三 错误说明

### 3.1 错误码说明

26000:
缺少必须参数

26001:
文件或路径不存在

26002:
参数超出范围、格式错误

26003:
网络加载失败

26004-26009:
预留错误码

26010:
读取、检查Input时报错

26011:
运行超时
