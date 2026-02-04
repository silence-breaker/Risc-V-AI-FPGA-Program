# Class ValueInfo[#](#class-valueinfo "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::HandleBase< ValueInfo, Handle, ValueInfoNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class ValueInfo : public icraft::xir::HandleBase<[ValueInfo](#_CPPv4N6icraft3xrt9ValueInfoE "icraft::xrt::ValueInfo"), Handle, [ValueInfoNode](classicraft_1_1xrt_1_1_value_info_node.md#_CPPv4N6icraft3xrt13ValueInfoNodeE "icraft::xrt::ValueInfoNode")>[#](#_CPPv4N6icraft3xrt9ValueInfoE "永久链接至目标")
:   ValueInfo引用类

    Public Functions

    ValueInfo() = default[#](#_CPPv4N6icraft3xrt9ValueInfo9ValueInfoEv "永久链接至目标")

    inline ValueInfo(const Value &value)[#](#_CPPv4N6icraft3xrt9ValueInfo9ValueInfoERK5Value "永久链接至目标")

    void setReal(bool real)[#](#_CPPv4N6icraft3xrt9ValueInfo7setRealEb "永久链接至目标")

    void setPhyAddr(uint64\_t phy\_addr)[#](#_CPPv4N6icraft3xrt9ValueInfo10setPhyAddrE8uint64_t "永久链接至目标")

    void setLogicAddr(uint64\_t logic\_addr)[#](#_CPPv4N6icraft3xrt9ValueInfo12setLogicAddrE8uint64_t "永久链接至目标")

    void setFakeFrom(const Value &value)[#](#_CPPv4N6icraft3xrt9ValueInfo11setFakeFromERK5Value "永久链接至目标")

    void setRealTo(const std::vector<Value> &value)[#](#_CPPv4N6icraft3xrt9ValueInfo9setRealToERKNSt6vectorI5ValueEE "永久链接至目标")

    void addRealTo(const Value &value)[#](#_CPPv4N6icraft3xrt9ValueInfo9addRealToERK5Value "永久链接至目标")

    void setValue(const Value &value)[#](#_CPPv4N6icraft3xrt9ValueInfo8setValueERK5Value "永久链接至目标")

    void setSegment(Segment segment)[#](#_CPPv4N6icraft3xrt9ValueInfo10setSegmentE7Segment "永久链接至目标")
