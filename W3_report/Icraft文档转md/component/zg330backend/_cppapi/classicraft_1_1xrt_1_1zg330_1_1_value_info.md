# Class ValueInfo[#](#class-valueinfo "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< ValueInfo, Handle, ValueInfoNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ValueInfo : public HandleBase<[ValueInfo](#_CPPv4N6icraft3xrt5zg3309ValueInfoE "icraft::xrt::zg330::ValueInfo"), Handle, [ValueInfoNode](classicraft_1_1xrt_1_1zg330_1_1_value_info_node.md#_CPPv4N6icraft3xrt5zg33013ValueInfoNodeE "icraft::xrt::zg330::ValueInfoNode")>[#](#_CPPv4N6icraft3xrt5zg3309ValueInfoE "永久链接至目标")
:   ValueInfo引用类

    Public Functions

    ValueInfo() = default[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo9ValueInfoEv "永久链接至目标")

    inline ValueInfo(const Value &value)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo9ValueInfoERK5Value "永久链接至目标")

    void setReal(bool real)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo7setRealEb "永久链接至目标")

    void setOcm(bool is\_ocm)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo6setOcmEb "永久链接至目标")

    void setPhyAddr(uint64\_t phy\_addr)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo10setPhyAddrE8uint64_t "永久链接至目标")

    void setLogicAddr(uint64\_t logic\_addr)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo12setLogicAddrE8uint64_t "永久链接至目标")

    void setFakeFrom(const Value &value)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo11setFakeFromERK5Value "永久链接至目标")

    void setRealTo(const std::vector<Value> &value)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo9setRealToERKNSt6vectorI5ValueEE "永久链接至目标")

    void addRealTo(const Value &value)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo9addRealToERK5Value "永久链接至目标")

    void setValue(const Value &value)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo8setValueERK5Value "永久链接至目标")

    void setSegmentType([SegmentType](enum_zg330backend_8h_1a45f8c604b4008a278fe9bde5156489ee.md#_CPPv4N6icraft3xrt5zg33011SegmentTypeE "icraft::xrt::zg330::SegmentType") segment)[#](#_CPPv4N6icraft3xrt5zg3309ValueInfo14setSegmentTypeE11SegmentType "永久链接至目标")
