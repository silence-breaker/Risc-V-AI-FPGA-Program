# host\_backend.CudaDevice[#](#host-backend-cudadevice "此标题的永久链接")

*class* CudaDevice(*self: [host\_backend.CudaDevice](#host_backend.CudaDevice "host_backend.CudaDevice")*)[#](#host_backend.CudaDevice "永久链接至目标")
:   基类：`Device`

    Methods

    |  |  |
    | --- | --- |
    | [`Close`](#host_backend.CudaDevice.Close "host_backend.CudaDevice.Close") | 关闭设备. |
    | [`Default`](#host_backend.CudaDevice.Default "host_backend.CudaDevice.Default") | 获取全局默认的CudaDevice对象 |
    | [`MemRegion`](#host_backend.CudaDevice.MemRegion "host_backend.CudaDevice.MemRegion") | 获取全局默认的CudaDevice的内存区域对象 |
    | [`Open`](#host_backend.CudaDevice.Open "host_backend.CudaDevice.Open") | 打开设备. |
    | [`check`](#host_backend.CudaDevice.check "host_backend.CudaDevice.check") | 检查设备. |
    | [`clone`](#host_backend.CudaDevice.clone "host_backend.CudaDevice.clone") | 克隆一份该对象 :param depth: 克隆的深度，默认为1，即浅克隆 :return: 克隆得到的新对象 |
    | [`defaultMemRegion`](#host_backend.CudaDevice.defaultMemRegion "host_backend.CudaDevice.defaultMemRegion") | 获取设备默认的MemRegion |
    | [`defaultRegRegion`](#host_backend.CudaDevice.defaultRegRegion "host_backend.CudaDevice.defaultRegRegion") | 获取设备默认的RegRegion |
    | [`defined`](#host_backend.CudaDevice.defined "host_backend.CudaDevice.defined") | 检查引用的实例是否存在，如果对象引用了空指针则返回false |
    | [`getMemRegion`](#host_backend.CudaDevice.getMemRegion "host_backend.CudaDevice.getMemRegion") | 根据名字获取设备的MemRegion. |
    | [`getRegRegion`](#host_backend.CudaDevice.getRegRegion "host_backend.CudaDevice.getRegRegion") | 根据名字获取设备的MemRegion. |
    | [`malloc`](#host_backend.CudaDevice.malloc "host_backend.CudaDevice.malloc") | Overloaded function. |
    | [`readReg`](#host_backend.CudaDevice.readReg "host_backend.CudaDevice.readReg") | Overloaded function. |
    | [`reset`](#host_backend.CudaDevice.reset "host_backend.CudaDevice.reset") | 复位设备. |
    | [`same_as`](#host_backend.CudaDevice.same_as "host_backend.CudaDevice.same_as") | 比较引用的实例是否相同，即对象的指针是否相同 |
    | [`setDefaultMemRegion`](#host_backend.CudaDevice.setDefaultMemRegion "host_backend.CudaDevice.setDefaultMemRegion") | 将指定的MemRegion设置为默认MemRegion. |
    | [`setDefaultRegRegion`](#host_backend.CudaDevice.setDefaultRegRegion "host_backend.CudaDevice.setDefaultRegRegion") | 将指定的MemRegion设置为默认MemRegion. |
    | [`setWaitTime`](#host_backend.CudaDevice.setWaitTime "host_backend.CudaDevice.setWaitTime") | 设置同步tensor的最长等待时间 |
    | [`showStatus`](#host_backend.CudaDevice.showStatus "host_backend.CudaDevice.showStatus") | 显示设备状态. |
    | [`typeKey`](#host_backend.CudaDevice.typeKey "host_backend.CudaDevice.typeKey") | 获取所引用对象的type\_key字符串，该字符串表示引用对象的类型 |
    | [`type_is`](#host_backend.CudaDevice.type_is "host_backend.CudaDevice.type_is") | 检查类型是否是字符串指定的类型 |
    | [`unique`](#host_backend.CudaDevice.unique "host_backend.CudaDevice.unique") | 判断引用是否唯一，即引用计数为1则返回true |
    | [`use_count`](#host_backend.CudaDevice.use_count "host_backend.CudaDevice.use_count") | 获取引用计数 |
    | [`version`](#host_backend.CudaDevice.version "host_backend.CudaDevice.version") | 获取设备的版本 |
    | [`writeReg`](#host_backend.CudaDevice.writeReg "host_backend.CudaDevice.writeReg") | Overloaded function. |

    Attributes

    |  |  |
    | --- | --- |
    | `type_key` |  |

    *static* Close(*device: xrt.Device*) → None[#](#host_backend.CudaDevice.Close "永久链接至目标")
    :   关闭设备.

        参数:
        :   **device** – 被关闭的设备对象URL

    *static* Default() → [host\_backend.CudaDevice](#host_backend.CudaDevice "host_backend.CudaDevice")[#](#host_backend.CudaDevice.Default "永久链接至目标")
    :   获取全局默认的CudaDevice对象

    *static* MemRegion() → [host\_backend.CudaMemRegion](host_backend.CudaMemRegion.md#host_backend.CudaMemRegion "host_backend.CudaMemRegion")[#](#host_backend.CudaDevice.MemRegion "永久链接至目标")
    :   获取全局默认的CudaDevice的内存区域对象

    *static* Open(*url: str*) → xrt.Device[#](#host_backend.CudaDevice.Open "永久链接至目标")
    :   打开设备.

        参数:
        :   **url** – 设备的URL

        返回:
        :   打开的设备对象

    check(*self: xrt.Device*, *level: int*) → bool[#](#host_backend.CudaDevice.check "永久链接至目标")
    :   检查设备.

        参数:
        :   **level** – 检查等级

        备注

        不同的设备具有不同的定义和实现，详见具体设备的使用说明

    clone(*self: xrt.Device*, *depth: int = 1*) → xrt.Device[#](#host_backend.CudaDevice.clone "永久链接至目标")
    :   克隆一份该对象
        :param depth: 克隆的深度，默认为1，即浅克隆
        :return: 克隆得到的新对象

    defaultMemRegion(*self: xrt.Device*) → xrt.MemRegion[#](#host_backend.CudaDevice.defaultMemRegion "永久链接至目标")
    :   获取设备默认的MemRegion

    defaultRegRegion(*self: xrt.Device*) → xrt.RegRegion[#](#host_backend.CudaDevice.defaultRegRegion "永久链接至目标")
    :   获取设备默认的RegRegion

    defined(*self: xir.ObjectRef*) → bool[#](#host_backend.CudaDevice.defined "永久链接至目标")
    :   检查引用的实例是否存在，如果对象引用了空指针则返回false

    getMemRegion(*self: xrt.Device*, *name: str*) → xrt.MemRegion[#](#host_backend.CudaDevice.getMemRegion "永久链接至目标")
    :   根据名字获取设备的MemRegion.

        参数:
        :   **name** – MemRegion的名字

        返回:
        :   相对应的MemRegion对象

    getRegRegion(*self: xrt.Device*, *name: str*) → xrt.RegRegion[#](#host_backend.CudaDevice.getRegRegion "永久链接至目标")
    :   根据名字获取设备的MemRegion.

        参数:
        :   **name** – RegRegion的名字

        返回:
        :   相对应的RegRegion对象

    malloc(*\*args*, *\*\*kwargs*)[#](#host_backend.CudaDevice.malloc "永久链接至目标")
    :   Overloaded function.

        1. malloc(self: xrt.Device, byte\_size: int) -> xrt.MemChunk

        在默认的MemRegion上申请分配内存.

        参数:
        :   **byte\_size** – 申请的内存大小的名字

        返回:
        :   申请得到的MemChunk对象

        2. malloc(self: xrt.Device, mem\_region: str, byte\_size: int) -> xrt.MemChunk

        在指定的MemRegion上申请分配内存.

        参数:
        :   * **mem\_region** – 指定的MemRegion的名字
            * **byte\_size** – 申请的内存大小

        返回:
        :   申请得到的MemChunk对象

    readReg(*\*args*, *\*\*kwargs*)[#](#host_backend.CudaDevice.readReg "永久链接至目标")
    :   Overloaded function.

        1. readReg(self: xrt.Device, byte\_size: int, relative: bool = False) -> int

        在默认的RegRegion上读取寄存器.

        参数:
        :   * **addr** – 读取的地址
            * **relative** – 是否以相对地址读取寄存器

        返回:
        :   读取得到的寄存器数据

        2. readReg(self: xrt.Device, region\_name: str, byte\_size: int, relative: bool = False) -> int

        在指定的的RegRegion上读取寄存器.

        参数:
        :   * **region\_name** – 指定的RegRegion的名字
            * **addr** – 读取的地址
            * **relative** – 是否以相对地址读取寄存器

        返回:
        :   读取得到的寄存器数据

    reset(*self: xrt.Device*, *level: int*) → None[#](#host_backend.CudaDevice.reset "永久链接至目标")
    :   复位设备.

        参数:
        :   **level** – 复位等级

        备注

        不同的设备具有不同的定义和实现，详见具体设备的使用说明

    same\_as(*self: xir.ObjectRef*, *arg0: xir.ObjectRef*) → bool[#](#host_backend.CudaDevice.same_as "永久链接至目标")
    :   比较引用的实例是否相同，即对象的指针是否相同

    setDefaultMemRegion(*self: xrt.Device*, *region\_name: str*) → xrt.Device[#](#host_backend.CudaDevice.setDefaultMemRegion "永久链接至目标")
    :   将指定的MemRegion设置为默认MemRegion.

        参数:
        :   **region\_name** – 指定的MemRegion名字

    setDefaultRegRegion(*self: xrt.Device*, *region\_name: str*) → xrt.Device[#](#host_backend.CudaDevice.setDefaultRegRegion "永久链接至目标")
    :   将指定的MemRegion设置为默认MemRegion.

        参数:
        :   **region\_name** – 指定的RegRegion名字

    setWaitTime(*self: xrt.Device*, *wait\_time: int*) → None[#](#host_backend.CudaDevice.setWaitTime "永久链接至目标")
    :   设置同步tensor的最长等待时间

        参数:
        :   **wait\_time** – 等待时间，单位ms

    showStatus(*self: xrt.Device*, *level: int*) → None[#](#host_backend.CudaDevice.showStatus "永久链接至目标")
    :   显示设备状态.

        参数:
        :   **level** – 状态等级

        备注

        不同的设备具有不同的定义和实现，详见具体设备的使用说明

    typeKey(*self: xir.ObjectRef*) → str[#](#host_backend.CudaDevice.typeKey "永久链接至目标")
    :   获取所引用对象的type\_key字符串，该字符串表示引用对象的类型

    type\_is(*self: xir.ObjectRef*, *arg0: type*) → bool[#](#host_backend.CudaDevice.type_is "永久链接至目标")
    :   检查类型是否是字符串指定的类型

    unique(*self: xir.ObjectRef*) → bool[#](#host_backend.CudaDevice.unique "永久链接至目标")
    :   判断引用是否唯一，即引用计数为1则返回true

    use\_count(*self: xir.ObjectRef*) → int[#](#host_backend.CudaDevice.use_count "永久链接至目标")
    :   获取引用计数

    version(*self: xrt.Device*) → Dict[str, str][#](#host_backend.CudaDevice.version "永久链接至目标")
    :   获取设备的版本

    writeReg(*\*args*, *\*\*kwargs*)[#](#host_backend.CudaDevice.writeReg "永久链接至目标")
    :   Overloaded function.

        1. writeReg(self: xrt.Device, addr: int, data: int, relative: bool = False) -> None

        将数据写入默认的RegRegion上的寄存器.

        参数:
        :   * **addr** – 写入的地址
            * **data** – 写入的数据
            * **relative** – 是否以相对地址写入寄存器

        2. writeReg(self: xrt.Device, region\_name: str, addr: int, data: int, relative: bool = False) -> None

        将数据写入指定的RegRegion上的寄存器.

        参数:
        :   * **region\_name** – 指定的RegRegion的名字
            * **addr** – 写入的地址
            * **data** – 写入的数据
            * **relative** – 是否以相对地址写入寄存器
