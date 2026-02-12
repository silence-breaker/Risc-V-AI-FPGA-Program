# Class HardOpInfo[#](#class-hardopinfo "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< HardOpInfo, Handle, HardOpInfoNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HardOpInfo : public HandleBase<[HardOpInfo](#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "icraft::xrt::zg330::HardOpInfo"), Handle, [HardOpInfoNode](classicraft_1_1xrt_1_1zg330_1_1_hard_op_info_node.md#_CPPv4N6icraft3xrt5zg33014HardOpInfoNodeE "icraft::xrt::zg330::HardOpInfoNode")>[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfoE "永久链接至目标")
:   HardOpInfo引用类

    Public Functions

    HardOpInfo() = default[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo10HardOpInfoEv "永久链接至目标")

    inline HardOpInfo(const HardOp &hardop)[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo10HardOpInfoERK6HardOp "永久链接至目标")

    void setWLogicAddr(uint64\_t w\_logic\_addr)[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo13setWLogicAddrE8uint64_t "永久链接至目标")

    void setWSize(uint64\_t w\_byte\_size)[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo8setWSizeE8uint64_t "永久链接至目标")

    void setWPhyAddr(uint64\_t w\_phy\_addr)[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo11setWPhyAddrE8uint64_t "永久链接至目标")

    void setILogicAddr(uint64\_t i\_logic\_addr)[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo13setILogicAddrE8uint64_t "永久链接至目标")

    void setISize(uint64\_t i\_byte\_size)[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo8setISizeE8uint64_t "永久链接至目标")

    void setIPhyAddr(uint64\_t i\_phy\_addr)[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo11setIPhyAddrE8uint64_t "永久链接至目标")

    void setSyncIdx(std::pair<int, int> sync\_idx)[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo10setSyncIdxENSt4pairIiiEE "永久链接至目标")

    std::vector<int64\_t> &getMergeFrom()[#](#_CPPv4N6icraft3xrt5zg33010HardOpInfo12getMergeFromEv "永久链接至目标")
