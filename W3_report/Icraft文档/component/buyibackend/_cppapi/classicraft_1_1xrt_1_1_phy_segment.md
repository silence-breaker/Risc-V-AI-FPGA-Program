# Class PhySegment[#](#class-physegment "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::HandleBase< PhySegment, Handle, PhySegmentNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class PhySegment : public icraft::xir::HandleBase<[PhySegment](#_CPPv4N6icraft3xrt10PhySegmentE "icraft::xrt::PhySegment"), Handle, [PhySegmentNode](classicraft_1_1xrt_1_1_phy_segment_node.md#_CPPv4N6icraft3xrt14PhySegmentNodeE "icraft::xrt::PhySegmentNode")>[#](#_CPPv4N6icraft3xrt10PhySegmentE "永久链接至目标")
:   PhySegment引用类

    Public Functions

    PhySegment() = default[#](#_CPPv4N6icraft3xrt10PhySegment10PhySegmentEv "永久链接至目标")

    inline PhySegment([LogicSegment](classicraft_1_1xrt_1_1_logic_segment.md#_CPPv4N6icraft3xrt12LogicSegmentE "icraft::xrt::LogicSegment") logic\_segment)[#](#_CPPv4N6icraft3xrt10PhySegment10PhySegmentE12LogicSegment "永久链接至目标")

    inline PhySegment(Segment segment\_type)[#](#_CPPv4N6icraft3xrt10PhySegment10PhySegmentE7Segment "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo")> &getValueMap()[#](#_CPPv4N6icraft3xrt10PhySegment11getValueMapEv "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1_hard_op_info.md#_CPPv4N6icraft3xrt10HardOpInfoE "icraft::xrt::HardOpInfo")> &getOpMap()[#](#_CPPv4N6icraft3xrt10PhySegment8getOpMapEv "永久链接至目标")

    void setPhyAddr(uint64\_t logic\_addr)[#](#_CPPv4N6icraft3xrt10PhySegment10setPhyAddrE8uint64_t "永久链接至目标")

    void setByteSize(uint64\_t byte\_size)[#](#_CPPv4N6icraft3xrt10PhySegment11setByteSizeE8uint64_t "永久链接至目标")

    void setUserUsed(bool user\_used)[#](#_CPPv4N6icraft3xrt10PhySegment11setUserUsedEb "永久链接至目标")

    void setMemChunk(MemChunk mem\_chunk)[#](#_CPPv4N6icraft3xrt10PhySegment11setMemChunkE8MemChunk "永久链接至目标")
