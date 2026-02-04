# Class ForwardInfoNode[#](#class-forwardinfonode "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::NodeBase< ForwardInfoNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ForwardInfoNode : public icraft::xir::NodeBase<[ForwardInfoNode](#_CPPv4N6icraft3xrt15ForwardInfoNodeE "icraft::xrt::ForwardInfoNode"), Node>[#](#_CPPv4N6icraft3xrt15ForwardInfoNodeE "永久链接至目标")
:   在非speedMode下包含前向所需要的信息

    Public Functions

    virtual XRT\_DLL void accept (AttrVisitor &visitor) override

    virtual XRT\_DLL bool reduceAccept (Node \*other, const ReduceVisitor &reduce) const override

    Public Members

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo")> value\_map[#](#_CPPv4N6icraft3xrt15ForwardInfoNode9value_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1_hard_op_info.md#_CPPv4N6icraft3xrt10HardOpInfoE "icraft::xrt::HardOpInfo")> hardop\_map[#](#_CPPv4N6icraft3xrt15ForwardInfoNode10hardop_mapE "永久链接至目标")

    std::map<int, std::pair<int, int>> idx\_map[#](#_CPPv4N6icraft3xrt15ForwardInfoNode7idx_mapE "永久链接至目标")
