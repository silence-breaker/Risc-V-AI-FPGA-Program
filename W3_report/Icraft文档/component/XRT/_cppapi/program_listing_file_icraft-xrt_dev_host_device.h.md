# Program Listing for File host_device.h

```cpp
#pragma once
#ifndef XRT_HOST_DEVICE_PCH_GUARD
#define XRT_HOST_DEVICE_PCH_GUARD
#include <icraft-xrt/core/device.h>

namespace icraft::xrt {
    class HostMemRegionNode : public NodeBase<HostMemRegionNode, MemRegionNode> {
    private:
        virtual void init() override {};

        virtual void deinit() override {};

        XRT_DLL virtual void read(char* dest, const MemPtr& src, uint64_t byte_size) const override;

        XRT_DLL virtual void write(const MemPtr& dest, char* src, uint64_t byte_size) const override;

        XRT_DLL virtual MemChunk malloc(uint64_t byte_size, bool auto_free, uint64_t alignment) const override;

        XRT_DLL virtual MemChunk malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter, bool auto_free) const override;

        XRT_DLL virtual void free(const MemPtr& src) const override;

        XRT_DLL virtual void memcpy(const MemPtr& dest, const MemPtr& src, uint64_t byte_size) const override;
    };

    class HostMemRegion : public HandleBase<HostMemRegion, MemRegion, HostMemRegionNode> {};

    class HostDeviceNode : public NodeBase<HostDeviceNode, DeviceNode> {
    public:
        ICRAFT_DECLARE_DEVICE_NODE(HostDeviceNode) {
            ICRAFT_DEFAULT_MEM_REGION_FIELD(host, HostMemRegion);
        }

        virtual void initBeforeRegions() override {};

        virtual void initAfterRegions() override {};

        virtual void deinitBeforeRegions() override {};

        virtual void deinitAfterRegions() override {};

        virtual void reset(int level) override {};

        virtual bool check(int level) const override { return true; };

        virtual void showStatus(int level) const override {};

        virtual std::unordered_map<std::string, std::string> version() const override {
            return {};
        };
    };

    class HostDevice : public HandleBase<HostDevice, Device, HostDeviceNode> {
    public:
        XRT_DLL static HostDevice& Default();

        XRT_DLL static HostMemRegion& MemRegion();
    };
}
#endif //XRT_HOST_DEVICE_PCH_GUARD
```

[Return to documentation for file](file_icraft-xrt_dev_host_device.h.md#file-icraft-xrt-dev-host-device-h)
