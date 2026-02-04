# Class HardOpInfoNode[#](#class-hardopinfonode "此标题的永久链接")

* Defined in [File zg330backend.h](file_icraft-backends_zg330backend_zg330backend.h.md#file-icraft-backends-zg330backend-zg330backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< HardOpInfoNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HardOpInfoNode : public NodeBase<[HardOpInfoNode](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNodeE "icraft::xrt::zg330::HardOpInfoNode"), Node>[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNodeE "永久链接至目标")
:   与icraft::xir::HardOp类的对应，包含ZG330Backend中一些补充信息

    Public Functions

    inline virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode6acceptER11AttrVisitor "永久链接至目标")

    Public Members

    uint64\_t weights\_logic\_addr = 0[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode18weights_logic_addrE "永久链接至目标")

    uint64\_t weights\_size = 0[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode12weights_sizeE "永久链接至目标")

    uint64\_t instr\_logic\_addr = 0[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode16instr_logic_addrE "永久链接至目标")

    uint64\_t instr\_size = 0[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode10instr_sizeE "永久链接至目标")

    uint64\_t weight\_phy\_addr[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode15weight_phy_addrE "永久链接至目标")

    uint64\_t instr\_phy\_addr[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode14instr_phy_addrE "永久链接至目标")

    HardOp net\_hardop[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode10net_hardopE "永久链接至目标")

    std::pair<int, int> sync\_idx[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode8sync_idxE "永久链接至目标")

    std::vector<int64\_t> merge\_from[#](#_CPPv4N6icraft3xrt5zg33014HardOpInfoNode10merge_fromE "永久链接至目标")
