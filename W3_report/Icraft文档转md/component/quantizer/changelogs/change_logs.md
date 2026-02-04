# 更新日志

## 目录

# 更新日志

## v3.33.0

* 升级功能

  + 优化混合精度量化，支持自动搜索量化配置，提升网络精度。

## v3.31.0

* 升级功能

  + 当target配置为zhuge情况下,且量化数据类型配置为浮点数据类型（bf16,fp16,tf32,fp32）时,由于不需要进行前向校准过程，因此forward\_dir、forward\_list、saturation和per不再为必须配置项，但若额外配置了混合精度mix\_precision，则上述四个配置仍为必配项。
  + 针对forward\_list中配置的txt文件中的量化校准集参数检查更加完善，路径或者文件不存在、含有特殊字符以及输入个数与实际网络个数不一致均会抛出对应报错信息。

## v3.6.0

* 新增功能

  + 新增算子sqrt
  + 新增算子clamp
* Bug修复

  + 解决split算子normratio中的bug

## v3.5.0

* 新增功能

  + 添加SmoothQuant功能，用于优化transformer中layernorm+matmul结构的量化，该功能需要配置smooth\_alpha参数。详见 [SmoothQuant功能介绍](../index.md#smoothquant)
  + 提供ImageMake接口与Icraft v3.3.0以及之前版本的兼容设计，详见 [imagemake接口介绍](../index.md#noimagemake)

## v3.4.0

* 新增功能

  + 新增算子hard\_tanh
  + 新增算子softplus
  + 新增算子softshrink
  + 支持多维度的自定义量化配置，详见 [自定义量化配置介绍](../index.md#customconfig)
* 性能优化

  + Quantize组件新增参数imagemake来根据imagemake硬件要求约束输入的量化系数，原方案Quantize不管是否使用imagemake，会在满足结构的网络输入端统一做输入量化系数的调整

## v3.3.0

* 新增功能

  + 新增支持add算子的按通道量化
  + 新增自定义量化配置——value\_range，用于解决计算过程中的乘累加溢出问题
* 其它更新

  + 删除接口参数forward\_mode

## v3.2.0

* 新增功能

  + 新增算子roll

目录