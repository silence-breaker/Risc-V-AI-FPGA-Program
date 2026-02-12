# Class LogicSegmentNode[#](#class-logicsegmentnode "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< LogicSegmentNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class LogicSegmentNode : public NodeBase<[LogicSegmentNode](#_CPPv4N6icraft3xrt5zg33016LogicSegmentNodeE "icraft::xrt::zg330::LogicSegmentNode"), Node>[#](#_CPPv4N6icraft3xrt5zg33016LogicSegmentNodeE "永久链接至目标")
:   逻辑分段类，在ZG330Backend 初始化时生成，表示对应network\_view的各分段的逻辑地址相关数据

    Public Functions

    inline virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt5zg33016LogicSegmentNode6acceptER11AttrVisitor "永久链接至目标")

    Public Members

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1zg330_1_1_value_info.md#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo")> info\_map[#](#_CPPv4N6icraft3xrt5zg33016LogicSegmentNode8info_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info.md#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo")> hardop\_map[#](#_CPPv4N6icraft3xrt5zg33016LogicSegmentNode10hardop_mapE "永久链接至目标")

    uint64\_t logic\_addr = 0[#](#_CPPv4N6icraft3xrt5zg33016LogicSegmentNode10logic_addrE "永久链接至目标")

    uint64\_t byte\_size = 0[#](#_CPPv4N6icraft3xrt5zg33016LogicSegmentNode9byte_sizeE "永久链接至目标")

    [SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType") segment\_type[#](#_CPPv4N6icraft3xrt5zg33016LogicSegmentNode12segment_typeE "永久链接至目标")
