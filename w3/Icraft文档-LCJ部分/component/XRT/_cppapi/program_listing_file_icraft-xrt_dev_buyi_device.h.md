# Program Listing for File buyi_device.h

```cpp
#pragma once
#ifndef XRT_BUYI_DEVICE_PCH_GUARD
#define XRT_BUYI_DEVICE_PCH_GUARD
#include <icraft-xrt/core/device.h>
#include <cstdint>
#include <map>

namespace icraft::xrt {


    class SegTableNode : public NodeBase<SegTableNode, Node>
    {
    public:
        std::array<uint32_t, 32> logic_bases_;
        std::array<uint32_t, 32> phy_bases_;
        uint32_t size = 0;


        virtual void accept(AttrVisitor& visitor) override {};

        virtual bool reduceAccept(Node* other, const ReduceVisitor& reduce) const override { return false; };
    };

    class SegTable :public HandleBase<SegTable, Handle, SegTableNode> {
    public:
        SegTable() = default;
        SegTable(const std::array<uint32_t, 32>& logi_bases, const std::array<uint32_t, 32>& phy_bases, uint32_t size)
        {
            auto node = make_object<SegTableNode>();
            node->logic_bases_ = logi_bases;
            node->phy_bases_ = phy_bases;
            node->size = size;
            data_ = std::move(node);
        };

    };

    class BuyiDeviceNode : public NodeBase<BuyiDeviceNode, DeviceNode> {
    private:
        static constexpr uint64_t FPGA_REG_BASE = 0x00000000;
        static constexpr uint64_t BUYI_REG_BASE = 0x00040000;
        static constexpr uint64_t MMU_REG_BASE = 0x100002000;

        //HOST_CTRL
        static constexpr uint64_t DEBUG_REG = 0x000 + FPGA_REG_BASE;
        static constexpr uint64_t DDR_STATE_CLR_REQ = 0x004 + FPGA_REG_BASE;
        static constexpr uint64_t DDR_STATE = 0x008 + FPGA_REG_BASE;
        static constexpr uint64_t AWLAYER_CNT = 0x00C + FPGA_REG_BASE;
        static constexpr uint64_t AWTILE_CNT = 0x010 + FPGA_REG_BASE;
        static constexpr uint64_t ARTILE_CNT = 0x014 + FPGA_REG_BASE;
        static constexpr uint64_t RUN_TIMER_CNT = 0x018 + FPGA_REG_BASE;
        static constexpr uint64_t PRJ_VER = 0x01C + FPGA_REG_BASE;
        static constexpr uint64_t ITF_EXHS_VLD = 0x020 + FPGA_REG_BASE;
        static constexpr uint64_t ITF_EXHS = 0x024 + FPGA_REG_BASE;
        static constexpr uint64_t ITF_EXHS_ACK_REQ = 0x028 + FPGA_REG_BASE;
        static constexpr uint64_t VMA_OFFSET = 0x038 + FPGA_REG_BASE;
        static constexpr uint64_t DR_STATUS = 0x20004 + FPGA_REG_BASE; //频率状态寄存器
        static constexpr uint64_t DR_CFG0 = 0x20200 + FPGA_REG_BASE;   //
        static constexpr uint64_t DR_CFG2 = 0x20208 + FPGA_REG_BASE;
        static constexpr uint64_t DR_CFG23 = 0x2025c + FPGA_REG_BASE;

        //BUYI_REG
        static constexpr uint64_t RESET_REG = 0x1DC + BUYI_REG_BASE;
        static constexpr uint64_t RUN_RESUME = 0x004 + BUYI_REG_BASE;
        static constexpr uint64_t RUN_BASE = 0x008 + BUYI_REG_BASE;
        static constexpr uint64_t RUN_SIZE = 0x00C + BUYI_REG_BASE;
        static constexpr uint64_t RUN_VALID = 0x010 + BUYI_REG_BASE;
        static constexpr uint64_t BUYI_DEBUG_REG = 0x3C + BUYI_REG_BASE;
        static constexpr uint64_t RA_IDMA_CNT = 0x40 + BUYI_REG_BASE;
        static constexpr uint64_t RA_TIMER = 0x44 + BUYI_REG_BASE;
        static constexpr uint64_t RA_DUMMY_FLAG = 0x48 + BUYI_REG_BASE;
        static constexpr uint64_t BYAI_VERSION1 = 0x4C + BUYI_REG_BASE;
        static constexpr uint64_t BYAI_VERSION2 = 0x50 + BUYI_REG_BASE;
        static constexpr uint64_t BYAI_VERSION3 = 0x54 + BUYI_REG_BASE;
        static constexpr uint64_t INST_BIST_STATUS = 0x5C + BUYI_REG_BASE;
        static constexpr uint64_t BIST_ABNORMAL = 0x60 + BUYI_REG_BASE;
        static constexpr uint64_t OCM_CLK_EN_B = 0x14 + BUYI_REG_BASE;
        static constexpr uint64_t OCM_BIST_ST_SEL = 0x18 + BUYI_REG_BASE;
        static constexpr uint64_t OCM_BIST_STATUS = 0x64 + BUYI_REG_BASE;
        static constexpr uint64_t STATIC_OCM_ERR = 0x68 + BUYI_REG_BASE;
        static constexpr uint64_t COL_ROW_EN = 0x6C + BUYI_REG_BASE;

        static constexpr uint64_t FPGA_DEBUG_REG = 0x00;
        static constexpr uint64_t FPGA_RESET_REG = 0x34;
        static constexpr uint64_t BUYI_RESET_REG = 0x1DC + BUYI_REG_BASE;

        //MMU_REG
        static constexpr uint64_t MMU_GP_START = 0x004 + MMU_REG_BASE;      //01bit, start mmu convert
        static constexpr uint64_t MMU_CONVERT_DONE = 0x008 + MMU_REG_BASE;  //01bit, hw set 0, sw set 1
        static constexpr uint64_t MMU_VERSION = 0x00C + MMU_REG_BASE;       //32bit, get MMU version
        static constexpr uint64_t MMU_TEST_REG = 0x010 + MMU_REG_BASE;      //32bit, TEST REG for debug
        static constexpr uint64_t MMU_TIME_CNT = 0x014 + MMU_REG_BASE;      //32bit, time counter
        static constexpr uint64_t MMU_SOFT_RESET = 0x018 + MMU_REG_BASE;    //01bit, set 1 to reset MMU
        static constexpr uint64_t MMU_MODE = 0x01C + MMU_REG_BASE;          //02bit, mode 0 disable , mode 1 activate
        static constexpr uint64_t MMU_LOG_BASE0 = 0x020 + MMU_REG_BASE;     //0x020~0x09C + 4byte area, LogiSegTable0, 32*32bit logiical base, low to high
        static constexpr uint64_t MMU_LOG_BASE1 = 0x0A0 + MMU_REG_BASE;     //0x0A0~0x11C + 4byte area, LogiSegTable1, 32*32bit logiical base, low to high
        static constexpr uint64_t MMU_PHY_BASE0 = 0x120 + MMU_REG_BASE;     //0x120~0x19C + 4byte area, PhySegTable0, 32*32bit (physical base - logiical base), low to high
        static constexpr uint64_t MMU_PHY_BASE1 = 0x1A0 + MMU_REG_BASE;     //0x1A0~0x21C + 4byte area, PhySegTable1, 32*32bit (physical base - logiical base), low to high
        static constexpr uint32_t MMU_SIZE = 32;

        float icore_clk_freq_ = 860E6;

        friend class BuyiDevice;

        SegTable seg_table_;

        static int sid;

        int id = 0;


    protected:
        XRT_DLL virtual void initAfterRegions() override;

        XRT_DLL virtual void reset(int level) override;

        XRT_DLL virtual bool check(int level) const override;

        XRT_DLL virtual void showStatus(int level) const override;

        XRT_DLL virtual std::unordered_map<std::string, std::string> version() const override;

        XRT_DLL uint32_t readReg(uint32_t cid, uint32_t rid, uint32_t offset) const;

        XRT_DLL void writeReg(uint32_t cid, uint32_t rid, uint32_t offset, uint32_t data) const;

        XRT_DLL std::pair<int, int> getRowsCols() const;

        XRT_DLL float calcTime() const;



    private:
        XRT_DLL bool dmaCheck() const;

        XRT_DLL bool regCheck() const;

        XRT_DLL bool patchCheck() const;

        XRT_DLL void showAllStatus() const;

        XRT_DLL void showAllCounts() const;

        XRT_DLL void showAllErrors() const;

        XRT_DLL void showReg(uint32_t base, std::string info) const;

        XRT_DLL void showReg(uint32_t cid, uint32_t rid, uint32_t offset, std::string info) const;

        XRT_DLL uint32_t readIcoreReg(uint32_t icore_reg_addr) const;

        XRT_DLL void writeIcoreReg(uint32_t icore_reg_addr, uint32_t data) const;

        XRT_DLL void showState() const;

        XRT_DLL int showMpeError() const;

        XRT_DLL int showVpeError() const;

        XRT_DLL int showOneError() const;

        XRT_DLL void showInstStatus() const;

        XRT_DLL int showMpeAvr() const;

        XRT_DLL int showVpeAvr() const;

        XRT_DLL int showOneAvr() const;

        XRT_DLL void showAvrStatus() const;

        XRT_DLL void showTileCnt() const;

        XRT_DLL void showOneState() const;

        void updateBuffer(const SegTable& seg_table);

        enum class PATCH :uint32_t {
            unpatch = 0,
            patched = 2,
            patched_fix_bug = 7
        };
    };



    class BuyiDevice : public HandleBase<BuyiDevice, Device, BuyiDeviceNode> {
    public:
        XRT_DLL std::pair<int, int> getRowsCols() const;

        XRT_DLL uint32_t readReg(uint32_t cid, uint32_t rid, uint32_t offset) const;

        XRT_DLL void writeReg(uint32_t cid, uint32_t rid, uint32_t offset, uint32_t data) const;

        XRT_DLL void setDType(int dtype) const;

        XRT_DLL void icoreCalc(uint64_t addr, uint64_t size) const;

        XRT_DLL void setClkFreq(float clk_freq);

        XRT_DLL float clkFreq() const;

        XRT_DLL uint32_t layerCount() const;

        XRT_DLL float calcTime() const;

        XRT_DLL void setEnabledMPE(uint32_t rows, uint64_t cols);

        XRT_DLL void updateBuffer(const SegTable& seg_table);

        XRT_DLL void mmuModeSwitch(bool is_on);

        XRT_DLL uint32_t modeInfo();

        XRT_DLL bool isMock();

        XRT_DLL int getId();

    };
}
#endif //XRT_BUYI_DEVICE_PCH_GUARD
```

[Return to documentation for file](file_icraft-xrt_dev_buyi_device.h.md#file-icraft-xrt-dev-buyi-device-h)
