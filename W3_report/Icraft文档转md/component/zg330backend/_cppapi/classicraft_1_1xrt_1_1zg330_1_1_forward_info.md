# Class ForwardInfo[#](#class-forwardinfo "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< ForwardInfo, Handle, ForwardInfoNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ForwardInfo : public HandleBase<[ForwardInfo](#_CPPv4N6icraft3xrt5zg33011ForwardInfoE "icraft::xrt::zg330::ForwardInfo"), Handle, [ForwardInfoNode](classicraft_1_1xrt_1_1zg330_1_1_forward_info_node.md#_CPPv4N6icraft3xrt5zg33015ForwardInfoNodeE "icraft::xrt::zg330::ForwardInfoNode")>[#](#_CPPv4N6icraft3xrt5zg33011ForwardInfoE "永久链接至目标")
:   ForwardInfo引用类

    Public Functions

    ForwardInfo() = default[#](#_CPPv4N6icraft3xrt5zg33011ForwardInfo11ForwardInfoEv "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1zg330_1_1_value_info.md#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo")> &getValueMap()[#](#_CPPv4N6icraft3xrt5zg33011ForwardInfo11getValueMapEv "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info.md#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo")> &getHardopMap()[#](#_CPPv4N6icraft3xrt5zg33011ForwardInfo12getHardopMapEv "永久链接至目标")

    std::unordered\_map<int, std::pair<int, int>> &getIdxMap()[#](#_CPPv4N6icraft3xrt5zg33011ForwardInfo9getIdxMapEv "永久链接至目标")

    std::unordered\_map<int64\_t, [MemChunkInfo](classicraft_1_1xrt_1_1zg330_1_1_mem_chunk_info.md#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "icraft::xrt::zg330::MemChunkInfo")> &getMemChunkMap()[#](#_CPPv4N6icraft3xrt5zg33011ForwardInfo14getMemChunkMapEv "永久链接至目标")
