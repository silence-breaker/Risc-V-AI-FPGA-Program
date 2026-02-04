# Class PhySegment[#](#class-physegment "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< PhySegment, Handle, PhySegmentNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class PhySegment : public HandleBase<[PhySegment](#_CPPv4N6icraft3xrt5zg33010PhySegmentE "icraft::xrt::zg330::PhySegment"), Handle, [PhySegmentNode](classicraft_1_1xrt_1_1zg330_1_1_phy_segment_node.md#_CPPv4N6icraft3xrt5zg33014PhySegmentNodeE "icraft::xrt::zg330::PhySegmentNode")>[#](#_CPPv4N6icraft3xrt5zg33010PhySegmentE "永久链接至目标")
:   PhySegment引用类

    Public Functions

    PhySegment() = default[#](#_CPPv4N6icraft3xrt5zg33010PhySegment10PhySegmentEv "永久链接至目标")

    inline PhySegment([LogicSegment](classicraft_1_1xrt_1_1zg330_1_1_logic_segment.md#_CPPv4N6icraft3xrt5zg33012LogicSegmentE "icraft::xrt::zg330::LogicSegment") logic\_segment)[#](#_CPPv4N6icraft3xrt5zg33010PhySegment10PhySegmentE12LogicSegment "永久链接至目标")

    inline PhySegment([SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType") segment\_type)[#](#_CPPv4N6icraft3xrt5zg33010PhySegment10PhySegmentE11SegmentType "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1zg330_1_1_value_info.md#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo")> &getValueMap()[#](#_CPPv4N6icraft3xrt5zg33010PhySegment11getValueMapEv "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info.md#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo")> &getOpMap()[#](#_CPPv4N6icraft3xrt5zg33010PhySegment8getOpMapEv "永久链接至目标")

    void setPhyAddr(uint64\_t logic\_addr)[#](#_CPPv4N6icraft3xrt5zg33010PhySegment10setPhyAddrE8uint64_t "永久链接至目标")

    void setByteSize(uint64\_t byte\_size)[#](#_CPPv4N6icraft3xrt5zg33010PhySegment11setByteSizeE8uint64_t "永久链接至目标")

    [MemChunkInfo](classicraft_1_1xrt_1_1zg330_1_1_mem_chunk_info.md#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "icraft::xrt::zg330::MemChunkInfo") &getSingleMemChunk()[#](#_CPPv4N6icraft3xrt5zg33010PhySegment17getSingleMemChunkEv "永久链接至目标")

    std::unordered\_map<int64\_t, [MemChunkInfo](classicraft_1_1xrt_1_1zg330_1_1_mem_chunk_info.md#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "icraft::xrt::zg330::MemChunkInfo")> &getMutiMemChunk()[#](#_CPPv4N6icraft3xrt5zg33010PhySegment15getMutiMemChunkEv "永久链接至目标")
