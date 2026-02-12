# Class PhySegmentNode[#](#class-physegmentnode "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::NodeBase< PhySegmentNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class PhySegmentNode : public icraft::xir::NodeBase<[PhySegmentNode](#_CPPv4N6icraft3xrt14PhySegmentNodeE "icraft::xrt::PhySegmentNode"), Node>[#](#_CPPv4N6icraft3xrt14PhySegmentNodeE "永久链接至目标")
:   物理分段类，在BuyiBackend在apply部署后生成，表示对应network\_view的各分段的真实物理地址相关数据

    Public Functions

    virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt14PhySegmentNode6acceptER11AttrVisitor "永久链接至目标")

    virtual bool reduceAccept(Node \*other, const ReduceVisitor &reduce) const override[#](#_CPPv4NK6icraft3xrt14PhySegmentNode12reduceAcceptEP4NodeRK13ReduceVisitor "永久链接至目标")

    Public Members

    Segment segment\_type[#](#_CPPv4N6icraft3xrt14PhySegmentNode12segment_typeE "永久链接至目标")

    uint64\_t byte\_size[#](#_CPPv4N6icraft3xrt14PhySegmentNode9byte_sizeE "永久链接至目标")

    uint64\_t phy\_addr[#](#_CPPv4N6icraft3xrt14PhySegmentNode8phy_addrE "永久链接至目标")

    MemChunk memchunk[#](#_CPPv4N6icraft3xrt14PhySegmentNode8memchunkE "永久链接至目标")

    std::unordered\_map<int64\_t, [ValueInfo](classicraft_1_1xrt_1_1_value_info.md#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo")> info\_map[#](#_CPPv4N6icraft3xrt14PhySegmentNode8info_mapE "永久链接至目标")

    std::unordered\_map<int64\_t, [HardOpInfo](classicraft_1_1xrt_1_1_hard_op_info.md#_CPPv4N6icraft3xrt10HardOpInfoE "icraft::xrt::HardOpInfo")> hardop\_map[#](#_CPPv4N6icraft3xrt14PhySegmentNode10hardop_mapE "永久链接至目标")

    bool user\_used = false[#](#_CPPv4N6icraft3xrt14PhySegmentNode9user_usedE "永久链接至目标")
