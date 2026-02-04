# Class MemChunkInfoNode[#](#class-memchunkinfonode "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< MemChunkInfoNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class MemChunkInfoNode : public NodeBase<[MemChunkInfoNode](#_CPPv4N6icraft3xrt5zg33016MemChunkInfoNodeE "icraft::xrt::zg330::MemChunkInfoNode"), Node>[#](#_CPPv4N6icraft3xrt5zg33016MemChunkInfoNodeE "永久链接至目标")
:   物理内存类，表示真实分配的物理内存相关数据

    Public Functions

    inline virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt5zg33016MemChunkInfoNode6acceptER11AttrVisitor "永久链接至目标")

    Public Members

    MemChunk memChunk[#](#_CPPv4N6icraft3xrt5zg33016MemChunkInfoNode8memChunkE "永久链接至目标")

    bool user\_used = false[#](#_CPPv4N6icraft3xrt5zg33016MemChunkInfoNode9user_usedE "永久链接至目标")

    std::unordered\_map<int64\_t, MemChunk> staged\_chunk[#](#_CPPv4N6icraft3xrt5zg33016MemChunkInfoNode12staged_chunkE "永久链接至目标")
