
                  
  
# xrt module

icraft xrt python interface

**class Backend(*args, **kwargs)[#](#xrt.Backend)**

表示后端的类型
Overloaded function.

- __init__(self: xrt.Backend) -> None

默认构造函数

- __init__(self: xrt.Backend, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**static Create(backend_type: type, network_view: xir.NetworkView, device: [xrt.Device](#xrt.Device)) → [xrt.Backend](#xrt.Backend)[#](#xrt.Backend.Create)**

创建指定类型的Backend.

**参数:**

- **backend_type** – 后端的类型

- **network_view** – 网络

- **device** – 设备

**apply(self: [xrt.Backend](#xrt.Backend)) → None[#](#xrt.Backend.apply)**

应用Backend的一些选项

**clone(self: [xrt.Backend](#xrt.Backend), depth: int = 1) → [xrt.Backend](#xrt.Backend)[#](#xrt.Backend.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**deinit(self: [xrt.Backend](#xrt.Backend)) → None[#](#xrt.Backend.deinit)**

释放Backend.

**property device[#](#xrt.Backend.device)**

绑定到该后端的设备

**enableTimeProfile(self: [xrt.Backend](#xrt.Backend), enable: bool) → None[#](#xrt.Backend.enableTimeProfile)**

使能时间分析

**fork(self: [xrt.Backend](#xrt.Backend)) → [xrt.Backend](#xrt.Backend)[#](#xrt.Backend.fork)**

复制一个Backend用于多线程

**forwardOp(self: [xrt.Backend](#xrt.Backend), op: xir.Operation, inputs: List[[xrt.Tensor](#xrt.Tensor)], outputs: List[[xrt.Tensor](#xrt.Tensor)] = []) → List[[xrt.Tensor](#xrt.Tensor)][#](#xrt.Backend.forwardOp)**

前向指定的算子.

**参数:**

- **op** – 指定的算子

- **inputs** – 输入的Tensors

- **outputs** – 输出的Tensors

**返回:**

前向的结果

**getForwardFunc(self: [xrt.Backend](#xrt.Backend), op: xir.Operation) → Optional[Callable[[xir.Operation, List[[xrt.Tensor](#xrt.Tensor)], List[[xrt.Tensor](#xrt.Tensor)], [xrt.Backend](#xrt.Backend)], List[[xrt.Tensor](#xrt.Tensor)]]][#](#xrt.Backend.getForwardFunc)**

获取指定算子的前向函数.

**参数:**

**op** – 指定的算子

**返回:**

前向函数(Optional)

**getInitFunc(self: [xrt.Backend](#xrt.Backend), op: xir.Operation) → Optional[Callable[[xir.Operation, [xrt.Backend](#xrt.Backend)], None]][#](#xrt.Backend.getInitFunc)**

获取指定算子的初始化函数.

**参数:**

**op** – 指定的算子

**返回:**

初始化函数(Optional)

**init(self: [xrt.Backend](#xrt.Backend), network_view: xir.NetworkView, device: [xrt.Device](#xrt.Device)) → None[#](#xrt.Backend.init)**

初始化Backend.

**参数:**

- **network_view** – 网络

- **device** – 设备

**initOp(self: [xrt.Backend](#xrt.Backend), op: xir.Operation) → None[#](#xrt.Backend.initOp)**

初始化指定的算子.

**参数:**

**op** – 指定的算子

**isOpSupported(self: [xrt.Backend](#xrt.Backend), op: xir.Operation) → bool[#](#xrt.Backend.isOpSupported)**

检查指定算子是否被支持.

**参数:**

**op** – 指定的算子

**返回:**

如果该算子被支持，后端有该算子的前向实现，则返回True

**property network_view[#](#xrt.Backend.network_view)**

绑定到该后端的网络视图

**setDevice(self: [xrt.Backend](#xrt.Backend), device: [xrt.Device](#xrt.Device)) → [xrt.Backend](#xrt.Backend)[#](#xrt.Backend.setDevice)**

为Backend绑定Device.

**参数:**

**device** – 被绑定的Device

**setTimeElapses(self: [xrt.Backend](#xrt.Backend), op_id: int, memcpy_time: float, hard_time: float) → None[#](#xrt.Backend.setTimeElapses)**

记录指定算子的前向时间（用于Backend的TimeProfile实现）.

**参数:**

- **op_id** – 指定的Op ID

- **memcpy_time** – 数据复制时间

- **hard_time** – 硬件计算时间

**property snapshot[#](#xrt.Backend.snapshot)**

是否是快照模式

**property time_profile[#](#xrt.Backend.time_profile)**

是否开启时间分析

**class BuyiDevice(*args, **kwargs)[#](#xrt.BuyiDevice)**

Overloaded function.

- __init__(self: xrt.BuyiDevice) -> None

- __init__(self: xrt.BuyiDevice, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**calcTime(self: [xrt.BuyiDevice](#xrt.BuyiDevice)) → float[#](#xrt.BuyiDevice.calcTime)**

获取执行时间

**clkFreq(self: [xrt.BuyiDevice](#xrt.BuyiDevice)) → float[#](#xrt.BuyiDevice.clkFreq)**

获取运行频率

**clone(self: [xrt.BuyiDevice](#xrt.BuyiDevice), depth: int = 1) → [xrt.BuyiDevice](#xrt.BuyiDevice)[#](#xrt.BuyiDevice.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**getRowsCols(self: [xrt.BuyiDevice](#xrt.BuyiDevice)) → Tuple[int, int][#](#xrt.BuyiDevice.getRowsCols)**

获取设备使能的MPE的行数和列数

**icoreCalc(self: [xrt.BuyiDevice](#xrt.BuyiDevice), addr: int, size: int) → None[#](#xrt.BuyiDevice.icoreCalc)**

启动Icore计算

**layerCount(self: [xrt.BuyiDevice](#xrt.BuyiDevice)) → int[#](#xrt.BuyiDevice.layerCount)**

获取当前的执行计数

**mmuModeSwitch(self: [xrt.BuyiDevice](#xrt.BuyiDevice), is_on配置mmu模式: bool) → None[#](#xrt.BuyiDevice.mmuModeSwitch)**

**modeInfo(self: [xrt.BuyiDevice](#xrt.BuyiDevice)) → int[#](#xrt.BuyiDevice.modeInfo)**

获取当前mmu模式状态

**readReg(self: [xrt.BuyiDevice](#xrt.BuyiDevice), cid: int, rid: int, offset: int) → int[#](#xrt.BuyiDevice.readReg)**

获取设备使能的MPE的行数和列数

**setClkFreq(self: [xrt.BuyiDevice](#xrt.BuyiDevice), clk_freq: float) → None[#](#xrt.BuyiDevice.setClkFreq)**

设置运行频率

**setDType(self: [xrt.BuyiDevice](#xrt.BuyiDevice), dtype: int) → None[#](#xrt.BuyiDevice.setDType)**

设置NPU计算的数据类型，是8位还是16位

**setEnabledMPE(self: [xrt.BuyiDevice](#xrt.BuyiDevice), rows: int, cols: int) → None[#](#xrt.BuyiDevice.setEnabledMPE)**

设置使能的MPE阵列

**updateBuffer(self: xrt.BuyiDevice, seg_table更新mmu段表: icraft::xrt::SegTable) → None[#](#xrt.BuyiDevice.updateBuffer)**

**writeReg(self: [xrt.BuyiDevice](#xrt.BuyiDevice), cid: int, rid: int, offset: int, data: int) → None[#](#xrt.BuyiDevice.writeReg)**

写指定行列位置的寄存器

**class Device(*args, **kwargs)[#](#xrt.Device)**

表示设备的类型
Overloaded function.

- __init__(self: xrt.Device) -> None

默认构造函数

- __init__(self: xrt.Device, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**static Close(device: [xrt.Device](#xrt.Device)) → None[#](#xrt.Device.Close)**

关闭设备.

**参数:**

**device** – 被关闭的设备对象URL

**static Open(url: str) → [xrt.Device](#xrt.Device)[#](#xrt.Device.Open)**

打开设备.

**参数:**

**url** – 设备的URL

**返回:**

打开的设备对象

**check(self: [xrt.Device](#xrt.Device), level: int) → bool[#](#xrt.Device.check)**

检查设备.

**参数:**

**level** – 检查等级

备注
不同的设备具有不同的定义和实现，详见具体设备的使用说明

**clone(self: [xrt.Device](#xrt.Device), depth: int = 1) → [xrt.Device](#xrt.Device)[#](#xrt.Device.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**defaultMemRegion(self: [xrt.Device](#xrt.Device)) → [xrt.MemRegion](#xrt.MemRegion)[#](#xrt.Device.defaultMemRegion)**

获取设备默认的MemRegion

**defaultRegRegion(self: [xrt.Device](#xrt.Device)) → [xrt.RegRegion](#xrt.RegRegion)[#](#xrt.Device.defaultRegRegion)**

获取设备默认的RegRegion

**getMemRegion(self: [xrt.Device](#xrt.Device), name: str) → [xrt.MemRegion](#xrt.MemRegion)[#](#xrt.Device.getMemRegion)**

根据名字获取设备的MemRegion.

**参数:**

**name** – MemRegion的名字

**返回:**

相对应的MemRegion对象

**getRegRegion(self: [xrt.Device](#xrt.Device), name: str) → [xrt.RegRegion](#xrt.RegRegion)[#](#xrt.Device.getRegRegion)**

根据名字获取设备的MemRegion.

**参数:**

**name** – RegRegion的名字

**返回:**

相对应的RegRegion对象

**malloc(*args, **kwargs)[#](#xrt.Device.malloc)**

Overloaded function.

- malloc(self: xrt.Device, byte_size: int) -> xrt.MemChunk

在默认的MemRegion上申请分配内存.

**参数:**

**byte_size** – 申请的内存大小的名字

**返回:**

申请得到的MemChunk对象

- malloc(self: xrt.Device, mem_region: str, byte_size: int) -> xrt.MemChunk

在指定的MemRegion上申请分配内存.

**参数:**

- **mem_region** – 指定的MemRegion的名字

- **byte_size** – 申请的内存大小

**返回:**

申请得到的MemChunk对象

**readReg(*args, **kwargs)[#](#xrt.Device.readReg)**

Overloaded function.

- readReg(self: xrt.Device, byte_size: int, relative: bool = False) -> int

在默认的RegRegion上读取寄存器.

**参数:**

- **addr** – 读取的地址

- **relative** – 是否以相对地址读取寄存器

**返回:**

读取得到的寄存器数据

- readReg(self: xrt.Device, region_name: str, byte_size: int, relative: bool = False) -> int

在指定的的RegRegion上读取寄存器.

**参数:**

- **region_name** – 指定的RegRegion的名字

- **addr** – 读取的地址

- **relative** – 是否以相对地址读取寄存器

**返回:**

读取得到的寄存器数据

**reset(self: [xrt.Device](#xrt.Device), level: int) → None[#](#xrt.Device.reset)**

复位设备.

**参数:**

**level** – 复位等级

备注
不同的设备具有不同的定义和实现，详见具体设备的使用说明

**setDefaultMemRegion(self: [xrt.Device](#xrt.Device), region_name: str) → [xrt.Device](#xrt.Device)[#](#xrt.Device.setDefaultMemRegion)**

将指定的MemRegion设置为默认MemRegion.

**参数:**

**region_name** – 指定的MemRegion名字

**setDefaultRegRegion(self: [xrt.Device](#xrt.Device), region_name: str) → [xrt.Device](#xrt.Device)[#](#xrt.Device.setDefaultRegRegion)**

将指定的MemRegion设置为默认MemRegion.

**参数:**

**region_name** – 指定的RegRegion名字

**setWaitTime(self: [xrt.Device](#xrt.Device), wait_time: int) → None[#](#xrt.Device.setWaitTime)**

设置同步tensor的最长等待时间

**参数:**

**wait_time** – 等待时间，单位ms

**showStatus(self: [xrt.Device](#xrt.Device), level: int) → None[#](#xrt.Device.showStatus)**

显示设备状态.

**参数:**

**level** – 状态等级

备注
不同的设备具有不同的定义和实现，详见具体设备的使用说明

**version(self: [xrt.Device](#xrt.Device)) → Dict[str, str][#](#xrt.Device.version)**

获取设备的版本

**writeReg(*args, **kwargs)[#](#xrt.Device.writeReg)**

Overloaded function.

- writeReg(self: xrt.Device, addr: int, data: int, relative: bool = False) -> None

将数据写入默认的RegRegion上的寄存器.

**参数:**

- **addr** – 写入的地址

- **data** – 写入的数据

- **relative** – 是否以相对地址写入寄存器

- writeReg(self: xrt.Device, region_name: str, addr: int, data: int, relative: bool = False) -> None

将数据写入指定的RegRegion上的寄存器.

**参数:**

- **region_name** – 指定的RegRegion的名字

- **addr** – 写入的地址

- **data** – 写入的数据

- **relative** – 是否以相对地址写入寄存器

**class HostDevice(self: [xrt.HostDevice](#xrt.HostDevice))[#](#xrt.HostDevice)**

**static Default() → [xrt.HostDevice](#xrt.HostDevice)[#](#xrt.HostDevice.Default)**

获取全局默认的HostDevice对象

**static MemRegion() → [xrt.HostMemRegion](#xrt.HostMemRegion)[#](#xrt.HostDevice.MemRegion)**

获取全局默认的HostDevice的内存区域对象

**class HostMemRegion(self: [xrt.HostMemRegion](#xrt.HostMemRegion))[#](#xrt.HostMemRegion)**

**class MemChunk(*args, **kwargs)[#](#xrt.MemChunk)**

表示一块连续的内存块
Overloaded function.

- __init__(self: xrt.MemChunk) -> None

默认构造函数

- __init__(self: xrt.MemChunk, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**static Init() → [xrt.MemChunk](#xrt.MemChunk)[#](#xrt.MemChunk.Init)**

创建一个初始化(非空)对象

**property begin[#](#xrt.MemChunk.begin)**

内存块开始的位置

**property byte_size[#](#xrt.MemChunk.byte_size)**

内存块的字节大小

**clone(self: [xrt.MemChunk](#xrt.MemChunk), depth: int = 1) → [xrt.MemChunk](#xrt.MemChunk)[#](#xrt.MemChunk.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**copyFrom(self: [xrt.MemChunk](#xrt.MemChunk), dest_offset: int, src_chunk: [xrt.MemChunk](#xrt.MemChunk), src_offset: int, byte_size: int) → None[#](#xrt.MemChunk.copyFrom)**

从其它MemChunk复制数据.

**参数:**

- **dest_offset** – 数据被写入的偏移位置

- **src_chunk** – 源MemChunk

- **src_offset** – 源偏移位置

- **byte_size** – 复制的字节大小

**free(self: [xrt.MemChunk](#xrt.MemChunk)) → None[#](#xrt.MemChunk.free)**

释放该MemChunk所占用的内存

**isOn(self: [xrt.MemChunk](#xrt.MemChunk), arg0: [xrt.MemRegion](#xrt.MemRegion)) → bool[#](#xrt.MemChunk.isOn)**

检查该MemChunk是否位于某个MemRegion上

**read(self: [xrt.MemChunk](#xrt.MemChunk), dest: buffer, src_offset: int, byte_size: int) → None[#](#xrt.MemChunk.read)**

读取指定偏移的数据.

**参数:**

- **dest** – 数据被读取到的位置

- **src_offset** – 从该偏移开始读取数据

- **byte_size** – 读取数据的字节大小

**property region[#](#xrt.MemChunk.region)**

内存块所在的内存区域

**write(self: [xrt.MemChunk](#xrt.MemChunk), dest_offset: int, src: buffer, byte_size: int) → None[#](#xrt.MemChunk.write)**

将数据写到指定偏移位置.

**参数:**

- **dest_offset** – 数据被写入的偏移位置

- **src** – 源数据

- **byte_size** – 写入数据的字节大小

**class MemManager(self: [xrt.MemManager](#xrt.MemManager), arg0: xir.ObjectRef)[#](#xrt.MemManager)**

表示内存管理器的引用类型
将父类强制转换为子类（该类型）

**clone(self: [xrt.MemManager](#xrt.MemManager), depth: int = 1) → [xrt.MemManager](#xrt.MemManager)[#](#xrt.MemManager.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**getAllMemChunk(self: [xrt.MemManager](#xrt.MemManager)) → List[icraft::xrt::MemChunk][#](#xrt.MemManager.getAllMemChunk)**

“获得当前已分配的所有MemChunk”

**getMemChunk(self: [xrt.MemManager](#xrt.MemManager), ptr: [xrt.MemPtr](#xrt.MemPtr), byte_size: int) → Optional[icraft::xrt::MemChunk][#](#xrt.MemManager.getMemChunk)**

“获取指定的已分配内存”

**参数:**

- **ptr** – 内存起始位置

- **byte_size** – 内存大小

**返回:**

若指定起始位置和大小的内存存在，返回对应的MemChunk，否则返回nullopt

**getMemRegionInfo(self: [xrt.MemManager](#xrt.MemManager)) → Dict[str, xir.ObjectRef][#](#xrt.MemManager.getMemRegionInfo)**

“获得设备信息，不同设备保存的信息不同，详见具体设备的内存管理器使用说明”

**class MemPtr(*args, **kwargs)[#](#xrt.MemPtr)**

表示内存指针的引用类型
Overloaded function.

- __init__(self: xrt.MemPtr) -> None

默认构造函数

- __init__(self: xrt.MemPtr, cptr: buffer, addr: int) -> None

构造函数，构造一个PtrType::BOTH类型的MemPtr.

**参数:**

- **cptr** – C指针的值

- **addr** – 物理地址的值

- __init__(self: xrt.MemPtr, cptr: buffer) -> None

构造函数，构造一个PtrType::CPTR类型的MemPtr.

**参数:**

**cptr** – C指针的值

- __init__(self: xrt.MemPtr, addr: int) -> None

构造函数，构造一个PtrType::ADDR类型的MemPtr.

**参数:**

**addr** – 物理地址的值

- __init__(self: xrt.MemPtr, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**static Init() → [xrt.MemPtr](#xrt.MemPtr)[#](#xrt.MemPtr.Init)**

创建一个初始化(非空)对象

**static NullPtr() → [xrt.MemPtr](#xrt.MemPtr)[#](#xrt.MemPtr.NullPtr)**

创建一个空指针.

**addr(self: [xrt.MemPtr](#xrt.MemPtr)) → int[#](#xrt.MemPtr.addr)**

“获取该MemPtr的物理地址, 如果MemPtr为PtrType::CPTR类型时，抛出异常”

**clone(self: [xrt.MemPtr](#xrt.MemPtr), depth: int = 1) → [xrt.MemPtr](#xrt.MemPtr)[#](#xrt.MemPtr.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**cptr(self: [xrt.MemPtr](#xrt.MemPtr)) → str[#](#xrt.MemPtr.cptr)**

获取该MemPtr的C指针, 如果MemPtr为PtrType::ADDR类型时，抛出异常.

**isNull(self: [xrt.MemPtr](#xrt.MemPtr)) → bool[#](#xrt.MemPtr.isNull)**

检查该MemPtr是否是空指针.

**ptype(self: [xrt.MemPtr](#xrt.MemPtr)) → [xrt.PtrType](#xrt.PtrType)[#](#xrt.MemPtr.ptype)**

获取该MemPtr的类型

**class MemRegion(*args, **kwargs)[#](#xrt.MemRegion)**

表示内存区域的类
内存区域表示一块受管理的内存空间，比如NPU的PLDDR或者PS上的UDMABuf区域
Overloaded function.

- __init__(self: xrt.MemRegion) -> None

默认构造函数

- __init__(self: xrt.MemRegion, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**clone(self: [xrt.MemRegion](#xrt.MemRegion), depth: int = 1) → [xrt.MemRegion](#xrt.MemRegion)[#](#xrt.MemRegion.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**device(self: [xrt.MemRegion](#xrt.MemRegion)) → icraft::xrt::Device[#](#xrt.MemRegion.device)**

获取所在的Device

**malloc(*args, **kwargs)[#](#xrt.MemRegion.malloc)**

Overloaded function.

- malloc(self: xrt.MemRegion, byte_size: int, auto_free: bool = True, alignment: int = 1) -> icraft::xrt::MemChunk

申请分配指定大小的内存.

**参数:**

- **byte_size** – 分配内存的大小

- **auto_free** – 指定分配的内存是否会被自动释放

- **alignment** – 指定分配的内存地址字节对齐

- malloc(self: xrt.MemRegion, begin: xrt.MemPtr, byte_size: int, deleter: Callable[[xrt.MemPtr], None] = <built-in method  of PyCapsule object at 0x000001CBF5563F30>, auto_free: bool = True) -> icraft::xrt::MemChunk

申请分配指定位置开始的内存.

**参数:**

- **byte_size** – 分配内存的大小

- **deleter** – 内存释放的自定义函数，若指定了Deleter，则调用该函数来释放内存

- **auto_free** – 指定分配的内存是否会被自动释放

**memManager(self: [xrt.MemRegion](#xrt.MemRegion)) → [xrt.MemManager](#xrt.MemManager)[#](#xrt.MemRegion.memManager)**

获取所属的MemManager

**class PtrType(self: [xrt.PtrType](#xrt.PtrType), value: int)[#](#xrt.PtrType)**

表示指针类型的枚举
Members:
CPTR : C指针
ADDR : 物理地址
BOTH : 既包含C指针，又包含物理地址

**property name[#](#xrt.PtrType.name)**

**class RegRegion(*args, **kwargs)[#](#xrt.RegRegion)**

表示寄存器区域的类
Overloaded function.

- __init__(self: xrt.RegRegion) -> None

默认构造函数

- __init__(self: xrt.RegRegion, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**clone(self: [xrt.RegRegion](#xrt.RegRegion), depth: int = 1) → [xrt.RegRegion](#xrt.RegRegion)[#](#xrt.RegRegion.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**device(self: [xrt.RegRegion](#xrt.RegRegion)) → icraft::xrt::Device[#](#xrt.RegRegion.device)**

获取该RegRegion所在的Device

**read(self: [xrt.RegRegion](#xrt.RegRegion), addr: int, relative: bool = False) → int[#](#xrt.RegRegion.read)**

读取指定地址的数据.

**参数:**

- **addr** – 读取的地址

- **relative** – 是否以相对地址读取数据

**返回:**

读取到的寄存器数据

**write(self: [xrt.RegRegion](#xrt.RegRegion), addr: int, data: int, relative: bool = False) → None[#](#xrt.RegRegion.write)**

将数据写入指定地址.

**参数:**

- **addr** – 写入的地址

- **data** – 写入的数据

- **relative** – 是否以相对地址写入数据

**class Session(*args, **kwargs)[#](#xrt.Session)**

表示会话的类型
Overloaded function.

- __init__(self: xrt.Session) -> None

默认构造函数

- __init__(self: xrt.Session, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**static Create(backend_types: List[type], network: xir.NetworkView, devices: List[[xrt.Device](#xrt.Device)]) → [xrt.Session](#xrt.Session)[#](#xrt.Session.Create)**

创建一个会话，按优先级绑定到指定的后端类型.

**参数:**

- **backend_types** – 会话绑定的后端类型列表

- **network** – 网络视图

- **devices** – 设备列表

备注
设备列表中的Device和后端类型列表中的后端是一一对应的

**static CreateByOrder(network: xir.NetworkView, backends: List[[xrt.Backend](#xrt.Backend)], devices: List[[xrt.Device](#xrt.Device)]) → [xrt.Session](#xrt.Session)[#](#xrt.Session.CreateByOrder)**

创建一个会话，按优先级绑定到指定的后端.

**参数:**

- **network** – 网络视图

- **backends** – 后端列表

- **devices** – 设备列表

备注
设备列表中的Device和后端类型列表中的后端是一一对应的

**static CreateWithBackends(network: xir.NetworkView, backends: List[[xrt.Backend](#xrt.Backend)]) → [xrt.Session](#xrt.Session)[#](#xrt.Session.CreateWithBackends)**

创建一个会话，使用绑定好网络和设备的后端.

**参数:**

- **network** – 网络视图

- **backends** – 后端列表

备注
backends中的后端均已绑定好了网络视图和后端，因此该方法创建Session时不再进行绑定

**static CreateWithSnapshot(filePath: str, backends: List[type], devices: List[[xrt.Device](#xrt.Device)]) → [xrt.Session](#xrt.Session)[#](#xrt.Session.CreateWithSnapshot)**

根据二进制文件反序列化得到session

**参数:**

- **filePath** – 二进制文件保存路径

- **backends** – 后端列表

- **devices** – 设备列表

**static Init() → [xrt.Session](#xrt.Session)[#](#xrt.Session.Init)**

创建一个初始化(非空)对象

**apply(self: [xrt.Session](#xrt.Session)) → None[#](#xrt.Session.apply)**

应用Session的一些选项

**backendBindings(self: [xrt.Session](#xrt.Session)) → Dict[int, [xrt.Backend](#xrt.Backend)][#](#xrt.Session.backendBindings)**

获取会话中所有算子的后端绑定关系.

**返回:**

dict[int, xrt.Backend]表示的算子后端绑定关系，其键为Op ID, 值为该算子绑定的后端

**property backends[#](#xrt.Session.backends)**

绑定到该session的后端

**clone(self: [xrt.Session](#xrt.Session), depth: int = 1) → [xrt.Session](#xrt.Session)[#](#xrt.Session.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**dumpSnapshot(self: [xrt.Session](#xrt.Session), filePath: str) → None[#](#xrt.Session.dumpSnapshot)**

对当前session进行序列化得到二进制文件

**Params filePath:**

二进制文件保存路径

**enableTimeProfile(self: [xrt.Session](#xrt.Session), enable: bool) → None[#](#xrt.Session.enableTimeProfile)**

使能时间分析

**forward(*args, **kwargs)[#](#xrt.Session.forward)**

Overloaded function.

- forward(self: xrt.Session, inputs: List[xrt.Tensor]) -> List[xrt.Tensor]

前向会话中绑定的整个网络视图.

**参数:**

**inputs** – 输入的Tensor列表

**返回:**

整个网络视图的前向结果

2. forward(self: xrt.Session, inputs: List[xrt.Tensor], outputs
前向会话中绑定的整个网络视图.

**参数:**

- **inputs** – 输入的Tensor列表

- **outputs** – 输出的Tensor列表

: List[xrt.Tensor]) -> None

**getForwards(self: [xrt.Session](#xrt.Session)) → List[Tuple[xir.Operation, [xrt.Backend](#xrt.Backend), Callable[[xir.Operation, List[[xrt.Tensor](#xrt.Tensor)], List[[xrt.Tensor](#xrt.Tensor)], [xrt.Backend](#xrt.Backend)], List[[xrt.Tensor](#xrt.Tensor)]], List[int], List[int]]][#](#xrt.Session.getForwards)**

获取会话的前向算子列表

**返回:**

前向算子列表

**property network_view[#](#xrt.Session.network_view)**

会话中的网络视图

**setDumpOutputs(self: [xrt.Session](#xrt.Session), flag: bool, path: str, format: str) → None[#](#xrt.Session.setDumpOutputs)**

设置每层前向结束后是否保存输出结果至指定路径下，默认关闭

**Params flag:**

开启标志

**Params path:**

保存输出结果路径

**Params format:**

指定的输出格式

支持的格式由三个字母表示：

- 第一个字母表示排布，H表示硬件，S表示软件

- 第二个字母表示数值，F表示浮点，Q表示定点

- 第三个字母表示序列化形式，B表示二进制，T表示文本

若一个Tensor原本的排布时H，那么可以转为S；若原本的数值为Q，那么可以转为F；反之不可

**setLogIO(self: [xrt.Session](#xrt.Session), flag: bool) → None[#](#xrt.Session.setLogIO)**

设置每层前向结束后是否打印IO信息，默认关闭

**Params flag:**

开启标志

**setLogTime(self: [xrt.Session](#xrt.Session), flag: bool) → None[#](#xrt.Session.setLogTime)**

设置每层前向结束后是否打印耗时信息，默认关闭

**Params flag:**

开启标志

**setPostCallBack(self: [xrt.Session](#xrt.Session), func: Callable[[[xrt.Session](#xrt.Session), xir.Operation, [xrt.Backend](#xrt.Backend), List[[xrt.Tensor](#xrt.Tensor)]], None]) → None[#](#xrt.Session.setPostCallBack)**

为会话添加回调函数，该回调函数在会话前向之后执行

**Params func:**

回调函数

**setPreCallBack(self: [xrt.Session](#xrt.Session), func: Callable[[[xrt.Session](#xrt.Session), xir.Operation, [xrt.Backend](#xrt.Backend), List[[xrt.Tensor](#xrt.Tensor)]], None]) → None[#](#xrt.Session.setPreCallBack)**

为会话添加回调函数，该回调函数在会话前向之前执行

**Params func:**

回调函数

**stepTo(self: [xrt.Session](#xrt.Session), op_id: int, inputs: List[[xrt.Tensor](#xrt.Tensor)] = []) → List[[xrt.Tensor](#xrt.Tensor)][#](#xrt.Session.stepTo)**

前向到指定的算子.

**参数:**

- **op_id** – 指定算子的Op ID

- **inputs** – 输入的Tensor列表

**返回:**

指定算子的前向结果

备注
只有在算子的输入来自外部时，才会取输入Tensor列表中的，否则使用生产者算子产生的Tensor

**sub(*args, **kwargs)[#](#xrt.Session.sub)**

Overloaded function.

- sub(self: xrt.Session, start_index: int, end_index: int) -> xrt.Session

从该session创建一个新的session, 共享相同的backends, 但是network_view不同.

**参数:**

- **start_index** – NetworkView包含的算子在原网络中的开始索引(包含)，支持负数索引

- **end_index** – NetworkView包含的算子在原网络中的结束索引(不包含)，支持负数索引

**返回:**

创建的session

2. sub(self: xrt.Session, start_index
从该session创建一个新的session, 共享相同的backends, 但是network_view不同.

**参数:**

**start_index** – NetworkView包含的算子在原网络中的开始索引(包含)，支持负数索引

**返回:**

创建的session

: int) -> xrt.Session

**timeProfileResults(self: [xrt.Session](#xrt.Session)) → Dict[int, Tuple[float, float, float, float]][#](#xrt.Session.timeProfileResults)**

获取时间分析的结果.

**返回:**

Dict[int, Tuple[float, float, float, float]]表示的时间分析结果

时间分析结果的键表示Op ID，值表示不同的时间类型，依次如下（单位：ms）：

- 总时间，即墙上时间

- 数据复制时间

- 硬件计算时间

- 其他时间

**totalTime(self: [xrt.Session](#xrt.Session)) → float[#](#xrt.Session.totalTime)**

获取会话总时间（单位：ms）

**class Tensor(*args, **kwargs)[#](#xrt.Tensor)**

表示张量的类型
Overloaded function.

- __init__(self: xrt.Tensor) -> None

默认构造函数

- __init__(self: xrt.Tensor, dtype: xir.TensorType, chunk: xrt.MemChunk, offset: int = 0, check_func: Callable[[xrt.Device], bool] = None) -> None

构造函数.

**参数:**

- **dtype** – 数据类型

- **chunk** – 数据所在的内存块

- **offset** – 数据在内存块中的偏移

- **check_func** – 状态检查函数

- __init__(self: xrt.Tensor, dtype: xir.TensorType) -> None

构造函数，构造一个没有数据的Tensor.

**参数:**

**dtype** – 数据类型

4. __init__(self: xrt.Tensor, dtype: xir.TensorType, check_func
构造函数，构造一个没有数据的Tensor.

**参数:**

- **dtype** – 数据类型

- **check_func** – 状态检查函数

: Callable[[xrt.Device], bool]) -> None

- __init__(self: xrt.Tensor, value: xir.Value) -> None

构造函数，从xir.Value构造.

- __init__(self: xrt.Tensor, b: buffer, layout: xir.Layout = <xir.Layout object at 0x000001CBF5554D70>) -> None

构造函数, 构造一个HostMemRegion上的Tensor, 从buffer推断数据类型并复制数据.

**参数:**

- **b** – python buffer

- **layout** – 数据排布

- __init__(self: xrt.Tensor, b: buffer, dtype: xir.TensorType) -> None

构造函数, 使用指定的数据类型, 构造一个HostMemRegion上的Tensor, 复制指定buffer的数据.

**参数:**

- **b** – python buffer

- **dtype** – 数据类型

- __init__(self: xrt.Tensor, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**static Init() → [xrt.Tensor](#xrt.Tensor)[#](#xrt.Tensor.Init)**

创建一个初始化(非空)对象

**chunk(self: [xrt.Tensor](#xrt.Tensor)) → [xrt.MemChunk](#xrt.MemChunk)[#](#xrt.Tensor.chunk)**

获取该Tensor数据所在的内存块

**clone(self: [xrt.Tensor](#xrt.Tensor), depth: int = 1) → [xrt.Tensor](#xrt.Tensor)[#](#xrt.Tensor.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**copyData(self: [xrt.Tensor](#xrt.Tensor), b: buffer) → None[#](#xrt.Tensor.copyData)**

复制别的数据作为参数数据.

**copyFrom(self: [xrt.Tensor](#xrt.Tensor), dest_offset: int, src_tensor: [xrt.Tensor](#xrt.Tensor), src_offset: int, byte_size: int) → None[#](#xrt.Tensor.copyFrom)**

从指定的Tensor复制数据.

**参数:**

- **dest_offset** – 目标偏移位置

- **src_tensor** – 源Tensor

- **src_offset** – 源偏移位置

- **byte_size** – 字节大小

**data(self: [xrt.Tensor](#xrt.Tensor)) → [xrt.MemPtr](#xrt.MemPtr)[#](#xrt.Tensor.data)**

获取该Tensor数据的起始位置指针

**dtype(self: [xrt.Tensor](#xrt.Tensor)) → xir.TensorType[#](#xrt.Tensor.dtype)**

获取该Tensor的数据类型

**dump(self: [xrt.Tensor](#xrt.Tensor), os: io.BytesIO, format: str = '') → None[#](#xrt.Tensor.dump)**

将Tensor的数据按指定格式导出到指定的输出流中.

**参数:**

- **os** – 指定的输出流

- **format** – 指定的输出格式

支持的格式由三个字母表示：

- 第一个字母表示排布，H表示硬件，S表示软件

- 第二个字母表示数值，F表示浮点，Q表示定点

- 第三个字母表示序列化形式，B表示二进制，T表示文本

若一个Tensor原本的排布时H，那么可以转为S；若原本的数值为Q，那么可以转为F；反之不可

**fill(*args, **kwargs)[#](#xrt.Tensor.fill)**

Overloaded function.

- fill(self: xrt.Tensor, f: Callable[[int], float]) -> xrt.Tensor

填充数据

- fill(self: xrt.Tensor, f: Callable[[int], int]) -> xrt.Tensor

填充数据

**hasData(self: [xrt.Tensor](#xrt.Tensor)) → bool[#](#xrt.Tensor.hasData)**

检查该Tensor是否具有数据

**isOn(self: [xrt.Tensor](#xrt.Tensor), mregion: [xrt.MemRegion](#xrt.MemRegion)) → bool[#](#xrt.Tensor.isOn)**

检查该Tensor是否在指定的MemRegion上

**isReady(self: [xrt.Tensor](#xrt.Tensor)) → bool[#](#xrt.Tensor.isReady)**

检查该Tensor是否ready

**mallocOn(self: [xrt.Tensor](#xrt.Tensor), mregion: [xrt.MemRegion](#xrt.MemRegion)) → [xrt.Tensor](#xrt.Tensor)[#](#xrt.Tensor.mallocOn)**

在指定的MemRegion上分配Tensor所需要的内存.

**参数:**

**mregion** – 指定的MemRegion

备注
如果Tensor已经分配了内存块，该方法会覆盖原有的内存块

**memRegion(self: [xrt.Tensor](#xrt.Tensor)) → [xrt.MemRegion](#xrt.MemRegion)[#](#xrt.Tensor.memRegion)**

获取该Tensor所在的MemRegion

**offset(self: [xrt.Tensor](#xrt.Tensor)) → int[#](#xrt.Tensor.offset)**

获取该Tensor数据在内存块中的偏移

**read(self: [xrt.Tensor](#xrt.Tensor), dest: buffer, src_offset: int, byte_size: int) → None[#](#xrt.Tensor.read)**

读取指定偏移的数据.

**参数:**

- **dest** – 读取到目标位置

- **src_offset** – 源偏移位置

- **byte_size** – 字节大小

**setCheckFunc(self: [xrt.Tensor](#xrt.Tensor), check_func: Callable[[[xrt.Device](#xrt.Device)], bool]) → [xrt.Tensor](#xrt.Tensor)[#](#xrt.Tensor.setCheckFunc)**

设置张量的数据检查函数.

**参数:**

**check_func** – 状态检查函数

**setDType(self: [xrt.Tensor](#xrt.Tensor), dtype: xir.TensorType) → [xrt.Tensor](#xrt.Tensor)[#](#xrt.Tensor.setDType)**

设置张量的数据类型.

**参数:**

**dtype** – 数据类型

**setData(self: [xrt.Tensor](#xrt.Tensor), chunk: [xrt.MemChunk](#xrt.MemChunk), offset: int = 0) → [xrt.Tensor](#xrt.Tensor)[#](#xrt.Tensor.setData)**

设置张量数据所在的内存块.

**参数:**

- **chunk** – 数据所在内存块

- **offset** – 数据在内存块中的偏移

**setReady(self: [xrt.Tensor](#xrt.Tensor), ready: bool) → [xrt.Tensor](#xrt.Tensor)[#](#xrt.Tensor.setReady)**

设置张量的的状态.

**参数:**

**ready** – 状态是否ready

**to(self: [xrt.Tensor](#xrt.Tensor), mregion: [xrt.MemRegion](#xrt.MemRegion)) → [xrt.Tensor](#xrt.Tensor)[#](#xrt.Tensor.to)**

将Tensor复制到指定的MemRegion的上.

**参数:**

**mregion** – 指定的MemRegion

**返回:**

在指定MemRegion复制得到的Tensor

备注
如果该Tensor已经在指定的MemRegion上，则复制不会发生，而是直接返回原Tensor

**waitForReady(self: [xrt.Tensor](#xrt.Tensor), timeout: datetime.timedelta, sleep: datetime.timedelta = datetime.timedelta(0)) → bool[#](#xrt.Tensor.waitForReady)**

等待Tensor的状态ready.

**参数:**

- **timeout** – 等待的超时时间，超时则返回false

- **sleep** – 两次查询之间的休眠时间，默认为0

**返回:**

若timeout时间内查询到状态ready则返回true，否则返回false

**write(self: [xrt.Tensor](#xrt.Tensor), arg0: int, arg1: buffer, arg2: int) → None[#](#xrt.Tensor.write)**

将数据写到指定偏移位置.

**参数:**

- **dest_offset** – 数据被写入的偏移位置

- **src** – 数据源

- **byte_size** – 字节大小

**class ZG330Device(*args, **kwargs)[#](#xrt.ZG330Device)**

Overloaded function.

- __init__(self: xrt.ZG330Device) -> None

- __init__(self: xrt.ZG330Device, arg0: xir.ObjectRef) -> None

将父类强制转换为子类（该类型）

**calcTime(self: [xrt.ZG330Device](#xrt.ZG330Device)) → float[#](#xrt.ZG330Device.calcTime)**

获取执行时间

**clone(self: [xrt.ZG330Device](#xrt.ZG330Device), depth: int = 1) → [xrt.ZG330Device](#xrt.ZG330Device)[#](#xrt.ZG330Device.clone)**

克隆一份该对象
:param depth:   克隆的深度，默认为1，即浅克隆
:return:                克隆得到的新对象

**configProfiler(self: [xrt.ZG330Device](#xrt.ZG330Device), chunk: [xrt.MemChunk](#xrt.MemChunk)) → None[#](#xrt.ZG330Device.configProfiler)**

配置Profiler的空间

**configTimer(self: [xrt.ZG330Device](#xrt.ZG330Device), chunk: [xrt.MemChunk](#xrt.MemChunk)) → None[#](#xrt.ZG330Device.configTimer)**

配置计时器的空间

**getRowsCols(self: [xrt.ZG330Device](#xrt.ZG330Device)) → Tuple[int, int][#](#xrt.ZG330Device.getRowsCols)**

获取设备使能的MPE的行数和列数

**icoreCalc(self: [xrt.ZG330Device](#xrt.ZG330Device), addr: int, size: int) → None[#](#xrt.ZG330Device.icoreCalc)**

启动Icore计算

**layerCount(self: [xrt.ZG330Device](#xrt.ZG330Device)) → int[#](#xrt.ZG330Device.layerCount)**

获取当前的执行计数

**rTileCount(self: [xrt.ZG330Device](#xrt.ZG330Device), cid: int) → int[#](#xrt.ZG330Device.rTileCount)**

获取当前的读Tile计数

**readReg(self: [xrt.ZG330Device](#xrt.ZG330Device), cid: int, rid: int, offset: int) → int[#](#xrt.ZG330Device.readReg)**

获取设备使能的MPE的行数和列数

**setDDRClkFreq(self: [xrt.ZG330Device](#xrt.ZG330Device), freq_hz: int) → None[#](#xrt.ZG330Device.setDDRClkFreq)**

设置DDR的时钟频率(Hz)

**setIcoreClkFreq(self: [xrt.ZG330Device](#xrt.ZG330Device), freq_hz: int) → None[#](#xrt.ZG330Device.setIcoreClkFreq)**

设置Icore的时钟频率(Hz)

**setMasterCID(self: [xrt.ZG330Device](#xrt.ZG330Device), master_cid: int) → None[#](#xrt.ZG330Device.setMasterCID)**

设置master_cid

**showLayerTime(self: [xrt.ZG330Device](#xrt.ZG330Device), from_idx: int, op_cnt: int) → None[#](#xrt.ZG330Device.showLayerTime)**

输出显示计时结果

**wTileCount(self: [xrt.ZG330Device](#xrt.ZG330Device), cid: int) → int[#](#xrt.ZG330Device.wTileCount)**

获取当前的写Tile计数

**writeReg(self: [xrt.ZG330Device](#xrt.ZG330Device), cid: int, rid: int, offset: int, data: int) → None[#](#xrt.ZG330Device.writeReg)**

写指定行列位置的寄存器

                