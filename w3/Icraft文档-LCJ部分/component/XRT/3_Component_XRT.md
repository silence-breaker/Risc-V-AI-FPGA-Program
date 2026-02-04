
                  
  
# Icraft XRT

Icraft XRT是统一前向后的运行时，在XRT中，不再区分仿真和运行，而是把不同的计算资源抽象为不同的后端，使得Icraft中的网络能够在任意的计算资源上完成计算。
XRT主要有以下数据结构组成：

- `Device` ：抽象了具体的硬件设备，比如一个板卡。一个 `Device` 中包含若干个 `RegRegion` 和 `MemRegion` ，分别表示不同的寄存器区域和内存区域

- `MemChunk` ： `MemRegion` 分配的一块连续内存

- `Tensor`：表示前向的输入和输出，包含 `dtype` 和 `chunk` 等属性分别描述数据类型和和数据

- `Backend` ：表示某一种计算资源，比如Host(CPU), Cuda（GPU）和Buyi(加速器)。 `Backend` 包含了其所支持的每一个算子在该计算资源上初始化和前向计算的逻辑。

- `Session`：表示会话（进程），主要的用户接口。创建 `Session` 的过程就是资源分配的过程，即将网络的每一个算子绑定到合适的计算资源（ `Backend` ）上。

以上数据结构之间的关系如下图所示：

Icraft XRT包括以下几个后端：HostBackend、BuyiBackend、ZG330Backend，分别表示不同的计算资源。
由于布衣和诸葛硬件架构的特殊性，对于XRT的API接口使用也不尽相同，这里特殊说明XRT的API接口在这两个后端使用上的区别：

- `前向时指定output tensor的数据存储地址` ：使用ZG330Backend进行前向时，可指定前向结果output tensor的数据存储地址，使用示例详见 `XRT手册的 1.3.2 小节`。该功能在BuyiBackend中暂不支持。

- `保存ocm上的数据` ： ZG330Backend支持表达ocm上的tensor，因此，如果开了ocm优化，可以保存在ocm上的中间层结果，使用示例详见 `XRT手册的 1.4.3 小节`。该功能在BuyiBackend中不支持，只能保存在etm上的中间层结果。

## 一 快速开始

## 1.1 创建Session

创建Session的过程就是将算子绑定到后端的过程。创建Session有三种方法：

- 按优先级将算子绑定到指定的后端

- 直接使用绑定好算子和设备的后端

- 直接使用序列化Session得到的快照文件

## 1.1.1 按优先级创建Session

## C++ 示例

```cpp
auto json_file = "D:/Workspace/V3.0/SSD_BY.json";
auto raw_file = "D:/Workspace/V3.0/SSD_BY.raw";
auto img_file = "D:/Workspace/V3.0/ssd300.png";

// 打开设备
auto host_device = HostDevice::Default();
auto buyi_device = Device::Open("axi://ql100aiu?npu=0x40000000&dma=0x80000000");

// 加载网络
auto network = Network::CreateFromJsonFile(json_file);
network.loadParamsFromFile(raw_file);

// 创建Session1
// 该方法会根据模板参数的顺序，自动创建Backend对象
// 首先尝试将算子绑定到BuyiBackend上，如果不支持，则绑定到HostBackend上
auto sess1 = Session::Create<BuyiBackend, HostBackend>(network, { buyi_device, host_device });

// 获取sess1所有的Backends
auto& backends = sess1->backends;
auto buyi_backend = backends[0].cast<BuyiBackend>();
auto host_backend = backends[1].cast<HostBackend>();

// 手动创建Backend对象
auto buyi_backend = BuyiBackend::Init();
auto host_backend = HostBackend::Init();

// 创建Session2
// 如果不适用模板Create方法，也可以使用CreateByOrder方法，将算子按顺序绑定到已有的Backend对象上
auto sess2 = Session::CreateByOrder(network, {buyi_backend, host_backend}, {buyi_device, host_device});
```

## Python示例

```python
# 导入必要的库
import xir
from xrt import *
from host_backend import *
from buyi_backend import *
import unittest

# 获取一个网络
# Input → Conv2d → Cast → HardOp → Cast → ReLU → MaxPool2d → Output
network = GenerateNetwork()

# 创建Session，按顺序传入想要绑定的后端类型
sess1 = Session.Create([BuyiBackend, HostBackend], network.view(0), [ HostDevice.Default(), Device() ])
sess1.apply()

backend_bindings = sess1.backendBindings()
self.assertTrue(backend_bindings[1].is_type(HostBackend)) # Conv2d
self.assertTrue(backend_bindings[2].is_type(HostBackend)) # Cast
self.assertTrue(backend_bindings[3].is_type(BuyiBackend)) # HardOp
self.assertTrue(backend_bindings[4].is_type(BuyiBackend)) # Cast
self.assertTrue(backend_bindings[5].is_type(HostBackend)) # ReLU
self.assertTrue(backend_bindings[6].is_type(HostBackend)) # MaxPool2d

# 也可以使用CreateByOrder方法，将算子按顺序绑定到已有的Backend对象上
sess2 = Session.CreateByOrder(network.view(0), [BuyiBackend.Init(), HostBackend.Init()], [ HostDevice.Default(), Device() ])
```

## 1.1.2 使用绑定好算子和设备的后端创建Session

## C++ 示例

```cpp
// 创建网络
auto network = generate_network("whatever", Framework::PYTORCH, "v1.9");

// 打开设备
auto host_device = HostDevice::Default();
auto buyi_device = Device::Open("axi://ql100aiu?npu=0x40000000&dma=0x80000000");

// 创建后端，并绑定网络视图和设备
auto host_backend = Backend::Create<HostBackend>(network.view({0, 1, 2, 5, 6, 7}), host_device);
auto buyi_backend = Backend::Create<BuyiBackend>(network.view(std::vector<int64_t>{3, 4}), buyi_device);

// 创建Session
// 直接使用指定后端已有的绑定关系
auto sess = Session::CreateWithBackends(network, { host_backend, buyi_backend });
```

## Python示例

```python
# 导入必要的库
import xir
from xrt import *
from host_backend import *
from buyi_backend import *
import unittest

# 获取一个网络
# Input → Conv2d → Cast → HardOp → Cast → ReLU → MaxPool2d → Output
network = GenerateNetwork()

# 创建HostBackend，绑定算子0, 1, 2, 5, 6, 7
host_backend = Backend.Create(HostBackend, network.view([0, 1, 2, 5, 6, 7]), HostDevice.Default())
# 创建BuyiBackend，绑定算子3, 4
buyi_backend = Backend.Create(BuyiBackend, network.view([3, 4]), Device())

# 创建Session
# 直接使用指定后端已有的绑定关系
sess = Session.CreateWithBackends(network.view(0), [ host_backend, buyi_backend ])
sess.apply()

backend_bindings = sess.backendBindings()
self.assertTrue(backend_bindings[1].is_type(HostBackend)) # Conv2d
self.assertTrue(backend_bindings[2].is_type(HostBackend)) # Cast
self.assertTrue(backend_bindings[3].is_type(BuyiBackend)) # HardOp
self.assertTrue(backend_bindings[4].is_type(BuyiBackend)) # Cast
self.assertTrue(backend_bindings[5].is_type(HostBackend)) # ReLU
self.assertTrue(backend_bindings[6].is_type(HostBackend)) # MaxPool2d
```

## 1.1.3 使用序列化得到的快照文件

该创建session的方式包含了构造网络network和apply部署，
且mmu模式、合并算子和内存优化等配置无效，是与生成快照文件时的配置一致。
序列化session生成快照文件的方法详见1.2小节。

## C++ 示例

```cpp
// 直接使用序列化得到的快照文件创建Session
Session sess = Session::CreateWithSnapshot(snapshot_file, { BuyiBackend::Init(), HostBackend::Init() }, { device, HostDevice::Default() });
```

## Python示例

```python
# 直接使用序列化得到的快照文件创建Session
sess = Session.CreateWithSnapshot(snapshot_file,[ BuyiBackend, HostBackend ],[device, HostDevice.Default()])
```

## 1.2 序列化Session生成快照文件

目前序列化session仅支持BY阶段的网络，对device、backend的各项配置请在序列化前进行调用。

```cpp
// 打开设备

// 加载网络

// 创建Session

// 部署session

// 序列化session，并保存快照文件至指定路径
sess.dumpSnapshot(filepath);
```

```python
# 打开设备

# 加载网络

# 创建Session

# 部署session

# 序列化session，并保存快照文件至指定路径
sess.dumpSnapshot(filepath)
```

提示
代码示例中的缺省部分参考1.1.1节，这里仅展示必要的接口使用方式和调用位置

## 1.3 Session前向

为了满足不同场景的需求，Session提供了两个前向的API：

- forward: 直接前向Session中绑定的整个网络视图

- stepTo: 前向到指定的算子

## 1.3.1 forward前向

## C++ 示例

```cpp
auto json_file = "D:/Workspace/V3.0/ssd300_quantized.json";
auto raw_file = "D:/Workspace/V3.0/ssd300_quantized.raw";
auto img_file = "D:/Workspace/V3.0/resnet18.png";

// 创建网络
auto network = Network::CreateFromJsonFile(json_file);
network.loadParamsFromFile(raw_file);

// 创建Session
auto sess = Session::Create<HostBackend>(network, { HostDevice::Default()});
// 应用Session的设置
sess.apply();

// 构造输入Tensor
auto input_dtype = network.inputOp()[0].dtype();
auto input_tensor = img2Tensor(img_file, input_dtype);

// 前向Session中绑定的整个网络视图
// 前向的过程即遍历网络视图中的每一个算子，执行其指定后端上的前向函数
// 若算子的输入来自外部，则按顺序从输入列表中取
auto output_tensors = sess.forward({ input_tensor });
```

## 1.3.2 forward前向，指定输出tensor数据存储地址

该API仅支持ZGBackend使用，BYBackend暂不支持。
主要应用于以下场景：

- 多次前向，输出存放至不同地址

- 环形网络，输入输出地址相同

## C++ 示例

```cpp
// 创建网络

// 创建Session

// 部署Session

// 构造输入Tensor
auto input_dtype = network.inputOp()[0].dtype();
auto input_tensor = img2Tensor(img_file, input_dtype);

std::vector<Tensor> output_tensors;
//构造输出tensor
for (const auto& output : network.outputs()) {
   auto output_chunk = device.defaultMemRegion().malloc(output.storageBytes(), true, 4096);
   //输出数据会保存在output_chunk对应的物理地址
   auto tensor = Tensor(output.tensorType(), output_chunk, 0);
   output_tensors.emplace_back(tensor);
}

session.forward(input_tensors, output_tensors);
```

提示
output_tensors可以是PL或者PS上的tensor，
output_tensors必须包含网络所有的输出，且都分配了内存

## 1.3.3 stepTo前向

## C++ 示例

```cpp
auto json_file = "D:/Workspace/V3.0/ssd300_quantized.json";
auto raw_file = "D:/Workspace/V3.0/ssd300_quantized.raw";
auto img_file = "D:/Workspace/V3.0/resnet18.png";

// 创建网络
auto network = Network::CreateFromJsonFile(json_file);
network.loadParamsFromFile(raw_file);

// 创建Session
auto sess = Session::Create<HostBackend>(network, { HostDevice::Default()});
// 应用Session的设置
sess.apply();

// 构造输入Tensor
auto input_dtype = network.inputOp()[0].dtype();
auto input_tensor = img2Tensor(img_file, input_dtype);
// 用于保存输出
auto output_tensors = std::vector<Tensor>();

// 以下代码使用stepTo实现了获取网络每个算子的执行结果，并dump
for (auto&& op : sess->network_view->ops) {
   // 前向到Op ID指定的算子，并返回该算子的输出
   // stepTo会记录上次前向到的位置，下次调用时会从记录位置开始继续前向
   // 只有在算子的输入来自外部时，才会取输入Tensor列表中的，否则使用生产者算子产生的Tensor
   output_tensors = sess.stepTo(op.opId(), { input_tensor });

   for (uint64_t i = 0; i < op.outputsNum(); i++) {
      auto output = op[i];
      auto output_tensor = output_tensors[i];

      std::string dump_dir = "dumps.SQB";
      std::filesystem::create_directory(dump_dir);
      auto os = std::ofstream(fmt::format("{}/{}.ftmp", dump_dir, output->v_id), std::ios::binary);
      output_tensors[0].dump(os, "SQB");
   }
}
```

## 1.4 前向Debug功能

前向前配置以下接口，可提供debug信息和功能，默认关闭：

- setLogIO：每层前向结束打印算子信息以及输入输出的信息, 如果开启了算子连贯执行，标注HardOp（Merged）

- setLogTime：每层前向结束打印算子耗时信息，如果开启了算子连贯执行，标注HardOp（Merged）

- setDumpOutputs：每层前向结束保存输出结果至指定路径下，如果需要保存中间每层结果，请关闭算子连贯执行

- setPreCallBack、setPostCallBack：设置回调函数，进行自定义操作，可在每层前向函数前和后被调用

## 1.4.1 setLogIO

## C++ 示例

```cpp
// 创建网络

// 创建Session

// 部署Session

// 配置Session
session.setLogIO(true);

//前向
```

## 1.4.2 setLogTime

## C++ 示例

```cpp
// 创建网络

// 创建Session

// 部署Session

// 配置Session
session.setLogTime(true);

//前向
```

## 1.4.3 setDumpOutputs

## C++ 示例

```cpp
// 创建网络

// 创建Session

// 部署Session

// 配置Session
session.setDumpOutputs(true, "./", "HQB");

//前向
```

## 1.4.4 setPreCallBack、setPostCallBack

## C++ 示例

```cpp
//每层前向前的回调函数定义
void preFunc(const Session& sess, const Operation& op,
const Backend& backend, std::vector<Tensor>& output_tensors) {
   ICRAFT_LOG(INFO).append("before forward op: {} \n", op->op_id);
}
//每层前向后的回调函数定义
void postFunc(const Session& sess, const Operation& op,
const Backend& backend, std::vector<Tensor>& output_tensors) {
   ICRAFT_LOG(INFO).append("after forward op: {} \n", op->op_id);
}

// 创建网络

// 创建Session

// 部署Session

// 配置Session
session.setPreCallBack(preFunc);
session.setPostCallBack(postFunc);

//前向
```

## 1.5 获取内存分配情况功能

成功打开硬件设备后，若分配了内存，可通过以下接口获取内存分配情况，以及对应Memchunk的引用：
目前暂不支持host device。

```cpp
// 打开设备
auto buyi_device = Device::Open("axi://ql100aiu?npu=0x40000000&dma=0x80000000");

// 分配内存
auto plddr_region = buyi_device.getMemRegion("plddr");
auto chunk1 = plddr_region.malloc(1024);
auto chunk2 = plddr_region.malloc(MemPtr(8192), 1024);
//获得当前已分配的所有MemChunk
auto pl_chunks = plddr_region.memManager().getAllMemChunk();
//获得指定的MemChunk，如果不存在，返回nullopt
auto unique_chunk = plddr_region.memManager().getMemChunk(MemPtr(4096), 1024);
```

## 二 数据结构

## 2.1 MemPtr

`MemPtr` 是对内存地址的统一抽象，无论是Host上、加速器上还是交换空间的内存地址都能通过MemPtr表达。
`MemPtr` 有三种类型：

- `PtrType::CPTR` ：C指针类型，主要来表达Host（操作系统）上的内存地址

- `PtrType::ADDR` ：物理地址类型，主要来表达加速器上的内存地址

- `PtrType::BOTH` ：包含以上两者，即既可以使用C指针访问，又可以通过物理地址访问，主要来表达交换空间的内存地址

`MemPtr` 可以表达空指针，即表示不指向任何内存地址。当且仅当 `MemPtr` 的类型是 `PtrType::CPTR` 且C指针为 `nullptr` 时，表示该 `MemPtr` 为空指针。
以下是一些 `MemPtr` 的使用和测试示例：

```cpp
// 空指针的几种构造方法
auto null_ptr1 = MemPtr::Init();
auto null_ptr2 = MemPtr(nullptr);
auto null_ptr3 = MemPtr::NullPtr();
REQUIRE(null_ptr1.isNull());
REQUIRE(null_ptr2.isNull());
REQUIRE(null_ptr3.isNull());

// 构造一个PtrType::CPTR类型的MemPtr
char tmp[8];
auto c_ptr1 = MemPtr(tmp);
REQUIRE(c_ptr1.ptype() == PtrType::CPTR);
REQUIRE(c_ptr1.cptr() == tmp);
REQUIRE(!c_ptr1.isNull());

// 构造一个PtrType::ADDR类型的MemPtr
auto addr = 0x40000000;
auto addr_ptr1 = MemPtr(addr);
REQUIRE(addr_ptr1.ptype() == PtrType::ADDR);
REQUIRE(addr_ptr1.addr() == addr);
REQUIRE(!addr_ptr1.isNull());

// 构造一个PtrType::BOTH类型的MemPtr
auto both_ptr1 = MemPtr(tmp, addr);
REQUIRE(both_ptr1.ptype() == PtrType::BOTH);
REQUIRE(both_ptr1.cptr() == tmp);
REQUIRE(both_ptr1.addr() == addr);
REQUIRE(!both_ptr1.isNull());

// MemPtr的一些运算
auto both_ptr2 = 40 + both_ptr1;
REQUIRE(both_ptr2 - both_ptr1 == 40);
REQUIRE(both_ptr1 - both_ptr2 == -40);
REQUIRE(both_ptr2 - 40 == both_ptr1);
REQUIRE(both_ptr1 < both_ptr2);
REQUIRE(both_ptr1 <= both_ptr2);
REQUIRE(both_ptr2 > both_ptr1);
REQUIRE(both_ptr2 >= both_ptr1);
```

## 2.2 MemRegion

`MemRegion` 表示设备上的一块独立的内存区域，不同的内存区域的内存访问实现方式可能不相同，比如布衣架构设备上的PLDDR和交换空间的区域。
`MemRegion` 抽象了一些内存访问的接口，这些接口需要被具体的 `MemRegion` 子类来实现。以下以 `SampleMemRegion` 为例，展示具体的接口定义和实现方法：

```cpp
class SampleMemRegionNode : public NodeBase<SampleMemRegionNode, MemRegionNode> {
     private:
   /** MemRegion的初始化接口，在该接口的实现中初始化资源 */
   virtual void init() override { ... ... };

   /** MemRegion的关闭接口，在该接口的实现中关闭初始化的资源 */
   virtual void deinit() override { ... ... };

   /**
    * @brief MemRegion的读接口，将指定位置的数据读到数据缓存.
    * @param dest               数据被读取到char*表示的缓存
    * @param src                     从该位置开始读取数据
    * @param byte_size       读取数据的字节大小
    */
   virtual void read(char* dest, const MemPtr& src, uint64_t byte_size) const override { ... ... };

   /**
    * @brief MemRegion的写接口，将数据缓存中数据写到指定位置.
    * @param dest               数据被写入的位置
    * @param src                     char*表示的数据缓存
    * @param byte_size       写入数据的字节大小
    */
   virtual void write(const MemPtr& dest, char* src, uint64_t byte_size) const override { ... ... };

   /**
    * @brief MemRegion的内存分配接口，分配指定大小的内存.
    * @param byte_size       分配内存的大小
    * @param auto_free       指定分配的内存是否会被自动释放
    */
   virtual MemChunk malloc(uint64_t byte_size, bool auto_free) const override { ... ... };

   /**
    * @brief MemRegion的内存分配接口，尝试分配指定位置开始的内存
    * @param begin           指定的内存位置
    * @param byte_size       分配内存的大小
    * @param deleter         内存释放的自定义函数，若指定了FChunkDeleter，则调用该函数来释放内存
    * @param auto_free       指定分配的内存是否会被自动释放
    */
   virtual MemChunk malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter, bool auto_free) const override { ... ... };

   /**
    * @brief MemRegion的内存释放接口，释放指定位置的内存
    * @param src             指定的内存位置
    */
   virtual void free(const MemPtr& src) const override { ... ... };

   /**
    * @brief MemRegion的内存复制接口，在指定的内存位置间复制数据
    * @param dest            内存复制的目的位置
    * @param src                     内存复制的源位置
    * @param byte_size       内存复制的字节大小
    */
   virtual void memcpy(const MemPtr& dest, const MemPtr& src, uint64_t byte_size) const override { ... ... };

   /**
    * @brief MemRegion的跨MemRegion内存复制接口
    * @param dest_ptr        内存复制的目的位置
    * @param src_region      内存复制的源MemRegion
    * @param src_ptr         内存复制的源位置
    * @param byte_size       内存复制的字节大小
    *
    * @note 该接口有默认实现，即将源MemRegion的数据复制到Host，然后写的目的MemRegion.
    * 若硬件对两个MemRegion之间的复制有特殊优化，可以覆盖实现
    */
    virtual void memcpy(
      const MemPtr& dest_ptr,
      const MemRegion& src_region,
      const MemPtr& src_ptr,
      uint64_t byte_size
    ) const override { ... ... };
     };

     class SampleMemRegion : public HandleBase<SampleMemRegion, MemRegion, SampleMemRegionNode> {};
```

更详细的示例请参考AXIQL100AIUDevice中 `AXIQL100AIUdmaMemRegion` 和 `AXIQL100AIPLDDRMemRegion` 的实现。

## 2.3 RegRegion

`RegRegion` 表示设备上的一块独立的寄存器区域，不同的寄存器区域的内存访问实现方式可能不相同。
`RegRegion` 抽象了一些寄存器访问的接口，这些接口需要被具体的 `RegRegion` 子类来实现。以下以 `SampleRegRegion` 为例，展示具体的接口定义和实现方法：

```cpp
class SampleRegRegionNode : public NodeBase<SampleRegRegionNode, RegRegionNode> {
private:
   /** RegRegion的初始化接口，在该接口的实现中初始化资源 */
   virtual void init() override { ... ... }

   /** RegRegion的关闭接口，在该接口的实现中关闭初始化的资源 */
   virtual void deinit() override { ... ... }

   /**
    * @brief RegRegion的读数据接口.
    * @param addr            读取的地址
    * @param relative        是否以相对地址读取数据
    * @return 读取到的寄存器数据
    */
   virtual uint64_t read(uint64_t addr, bool relative = false) const override { ... ... }

   /**
    * @brief RegRegion的写数据接口.
    * @param addr            写入的地址
    * @param data            写入的数据
    * @param relative        是否以相对地址写入数据
    */
   virtual void write(uint64_t addr, uint64_t data, bool relative = false) const override { ... ... }
};

class SampleRegRegion : public HandleBase<SampleRegRegion, RegRegion, SampleRegRegionNode> {};
```

## 2.4 MemChunk

`MemChunk` 表示某一个内存区域上分配的一块连续内存块。`MemChunk` 没有构造函数，所有的 `MemChunk` 都是由 `MemRegion` 的 `malloc` 方法分配产生的。
`MemRegion` 的 `malloc` 方法具有以下两种形式：

- `malloc(uint64_t byte_size, bool auto_free = true)` ：申请分配指定大小的内存块，当 `auto_free = true` 时，分配的内存在 `MemChunkNode` 析构时会自动释放，否则则不会自动释放。

- `malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter, bool auto_free)` : 申请分配指定位置开始的内存。该接口允许自定义内存释放方法，当 `deleter` 不为空时，会调用 `deleter` 来释放内存；auto_free的含义同上。

`MemChunk` 具有读写等一些列方法，当通过 `malloc` 分配得到 `MemChunk` 后，可以通过这些方法来操作分配所得内存：

- `read` ：读取数据

- `write` : 写入数据

- `copyFrom` ：从其他MemChunk复制数据

- `free` ：释放该MemChunk所占用的内存

- `isOn` ：检查该MemChunk是否位于某个MemRegion上

以上方法的具体定义请参考API。

## 2.5 Device

`Device` 是一系列 `MemRegion` 和 `RegRegion` 的集合。实现一个 `Device` 的主要过程就是声明该设备包含哪些 `MemRegion` 和 `RegRegion`
以下以 `AXIQL100AIUDevice` 为例，展示Device的实现方法：

```cpp
class AXIQL100AIUDeviceNode : public NodeBase<AXIQL100AIUDeviceNode, BuyiDeviceNode> {
public:
   // 调用宏声明该设备所包含的MemRegion和RegRegion
   // 需要注意的是AXIQL100AIPLDDRMemRegion需要依赖AXIQL100AIUdmaMemRegion，因此二者的声明有先后顺序
   // 还需要注意的是每个设备都包含一个默认的MemRegion和RegRegion
   ICRAFT_DECLARE_DEVICE_NODE(AXIQL100AIUDeviceNode){
      ICRAFT_MEM_REGION_FIELD(udma, AXIQL100AIUdmaMemRegion);
      ICRAFT_DEFAULT_MEM_REGION_FIELD(plddr, AXIQL100AIPLDDRMemRegion);
      ICRAFT_DEFAULT_REG_REGION_FIELD(npu, AXIQL100RegRegion);
   }

   // 实现初始化函数，在设备初始化是做一些信息打印
   virtual void init() override {
      spdlog::info("设备初始化成功,版本信息：");
      for(auto&& [i, v] : version()){
         spdlog::info("\t{}: {}", i, v);
      }
      spdlog::info("设备协议：{}", protocol);
      spdlog::info("设备名称：{}", device);
      spdlog::info("设备参数：");
      for(auto&& [k, v] : params){
         spdlog::info("\t{}: {}", k, v);
      }
      reset(0);
   }

   virtual void deinit() override {

   }
};

class AXIQL100AIUDevice : public HandleBase<AXIQL100AIUDevice, BuyiDevice, AXIQL100AIUDeviceNode> {};

// 注册该设备，注册后即可通过该URL打开设备
ICRAFT_REGISTER_DEVICE("axi://ql100aiu", AXIQL100AIUDevice);
```

## 2.6 Tensor

`Tensor` 表示前向工程中算子的输入和输出，包含 `dtype` 和 `chunk` 等属性分别描述数据类型和和数据。
以下是一些 `Tensor` 的使用和测试示例：

```cpp
// 使用已有的TensorType和MemChunk构造
auto host_mregion = HostDevice::MemRegion();
auto chunk1 = host_mregion.malloc(ttype1.bytes());
auto ttype1 = TensorType(FloatType::FP32(), { 1, 416, 416, 3 }, Layout("NHWC"));
auto tensor1 = Tensor(ttype1, chunk1);
auto data1 = tensor1.data();

REQUIRE(data1 == chunk1->begin);
REQUIRE(tensor1.isReady());
REQUIRE(tensor1.isOn(host_mregion));
REQUIRE(tensor1.memRegion().same_as(host_mregion));

// 将Tensor复制到指定的host_mregion的上
// 如果该Tensor已经在指定的MemRegion上，则复制不会发生，而是直接返回原Tensor
auto tensor2 = tensor1.to(host_mregion);
REQUIRE(tensor2.same_as(tensor1));

// 从xir::Params构造Tensor
auto weight = Params(ttype1).fill<float>([](size_t i) { return (float)i; });
auto tensor3 = Tensor(weight);
REQUIRE(tensor3.dtype() == weight.dtype());
auto data3 = tensor3.data();
tensor1.fill<float>([](size_t i) { return (float)i; });
auto equal = memcmp(data1.cptr(), data3.cptr(), ttype1.bytes()) == 0;
REQUIRE(equal);

auto chunk2_is_deleted = false;
{
   // tensor5 只有类型，没有数据
   auto ttype2 = TensorType(IntegerType::SInt8(), { 8 }, Layout("*"));
   auto tensor5 = Tensor(ttype2);
   REQUIRE(!tensor5.hasData());
   {
      auto tensor4 = Tensor(ttype2);
      REQUIRE(!tensor4.hasData());
      {
         // chunk2 在申请内存时指定了自定义的释放函数
         // 因此chunk2在析构释放内存时会调用该函数
         char buf[8];
         auto chunk2 = host_mregion.malloc(MemPtr(buf), 8, [&](auto& begin) {
            chunk2_is_deleted = true;
            std::cout << "chunk2 is deleted now!" << std::endl;
         });
         // tensor4和tensor5都包含了chunk2
         tensor4.setData(chunk2);
         tensor5.setData(chunk2);
      }
      REQUIRE(tensor4.hasData());
             }
   // 这里tensor4析构，但是chunk2不会析构，因为还有tensor5引用了它
   REQUIRE(!chunk2_is_deleted);
}
// 这里tensor5也析构了，chunk2也会被析构
REQUIRE(chunk2_is_deleted)

auto ttype3 = TensorType(FloatType::FP16(), { 1, 2, 3, 4 }, Layout("NHWC"));
auto checked_ready = false;
auto check_func = [&](const Device& device) {
   return checked_ready;
}

// 构造Tensor时可以指定一个状态查询函数
// mallocOn可以在指定的MemRegion分配Tensor所需大小的内存
auto tensor6 = Tensor(ttype3, check_func).mallocOn(HostDevice::MemRegion())
// 如果Tensor创建时指定了状态查询函数，那么该Tensor默认是不ready的
REQUIRE(!tensor6.isReady());
// 调用waitForReady，不断查询Tensor状态，直到ready或超时
// 此处checked_ready一直为false，因此会超时
REQUIRE(!tensor6.waitForReady(1000ms, 1ms));
// 把checked_ready设为true，则waitForReady成功
checked_ready = true;
tensor6.waitForReady(1000ms);
REQUIRE(tensor6.isReady());
```

Tensor的dump方法支持将内存中的数据导出到指定的输出流。
dump方法的接口定义如下：
`void dump(std::ostream& os, const std::string& format = "") const`
其中 `format` 默认为空，表示将内存中的原生数据导出到输出流。
当 `format` 不为空时，可以通过三个字母来表示：

- 第一个字母表示排布， `H` 表示硬件， `S` 表示软件

- 第二个字母表示数值， `F` 表示浮点， `Q` 表示定点

- 第三个字母表示序列化形式， `B` 表示二进制， `T` 表示文本

需要注意的是，若一个 `Tensor` 原本的排布时 `H` ，那么可以转为 `S` ；若原本的数值为 `Q` ，那么可以转为 `F` ；反之不可。

## 2.7 Backend

`Backend` 表示的是一种计算资源，比如Host(CPU), Cuda（GPU）和Buyi(加速器)。 `Backend` 包含了其所支持的每一个算子在该计算资源上初始化和前向计算的逻辑。
`Backend` 抽象了一系列后端相关的接口，这些接口需要被具体的 `Backend` 子类来实现。以下以 `SampleBackend` 为例，展示具体的接口定义和实现方法：

```cpp
class SampleBackendNode : public NodeBase<SampleBackendNode, BackendNode> {
public:
   bool fake_qf;     //每个后端可以设置一些独有的选项

private:
   /**
    * @brief 初始化Backend
    * @param network_view    网络
    * @param device                  设备
    */
   virtual void init(const NetworkView& network_view, const Device& device) override {... ... }

   /** 释放Backend */
   virtual void deinit() override {... ... }

   /** 应用Backend的一些选型 */
   virtual void apply() override {... ... }

   /** 复制一个Backend用于多线程 */
   virtual Backend fork() override {... ... }

   virtual void view(uint64_t start_index, uint64_t end_index) override {... ... }
   virtual MergedOps autoMerge() override {... ... }
   };

class SampleBackend : public HandleBase<SampleBackend, Backend, SampleBackendNode> {
public:
   // 提供方法设置相应的选项
   void setFakeQF(bool fake_qf);
};
```

除了实现以上 `Backend` 的接口外，还需要实现每一个支持的算子在该后端上的初始化和前向逻辑，以下是添加算子到后端的示例：

```cpp
// 调用宏添加Conv2d算子的初始化和前向实现
ICRAFT_ADD_OP_TO_BACKEND(Conv2d, SampleBackend)
.set_init([](const Conv2d& op, SampleBackend backend) {
   fmt::print("Initing Conv2d for samplebackend!\n");
})
// 所有的Backend在前向时都需要考虑计时功能
// 当backend->time_profile = true时，开启计时
// 计时结束调用setTimeElapses记录计时数据
.set_forward([](const Conv2d& op, const std::vector<Tensor>& inputs, SampleBackend backend) -> std::vector<Tensor> {
   static utils::Timer t;
   if (backend->time_profile) t.tik();
   fmt::print("Forwarding Conv2d for samplebackend!\n");
   return { Tensor(TensorType(FloatType::FP32(), { 1, 2, 3, 4 }, Layout("NHWC"))) };
   if (backend->time_profile) {
      t.tok();
      auto elapse = t.elapsed<milliseconds>();
      backend.setTimeElapses(op.opId(), 0, elapse);
   }
});

// 向后端添加算子时可以设置约束
// 比如该实例通过约束实现了，当Cast算子的输入和输出都在ETM上时，才在SampleBackend计算
// 可以调用Backend的isOpSupported来检查算子能否在该后端上计算
ICRAFT_ADD_OP_TO_BACKEND(Cast, SampleBackend)
.set_init([](const Cast& op, SampleBackend backend) {
   fmt::print("Initing Cast for samplebackend!\n");
})
.set_forward([](const Cast& op, const std::vector<Tensor>& inputs, SampleBackend backend) -> std::vector<Tensor> {
   fmt::print("Forwarding Cast for samplebackend!\n");
   return { Tensor(TensorType(FloatType::FP32(), { 2, 2, 3, 4 }, Layout("NHWC"))) };
})
.set_constraint([](const Cast& op, SampleBackend backend) {
   auto& input_mtype = op.getInput(0)->mtype;
   auto& ouput_mtype = op[0]->mtype;
   return input_mtype.is<ExternalMem>() && ouput_mtype.is<ExternalMem>();
});
```

## 2.8 Session

表示会话（进程），主要的用户接口，用户通过 `Session` 的接口来描述如何把网络放到各个后端上计算。创建 `Session` 的过程就是资源分配的过程，即将网络的每一个算子绑定到合适的计算资源（Backend）上。
`Session` 的创建和前向方法在《快速开始》部分已经进行说明，此处不再赘述。
`Session` 还支持一些选项，以控制前向的过程。目前支持的选项如下：

- `enableTimeProfile` ，使能时间分析功能

以下是使用示例:

```cpp
auto json_file = "D:/Workspace/V3.0/ssd300_quantized.json";
   auto raw_file = "D:/Workspace/V3.0/ssd300_quantized.raw";
   auto img_file = "D:/Workspace/V3.0/ssd300.png";

   // 加载网络
   auto network = Network::CreateFromJsonFile(json_file);
   network.loadParamsFromFile(raw_file);

   // 创建Session
   auto sess = Session::Create<HostBackend>(network, { HostDevice::Default()});
   // 使能时间分析
   sess.enableTimeProfile(true);
   // 应用选项
   sess.apply();

   // 前向
   auto input_dtype = network.inputOp()[0].dtype();
   auto input_tensor = img2Tensor(img_file, input_dtype);
   auto output_tensors = sess.forward({ input_tensor });

   // 获取时间分析结果
   auto profile_results = sess.timeProfileResults();
   for (auto&& [op_id, result] : profile_results) {
      auto&& [wall, mem, hard, other] = result;
      fmt::print("op_id = {}, wall = {}ms, mem = {}ms, hard = {}ms, other = {}ms\n", op_id, wall, mem, hard, other);
   }
   // 获取总的执行时间
   // 无论是否开启时间分析功能，总时间都会被统计
   fmt::print("total_time = {}s\n", sess.totalTime<seconds>());
```

## 三 错误码 errorcode

## 3.1 错误码说明

**11002:**

- `文件或路径不存在`

**11003:**

- `参数超出范围、格式错误`

**11004-11009:**

- `预留错误码`

**11010:**

- `参数类型或值错误`

**11011:**

- `文件加载失败`

**11012:**

- `接口调用逻辑错误`

**11013:**

- `Backend内部错误`

**11014:**

- `Device内部错误`

**11015:**

- `运行超时`

## 三 索引

- [索引](genindex.md)

- [C++ API reference](_cppapi/api_root.md)

- [Python API reference](_autosummary/xrt.md)

                