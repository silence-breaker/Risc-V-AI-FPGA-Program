# Class HardOpInfoNode[#](#class-hardopinfonode "此标题的永久链接")

* Defined in [File buyibackend.h](file_icraft-backends_buyibackend_buyibackend.h.md#file-icraft-backends-buyibackend-buyibackend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public icraft::xir::NodeBase< HardOpInfoNode, Node >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HardOpInfoNode : public icraft::xir::NodeBase<[HardOpInfoNode](#_CPPv4N6icraft3xrt14HardOpInfoNodeE "icraft::xrt::HardOpInfoNode"), Node>[#](#_CPPv4N6icraft3xrt14HardOpInfoNodeE "永久链接至目标")
:   与icraft::xir::HardOp类的对应，包含BuyiBackend中一些补充信息

    Public Functions

    virtual void accept(AttrVisitor &visitor) override[#](#_CPPv4N6icraft3xrt14HardOpInfoNode6acceptER11AttrVisitor "永久链接至目标")

    virtual bool reduceAccept(Node \*other, const ReduceVisitor &reduce) const override[#](#_CPPv4NK6icraft3xrt14HardOpInfoNode12reduceAcceptEP4NodeRK13ReduceVisitor "永久链接至目标")

    Public Members

    uint64\_t weights\_logic\_addr = 0[#](#_CPPv4N6icraft3xrt14HardOpInfoNode18weights_logic_addrE "永久链接至目标")

    uint64\_t weights\_size = 0[#](#_CPPv4N6icraft3xrt14HardOpInfoNode12weights_sizeE "永久链接至目标")

    uint64\_t instr\_logic\_addr = 0[#](#_CPPv4N6icraft3xrt14HardOpInfoNode16instr_logic_addrE "永久链接至目标")

    uint64\_t instr\_size = 0[#](#_CPPv4N6icraft3xrt14HardOpInfoNode10instr_sizeE "永久链接至目标")

    bool user\_used = false[#](#_CPPv4N6icraft3xrt14HardOpInfoNode9user_usedE "永久链接至目标")

    uint64\_t weight\_phy\_addr[#](#_CPPv4N6icraft3xrt14HardOpInfoNode15weight_phy_addrE "永久链接至目标")

    uint64\_t instr\_phy\_addr[#](#_CPPv4N6icraft3xrt14HardOpInfoNode14instr_phy_addrE "永久链接至目标")

    HardOp net\_hardop[#](#_CPPv4N6icraft3xrt14HardOpInfoNode10net_hardopE "永久链接至目标")

    std::vector<[ULL](typedef_buyibackend_8h_1a114b7183aabd6c95ddb1f1cb7882cb9f.md#_CPPv43ULL "ULL")> instr\_data[#](#_CPPv4N6icraft3xrt14HardOpInfoNode10instr_dataE "永久链接至目标")

    std::vector<int64\_t> merge\_from[#](#_CPPv4N6icraft3xrt14HardOpInfoNode10merge_fromE "永久链接至目标")

    std::pair<int, int> sync\_idx[#](#_CPPv4N6icraft3xrt14HardOpInfoNode8sync_idxE "永久链接至目标")
