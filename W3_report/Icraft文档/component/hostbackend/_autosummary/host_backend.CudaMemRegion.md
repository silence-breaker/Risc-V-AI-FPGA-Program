# host\_backend.CudaMemRegion[#](#host-backend-cudamemregion "此标题的永久链接")

*class* CudaMemRegion(*self: [host\_backend.CudaMemRegion](#host_backend.CudaMemRegion "host_backend.CudaMemRegion")*)[#](#host_backend.CudaMemRegion "永久链接至目标")
:   基类：`MemRegion`

    Methods

    |  |  |
    | --- | --- |
    | [`clone`](#host_backend.CudaMemRegion.clone "host_backend.CudaMemRegion.clone") | 克隆一份该对象 :param depth: 克隆的深度，默认为1，即浅克隆 :return: 克隆得到的新对象 |
    | [`defined`](#host_backend.CudaMemRegion.defined "host_backend.CudaMemRegion.defined") | 检查引用的实例是否存在，如果对象引用了空指针则返回false |
    | [`device`](#host_backend.CudaMemRegion.device "host_backend.CudaMemRegion.device") | 获取所在的Device |
    | [`malloc`](#host_backend.CudaMemRegion.malloc "host_backend.CudaMemRegion.malloc") | Overloaded function. |
    | [`memManager`](#host_backend.CudaMemRegion.memManager "host_backend.CudaMemRegion.memManager") | 获取所属的MemManager |
    | [`same_as`](#host_backend.CudaMemRegion.same_as "host_backend.CudaMemRegion.same_as") | 比较引用的实例是否相同，即对象的指针是否相同 |
    | [`typeKey`](#host_backend.CudaMemRegion.typeKey "host_backend.CudaMemRegion.typeKey") | 获取所引用对象的type\_key字符串，该字符串表示引用对象的类型 |
    | [`type_is`](#host_backend.CudaMemRegion.type_is "host_backend.CudaMemRegion.type_is") | 检查类型是否是字符串指定的类型 |
    | [`unique`](#host_backend.CudaMemRegion.unique "host_backend.CudaMemRegion.unique") | 判断引用是否唯一，即引用计数为1则返回true |
    | [`use_count`](#host_backend.CudaMemRegion.use_count "host_backend.CudaMemRegion.use_count") | 获取引用计数 |

    Attributes

    |  |  |
    | --- | --- |
    | `type_key` |  |

    clone(*self: xrt.MemRegion*, *depth: int = 1*) → xrt.MemRegion[#](#host_backend.CudaMemRegion.clone "永久链接至目标")
    :   克隆一份该对象
        :param depth: 克隆的深度，默认为1，即浅克隆
        :return: 克隆得到的新对象

    defined(*self: xir.ObjectRef*) → bool[#](#host_backend.CudaMemRegion.defined "永久链接至目标")
    :   检查引用的实例是否存在，如果对象引用了空指针则返回false

    device(*self: xrt.MemRegion*) → icraft::xrt::Device[#](#host_backend.CudaMemRegion.device "永久链接至目标")
    :   获取所在的Device

    malloc(*\*args*, *\*\*kwargs*)[#](#host_backend.CudaMemRegion.malloc "永久链接至目标")
    :   Overloaded function.

        1. malloc(self: xrt.MemRegion, byte\_size: int, auto\_free: bool = True, alignment: int = 1) -> icraft::xrt::MemChunk

        申请分配指定大小的内存.

        参数:
        :   * **byte\_size** – 分配内存的大小
            * **auto\_free** – 指定分配的内存是否会被自动释放
            * **alignment** – 指定分配的内存地址字节对齐

        2. malloc(self: xrt.MemRegion, begin: xrt.MemPtr, byte\_size: int, deleter: Callable[[xrt.MemPtr], None] = <built-in method of PyCapsule object at 0x000001E3BD773840>, auto\_free: bool = True) -> icraft::xrt::MemChunk

        申请分配指定位置开始的内存.

        参数:
        :   * **byte\_size** – 分配内存的大小
            * **deleter** – 内存释放的自定义函数，若指定了Deleter，则调用该函数来释放内存
            * **auto\_free** – 指定分配的内存是否会被自动释放

    memManager(*self: xrt.MemRegion*) → xrt.MemManager[#](#host_backend.CudaMemRegion.memManager "永久链接至目标")
    :   获取所属的MemManager

    same\_as(*self: xir.ObjectRef*, *arg0: xir.ObjectRef*) → bool[#](#host_backend.CudaMemRegion.same_as "永久链接至目标")
    :   比较引用的实例是否相同，即对象的指针是否相同

    typeKey(*self: xir.ObjectRef*) → str[#](#host_backend.CudaMemRegion.typeKey "永久链接至目标")
    :   获取所引用对象的type\_key字符串，该字符串表示引用对象的类型

    type\_is(*self: xir.ObjectRef*, *arg0: type*) → bool[#](#host_backend.CudaMemRegion.type_is "永久链接至目标")
    :   检查类型是否是字符串指定的类型

    unique(*self: xir.ObjectRef*) → bool[#](#host_backend.CudaMemRegion.unique "永久链接至目标")
    :   判断引用是否唯一，即引用计数为1则返回true

    use\_count(*self: xir.ObjectRef*) → int[#](#host_backend.CudaMemRegion.use_count "永久链接至目标")
    :   获取引用计数
