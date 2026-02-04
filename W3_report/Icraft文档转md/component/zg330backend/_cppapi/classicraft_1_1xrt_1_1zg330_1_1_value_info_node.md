# Class ValueInfoNode[#](#class-valueinfonode "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< ValueInfoNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ValueInfoNode : public NodeBase<[ValueInfoNode](#_CPPv4N6icraft3xrt5zg33013ValueInfoNodeE "icraft::xrt::zg330::ValueInfoNode"), Node>[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNodeE "永久链接至目标")
:   Public Functions

    inline virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode6acceptER11AttrVisitor "永久链接至目标")

    Public Members

    Value value[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode5valueE "永久链接至目标")

    bool real = true[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode4realE "永久链接至目标")

    bool is\_ocm = false[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode6is_ocmE "永久链接至目标")

    bool is\_host = false[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode7is_hostE "永久链接至目标")

    std::vector<Value> real\_to[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode7real_toE "永久链接至目标")

    Value fake\_from[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode9fake_fromE "永久链接至目标")

    uint64\_t logic\_addr = 0[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode10logic_addrE "永久链接至目标")

    uint64\_t phy\_addr = 0[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode8phy_addrE "永久链接至目标")

    uint64\_t byte\_size = 0[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode9byte_sizeE "永久链接至目标")

    [SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType") segment = [SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType")::[FTMP](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentType4FTMPE "icraft::xrt::zg330::SegmentType::FTMP")[#](#_CPPv4N6icraft3xrt5zg33013ValueInfoNode7segmentE "永久链接至目标")
