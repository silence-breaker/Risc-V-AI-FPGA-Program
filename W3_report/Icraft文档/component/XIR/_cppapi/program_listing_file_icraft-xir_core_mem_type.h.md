# Program Listing for File mem_type.h



↰ [Return to documentation for file](file_icraft-xir_core_mem_type.h.md#file-icraft-xir-core-mem-type-h) (`icraft-xir\core\mem_type.h`)


```cpp
#pragma once
#include <icraft-xir/core/node.h>
#include <icraft-xir/core/reflection.h>
#include <icraft-xir/base/dllexport.h>

namespace icraft::xir {

    class MemTypeNode : public NodeBase<MemTypeNode, Node> {
    public:
        virtual uint64_t getStorageBits(uint64_t bits) const { return 0; };

        virtual void accept(AttrVisitor& visitor) override {}
    };

    class HostMemNode;
    class OnChipMemNode;
    class ExternalMemNode;

    class MemType : public VirtualBase<MemType, Handle, MemTypeNode> {};

    class HostMemNode : public NodeBase<HostMemNode, MemTypeNode> {
    public:
        virtual void accept(AttrVisitor& visitor) override {};

        XIR_DLL virtual uint64_t getStorageBits(uint64_t bits) const override;
    };

    class HostMem : public HandleBase<HostMem, MemType, HostMemNode> {};

    class OnChipMemNode : public NodeBase<OnChipMemNode, MemTypeNode> {
    public:
        uint64_t addr;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(OnChipMemNode* other, const ReduceVisitor& reduce) const;

        XIR_DLL virtual uint64_t getStorageBits(uint64_t bits) const override;
    };

    class OnChipMem : public HandleBase<OnChipMem, MemType, OnChipMemNode> {
    public:
        OnChipMem() = default;

        XIR_DLL explicit OnChipMem(uint64_t addr);

        XIR_DLL OnChipMem& setAddr(uint64_t addr);
    };

    class ExternalMemNode : public NodeBase<ExternalMemNode, MemTypeNode> {
    public:
        uint64_t addr;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(ExternalMemNode* other, const ReduceVisitor& reduce) const;

        XIR_DLL virtual uint64_t getStorageBits(uint64_t bits) const override;
    };

    class ExternalMem : public HandleBase<ExternalMem, MemType, ExternalMemNode> {
    public:
        ExternalMem() = default;

        XIR_DLL explicit ExternalMem(uint64_t addr);

        XIR_DLL ExternalMem& setAddr(uint64_t addr);
    };

    class ChunkMemNode : public NodeBase<ChunkMemNode, MemTypeNode> {
    public:
        uint64_t chunk_id;
        uint64_t offset;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(ChunkMemNode* other, const ReduceVisitor& reduce) const;

        XIR_DLL virtual uint64_t getStorageBits(uint64_t bits) const override;
    };

    class ChunkMem: public HandleBase<ChunkMem, MemType, ChunkMemNode> {
    public:
        ChunkMem() = default;

        XIR_DLL explicit ChunkMem(uint64_t chunk_id, uint64_t offset);

        XIR_DLL ChunkMem& setAddr(uint64_t chunk_id, uint64_t offset);
    };
}
</pre>
```
