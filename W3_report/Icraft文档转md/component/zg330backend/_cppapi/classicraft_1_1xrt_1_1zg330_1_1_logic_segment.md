# Class LogicSegment[#](#class-logicsegment "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< LogicSegment, Handle, LogicSegmentNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class LogicSegment : public HandleBase<[LogicSegment](#_CPPv4N6icraft3xrt5zg33012LogicSegmentE "icraft::xrt::zg330::LogicSegment"), Handle, [LogicSegmentNode](classicraft_1_1xrt_1_1zg330_1_1_logic_segment_node.md#_CPPv4N6icraft3xrt5zg33016LogicSegmentNodeE "icraft::xrt::zg330::LogicSegmentNode")>[#](#_CPPv4N6icraft3xrt5zg33012LogicSegmentE "永久链接至目标")
:   LogicSegment引用类

    Public Functions

    LogicSegment() = default[#](#_CPPv4N6icraft3xrt5zg33012LogicSegment12LogicSegmentEv "永久链接至目标")

    inline LogicSegment([SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType") segment\_type)[#](#_CPPv4N6icraft3xrt5zg33012LogicSegment12LogicSegmentE11SegmentType "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1zg330_1_1_value_info.md#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo")> &getValueMap()[#](#_CPPv4N6icraft3xrt5zg33012LogicSegment11getValueMapEv "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info.md#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo")> &getOpMap()[#](#_CPPv4N6icraft3xrt5zg33012LogicSegment8getOpMapEv "永久链接至目标")

    void setLogicAddr(uint64\_t logic\_addr)[#](#_CPPv4N6icraft3xrt5zg33012LogicSegment12setLogicAddrE8uint64_t "永久链接至目标")

    void setByteSize(uint64\_t byte\_size)[#](#_CPPv4N6icraft3xrt5zg33012LogicSegment11setByteSizeE8uint64_t "永久链接至目标")
