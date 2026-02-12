# Class PhySegmentNode[#](#class-physegmentnode "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< PhySegmentNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class PhySegmentNode : public NodeBase<[PhySegmentNode](#_CPPv4N6icraft3xrt5zg33014PhySegmentNodeE "icraft::xrt::zg330::PhySegmentNode"), Node>[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNodeE "永久链接至目标")
:   物理分段类，在ZG330Backend在apply部署后生成，表示对应network\_view的各分段的真实物理地址相关数据

    Public Functions

    inline virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNode6acceptER11AttrVisitor "永久链接至目标")

    Public Members

    [SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType") segment\_type[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNode12segment_typeE "永久链接至目标")

    uint64\_t byte\_size[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNode9byte_sizeE "永久链接至目标")

    uint64\_t phy\_addr[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNode8phy_addrE "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1zg330_1_1_value_info.md#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo")> info\_map[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNode8info_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info.md#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo")> hardop\_map[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNode10hardop_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [MemChunkInfo](classicraft_1_1xrt_1_1zg330_1_1_mem_chunk_info.md#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "icraft::xrt::zg330::MemChunkInfo")> multi\_chunk[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNode11multi_chunkE "永久链接至目标")

    [MemChunkInfo](classicraft_1_1xrt_1_1zg330_1_1_mem_chunk_info.md#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "icraft::xrt::zg330::MemChunkInfo") single\_chunk[#](#_CPPv4N6icraft3xrt5zg33014PhySegmentNode12single_chunkE "永久链接至目标")

    Friends

    *friend class* PhySegment
