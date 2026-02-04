# Program Listing for File device.h[#](#program-listing-for-file-device-h "此标题的永久链接")

↰ [Return to documentation for file](file_icraft-backends_hostbackend_cuda_device.h.md#file-icraft-backends-hostbackend-cuda-device-h) (`icraft-backends\hostbackend\cuda\device.h`)

```
#pragma once
#include "icraft-xrt/core/device.h"
#include "icraft-backends/hostbackend/cuda/memory.h"
#include "icraft-backends/hostbackend/cuda/dllexport.h"

namespace icraft {
    namespace xrt {
        class CudaDeviceNode : public NodeBase<CudaDeviceNode, DeviceNode> {
        public:
            ICRAFT_DECLARE_DEVICE_NODE(CudaDeviceNode) {
                ICRAFT_DEFAULT_MEM_REGION_FIELD(cuda, CudaMemRegion);
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

        class CudaDevice : public HandleBase<CudaDevice, Device, CudaDeviceNode> {
        public:
            CUDADEV_DLL static CudaDevice& Default();

            CUDADEV_DLL static CudaMemRegion& MemRegion();
        };
    }
}
```
