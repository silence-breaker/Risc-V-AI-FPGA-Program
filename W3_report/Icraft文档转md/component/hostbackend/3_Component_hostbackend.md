# Icraft HostBackend

## 一 简介

Icraft HostBackend(以下简称HostBackend)是Icraft XRT的计算后端之一，主要负责Host(CPU)和Cuda(NvidiaGpu)计算资源的初始化和前向计算。

从用户角度上，HostBackend模块包括HostBackend、CudaDevice、CudaMemRegion三个数据结构（因为其特殊性，HostDevice和HostMemRegion由XRT直接定义和管理），分别是XRT的Backend、Device、MemRegion在CPU和CUDA
计算资源上的具体实现。用户可以通过C++或Python的API实例化并使用HostBackend、HostDevice、CudaDevice，具体用法请见文档API说明和下文中的代码用例。

在内部实现上，HostBackend负责Icraft算子在CPU和CUDA后端硬件上的初始化和前向计算。

此外，为了方便用户和开发者，HostBackend提供了一个Utils接口，提供了若干功能函数，包括Image2Tensor、Ftmp2Tensor、Cast、DecodeWithDecoder，使用方法请见文档API说明和下文中的代码用例。

## 二 接口说明

下面的代码说明了如何使用HostBackend、HostDevice和CudaDevice。

### 2.1 C++接口使用说明

#### 2.1.1 创建基于HostDevice或CudaDevice的Session

```
auto json_file = "D:/Workspace/V3.0/SSD_BY.json";
auto raw_file = "D:/Workspace/V3.0/SSD_BY.raw";

// 初始化设备
auto host_device = HostDevice::Default();
auto cuda_device = CudaDevice::Default();

// 加载网络
auto network = Network::CreateFromJsonFile(json_file);
network.loadParamsFromFile(raw_file);

// 创建基于CudaDevice的Session,
// 仅限于有Cuda设备的环境里，否则无法运行;
// 在某些无法运行在Cuda设备上的算子会自动跳转到host_device上运行；
auto sess_cuda = Session::Create<HostBackend>(network, { cuda_device });

// 创建基于HostDevice的Session
auto sess_host = Session::Create<HostBackend>(network, { host_device });

// 创建Session2
// 如果不适用模板Create方法，也可以使用CreateByOrder方法
auto sess_cuda1 = Session::CreateByOrder(network, {host_backend}, {cuda_device});
auto sess_host1 = Session::CreateByOrder(network, {host_backend}, {host_device});
```

#### 2.1.2 fakeQf模式

```
// 创建Backend对象
auto host_backend = HostBackend::Init();

// HostBackend有两个独有的接口：setFakeQf和getFakeQf。通过它们可以设置和查询HostBackend算子定点前向（数据类型非FP32的前向）是否以fake模式进行。
// fakeQf是fake quantize forward的简称，该模式下定点前向过程中不做截位和饱和操作，
// 因此可以直接对比HostBackend的指令前向结果和adapted模型的前向结果
host_backend.setFakeQf(true); // 激活fakeQF模式
bool fakeQf = host_backend.getFakeQf(); // 查询fakeQF模式
if(fakeQf){
 printf("Xrt HostBackend FakeQf mode on.\n");
}
host_backend.setFakeQf(false); // 关闭fakeQF模式
fakeQf = host_backend.getFakeQf(); // 查询fakeQF模式
if(!fakeQf){
 printf("Xrt HostBackend FakeQf mode off.\n");
}
```

#### 2.1.3 Utils使用方法

```
// Image2Tensor使用方法
// 读取image(opencv支持的图片类型，如png,jpg,jpng等）转为xrt::Tensor
auto img_file = "D:/Workspace/imgs/cat224.png";
// 读取img_file路径上的图片转为Tensor，高和宽均为原图大小
auto img_tensor_orig = Image2Tensor(img_file);
// 读取img_file路径上的图片转为Tensor，height resize为300, width保留原图大小
auto img_tensor_300_224 = Image2Tensor(img_file, 300, -1）
// 读取img_file路径上的图片转为Tensor，height保留原图大小, width resize为300
auto img_tensor_224_300 = Image2Tensor(img_file, -1, 300）

// Ftmp2Tensor使用方法
// 读取ftmp二进制文件转为xrt::Tensor
auto ftmp_file = "D:/Workspace/ftmp/value0.ftmp";
// 读取ftmp_file路径下的ftmp二进制文件转为value对应的Tensor, value为xir的Value类数据
// 根据value创建一个Tensor，把读取自ftmp_file的数据绑定到该Tensor上
auto v_tensor = Ftmp2Tensor(ftmp_file, value);

// Cast使用方法
// 输出的Tensor是输入Tensor的数据类型(int8_t, float32等)和Layout(NHWC等)
// 从input_dtype转为output_dtype的结果。需要注意，数据类型的转换需要由data_type提供normratio。
// auto tensor_new = Cast(tensor_old, tensor_old_dtype, tensor_new_dtype, host_backend);

// DecodeWithDecoder使用方法
// 将数据文件使用用户提供的CustomDecoder模块解析为HostDevice上的Xrt Tensor
// tensor_new = DecodeWithDecoder(dll_path, file_path, data_type);
```

### 2.2 Python接口使用说明

#### 2.2.1 创建基于HostDevice或CudaDevice的Session

```
import xir
from xrt import *
from host_backend import *
import unittest
import os

json_file = "D:\debugs\hostbknd\jr\optimized\Resnet18_optimized.json"
raw_file = "D:\debugs\hostbknd\jr\optimized\Resnet18_optimized.raw"
img_file = "D:\debugs\hostbknd\imgs\cat224.png"

# 初始化设备
host_device = HostDevice.Default()
cuda_device = CudaDevice.Default()

# 加载网络
network = xir.Network.CreateFromJsonFile(json_file)
network.loadParamsFromFile(raw_file)

# 创建基于CudaDevice的Session,
# 仅限于有Cuda设备的环境里，否则无法运行;
# 在某些无法运行在Cuda设备上的算子会自动跳转到host_device上运行；
sess_cuda = Session.Create([HostBackend], network.view(0), [cuda_device])

# 创建基于HostDevice的Session
sess_host = Session.Create([HostBackend], network.view(0), [host_device])

# 创建Session2
# 如果不适用模板Create方法，也可以使用CreateByOrder方法
sess_cuda1 = Session.CreateByOrder(network.view(0), [HostBackend.Init()], [CudaDevice.Default()])
sess_host1 = Session.CreateByOrder(network.view(0), [HostBackend.Init()], [HostDevice.Default()])
```

#### 2.2.2 fakeQf模式

```
# 创建Backend对象
host_backend = HostBackend.Init()

# fakeQF模式
# HostBackend有两个独有的接口：setFakeQf和getFakeQf。通过它们可以设置和查询HostBackend算子定点前向（数据类型非FP32的前向）是否以fake模式进行。
# fakeQf模式下定点前向过程中不做截位和饱和操作，因此可以直接对比HostBackend的指令前向结果和adapted模型的前向结果
host_bknd = HostBackend.Init()
host_bknd.setFakeQf(True) # 激活fakeQF模式
fakeQf = host_bknd.getFakeQf() # 查询fakeQF模式
if fakeQf:
    print("HostBackend fakeQf mode is on.")
host_bknd.setFakeQf(False) # 关闭fakeQF模式
fakeQf = host_bknd.getFakeQf() # 查询fakeQF模式
if not fakeQf:
    print("HostBackend fakeQf mode is off.")
```

#### 2.2.3 Utils使用方法

```
# Image2Tensor使用方法
# 读取image(opencv支持的图片类型，如png,jpg,jpng等）转为xrt::Tensor
img_file = "D:/Workspace/imgs/cat224.png";
# 读取img_file路径上的图片转为Tensor，高和宽均为原图大小
img_tensor_orig = Image2Tensor(img_file);
# 读取img_file路径上的图片转为Tensor，height resize为300, width保留原图大小
img_tensor_300_224 = Image2Tensor(img_file, 300, -1）
# 读取img_file路径上的图片转为Tensor，height保留原图大小, width resize为300
img_tensor_224_300 = Image2Tensor(img_file, -1, 300）

# Ftmp2Tensor使用方法
# 读取ftmp二进制文件转为xrt::Tensor
ftmp_file = "D:/Workspace/ftmp/value0.ftmp";
# 读取ftmp_file路径下的ftmp二进制文件转为value对应的Tensor, value为xir的Value类数据
# 根据value创建一个Tensor，把读取自ftmp_file的数据绑定到该Tensor上
v_tensor = Ftmp2Tensor(ftmp_file, value);

# Cast使用方法
# 输出的Tensor是输入Tensor的数据类型(int8_t, float32等)和Layout(NHWC等)
# 从input_dtype转为output_dtype的结果。需要注意，数据类型的转换需要由data_type提供normratio。
#tensor_new = Cast(tensor_old, tensor_old_dtype, tensor_new_dtype, host_backend);

# DecodeWithDecoder使用方法
# 将数据文件使用用户提供的CustomDecoder模块解析为HostDevice上的Xrt Tensor
#tensor_new = DecodeWithDecoder(dll_path, file_path, data_type);
```

### 2.3 其他HostBackend接口

除了上述几个接口之外，HostBackend还提供了若干其他接口，c++/Python接口使用方法和fakeQf模式类似，这里不再赘述，具体请参考API文档。

## 三 算子说明

HostBackend主要实现内容是Icraft所有算子在HostBackend上的初始化、前向计算以及相关数据管理。
目前实现了所有Icraft算子在HostDevice(CPU)上的实现，由于一些约束，部分计算尚未支持CUDA，在前向计算过程中CUDA不支持时会自动回落到Host上进行计算。
下表是HostBackend支持的算子以及支持情况。

| 算子名称 | CPU支持 | CUDA支持 | 备注 |
| --- | --- | --- | --- |
| add | √ | √ |  |
| align\_axis | √ | √ |  |
| avg\_pool2d | √ | 部分支持 | 仅在左右pad相等且上下pad相等时支持CUDA |
| batchnorm | √ | √ |  |
| cast | √ | √ |  |
| concat | √ | √ |  |
| conv2d | √ | √ |  |
| conv2d\_transpose | √ | √ |  |
| copy | √ | √ |  |
| divide\_scalar | √ | √ |  |
| elu | √ | √ |  |
| gelu | √ | √ |  |
| hardop | √ | x | hardop是硬件指令前向，暂不支持CUDA |
| hardsigmoid | √ | 部分支持 | 仅当alpha参数为3时支持CUDA |
| hardswish | √ | √ |  |
| input | x 标记算子，无需计算 | x 标记算子，无需计算 |  |
| layernorm | √ | √ |  |
| matmul | √ | √ |  |
| maxpool | √ | √ |  |
| mish | √ | √ |  |
| multiply | √ | √ |  |
| output | x 标记算子，无需计算 | x 标记算子，无需计算 |  |
| pad | √ | √ |  |
| pixel\_shuffle | √ | √ |  |
| prelu | 尚未支持定点前向 | 尚未支持定点前向 |  |
| prune\_axis | √ | √ |  |
| relu | √ | 部分支持 | max\_value != DBL\_MAX 或 threshold != 0时不支持CUDA计算 |
| reshape | √ | √ |  |
| resize | √ | x | 通过opencv实现，暂不支持CUDA计算 |
| sigmoid | √ | √ |  |
| silu | √ | √ |  |
| slice | √ | √ |  |
| softmax | √ | √ |  |
| split | √ | √ |  |
| squeeze | √ | x | 只是维度信息的更新，不需要CUDA加速 |
| swap\_order | √ | √ |  |
| tanh | √ | √ |  |
| transpose | √ | √ |  |
| upsample | √ | √ |  |

## 四 错误码 errorcode

### 4.1 错误码说明

**12000:**

* `argueparse解析报错`

**12001:**

* `缺少必须参数`

**12002:**

* `文件或路径不存在`

**12003:**

* `参数超出范围、格式错误`

**12004-12009:**

* `预留错误码`

**12010:**

* `Dll加载相关错误`

**12011:**

* `参数类型或值错误`

**12012:**

* `文件加载失败`

## 五 License

This project includes the following third-party libraries:

* [MNN]([alibaba/MNN](https://github.com/alibaba/MNN)): Licensed under the Apache License 2.0. See the LICENSE file in the third-party library.
* [Libtorch]([pytorch/pytorch](https://github.com/pytorch/pytorch)): Licensed under the BSD-style. See the LICENSE file in the third-party library.

## 六 索引

* [索引](genindex.md)

* [C++ API reference](_cppapi/api_root.md)
  + [Class Hierarchy](_cppapi/api_root.md#class-hierarchy)
  + [File Hierarchy](_cppapi/api_root.md#file-hierarchy)
  + [Full API](_cppapi/api_root.md#full-api)
* [Python API reference](_autosummary/host_backend.md)
  + [host\_backend.Cast](_autosummary/host_backend.Cast.md)
  + [host\_backend.DecodeWithDecoder](_autosummary/host_backend.DecodeWithDecoder.md)
  + [host\_backend.Ftmp2Tensor](_autosummary/host_backend.Ftmp2Tensor.md)
  + [host\_backend.Image2Tensor](_autosummary/host_backend.Image2Tensor.md)
  + [host\_backend.CudaDevice](_autosummary/host_backend.CudaDevice.md)
  + [host\_backend.CudaMemRegion](_autosummary/host_backend.CudaMemRegion.md)
  + [host\_backend.HostBackend](_autosummary/host_backend.HostBackend.md)

## 七 注意事项

在3.8版本开始支持Buyi和Zhuge两种Target，在算子实现内部添加了一个checkTarget接口，用来保证算子前向时input tensor是符合op绑定的target的。
但是，目前有一个数据类型uint8处于悬空状态，它在网络初始阶段出现，为了兼容它，形变算子/cast/resize算子跳过了检查。
后续需要定位清楚uint8在编译体系中的位置，然后再针对性地调整代码。
