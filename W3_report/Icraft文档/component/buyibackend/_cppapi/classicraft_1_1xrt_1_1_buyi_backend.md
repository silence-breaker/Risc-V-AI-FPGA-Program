# Class BuyiBackend[#](#class-buyibackend "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::HandleBase< BuyiBackend, Backend, BuyiBackendNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class BuyiBackend : public icraft::xir::HandleBase<[BuyiBackend](#_CPPv4N6icraft3xrt11BuyiBackendE "icraft::xrt::BuyiBackend"), Backend, [BuyiBackendNode](classicraft_1_1xrt_1_1_buyi_backend_node.md#_CPPv4N6icraft3xrt15BuyiBackendNodeE "icraft::xrt::BuyiBackendNode")>[#](#_CPPv4N6icraft3xrt11BuyiBackendE "永久链接至目标")
:   Public Functions

    XRT\_DLL void speedMode ()
    :   开启speedMode模式，该模式下连续且可以合并的硬算子会自动合并，减少硬算子过多导致频繁同步带来的软件开销 mmu模式下不支持buyibackend开启speedmode

    XRT\_DLL void compressFtmp ()
    :   压缩中间层，将ftmp段的网络中间层进行地址复用，从而减少网络对etm的使用量 中间层压缩开启后会对网络逻辑ftmp分段进行修改，apply部署以后才会真正生效 mmu模式下不支持buyibackend开启内存优化

    XRT\_DLL void log ()
    :   生成BuyiBackend对应的log log保存在 ${工作目录}/logs/runtime/ 路径下

    XRT\_DLL uint64\_t getDeploySize ()
    :   获得该网络在etm上的部署字节大小

        返回:
        :   该网络在bybakned部署的字节大小

    XRT\_DLL bool precheck ()
    :   对改buyibackend进行预检，会检查内存中的指令以及权重数据是否正确上传至etm指定地址

        返回:
        :   若为True则预检通过

    XRT\_DLL void userSetSegment (MemChunk &memchunk, Segment segment\_type, uint64\_t offset=0)
    :   用户配置指定网络数据段的memchunk

        参数:
        :   * **memchunk** – 用户自行申请的memchunk
            * **segment\_type** – buyibackend 物理数据段phySegment的类型
            * **uint64\_t** – memchunk的偏移，数据会放到memchunk的首地址+偏移的位置
