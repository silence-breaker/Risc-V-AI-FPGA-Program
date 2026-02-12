# Class HardOpInfo[#](#class-hardopinfo "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::HandleBase< HardOpInfo, Handle, HardOpInfoNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HardOpInfo : public icraft::xir::HandleBase<[HardOpInfo](#_CPPv4N6icraft3xrt10HardOpInfoE "icraft::xrt::HardOpInfo"), Handle, [HardOpInfoNode](classicraft_1_1xrt_1_1_hard_op_info_node.md#_CPPv4N6icraft3xrt14HardOpInfoNodeE "icraft::xrt::HardOpInfoNode")>[#](#_CPPv4N6icraft3xrt10HardOpInfoE "永久链接至目标")
:   HardOpInfo引用类

    Public Functions

    HardOpInfo() = default[#](#_CPPv4N6icraft3xrt10HardOpInfo10HardOpInfoEv "永久链接至目标")

    inline HardOpInfo(const HardOp &hardop)[#](#_CPPv4N6icraft3xrt10HardOpInfo10HardOpInfoERK6HardOp "永久链接至目标")

    void setWLogicAddr(uint64\_t w\_logic\_addr)[#](#_CPPv4N6icraft3xrt10HardOpInfo13setWLogicAddrE8uint64_t "永久链接至目标")

    void setWSize(uint64\_t w\_byte\_size)[#](#_CPPv4N6icraft3xrt10HardOpInfo8setWSizeE8uint64_t "永久链接至目标")

    void setWPhyAddr(uint64\_t w\_phy\_addr)[#](#_CPPv4N6icraft3xrt10HardOpInfo11setWPhyAddrE8uint64_t "永久链接至目标")

    void setILogicAddr(uint64\_t i\_logic\_addr)[#](#_CPPv4N6icraft3xrt10HardOpInfo13setILogicAddrE8uint64_t "永久链接至目标")

    void setISize(uint64\_t i\_byte\_size)[#](#_CPPv4N6icraft3xrt10HardOpInfo8setISizeE8uint64_t "永久链接至目标")

    void setIPhyAddr(uint64\_t i\_phy\_addr)[#](#_CPPv4N6icraft3xrt10HardOpInfo11setIPhyAddrE8uint64_t "永久链接至目标")

    void setSyncIdx(std::pair<int, int> sync\_idx)[#](#_CPPv4N6icraft3xrt10HardOpInfo10setSyncIdxENSt4pairIiiEE "永久链接至目标")

    std::vector<[ULL](typedef_buyibackend_8h_1a114b7183aabd6c95ddb1f1cb7882cb9f.md#_CPPv43ULL "ULL")> &getInstrData()[#](#_CPPv4N6icraft3xrt10HardOpInfo12getInstrDataEv "永久链接至目标")

    std::vector<int64\_t> &getMergeFrom()[#](#_CPPv4N6icraft3xrt10HardOpInfo12getMergeFromEv "永久链接至目标")
