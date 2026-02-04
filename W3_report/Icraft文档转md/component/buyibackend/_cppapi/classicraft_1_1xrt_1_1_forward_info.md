# Class ForwardInfo[#](#class-forwardinfo "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::HandleBase< ForwardInfo, Handle, ForwardInfoNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ForwardInfo : public icraft::xir::HandleBase<[ForwardInfo](#_CPPv4N6icraft3xrt11ForwardInfoE "icraft::xrt::ForwardInfo"), Handle, [ForwardInfoNode](classicraft_1_1xrt_1_1_forward_info_node.md#_CPPv4N6icraft3xrt15ForwardInfoNodeE "icraft::xrt::ForwardInfoNode")>[#](#_CPPv4N6icraft3xrt11ForwardInfoE "永久链接至目标")
:   ForwardInfo引用类

    Public Functions

    ForwardInfo() = default[#](#_CPPv4N6icraft3xrt11ForwardInfo11ForwardInfoEv "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo")> &getValueMap()[#](#_CPPv4N6icraft3xrt11ForwardInfo11getValueMapEv "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1_hard_op_info.md#_CPPv4N6icraft3xrt10HardOpInfoE "icraft::xrt::HardOpInfo")> &getHardopMap()[#](#_CPPv4N6icraft3xrt11ForwardInfo12getHardopMapEv "永久链接至目标")

    std::map<int, std::pair<int, int>> &getIdxMap()[#](#_CPPv4N6icraft3xrt11ForwardInfo9getIdxMapEv "永久链接至目标")
