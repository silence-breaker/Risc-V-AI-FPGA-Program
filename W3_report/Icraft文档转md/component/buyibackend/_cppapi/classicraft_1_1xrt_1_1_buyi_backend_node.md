# Class BuyiBackendNode[#](#class-buyibackendnode "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::NodeBase< BuyiBackendNode, BackendNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class BuyiBackendNode : public icraft::xir::NodeBase<[BuyiBackendNode](#_CPPv4N6icraft3xrt15BuyiBackendNodeE "icraft::xrt::BuyiBackendNode"), BackendNode>[#](#_CPPv4N6icraft3xrt15BuyiBackendNodeE "永久链接至目标")
:   [BuyiBackend](classicraft_1_1xrt_1_1_buyi_backend.md#classicraft_1_1xrt_1_1_buyi_backend) 表示执行在BUYI架构7100芯片的后端 必须配置对应的device才能正确执行

    Public Functions

    virtual XRT\_DLL void accept (AttrVisitor &visitor) override

    virtual XRT\_DLL void init (const NetworkView &network, const Device &device) override
    :   BuyiBackend初始化.初始化的过程中会将网络在etm的存储区域进行分段，生成network\_view对应的逻辑地址信息

        参数:
        :   * **network\_view** – NetworkView中包含所有需要部署在BuyiBackend的算子
            * **device** – 执行的硬件设备，需要传入对应的7100device

    virtual XRT\_DLL void apply () override
    :   [BuyiBackend](classicraft_1_1xrt_1_1_buyi_backend.md#classicraft_1_1xrt_1_1_buyi_backend) 部署，session部署的过程中会调用. 部署的过程中会根据用户的配置执行响应的操作，修改指令，上传修改后的指令，执行每个算子的init函数

    virtual XRT\_DLL void view (uint64\_t start\_index, uint64\_t end\_index) override

    virtual XRT\_DLL Backend fork () override

    virtual XRT\_DLL MergedOps autoMerge () override

    virtual XRT\_DLL void deinit () override

    virtual XRT\_DLL Operation serialize (int64\_t op\_id) override
    :   序列化当前算子相关信息

        参数:
        :   * **builder** – flatbuffer构建器对象
            * **op\_id** – 当前算子的id

        返回:
        :   当前算子以及其输入输出的序列化对象

    void FtmpRealloc(const Value &input\_ftmp)[#](#_CPPv4N6icraft3xrt15BuyiBackendNode11FtmpReallocERK5Value "永久链接至目标")

    void overlapFtmp([ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo") &big, [ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo") &small)[#](#_CPPv4N6icraft3xrt15BuyiBackendNode11overlapFtmpER9ValueInfoR9ValueInfo "永久链接至目标")

    void setSegmentValueMap()[#](#_CPPv4N6icraft3xrt15BuyiBackendNode18setSegmentValueMapEv "永久链接至目标")

    void calcLogic()[#](#_CPPv4N6icraft3xrt15BuyiBackendNode9calcLogicEv "永久链接至目标")

    void userSetSegment(MemChunk &memchunk, Segment segment\_type, uint64\_t offset = 0)[#](#_CPPv4N6icraft3xrt15BuyiBackendNode14userSetSegmentER8MemChunk7Segment8uint64_t "永久链接至目标")

    void updateSegTable()[#](#_CPPv4N6icraft3xrt15BuyiBackendNode14updateSegTableEv "永久链接至目标")

    void compressFtmp()[#](#_CPPv4N6icraft3xrt15BuyiBackendNode12compressFtmpEv "永久链接至目标")

    Public Members

    std::map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo")> value\_info[#](#_CPPv4N6icraft3xrt15BuyiBackendNode10value_infoE "永久链接至目标")

    [ForwardInfo](classicraft_1_1xrt_1_1_forward_info.md#_CPPv4N6icraft3xrt11ForwardInfoE "icraft::xrt::ForwardInfo") forward\_info = [ForwardInfo](classicraft_1_1xrt_1_1_forward_info.md#_CPPv4N6icraft3xrt11ForwardInfoE "icraft::xrt::ForwardInfo")::Init()[#](#_CPPv4N6icraft3xrt15BuyiBackendNode12forward_infoE "永久链接至目标")

    SegTable seg\_table\_[#](#_CPPv4N6icraft3xrt15BuyiBackendNode10seg_table_E "永久链接至目标")

    std::unordered\_map<Segment, [LogicSegment](classicraft_1_1xrt_1_1_logic_segment.md#_CPPv4N6icraft3xrt12LogicSegmentE "icraft::xrt::LogicSegment")> logic\_segment\_map[#](#_CPPv4N6icraft3xrt15BuyiBackendNode17logic_segment_mapE "永久链接至目标")

    std::unordered\_map<Segment, [PhySegment](classicraft_1_1xrt_1_1_phy_segment.md#_CPPv4N6icraft3xrt10PhySegmentE "icraft::xrt::PhySegment")> phy\_segment\_map[#](#_CPPv4N6icraft3xrt15BuyiBackendNode15phy_segment_mapE "永久链接至目标")

    std::list<Value> value\_list[#](#_CPPv4N6icraft3xrt15BuyiBackendNode10value_listE "永久链接至目标")

    std::vector<[HardOpInfo](classicraft_1_1xrt_1_1_hard_op_info.md#_CPPv4N6icraft3xrt10HardOpInfoE "icraft::xrt::HardOpInfo")> speed\_ops\_[#](#_CPPv4N6icraft3xrt15BuyiBackendNode10speed_ops_E "永久链接至目标")

    bool is\_speedmode\_ = false[#](#_CPPv4N6icraft3xrt15BuyiBackendNode13is_speedmode_E "永久链接至目标")

    bool is\_compressftmp\_ = false[#](#_CPPv4N6icraft3xrt15BuyiBackendNode16is_compressftmp_E "永久链接至目标")

    bool is\_applied\_ = false[#](#_CPPv4N6icraft3xrt15BuyiBackendNode11is_applied_E "永久链接至目标")

    bool is\_mmu = true[#](#_CPPv4N6icraft3xrt15BuyiBackendNode6is_mmuE "永久链接至目标")

    bool is\_pure\_ = false[#](#_CPPv4N6icraft3xrt15BuyiBackendNode8is_pure_E "永久链接至目标")

    int buyibackend\_id = 0[#](#_CPPv4N6icraft3xrt15BuyiBackendNode14buyibackend_idE "永久链接至目标")

    friend BuyiBackend

    friend ApplyHelper

    Public Static Attributes

    static int buyibackend\_sid[#](#_CPPv4N6icraft3xrt15BuyiBackendNode15buyibackend_sidE "永久链接至目标")
