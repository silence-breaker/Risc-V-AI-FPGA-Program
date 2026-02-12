
                  
  
# 更新日志

## v3.31.0

- 

**算子变更**

- 
`Add` 的属性 `alpha` 或 `beta` 如果是数组，则元素数量必须与通道数相同

- 
`BatchNorm` 的属性 `variance` 或 `mean` 元素数量必须与通道数相同

- 
`Conv` 输入和卷积核的数据类型必须一致

- 
`Conv` 输入通道必须等于卷积核的 `I` 通道数 * `groups`

- 
`Conv` 偏置如果有的话，通道数必须与卷积核的 `O` 通道数相等

- 
`InstanceNorm` 的属性 `gamma` 或 `beta` 如果存在，则元素数量必须与通道数相同

- 
`LogSoftmax` 的属性 `axis` 下标不能越界

- 
`Matmul` 两个输入中至少一个是 `Value`

- 
`Layout` 中小写字母的坐标轴单位长度必须等于 `Shape` 中对应的维度

- 
修复 `Matmul` 算子自动形状推导时的 `bug`

- 
修复 `Split` 算子自动形状推导时的 `bug`

- 
`HardOp` 的属性 `instr` 从 `Params` 扩展为 `Array<Params>`

- 

**代码重构**

- 
`ZhugeTarget` 的属性 `chips` 修改为 `core`

- 
重构 `Equal/Clone` 机制，支持用户在自定义上下文中修改 `Equal/Clone` 规则

- 
`(Exp)QuantizedScaleArray` 的 `split` 方法升级：现在新增 `stride` 参数，默认依然为 `1`

- 

**Network 相关**

- 
`Network` 构造函数添加参数 `ai_target` ，准备部署到的 `ICore` 后端，默认为 `BuyiTarget`

- 
`Network` 接管算子的 `Params` 输入

- 
修复 `NetworkBase::setAITarget` 不支持 `WolongTarget` 的 `bug`

- 
`loadParams` 相关接口新增 `calc_md5` ，表示反序列化时是否计算参数的 `MD5` ，默认开启

- 

**其它更新**

- 
`flatbuffers` 序列化时 `Params` 的数据 `4K` 对齐

- 
序列化 `Raw` 时，重复的 `Params` 只存储一次

- 
`Params` 现在直接记录绑定到的 `Network` ， `Value` 依然通过 `Op` 间接绑定

- 
`paramsAttrs` 返回值从哈希表改为列表

- 
修复 `paramsAttrs` 无法获取到 `Array` 中的 `Params` 的问题

- 
修复 `Operation::paramsAttrs(true)` 对空 `Array` 失效的 `bug`

- 
修复克隆无数据的 `Params` 时的错误

## v3.30.0

- 

**算子变更**

- 
`Reshape` 算子构造函数现在必须传入 `Layout`

- 
修复 `Transpose` 算子自动形状推到时，输出未深度克隆的 `bug`

- 
修复 `Argmax` 算子自动形状推导时，特殊情况会产生形状为空的输出的 `bug`

- 
部分算子的输出形状推导支持了动态形状

- 

**代码重构**

- 

**规范化大量算子的命名，但兼容旧命名**

- 
`Avgpool` -> `AvgPool2d`

- 
`Batchnorm` -> `BatchNorm2d`

- 
`Conv2dTranspose` -> `ConvTranspose2d`

- 
`Elu` -> `ELU`

- 
`Gelu` -> `GELU`

- 
`Layernorm` -> `LayerNorm`

- 
`Maxpool` -> `MaxPool2d`

- 
`Prelu` -> `PReLU`

- 
`Relu` -> `ReLU`

- 
`Silu` -> `SiLU`

- 
将全部 `double` 类型替换为 `float`

- 
移除老 `IR` 及其相关 `API`

- 

**Network 相关**

- 
`NetworkBase` 新增属性 `ai_target` ，表示准备部署到的 `ICore` 后端

- 
`Network` 新增方法 `dumpToFile` ：将所有序列化方式通过枚举类型统一起来

- 

**文档**

- 
将主文档中网络部分移至单独的侧栏

- 

**Bug 修复**

- 
修复了 `OptionalOpPattern` 在算子有多输出且缺省状态下无法匹配的问题

- 
修复了 `getProducersByOpId` 接口会改变算入输入快查表的问题

- 
修复了 `Array.sort` 不支持 `pod` 类型的问题

- 

**其它更新**

- 
`DataType` 新增方法 `getZeroPoints`、 `setZeroPoints`

- 
新增 `WolongTarget`

- 
`ZhugeTarget` 细分为 `ZG330` 、 `ZG340` 、 `ZG30S` 三种芯片

- 
`BoolType` 从 `IntegerType` 中独立出来

## v3.8.0

- 

**算子变更**

- 
废弃三个 `Darknet` 算子 `Reorg`、 `Route`、 `Yolo` ，但未彻底删除

- 

**代码重构**

- 
移除 `OneResult` 及其相关 `API`

- 
移除 `AndPattern` 及其相关 `API`

- 

**文档**

- 
侧栏《算子 `SPEC` 》栏目移至 `Icraft-Docs` 组件内

- 
移除 `README.md` 文件，更新日志只在此处记录

- 

**其它更新**

- 
`FloatType` 新增两种数据类型： `FPE7M8` 、 `FPE6M9`

- 
`Layout` 新增字母 `L` ，用以支持 `1D` 算子

- 
现在一个 `OpPattern` 可以模糊对应多种算子类型

- 
检查规则⟬ `NormalizedQuantizedType` 的 `normratio` 数量必须与对应维度相等⟭现在只对 `IntegerType` 生效

- 
修复 `Value::setId()` 修改前后 `ID` 相同时产生的错误

## v3.7.0

- 

**算子变更**

- 
新增算子： `Argmax` 、 `Log` 、 `Mean` 、 `Neg`

- 
新增算子： `Equal` 、 `NotEqual` 、 `Greater` 、 `GreaterEqual` 、 `Less` 、 `LessEqual`

- 
新增算子： `AvgPool1d` 、 `BatchNorm1d` 、 `Conv1d` 、 `Conv1dTranspose` 、 `InstanceNorm1d` 、 `MaxPool1d`

- 
新增算子： `AvgPool3d` 、 `BatchNorm3d` 、 `Conv3d` 、 `Conv3dTranspose` 、 `InstanceNorm3d` 、 `MaxPool3d`

- 
新增算子： `Unsupport` ：用来表示目前无法支持的算子，使用该算子以维持网络的完整连接关系

- 
`Squeeze` 移除属性 `layout` ，现在输出 `Layout` 根据输出 `Shape` 的维度数量自动设置为 `***C` 的形式

- 
`HardOp` 取消必须至少有一个输入的检查

- 
`Pad` 输出 `Layout` 不再设置为 `NHWC` ，现在改为与输入 `Layout` 相同

- 
`Resize` 输出 `Layout` 不再设置为 `NHWC` ，现在改为与输入 `Layout` 相同

- 
`Conv2dTranspose` 新增属性 `output_pad_width` 、 `output_pad_height` ，现在定义与框架相同

- 
`Sum` 属性 `dim` 不再要求是严格升序的

- 

**Network 相关**

- 
`NetworkView` 新增方法 `toNetwork()` ：将当前网络视图转为一个独立的网络，如果缺失输入输出会自动补全

- 
`NetworkView` 支持不含任何算子

- 
`NetworkView` 现在不会有重复的输入输出

- 
移除 `Network` 的 `toJson` 、 `CreateFromJson` 方法，可改用其它 `API` 替代

- 
将 `Network.rewrite` 陷入死循环的判断依据从 `1` 千次 改为 `1` 万次

- 
新增方法 `Network.setName`

- 
`NetworkView` 新增方法 `setOutputsOrderByValueIds` ，可以修改输出 `Value` 的顺序

- 
如果 `View` 前后输出 `Value` 仅有顺序不同，则按 `View` 前的原顺序输出；否则按执行序输出

- 

**序列化**

- 
新增一种序列化和反序列化方式： `flatbuffers` [参考链接](../index.md#serialize)

- 
大幅优化 `json` 反序列化时的内存占用和耗时

- 
大幅优化 `msgpack` 反序列化时的内存占用和耗时

- 
三种序列化方式 `dump` 网络到文件方法新增参数 `validate` ，决定序列化时是否检查网络必须符合规范，默认开启

- 

**代码重构**

- 
不再使用 `and` 、 `or` 关键字，改为标准的 `&&` 、 `||`

- 
大量 `set` 方法的返回值改为自身，方便连续多次 `set`

- 
将 `DLL、String` 辅助工具迁移至 `Icraft-Utils`

- 
修复所有在不同编译器下不同的行为

- 
部分接口添加 `const` 限定符

- 
新增 `icraft-xir/ops/ops.h` 头文件，包含了所有算子的头文件

- 

**Value 相关**

- 
修复 `Value` 的 `ID` 不连续的 `bug`

- 
移除 `Value` 不再要求 `Value` 必须存在，增加使用灵活性

- 
`Value` 及 `Params` 现在也支持记录 `tag` 了

- 

**其它更新**

- 
新增模板方法 `TypeName<T>()` ，可获取类型 `T` 的字符串形式

- 
所有 `Node` 均可以通过访问 `::ParentNode` 获取父 `Node`

- 
重构 `visit` 机制，现在使用 `type_name` 而不再是 `type_info` 区分类型

- 
`Array.map` 支持跨 `Pod` 和 `ObjectRef` 转换

- 
`undefined` 的 `ObjectRef` 在 `Clone` 时不再抛异常

- 
`MemType` 新增一种类型： `ChunkMem` [参考链接](../index.md#memtype)

- 
新增 `IsOptionalOp` ，可用于添加不确定是否存在的 `OpPattern`

- 
支持一个算子有多个相同的输入，解除该检查

- 
`DataType` 新增方法 `setStorageType` ，用来设置存储类型

## v3.6.0

- 

**算子变更**

- 
新增算子： `Sum`、 `Sqrt`、 `Hardshrink`、 `LogSigmoid`、 `Softsign`、 `Tanhshrink`、 `ClampScalar`

- 
`Layernorm`、 `Normalize`、 `PruneAxis` 的系数 `axis` 支持负数索引

- 

**Bug 修复**

- 
修复一些头文件 `include` 的缺失

- 

**代码重构**

- 
序列化相关工具独立存放在专门的文件夹中

- 
移除 `MultiYolo`、 `Region`、 `SSDOutput` 三个算子的单元测试、 `pythonAPI`

- 

**其它更新**

- 
`CalibratedTypeNode` 的属性 `mim`、 `max`、 `sat` 从 `double` 升级为 `Array<double>`

- 
`FloatType` 新增 `TF32` 浮点类型

- 
浮点 `QuantizedType` 允许 `scale` 为空

- 
新增检查：算子不能存在两个相同的输入特征图、输出特征图

## v3.5.0

- 

**算子变更**

- 
新增算子 `ChannelShuffle`、 `Einsum`、 `Stack`、 `Unstack`

- 
新增算子 `Clamp`，实际等价于 `Hardtanh`

- 
新增算子 `Swish`，实际等价于 `Silu`

- 
新增算子 `Unbind`，实际等价于 `Unstack`

- 
`Hardsigmoid` 定义进行了修改

- 
大量接口的 `index` 参数现在显式地支持负数索引了

- 
`Pass` 注册方式进行了简化，但保留旧接口

- 
`MergedDistr` 添加 `uvalue` 属性，表示无效值，可选 `ZERO` 表示填 `0`， `NONE` 表示不存在

- 

**Bug 修复**

- 
修复无法 `lazyLoad` 空的 `raw` 文件的 `bug`

- 
修复 `Params`、 `Network` 类型在 `clone` 时未考虑 `depth` 的问题

- 
修复 `Roll` 算子的构造函数中 `dims` 参数传入空的 `Array` 会出错的问题

## v3.4.0

- 

**算子变更**

- 
`AlignAxis` 定义进行了修改，支持 `layout` 之后的输入

- 
`PruneAxis` 定义进行了修改，支持指定去除的无效数据

- 
新增四个激活算子 `Hardtanh`、 `LogSoftmax`、 `Softplus`、 `Softshrink`

- 
废弃三个后处理算子 `MultiYolo`、 `Region`、 `SSDOutput` 和一个后处理属性类 `PriorBox` ，但未彻底删除

- 

**Array 优化**

- 
`Array` 重构，支持存放 `pod` 类型

- 
`Array` 存放 `bool` 时做了特殊优化，一个 `bool` 仅占一个比特

- 
移除类 `PackedFragment`，在序列化和反序列化 `Json` 时不再使用其对 `Array` 做压缩

- 
将 `Array<IntImm>`、 `Array<FloatImm>` 优化为 `Array<int64_t>` 、 `Array<double>` ，网络占用内存减少五倍

- 

**scale & normratio**

- 
新增类 `NormratioArray` ，用来存放 `normratio`

- 
`NormalizedType`、 `NormalizedQuantizedType` 的属性 `normratio` 从 `Array<FloatImm>` 更改为 `NormratioArray`

- 
`NormratioArray`、 `ExpQuantizedScaleArray` 新增属性 `axis`，新增方法 `setAxis`

- 
`scale` 和 `normratio` 在 `Json` 中使用 `RLE` 压缩形式的字符串代称，更加简洁

- 

**其它更新**

- 
新增类 `NetworkBase` 存放原 `Network` 的大部分属性和方法，子类为 `Network` 和 `NetworkView`，所以 `NetworkView` 现在共享 `Network` 的全部接口

- 
使用预编译头文件 `PCH`， `Windows` 下编译快了 `44%`

## v3.3.0

- 

**算子变更**

- 
将 `Add` 算子的属性 `alpha` 、 `beta` 从 `ScalarImm` 扩展为 `Array<ScalarImm>`

- 

**Roll 算子新增检查：**

- 
如果 `dims` 不为 `NullOpt` ， `shifts` 的 `size``必须与 ``dims` 的 `size` 相同

- 
如果 `dims` 为 `NullOpt` ， `shifts` 的 `size` 必须为 `1`

- 

**文档**

- 
侧栏新增《验证规则》栏目，描述现在已经推送的对各类型的验证规则

- 
侧栏新增《算子 `SPEC` 》栏目，描述算子的设计 `SPEC`

- 

**Bug 修复**

- 
修复转译 `AddConst` 算子时 `Layout` 的错误

- 
修复 `OpPattern` 未考虑算子输入可能为 `Params` 的 `bug`

- 
修复 `Linux` 单元测试： `hasAttr` 方法需要明确指定数据位宽，不能使用 `long` 等模糊类型

- 

**Layout 更新**

- 
`Layout` 新增 `isLayouted()` 方法，判断是否是 `Layout` 后的张量数据类型； `Matmul` 算子检验时利用该方法，区分 `Layout` 前后两种情况

- 
`Layout` 新增 `toString()` 方法，便于直接获得字符串形式的 `Layout`

- 

**检查**

- 
为 `Network` 、 `Value` 、 `TensorType` 类型添加 `validate()` ，用来验证该对象是否符合规范

- 
网络必须符合规范，才允许 `dump` 到文件内（ `std::cout` 等其它方式输出不受该限制）

- 
修改检查：网络中最后一个算子必须是 `Output` 改为网络中最后一个算子必须是 `OutputLike`

- 

**其它更新**

- 
将部分 `for` 循环的循环变量改为右值引用，避免复制，提高性能

- 
`MergedAxisDistr` 的构造函数和方法中传入的 `element_num` 参数由 `uint64_t` 改为 `int64_t` ，并添加检查：必须为正整数

- 
`Value` 新增方法 `index()` ，获取该数据在其绑定的算子中的顺序

- 
`Operation` 的方法 `producers()` 、 `consumers()` ， `Network` 的方法 `getProducersByOpId()` 、 `getConsumersByOpId()` 新增参数 `bool sorted = false` ，设为 `true` 时对输出算子列表按执行序排序

- 
`Array` 新增方法 `void sort(std::function<bool(T, T)> comp)` ：对 `Array` 内部元素进行原地排序

## v2.2.0

- 

**算子变更**

- 
新增算子 `Unknown`

- 
新增算子 `Roll`

- 
`HardOp` 新增属性 `layer_count` ，表示硬件 `layer_count` 信息，新增属性 `sub_hard_ops` ，表示 `SpeedMode` 时合并前的 `HardOp` 们

- 

**Bug 修复**

- 
修复 `LazyLoadParams` 未考虑 `ParamsNode` 新增的属性 `_allow_no_data` 的问题

- 
修复 `Network` 的 `rewrite` 方法过多次调用的问题

- 

**其它更新**

- 
`ParamsNode` 新增属性 `_allow_no_data` ，表示是否允许该参数无 `_data`

- 
`Network` 新增方法 `removeOpsById` ，一次性移除网络中的若干算子，但保留它们之间的连接关系

- 
将 `msgpack` 库从 `conan` 移到 `source` 中

- 
修改 `msgpack` 库，在保存浮点数时不再根据数值优化为整数

## v2.1.0

- 

**Network 更新**

- 
`Network` 及 `NetworkView` 新增方法 `viewExcept` ，包含除了指定 `op_id` 们以外的 `op`

- 
`Network` 及 `NetworkView` 新增方法 `viewByOpId` ，通过 `op_id` 指定范围

- 
`Network` 及 `NetworkView` 的 `view` 方法支持负数索引，并对索引进行检查

- 
`Network` 的 `view` 方法支持传入判断函数

- 
为 `Network` 的方法 `allParams`、 `Operation` 的方法 `paramsInputs` 实现 `Python` 接口

- 
`Network` 新增方法 `allParams`，获取网络中所有算子的 `Params`

- 
`Network` 在析构时，会通知所有 `ops` 清除自己记录的所属 `Network`

- 
现在两个 `NetworkView` 可以判断是否相等了。相等条件为：属性 `ops` 、 `network_` 对应相等

- 
`NetworkView` 构造时传入源 `Network`

- 
现在只要有任意个子图存在，原始 `Network` 就不会自动析构；

- 
`NetworkView` 类现在也提供 `getOpIndexById` 方法了，输入 `op_id` 即可查询在子图中的 `index`

- 
将 `Network` 的 `rewrite` 方法，从递归改为循环，减少堆栈占用

- 

**Operation 更新**

- 
`OperationNode` 新增方法 `paramsAttrs` ，获取算子中所有 `Params` 属性的哈希表

- 
`Operation` 新增方法 `paramsInputs` ，获取算子 `Params` 的输入列表

- 

**Bug 修复**

- 
修复 `NetworkView` 类的 `getOpIndexById` 方法计数时不包括输入输出算子的 `bug`

- 

**其它更新**

- 
消除所有 `warning`

- 
`Object` 减引用计数时保证线程安全

- 
`NormalizedType`、 `QuantizedScale`、 `QuantizedScaleArray` 添加属性 `axis=-1` ，表示其系数对应的维度；并提供 `setAxis` 方法供修改

                