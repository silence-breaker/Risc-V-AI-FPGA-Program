# host\_backend.HostBackend[#](#host-backend-hostbackend "此标题的永久链接")

*class* HostBackend(*\*args*, *\*\*kwargs*)[#](#host_backend.HostBackend "永久链接至目标")
:   基类：`Backend`

    表示Host类型的后端

    Overloaded function.

    1. \_\_init\_\_(self: host\_backend.HostBackend) -> None

    默认构造函数

    2. \_\_init\_\_(self: host\_backend.HostBackend, arg0: xir.ObjectRef) -> None

    将父类强制转换为子类（该类型）

    Methods

    |  |  |
    | --- | --- |
    | [`Create`](#host_backend.HostBackend.Create "host_backend.HostBackend.Create") | 创建指定类型的Backend. |
    | [`Init`](#host_backend.HostBackend.Init "host_backend.HostBackend.Init") | 创建一个初始化(非空)对象 |
    | [`apply`](#host_backend.HostBackend.apply "host_backend.HostBackend.apply") | 应用Backend的一些选项 |
    | [`clone`](#host_backend.HostBackend.clone "host_backend.HostBackend.clone") | 克隆一份该对象 :param depth: 克隆的深度，默认为1，即浅克隆 :return: 克隆得到的新对象 |
    | [`defined`](#host_backend.HostBackend.defined "host_backend.HostBackend.defined") | 检查引用的实例是否存在，如果对象引用了空指针则返回false |
    | [`deinit`](#host_backend.HostBackend.deinit "host_backend.HostBackend.deinit") | 释放Backend. |
    | [`enableTimeProfile`](#host_backend.HostBackend.enableTimeProfile "host_backend.HostBackend.enableTimeProfile") | 使能时间分析 |
    | [`fork`](#host_backend.HostBackend.fork "host_backend.HostBackend.fork") | 复制一个Backend用于多线程 |
    | [`forwardOp`](#host_backend.HostBackend.forwardOp "host_backend.HostBackend.forwardOp") | 前向指定的算子. |
    | [`getFakeQf`](#host_backend.HostBackend.getFakeQf "host_backend.HostBackend.getFakeQf") | 获取fakeQF信息. |
    | [`getForwardFunc`](#host_backend.HostBackend.getForwardFunc "host_backend.HostBackend.getForwardFunc") | 获取指定算子的前向函数. |
    | [`getInitFunc`](#host_backend.HostBackend.getInitFunc "host_backend.HostBackend.getInitFunc") | 获取指定算子的初始化函数. |
    | [`getThreadsNum`](#host_backend.HostBackend.getThreadsNum "host_backend.HostBackend.getThreadsNum") | 查询CPU前向推理时算子库自动启用的线程数. |
    | [`init`](#host_backend.HostBackend.init "host_backend.HostBackend.init") | 初始化Backend. |
    | [`initOp`](#host_backend.HostBackend.initOp "host_backend.HostBackend.initOp") | 初始化指定的算子. |
    | [`isOpSupported`](#host_backend.HostBackend.isOpSupported "host_backend.HostBackend.isOpSupported") | 检查指定算子是否被支持. |
    | [`same_as`](#host_backend.HostBackend.same_as "host_backend.HostBackend.same_as") | 比较引用的实例是否相同，即对象的指针是否相同 |
    | [`setDevice`](#host_backend.HostBackend.setDevice "host_backend.HostBackend.setDevice") | 为Backend绑定Device. |
    | [`setFakeQf`](#host_backend.HostBackend.setFakeQf "host_backend.HostBackend.setFakeQf") | 修改fakeQF状态，默认状态为false。激活时定点前向过程中不进行截位和饱和操作，主要用于Adapted和Generated阶段的结果对比. |
    | [`setThreadsNum`](#host_backend.HostBackend.setThreadsNum "host_backend.HostBackend.setThreadsNum") | 设置CPU前向推理时算子库自动启用的线程数, 默认值为4，在某些情况下占用过多资源会导致问题，需要手动降低线程数. |
    | [`setTimeElapses`](#host_backend.HostBackend.setTimeElapses "host_backend.HostBackend.setTimeElapses") | 记录指定算子的前向时间（用于Backend的TimeProfile实现）. |
    | [`typeKey`](#host_backend.HostBackend.typeKey "host_backend.HostBackend.typeKey") | 获取所引用对象的type\_key字符串，该字符串表示引用对象的类型 |
    | [`type_is`](#host_backend.HostBackend.type_is "host_backend.HostBackend.type_is") | 检查类型是否是字符串指定的类型 |
    | [`unique`](#host_backend.HostBackend.unique "host_backend.HostBackend.unique") | 判断引用是否唯一，即引用计数为1则返回true |
    | [`use_count`](#host_backend.HostBackend.use_count "host_backend.HostBackend.use_count") | 获取引用计数 |

    Attributes

    |  |  |
    | --- | --- |
    | [`device`](#host_backend.HostBackend.device "host_backend.HostBackend.device") | 绑定到该后端的设备 |
    | [`network_view`](#host_backend.HostBackend.network_view "host_backend.HostBackend.network_view") | 绑定到该后端的网络视图 |
    | [`snapshot`](#host_backend.HostBackend.snapshot "host_backend.HostBackend.snapshot") | 是否是快照模式 |
    | [`time_profile`](#host_backend.HostBackend.time_profile "host_backend.HostBackend.time_profile") | 是否开启时间分析 |
    | `type_key` |  |

    *static* Create(*backend\_type: type*, *network\_view: xir.NetworkView*, *device: xrt.Device*) → xrt.Backend[#](#host_backend.HostBackend.Create "永久链接至目标")
    :   创建指定类型的Backend.

        参数:
        :   * **backend\_type** – 后端的类型
            * **network\_view** – 网络
            * **device** – 设备

    *static* Init() → [host\_backend.HostBackend](#host_backend.HostBackend "host_backend.HostBackend")[#](#host_backend.HostBackend.Init "永久链接至目标")
    :   创建一个初始化(非空)对象

    apply(*self: xrt.Backend*) → None[#](#host_backend.HostBackend.apply "永久链接至目标")
    :   应用Backend的一些选项

    clone(*self: [host\_backend.HostBackend](#host_backend.HostBackend "host_backend.HostBackend")*, *depth: int = 1*) → [host\_backend.HostBackend](#host_backend.HostBackend "host_backend.HostBackend")[#](#host_backend.HostBackend.clone "永久链接至目标")
    :   克隆一份该对象
        :param depth: 克隆的深度，默认为1，即浅克隆
        :return: 克隆得到的新对象

    defined(*self: xir.ObjectRef*) → bool[#](#host_backend.HostBackend.defined "永久链接至目标")
    :   检查引用的实例是否存在，如果对象引用了空指针则返回false

    deinit(*self: xrt.Backend*) → None[#](#host_backend.HostBackend.deinit "永久链接至目标")
    :   释放Backend.

    *property* device[#](#host_backend.HostBackend.device "永久链接至目标")
    :   绑定到该后端的设备

    enableTimeProfile(*self: xrt.Backend*, *enable: bool*) → None[#](#host_backend.HostBackend.enableTimeProfile "永久链接至目标")
    :   使能时间分析

    fork(*self: xrt.Backend*) → xrt.Backend[#](#host_backend.HostBackend.fork "永久链接至目标")
    :   复制一个Backend用于多线程

    forwardOp(*self: xrt.Backend*, *op: xir.Operation*, *inputs: List[xrt.Tensor]*, *outputs: List[xrt.Tensor] = []*) → List[xrt.Tensor][#](#host_backend.HostBackend.forwardOp "永久链接至目标")
    :   前向指定的算子.

        参数:
        :   * **op** – 指定的算子
            * **inputs** – 输入的Tensors
            * **outputs** – 输出的Tensors

        返回:
        :   前向的结果

    getFakeQf(*self: [host\_backend.HostBackend](#host_backend.HostBackend "host_backend.HostBackend")*) → bool[#](#host_backend.HostBackend.getFakeQf "永久链接至目标")
    :   获取fakeQF信息.

        Return bool:
        :   当前fakeQF状态

    getForwardFunc(*self: xrt.Backend*, *op: xir.Operation*) → Optional[Callable[[xir.Operation, List[xrt.Tensor], List[xrt.Tensor], xrt.Backend], List[xrt.Tensor]]][#](#host_backend.HostBackend.getForwardFunc "永久链接至目标")
    :   获取指定算子的前向函数.

        参数:
        :   **op** – 指定的算子

        返回:
        :   前向函数(Optional)

    getInitFunc(*self: xrt.Backend*, *op: xir.Operation*) → Optional[Callable[[xir.Operation, xrt.Backend], None]][#](#host_backend.HostBackend.getInitFunc "永久链接至目标")
    :   获取指定算子的初始化函数.

        参数:
        :   **op** – 指定的算子

        返回:
        :   初始化函数(Optional)

    *static* getThreadsNum() → int[#](#host_backend.HostBackend.getThreadsNum "永久链接至目标")
    :   查询CPU前向推理时算子库自动启用的线程数.

        Return int:
        :   CPU前向推理时将启用的线程数

    init(*self: xrt.Backend*, *network\_view: xir.NetworkView*, *device: xrt.Device*) → None[#](#host_backend.HostBackend.init "永久链接至目标")
    :   初始化Backend.

        参数:
        :   * **network\_view** – 网络
            * **device** – 设备

    initOp(*self: xrt.Backend*, *op: xir.Operation*) → None[#](#host_backend.HostBackend.initOp "永久链接至目标")
    :   初始化指定的算子.

        参数:
        :   **op** – 指定的算子

    isOpSupported(*self: xrt.Backend*, *op: xir.Operation*) → bool[#](#host_backend.HostBackend.isOpSupported "永久链接至目标")
    :   检查指定算子是否被支持.

        参数:
        :   **op** – 指定的算子

        返回:
        :   如果该算子被支持，后端有该算子的前向实现，则返回True

    *property* network\_view[#](#host_backend.HostBackend.network_view "永久链接至目标")
    :   绑定到该后端的网络视图

    same\_as(*self: xir.ObjectRef*, *arg0: xir.ObjectRef*) → bool[#](#host_backend.HostBackend.same_as "永久链接至目标")
    :   比较引用的实例是否相同，即对象的指针是否相同

    setDevice(*self: xrt.Backend*, *device: xrt.Device*) → xrt.Backend[#](#host_backend.HostBackend.setDevice "永久链接至目标")
    :   为Backend绑定Device.

        参数:
        :   **device** – 被绑定的Device

    setFakeQf(*self: [host\_backend.HostBackend](#host_backend.HostBackend "host_backend.HostBackend")*, *fakeQF: bool*) → None[#](#host_backend.HostBackend.setFakeQf "永久链接至目标")
    :   修改fakeQF状态，默认状态为false。激活时定点前向过程中不进行截位和饱和操作，主要用于Adapted和Generated阶段的结果对比.

        参数:
        :   **fakeQF** – bool变量，fakeQF设为ture或false

    *static* setThreadsNum(*num\_threads: int*) → None[#](#host_backend.HostBackend.setThreadsNum "永久链接至目标")
    :   设置CPU前向推理时算子库自动启用的线程数, 默认值为4，在某些情况下占用过多资源会导致问题，需要手动降低线程数.

        参数:
        :   **num\_threads** – int变量，期望用于CPU推理加速的线程数

    setTimeElapses(*self: xrt.Backend*, *op\_id: int*, *memcpy\_time: float*, *hard\_time: float*) → None[#](#host_backend.HostBackend.setTimeElapses "永久链接至目标")
    :   记录指定算子的前向时间（用于Backend的TimeProfile实现）.

        参数:
        :   * **op\_id** – 指定的Op ID
            * **memcpy\_time** – 数据复制时间
            * **hard\_time** – 硬件计算时间

    *property* snapshot[#](#host_backend.HostBackend.snapshot "永久链接至目标")
    :   是否是快照模式

    *property* time\_profile[#](#host_backend.HostBackend.time_profile "永久链接至目标")
    :   是否开启时间分析

    typeKey(*self: xir.ObjectRef*) → str[#](#host_backend.HostBackend.typeKey "永久链接至目标")
    :   获取所引用对象的type\_key字符串，该字符串表示引用对象的类型

    type\_is(*self: xir.ObjectRef*, *arg0: type*) → bool[#](#host_backend.HostBackend.type_is "永久链接至目标")
    :   检查类型是否是字符串指定的类型

    unique(*self: xir.ObjectRef*) → bool[#](#host_backend.HostBackend.unique "永久链接至目标")
    :   判断引用是否唯一，即引用计数为1则返回true

    use\_count(*self: xir.ObjectRef*) → int[#](#host_backend.HostBackend.use_count "永久链接至目标")
    :   获取引用计数
