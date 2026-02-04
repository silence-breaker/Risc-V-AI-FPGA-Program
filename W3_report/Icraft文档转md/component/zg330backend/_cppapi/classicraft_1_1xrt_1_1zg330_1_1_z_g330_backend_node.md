# Class ZG330BackendNode[#](#class-zg330backendnode "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< ZG330BackendNode, BackendNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ZG330BackendNode : public NodeBase<[ZG330BackendNode](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNodeE "icraft::xrt::zg330::ZG330BackendNode"), BackendNode>[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNodeE "永久链接至目标")
:   [ZG330Backend](classicraft_1_1xrt_1_1zg330_1_1_z_g330_backend.md#classicraft_1_1xrt_1_1zg330_1_1_z_g330_backend) 表示执行在ZG330芯片的后端 必须配置对应的device才能正确执行

    Public Functions

    XRT\_DLL ZG330BackendNode()[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode16ZG330BackendNodeEv "永久链接至目标")

    virtual XRT\_DLL void init (const NetworkView &network, const Device &device) override
    :   ZG330Backend初始化.初始化的过程中会将网络在etm的存储区域进行分段，生成network\_view对应的逻辑地址信息

        参数:
        :   * **network\_view** – NetworkView中包含所有需要部署在ZG330Backend的算子
            * **device** – 执行的硬件设备

    virtual XRT\_DLL void apply () override
    :   ZG330Backend部署，session部署的过程中会调用.

    virtual XRT\_DLL void view (uint64\_t start\_index, uint64\_t end\_index) override

    virtual XRT\_DLL Backend fork () override

    virtual XRT\_DLL MergedOps autoMerge () override

    virtual XRT\_DLL void deinit () override

    virtual XRT\_DLL Operation serialize (int64\_t op\_id) override

    Public Members

    [ForwardInfo](classicraft_1_1xrt_1_1zg330_1_1_forward_info.md#_CPPv4N6icraft3xrt5zg33011ForwardInfoE "icraft::xrt::zg330::ForwardInfo") forward\_info = [ForwardInfo](classicraft_1_1xrt_1_1zg330_1_1_forward_info.md#_CPPv4N6icraft3xrt5zg33011ForwardInfoE "icraft::xrt::zg330::ForwardInfo")::Init()[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode12forward_infoE "永久链接至目标")

    std::unordered\_map<[SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType"), [LogicSegment](classicraft_1_1xrt_1_1zg330_1_1_logic_segment.md#_CPPv4N6icraft3xrt5zg33012LogicSegmentE "icraft::xrt::zg330::LogicSegment")> logic\_segment\_map[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode17logic_segment_mapE "永久链接至目标")

    std::unordered\_map<[SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType"), [PhySegment](classicraft_1_1xrt_1_1zg330_1_1_phy_segment.md#_CPPv4N6icraft3xrt5zg33010PhySegmentE "icraft::xrt::zg330::PhySegment")> phy\_segment\_map[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode15phy_segment_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1zg330_1_1_value_info.md#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo")> value\_info[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode10value_infoE "永久链接至目标")

    std::unordered\_map<uint16\_t, std::tuple<std::vector<[ValueInfo](classicraft_1_1xrt_1_1zg330_1_1_value_info.md#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo")>, uint64\_t, uint64\_t, [MemChunkInfo](classicraft_1_1xrt_1_1zg330_1_1_mem_chunk_info.md#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "icraft::xrt::zg330::MemChunkInfo")>> value\_chunk\_ids[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode15value_chunk_idsE "永久链接至目标")

    std::unordered\_map<uint16\_t, [HardOpInfo](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info.md#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo")> params\_chunk\_ids[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode16params_chunk_idsE "永久链接至目标")

    std::vector<[HardOpInfo](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info.md#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo")> speed\_ops[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode9speed_opsE "永久链接至目标")

    HardOp first\_instr\_hardop[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode18first_instr_hardopE "永久链接至目标")

    MMUMapTable map\_table[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode9map_tableE "永久链接至目标")

    MemChunk map\_table\_chunk[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode15map_table_chunkE "永久链接至目标")

    MemChunk time\_info[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode9time_infoE "永久链接至目标")

    int zg330backend\_id = 0[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode15zg330backend_idE "永久链接至目标")

    bool is\_applied = false[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode10is_appliedE "永久链接至目标")

    bool is\_mergeHardop = true[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode14is_mergeHardopE "永久链接至目标")

    bool is\_etmOptimize = true[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode14is_etmOptimizeE "永久链接至目标")

    [AllocMode](enum_zg330backend_8h_1ac48a6652dccc7cc16a301db1d7cf52b3.md#_CPPv4N6icraft3xrt5zg3309AllocModeE "icraft::xrt::zg330::AllocMode") alloc\_mode = [AllocMode](enum_zg330backend_8h_1ac48a6652dccc7cc16a301db1d7cf52b3.md#_CPPv4N6icraft3xrt5zg3309AllocModeE "icraft::xrt::zg330::AllocMode")::[BYPASS](enum_zg330backend_8h_1ac48a6652dccc7cc16a301db1d7cf52b3.md#_CPPv4N6icraft3xrt5zg3309AllocMode6BYPASSE "icraft::xrt::zg330::AllocMode::BYPASS")[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode10alloc_modeE "永久链接至目标")

    [OcmOpt](enum_zg330backend_8h_1a96f0e25ea55fa6499cf8d03dd36ebadd.md#_CPPv4N6icraft3xrt5zg3306OcmOptE "icraft::xrt::zg330::OcmOpt") ocmopt = [OcmOpt](enum_zg330backend_8h_1a96f0e25ea55fa6499cf8d03dd36ebadd.md#_CPPv4N6icraft3xrt5zg3306OcmOptE "icraft::xrt::zg330::OcmOpt")::[BEST\_SCORE](enum_zg330backend_8h_1a96f0e25ea55fa6499cf8d03dd36ebadd.md#_CPPv4N6icraft3xrt5zg3306OcmOpt10BEST_SCOREE "icraft::xrt::zg330::OcmOpt::BEST_SCORE")[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode6ocmoptE "永久链接至目标")

    Public Static Attributes

    static int zg330backend\_sid[#](#_CPPv4N6icraft3xrt5zg33016ZG330BackendNode16zg330backend_sidE "永久链接至目标")
