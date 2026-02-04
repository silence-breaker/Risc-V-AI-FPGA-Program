# 更新日志[#](#id1 "此标题的永久链接")

## v3.33.1[#](#v3-33-1 "此标题的永久链接")

1.新增算子
:   == Buyi ==
    - 无
    == Zhuge ==
    - 无

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   * 无

3.新增Feature
:   * Buyi架构下relu前向修改：alpha<0时使用查表前向

## v3.33.0[#](#v3-33-0 "此标题的永久链接")

1.新增算子
:   == Buyi ==
    - 无
    == Zhuge ==
    - 无

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   * 无

3.新增Feature
:   * 无

## v3.31.0[#](#v3-31-0 "此标题的永久链接")

1.新增算子
:   == Buyi ==
    - 无
    == Zhuge ==
    - 无

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   * Cast算子fakeQF时计算错误的问题

3.新增Feature
:   * 调整img2tensor接口，保证3通道图片是RGB格式排布(之前是BGR排布)
    * 调整Resize算子，如果输入数据范围超过int8就转为int16处理

## v3.8.0[#](#v3-8-0 "此标题的永久链接")

1.新增算子
:   == Buyi ==
    - 无
    == Zhuge ==
    (合并分支，初始支持Ops以当前状态为准)

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   * 修复了add, multiply在量化前向时浮点数转定点数时没有考虑fake\_qf的问题
    * 调整了底层数据管理逻辑，避免多个chunk同时指向同一块内存地址导致析构出错
    * 去掉了pad算子在没有’N’ layout的情况下还去掉第0维Pad参数的bug
    * 修复zhuge量化前向bug: sqrt, clamp\_scalar, softshrik
    * 修复zhuge hardopbug: 完善一些数据类型

3.新增Feature
:   * 调整了架构，合并了zhuge分支代码，同时支持Buyi和Zhuge Target，做了很多代码适配但是api基本没有修改
    * 适配xrt前向接口改变，Op的forward接受output\_tensors参数，把输出数据搬移到用户指定的tensor中，在fakeqf模式下不支持该参数
    * 调整buyi-sqrt前向，保留小于0的元素，大于等于0的部分进行sqrt计算
    * 整理buyi-relu前向，前向规则如下：
      :   首先单独的relu 不管是什么relu都是用查表,
          跟在卷积后面的relu 如果卷积输出只给relu 则可以合起来 这个时候只要relu不是relu6或者relux 则都可以用激活模块做 包括leaky relu
          但是如果卷积不仅给relu 还给了其他算子 则不能合起来 这个时候不管是什么relu 都是查表
    * libtorch依赖重新编译，去掉找不到cuda时报warning的特性
    * 修改了Image2Tensor读图方式为-1，可以直接读取所有OpenCV支持的类型图片，不再需要各种Decoder CustomOp

## v3.7.0[#](#v3-7-0 "此标题的永久链接")

1.新增算子
:   * avgpool3d
    * batchnorm3d
    * conv3d
    * conv3d\_transpose
    * instance\_norm3d
    * maxpool3d
    * equal
    * greater
    * greater\_equal
    * less
    * less\_equal
    * not\_equal
    * mean

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   * 无

3.新增Feature
:   * Pad适配3d输入
    * Prelu前向测试通过
    * Ftmp2Tensor添加了文件大小检查，如果文件大小和Tensor大小不匹配报warning
    * 指令仿真申请ddr映射空间时保证空间大小是32字节的倍数，适配指令前向新特性

## v3.6.3[#](#v3-6-3 "此标题的永久链接")

1.新增算子
:   无
    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   无

3.新增Feature
:   * pixel\_shuffle不再要求输入输出layout一致

## v3.6.0[#](#v3-6-0 "此标题的永久链接")

1.新增算子
:   * sum
    * sqrt
    * clamp
    * einsum

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   * 修复了torch数据指针无效时HostBackend析构出错的问题

3.新增Feature
:   无

## v3.5.0[#](#v3-5-0 "此标题的永久链接")

1.新增算子
:   * ChannelShuffle
    * stack
    * unbind

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   无

3.新增Feature
:   * 在Windows平台上pythonAPI支持和Pytorch同时使用，在Linux平台上没有办法支持；

## v3.4.0[#](#v3-4-0 "此标题的永久链接")

1.新增算子
:   * Hard\_tanh
    * Softplus
    * SoftShrink

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   无

3.新增Feature
:   无

## v3.3.0[#](#v3-3-0 "此标题的永久链接")

1.新增算子
:   无
    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   无

3.新增Feature
:   * 支持MMU指令仿真
    * 调整异常抛出机制，抛出异常携带算子的id和类型信息；

## v3.2.0[#](#v3-2-0 "此标题的永久链接")

1.新增算子
:   * Roll

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   无

3.新增Feature
:   无

## v3.1.0[#](#v3-1-0 "此标题的永久链接")

1.新增算子
:   * InstanceNorm2d

    具体算子支持情况详见 [《Icraft-Docs之算子支持》](../../ops/op_support.md)

2.修复Bug
:   无

3.新增Feature
:   无
