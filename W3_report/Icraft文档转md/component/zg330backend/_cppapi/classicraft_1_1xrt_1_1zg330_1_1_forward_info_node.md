# Class ForwardInfoNode[#](#class-forwardinfonode "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< ForwardInfoNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ForwardInfoNode : public NodeBase<[ForwardInfoNode](#_CPPv4N6icraft3xrt5zg33015ForwardInfoNodeE "icraft::xrt::zg330::ForwardInfoNode"), Node>[#](#_CPPv4N6icraft3xrt5zg33015ForwardInfoNodeE "永久链接至目标")
:   ZG330Backend前向所需要的信息

    Public Functions

    inline virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt5zg33015ForwardInfoNode6acceptER11AttrVisitor "永久链接至目标")

    Public Members

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1zg330_1_1_value_info.md#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo")> value\_map[#](#_CPPv4N6icraft3xrt5zg33015ForwardInfoNode9value_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info.md#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo")> hardop\_map[#](#_CPPv4N6icraft3xrt5zg33015ForwardInfoNode10hardop_mapE "永久链接至目标")

    std::unordered\_map<int, std::pair<int, int>> idx\_map[#](#_CPPv4N6icraft3xrt5zg33015ForwardInfoNode7idx_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [MemChunkInfo](classicraft_1_1xrt_1_1zg330_1_1_mem_chunk_info.md#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "icraft::xrt::zg330::MemChunkInfo")> memchunk\_map[#](#_CPPv4N6icraft3xrt5zg33015ForwardInfoNode12memchunk_mapE "永久链接至目标")
