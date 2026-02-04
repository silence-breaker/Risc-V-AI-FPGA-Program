# Class LogicSegment[#](#class-logicsegment "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::HandleBase< LogicSegment, Handle, LogicSegmentNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class LogicSegment : public icraft::xir::HandleBase<[LogicSegment](#_CPPv4N6icraft3xrt12LogicSegmentE "icraft::xrt::LogicSegment"), Handle, [LogicSegmentNode](classicraft_1_1xrt_1_1_logic_segment_node.md#_CPPv4N6icraft3xrt16LogicSegmentNodeE "icraft::xrt::LogicSegmentNode")>[#](#_CPPv4N6icraft3xrt12LogicSegmentE "永久链接至目标")
:   LogicSegment引用类

    Public Functions

    LogicSegment() = default[#](#_CPPv4N6icraft3xrt12LogicSegment12LogicSegmentEv "永久链接至目标")

    inline LogicSegment(Segment segment\_type)[#](#_CPPv4N6icraft3xrt12LogicSegment12LogicSegmentE7Segment "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo")> &getValueMap()[#](#_CPPv4N6icraft3xrt12LogicSegment11getValueMapEv "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1_hard_op_info.md#_CPPv4N6icraft3xrt10HardOpInfoE "icraft::xrt::HardOpInfo")> &getOpMap()[#](#_CPPv4N6icraft3xrt12LogicSegment8getOpMapEv "永久链接至目标")

    void setLogicAddr(uint64\_t logic\_addr)[#](#_CPPv4N6icraft3xrt12LogicSegment12setLogicAddrE8uint64_t "永久链接至目标")

    void setByteSize(uint64\_t byte\_size)[#](#_CPPv4N6icraft3xrt12LogicSegment11setByteSizeE8uint64_t "永久链接至目标")
