# 命令行参数

## 一 调用方法

Icraft提供了CLI命令 `icraft` 来支持用户完成 **解析**、 **优化** 、 **量化** 、 **适配** 、 **指令生成** 以及 **运行** 等过程。其调用方法如下：

Icraft CLI 命令格式
```
icraft <command> [<config file>][–<key> <value>]…
```

其中 `command` 表示要执行的功能命令，当前支持的命令如下：


| 功能 | 命令 |
| --- | --- |
| parse | 解析 |
| optimize | 优化 |
| quantize | 量化 |
| adapt | 适配 |
| generate | 指令生成 |
| compile | 编译，根据配置文件依次执行解析、优化、量化、适配和指令生成四个过程 |
| run | 在指定的后端上运行编译产生的中间层网络 |
| show | 打开可视化、模型分析工具icraft-show |


例如，指令生成的命令行调用方法为 `icraft generate [<config file>] [--<key> <value>]...`





## 二 参数配置



CLI命令 `icraft` 的参数可以在配置文件中指定，也可以通过命令行参数 `--<key> <value>` 的方式指定。


CLI命令 `icraft` 的配置文件为 `toml` 格式。以 `PPyoloe` 的编译配置为例，其配置文件内容如下。


`100TAI` 的配置：
PPyoloe_crn_s.toml

``` toml
[parse]
net_name = "PPyoloe_crn_s"
framework = "Onnx"
inputs = [ 1, 640, 640, 3,]
inputs_layout = "NHWC"
pre_method = "resize"
pre_scale = [ 255.0, 255.0, 255.0,]
pre_mean = [ 0.0, 0.0, 0.0,]
channel_swap = [ 2, 1, 0,]
network = "./ModelZoo/PPyoloe/ppyoloe_crn_s_300e_coco.onnx"
jr_path = "./json&raw/PPyoloe_crn_s_BY/"

[optimize]
json = "./json&raw/PPyoloe_crn_s_BY/PPyoloe_crn_s_parsed.json"
raw = "./json&raw/PPyoloe_crn_s_BY/PPyoloe_crn_s_parsed.raw"
jr_path = "./json&raw/PPyoloe_crn_s_BY/"

[quantize]
forward_mode = "image"
saturation = "kld"
forward_dir = "./images/ModelZoo_images/coco"
forward_list = "./ModelZoo_images/v3.0_list/coco.txt"
names_file = "./names/coco.names"
bits = 8
json = "./json&raw/PPyoloe_crn_s_BY/PPyoloe_crn_s_optimized.json"
raw = "./json&raw/PPyoloe_crn_s_BY/PPyoloe_crn_s_optimized.raw"
jr_path = "./json&raw/PPyoloe_crn_s_BY/"
per = "tensor"

[adapt]
json = "./json&raw/PPyoloe_crn_s_BY/PPyoloe_crn_s_quantized.json"
raw = "./json&raw/PPyoloe_crn_s_BY/PPyoloe_crn_s_quantized.raw"
jr_path = "./json&raw/PPyoloe_crn_s_BY/"

[generate]
json = "./json&raw/PPyoloe_crn_s_BY/PPyoloe_crn_s_adapted.json"
raw = "./json&raw/PPyoloe_crn_s_BY/PPyoloe_crn_s_adapted.raw"
jr_path = "./json&raw/PPyoloe_crn_s_BY/"
```




`30TAI` 的配置：



PPyoloe_crn_s.toml
``` toml
[parse]
net_name = "PPyoloe_crn_s"
framework = "Onnx"
inputs = [ 1, 640, 640, 3,]
inputs_layout = "NHWC"
pre_method = "resize"
pre_scale = [ 255.0, 255.0, 255.0,]
pre_mean = [ 0.0, 0.0, 0.0,]
channel_swap = [ 2, 1, 0,]
network = "./ModelZoo/PPyoloe/ppyoloe_crn_s_300e_coco.onnx"
jr_path = "./json&raw/PPyoloe_crn_s_ZG/"
target = "zhuge"
inputs_dtype = "UInt8"

[optimize]
json = "./json&raw/PPyoloe_crn_s_ZG/PPyoloe_crn_s_parsed.json"
raw = "./json&raw/PPyoloe_crn_s_ZG/PPyoloe_crn_s_parsed.raw"
jr_path = "./json&raw/PPyoloe_crn_s_ZG/"

[quantize]
forward_mode = "image"
saturation = "kld"
forward_dir = "./images\\2.1ModelZoo_images/coco"
forward_list = "./images\\2.1ModelZoo_images/v3.0_list/coco.txt"
qdtype = "int8"
json = "./json&raw/PPyoloe_crn_s_ZG/PPyoloe_crn_s_optimized.json"
raw = "./json&raw/PPyoloe_crn_s_ZG/PPyoloe_crn_s_optimized.raw"
jr_path = "./json&raw/PPyoloe_crn_s_ZG/"
per = "tensor"

[adapt]
json = "./json&raw/PPyoloe_crn_s_ZG/PPyoloe_crn_s_quantized.json"
raw = "./json&raw/PPyoloe_crn_s_ZG/PPyoloe_crn_s_quantized.raw"
jr_path = "./json&raw/PPyoloe_crn_s_ZG/"

[generate]
json = "./json&raw/PPyoloe_crn_s_ZG/PPyoloe_crn_s_adapted.json"
raw = "./json&raw/PPyoloe_crn_s_ZG/PPyoloe_crn_s_adapted.raw"
jr_path = "./json&raw/PPyoloe_crn_s_ZG/"

```
>**备注**
>`100TAI` 的接口完全与Icraft v3.30之前的版本兼容，`30TAI` 为Icraft v3.30新增支持的后端，使用上与``100TAI`` 略有差异，详见下文`《icraft 参数列表》 <./#_param_line>`_。



如上所示， 在toml文件中，方括号括起来的部分，比如 `[parse]` 和 `[generate]` 等表示一个小节， icraft使用一个小节来配置一个命令。小节的名称，即 `parse` 和 `generate` 等表示被配置的命令，小节中使用 `=` 表达的键值对表示该命令的参数的键和值。例如，当执行 `icraft parse yolov5s.toml` 时， `icraft` 会使用 `[parse]` 这一小节的键值对来配置 `parse` 命令。


除了使用配置文件外，CLI命令 `icraft` 还支持直接使用命令行来指定参数，比如上文中的 `icraft parse PPyoloe_crn_s.toml` ，等价于以下命令：


```
icraft parse                                                                 \
--net_name  PPyoloe_crn_s                                                    \
--framework  Onnx                                                            \
--inputs  1, 640, 640, 3                                                     \
--inputs_layout NHWC                                                         \
--pre_method resize                                                          \
--pre_scale 255.0,255.0,255.0                                                \
--pre_mean 0.0,0.0,0.0                                                       \
--channel_swap 2,1,0                                                         \
--network ./ModelZoo/PPyoloe/ppyoloe_crn_s_300e_coco.onnx.onnx               \
--jr_path "./json&raw/PPyoloe_crn_s_ZG/"                                     \

```



CLI命令还支持配置文件和命令行参数混用，在混用时，命令行参数中的配置将覆盖配置文件中的同名参数，比如 `icraft parser PPyoloe_crn_s.toml --pre_method nop` 会将配置文件中的 `pre_method` 改为 `nop` 。



>备注
>`compile` 命令需要根据配置文件中各个命令的配置依次调用 `parse` , `optimize` , `quantize` , `adapt` , `generate` 等过程，因此不支持使用命令行来指定参数。






## 三 参数列表



目前， `icraft` 支持的命令及其参数如下：


| 组件名称 | 文档 |
| --- | --- |
| parse | [《icraft parse 参数说明表》](component/parse/3_Component_parse.md) |
| optimize | [《icraft optimize 参数说明表》](component/adapt/3_Component_adapt.md) |
| quantize | [《icraft quantize 参数说明表》](component/quantizer/3_Component_quantizer.md) |
| adapt | [《icraft adapt 参数说明表》](component/adapt/3_Component_adapt.md) |
| generate | [《icraft generate 参数说明表》](component/codegen/3_Component_codegen.md) |
| run | [《icraft run 参数说明表》](component/run/3_Component_run.md) |
| show | [《icraft show 参数说明表》](component/show/3_Component_show.md) |
---


