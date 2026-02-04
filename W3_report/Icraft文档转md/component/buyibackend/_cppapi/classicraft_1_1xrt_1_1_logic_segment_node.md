# Class LogicSegmentNode[#](#class-logicsegmentnode "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::NodeBase< LogicSegmentNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class LogicSegmentNode : public icraft::xir::NodeBase<[LogicSegmentNode](#_CPPv4N6icraft3xrt16LogicSegmentNodeE "icraft::xrt::LogicSegmentNode"), Node>[#](#_CPPv4N6icraft3xrt16LogicSegmentNodeE "永久链接至目标")
:   逻辑分段类，在BuyiBackend 初始化时生成，表示对应network\_view的各分段的逻辑地址相关数据

    Public Functions

    virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt16LogicSegmentNode6acceptER11AttrVisitor "永久链接至目标")

    virtual bool reduceAccept(Node \*other, const ReduceVisitor &reduce) const override[#](#_CPPv4NK6icraft3xrt16LogicSegmentNode12reduceAcceptEP4NodeRK13ReduceVisitor "永久链接至目标")

    Public Members

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo")> info\_map[#](#_CPPv4N6icraft3xrt16LogicSegmentNode8info_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1_hard_op_info.md#_CPPv4N6icraft3xrt10HardOpInfoE "icraft::xrt::HardOpInfo")> hardop\_map[#](#_CPPv4N6icraft3xrt16LogicSegmentNode10hardop_mapE "永久链接至目标")

    uint64\_t logic\_addr = 0[#](#_CPPv4N6icraft3xrt16LogicSegmentNode10logic_addrE "永久链接至目标")

    uint64\_t byte\_size = 0[#](#_CPPv4N6icraft3xrt16LogicSegmentNode9byte_sizeE "永久链接至目标")

    Segment segment\_type[#](#_CPPv4N6icraft3xrt16LogicSegmentNode12segment_typeE "永久链接至目标")
