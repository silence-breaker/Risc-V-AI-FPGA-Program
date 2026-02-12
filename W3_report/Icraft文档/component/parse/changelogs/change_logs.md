# 更新日志

## 目录

# 更新日志

## v3.33.0

* `功能` 扩充

  > + 新增支持 `ZhugeTarget` , `BuyiTarget` 兼容 v3.8.0.

## v3.8.1

1. 修复bug

* PytorchParser：用户配置输入数量和模型输入数量不一致时不再抛出异常，改为warning
* PytorchParser：修复normalize融合Pass的Layout前后不一致的bug

## v3.8.0

1. 调整算子库

* Pytorch

  + AdaptiveAvgPool3d（新增算子）
  + AdaptiveMaxPool3d（新增算子）
  + AveragePool3D（新增算子）
  + BatchNorm3D（新增算子）
  + Conv3D（新增算子）
  + equal(新增算子)
  + greater(新增算子)
  + great\_equal(新增算子)
  + InstanceNorm3D（新增算子）
  + less(新增算子)
  + less\_equal(新增算子)
  + MaxPool3D（新增算子）
  + not\_equal(新增算子)

2. 新增功能

* PytorchParser：全面升级PytorchParser，完善算子支持范围（详见 [《Icraft-Docs之算子支持》](../../ops/framework.md#pytorch)），支持常数折叠、预检、unsupport算子解析等功能

3. 修复bug

* OnnxParser：修复网络多个输出中包含SequenceConstruct算子时解析错误的bug
* OnnxParser：修复读取网络内部Bool类型参数错误的bug

## v3.7.0

1. 调整算子库

* Onnx

  + AveragePool（完善算子支持程度，支持AveragePool3D）
  + BatchNormalization（完善算子支持程度，支持BatchNormalization3D）
  + Conv（完善算子支持程度，支持Conv3D）
  + Equal(新增算子)
  + Gemm（完善算子支持程度，完全支持）
  + Greater(新增算子)
  + GreatOrEqual(新增算子)
  + InstanceNormalization（完善算子支持程度，支持InstanceNormalization3D）
  + Less(新增算子)
  + LessOrEqual(新增算子)
  + MaxPool（完善算子支持程度，支持MaxPool3D）
  + Not(新增算子)
  + Pad（完善算子支持程度，支持Pad3D）
  + ReduceMax(新增算子)
  + ReduceMean（完善算子支持程度，完全支持）

2. 新增功能

* OnnxParser：升级OnnxParser，支持unsupport算子：对于不支持算子解析为unsupport算子占位并保存josn&raw文件，方便查看、分析网络
* OnnxParser：新增支持TensorFlow2Onnx的模型：支持tf1、tf2保存的Onnx模型，仅支持data\_format为默认值channels\_last，即排布为NHWC格式

3. 修复的bug

* OnnxParser：修复Gather算子indices为负数解析错误的bug
* OnnxParser：修复Squeeze算子axis为空时不支持解析的bug

## v3.6.3

1. 调整算子库

* Onnx

  + normalize（新增pattern）

## v3.6.2

1. 修复bug

* OnnxParser：修复OnnxParser无法在win7上编译的bug

## v3.6.1

1. 修复bug

* OnnxParser：修复pixelshuffle添加transpose错误的bug
* OnnxParser：修复pad中pad value为空的bug

## v3.6.0

1. 调整算子库

* Pytorch

  + sum（新增算子）
  + sqrt（新增算子）
  + clamp（新增算子，约束详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md#pytorch)）
  + einsum（新增算子）

2. 新增功能

* 所有Parser：根据Icraft硬件特性，升级parser对1D算子的解析方式，从而提升1D算子的性能
* 所有Parser：升级预检功能，新增参数pre\_check，默认为true，用于启动整个编译器级别的模型预检；配置为false，则只完成Praser组件的预检，目前仅OnnxParser支持升级后的模型预检功能
* OnnxParser：全面升级OnnxParser，OnnxParser目前支持Pytorch（opset17）、PaddlePaddle（opset11），具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

## v3.5.0

1. 调整算子库

* Pytorch

  + ChannelShuffle（新增算子）
  + stack（新增算子）
  + unbind（新增算子）

## v3.4.0

1. 调整算子库

* Pytorch

  + hard\_tanh（新增算子）
  + Softplus（新增算子）
  + SoftShrink（新增算子）
  + AdaptiveMaxPool2d（完善算子支持程度，完全支持）
  + AdaptiveAvgPool2d（完善算子支持程度，完全支持）

2. 修复bug

* PytorchParser：修复expand算子参数dim=-1时，显示不支持该算子
* PytorchParser：修复relu6解析错误

## v3.3.0

1. 调整算子库

* Pytorch

  + AdaptiveMaxPool1d（新增算子）
  + Batchnorm1d（新增算子）
  + Conv1d（新增算子）
  + Maxpool1d（新增算子）
  + InstanceNorm1d（新增算子）

## v3.2.0

1. 调整算子库

* Pytorch

  + Roll（新增算子，约束详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md#pytorch)）
  + AvgPool1d（新增算子）
  + AdaptiveAvgPool1d（新增算子，约束详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md#pytorch)）
  + bmm（新增算子）
  + Add（完善算子支持程度：完全支持）
  + Multiply（完善算子支持程度：完全支持）
  + Matmul（完善算子支持程度：完全支持）

2. 新增功能

* PytorchParser：扩充支持pytorch2.0.1

## v3.1.1

1. 修复bug

* PytorchParser：修复多输出算子的bug，影响网络：img\_cnn\_lstm

## v3.1.0

1. 调整算子库

* Pytorch

  + InstanceNorm2d（新增算子）
  + AdaptiveMaxPool2d（新增算子：仅支持可以等效为MaxPool的场景）
  + Reshape（完善算子支持程度：完全支持）
  + View（完善算子支持程度：完全支持）
  + Add（添加算子约束：不支持input0为常量，input1为变量的场景）
  + Multiply（添加算子约束：不支持input0为常量，input1为变量的场景）
  + Matmul（添加算子约束：不支持input0为常量，input1为变量的场景）
* Onnx(PaddlePaddle)

  + Reshape（完善算子支持程度：完全支持）
  + View（完善算子支持程度：完全支持）
  + Add（添加算子约束：不支持input0为常量，input1为变量的场景）
  + Multiply（添加算子约束：不支持input0为常量，input1为变量的场景）
  + Matmul（添加算子约束：不支持input0为常量，input1为变量的场景）

目录