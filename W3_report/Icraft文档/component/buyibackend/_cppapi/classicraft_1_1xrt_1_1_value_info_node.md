# Class ValueInfoNode[#](#class-valueinfonode "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::NodeBase< ValueInfoNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ValueInfoNode : public icraft::xir::NodeBase<[ValueInfoNode](#_CPPv4N6icraft3xrt13ValueInfoNodeE "icraft::xrt::ValueInfoNode"), Node>[#](#_CPPv4N6icraft3xrt13ValueInfoNodeE "永久链接至目标")
:   Public Functions

    virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt13ValueInfoNode6acceptER11AttrVisitor "永久链接至目标")

    virtual bool reduceAccept(Node \*other, const ReduceVisitor &reduce) const override[#](#_CPPv4NK6icraft3xrt13ValueInfoNode12reduceAcceptEP4NodeRK13ReduceVisitor "永久链接至目标")

    Public Members

    Value value[#](#_CPPv4N6icraft3xrt13ValueInfoNode5valueE "永久链接至目标")

    bool real = true[#](#_CPPv4N6icraft3xrt13ValueInfoNode4realE "永久链接至目标")

    bool is\_ocm = false[#](#_CPPv4N6icraft3xrt13ValueInfoNode6is_ocmE "永久链接至目标")

    bool is\_host = false[#](#_CPPv4N6icraft3xrt13ValueInfoNode7is_hostE "永久链接至目标")

    std::vector<Value> real\_to[#](#_CPPv4N6icraft3xrt13ValueInfoNode7real_toE "永久链接至目标")

    Value fake\_from[#](#_CPPv4N6icraft3xrt13ValueInfoNode9fake_fromE "永久链接至目标")

    uint64\_t logic\_addr = 0[#](#_CPPv4N6icraft3xrt13ValueInfoNode10logic_addrE "永久链接至目标")

    bool user\_used = false[#](#_CPPv4N6icraft3xrt13ValueInfoNode9user_usedE "永久链接至目标")

    uint64\_t phy\_addr = 0[#](#_CPPv4N6icraft3xrt13ValueInfoNode8phy_addrE "永久链接至目标")

    uint64\_t byte\_size = 0[#](#_CPPv4N6icraft3xrt13ValueInfoNode9byte_sizeE "永久链接至目标")

    Segment segment = Segment::FTMP[#](#_CPPv4N6icraft3xrt13ValueInfoNode7segmentE "永久链接至目标")
