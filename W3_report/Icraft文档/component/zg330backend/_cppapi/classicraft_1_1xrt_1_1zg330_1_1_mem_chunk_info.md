# Class MemChunkInfo[#](#class-memchunkinfo "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< MemChunkInfo, Handle, MemChunkInfoNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class MemChunkInfo : public HandleBase<[MemChunkInfo](#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "icraft::xrt::zg330::MemChunkInfo"), Handle, [MemChunkInfoNode](classicraft_1_1xrt_1_1zg330_1_1_mem_chunk_info_node.md#_CPPv4N6icraft3xrt5zg33016MemChunkInfoNodeE "icraft::xrt::zg330::MemChunkInfoNode")>[#](#_CPPv4N6icraft3xrt5zg33012MemChunkInfoE "永久链接至目标")
:   MemChunkInfo引用类

    Public Functions

    MemChunkInfo() = default[#](#_CPPv4N6icraft3xrt5zg33012MemChunkInfo12MemChunkInfoEv "永久链接至目标")

    inline MemChunkInfo(MemChunk memchunk, bool user\_used = false)[#](#_CPPv4N6icraft3xrt5zg33012MemChunkInfo12MemChunkInfoE8MemChunkb "永久链接至目标")

    void setMemChunk(MemChunk mem\_chunk)[#](#_CPPv4N6icraft3xrt5zg33012MemChunkInfo11setMemChunkE8MemChunk "永久链接至目标")

    void setUserUsed(bool user\_used)[#](#_CPPv4N6icraft3xrt5zg33012MemChunkInfo11setUserUsedEb "永久链接至目标")

    void setStagedChunk(int64\_t v\_id, MemChunk staged\_chunk)[#](#_CPPv4N6icraft3xrt5zg33012MemChunkInfo14setStagedChunkE7int64_t8MemChunk "永久链接至目标")
