# Class CudaDeviceNode[#](#class-cudadevicenode "此标题的永久链接")

* Defined in [File device.h](file_icraft-backends_hostbackend_cuda_device.h.md#file-icraft-backends-hostbackend-cuda-device-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< CudaDeviceNode, DeviceNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class CudaDeviceNode : public NodeBase<[CudaDeviceNode](#_CPPv4N6icraft3xrt14CudaDeviceNodeE "icraft::xrt::CudaDeviceNode"), DeviceNode>[#](#_CPPv4N6icraft3xrt14CudaDeviceNodeE "永久链接至目标")
:   表示Cuda设备的类型.

    Public Functions

    inline ICRAFT\_DECLARE\_DEVICE\_NODE([CudaDeviceNode](#_CPPv4N6icraft3xrt14CudaDeviceNodeE "icraft::xrt::CudaDeviceNode"))[#](#_CPPv4N6icraft3xrt14CudaDeviceNode26ICRAFT_DECLARE_DEVICE_NODEE14CudaDeviceNode "永久链接至目标")

    inline virtual void initBeforeRegions() override[#](#_CPPv4N6icraft3xrt14CudaDeviceNode17initBeforeRegionsEv "永久链接至目标")
    :   实现initBeforeRegions接口

    inline virtual void initAfterRegions() override[#](#_CPPv4N6icraft3xrt14CudaDeviceNode16initAfterRegionsEv "永久链接至目标")
    :   实现initAfterRegions接口

    inline virtual void deinitBeforeRegions() override[#](#_CPPv4N6icraft3xrt14CudaDeviceNode19deinitBeforeRegionsEv "永久链接至目标")
    :   实现deinitBeforeRegions接口

    inline virtual void deinitAfterRegions() override[#](#_CPPv4N6icraft3xrt14CudaDeviceNode18deinitAfterRegionsEv "永久链接至目标")
    :   实现deinitAfterRegions接口

    inline virtual void reset(int level) override[#](#_CPPv4N6icraft3xrt14CudaDeviceNode5resetEi "永久链接至目标")
    :   实现reset接口

    inline virtual bool check(int level) const override[#](#_CPPv4NK6icraft3xrt14CudaDeviceNode5checkEi "永久链接至目标")
    :   实现check接口

    inline virtual void showStatus(int level) const override[#](#_CPPv4NK6icraft3xrt14CudaDeviceNode10showStatusEi "永久链接至目标")
    :   实现showStatus接口

    inline virtual std::unordered\_map<std::string, std::string> version() const override[#](#_CPPv4NK6icraft3xrt14CudaDeviceNode7versionEv "永久链接至目标")
    :   实现version接口
