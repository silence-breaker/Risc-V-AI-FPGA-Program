# Class ZG330Backend[#](#class-zg330backend "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< ZG330Backend, Backend, ZG330BackendNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ZG330Backend : public HandleBase<[ZG330Backend](#_CPPv4N6icraft3xrt5zg33012ZG330BackendE "icraft::xrt::zg330::ZG330Backend"), Backend, [ZG330BackendNode](classicraft_1_1xrt_1_1zg330_1_1_z_g330_backend_node.md#_CPPv4N6icraft3xrt5zg33016ZG330BackendNodeE "icraft::xrt::zg330::ZG330BackendNode")>[#](#_CPPv4N6icraft3xrt5zg33012ZG330BackendE "永久链接至目标")
:   Public Functions

    XRT\_DLL void log ()
    :   生成ZG330Backend对应的log，log保存在 ${工作目录}/.icraft/logs/ 路径下

        备注

        在apply后调用

    XRT\_DLL bool precheck ()
    :   对ZG330Backend进行预检，会检查内存中的指令以及权重数据是否正确上传至etm指定地址

        备注

        在apply后调用

        返回:
        :   若为True则预检通过

    XRT\_DLL void userReuseSegment (MemChunk &memchunk, SegmentType segment\_type)
    :   用户配置网络权重/指令/中间层数据段的memchunk，用于复用数据或内存空间，减少多网络部署对etm的使用量

        备注

        在apply前调用

        参数:
        :   * **memchunk** – 用户自行申请的 memchunk
            * **segment\_type** – 物理数据段phySegment的类型

    XRT\_DLL void userConnectNetwork (MemChunk &memchunk, int64\_t v\_id)
    :   用户配置网络输入/输出数据段的memchunk，用于连接多网络在etm上的输入和输出

        备注

        在apply前调用

        参数:
        :   * **memchunk** – 用户自行申请的 memchunk
            * **v\_id** – 网络中指定的value id

    XRT\_DLL void disableMergeHardOp ()
    :   关闭算子连贯执行模式，ZG330Backend默认是使用算子连贯执行模式，该模式下连续在icore上运行的算子连贯执行，从而减少频繁同步带来的软件开销

        备注

        在apply前调用

    XRT\_DLL void disableEtmOptimize ()
    :   关闭etm内存回收，ZG330Backend默认开启etm内存回收，网络中间层特征图的内存可以复用，从而减少对etm的使用量

        备注

        在apply前调用

    XRT\_DLL void ocmOptimize (OcmOpt option)
    :   选择ocm优化方案，ZG330Backend默认使用OcmOpt::BEST\_SCORE，即开启ocm优化并选取方案一、方案二、方案三中评分最高的作为最后使用的方案， 开启ocm优化可以将满足条件的特征图存放在片上存储中，从而减小读写etm的带宽压力，提高模型在硬件上的运行效率 关闭ocm优化选择OcmOpt::None

        备注

        在apply前调用
