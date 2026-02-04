# Class CudaDevice[#](#class-cudadevice "此标题的永久链接")

* Defined in [File device.h](file_icraft-backends_hostbackend_cuda_device.h.md#file-icraft-backends-hostbackend-cuda-device-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< CudaDevice, Device, CudaDeviceNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class CudaDevice : public HandleBase<[CudaDevice](#_CPPv4N6icraft3xrt10CudaDeviceE "icraft::xrt::CudaDevice"), Device, [CudaDeviceNode](classicraft_1_1xrt_1_1_cuda_device_node.md#_CPPv4N6icraft3xrt14CudaDeviceNodeE "icraft::xrt::CudaDeviceNode")>[#](#_CPPv4N6icraft3xrt10CudaDeviceE "永久链接至目标")
:   Public Static Functions

    static [CudaDevice](#_CPPv4N6icraft3xrt10CudaDeviceE "icraft::xrt::CudaDevice") &Default()[#](#_CPPv4N6icraft3xrt10CudaDevice7DefaultEv "永久链接至目标")
    :   获取全局默认的CudaDevice对象.

    static [CudaMemRegion](classicraft_1_1xrt_1_1_cuda_mem_region.md#_CPPv4N6icraft3xrt13CudaMemRegionE "icraft::xrt::CudaMemRegion") &MemRegion()[#](#_CPPv4N6icraft3xrt10CudaDevice9MemRegionEv "永久链接至目标")
    :   获取全局默认的CudaDevice的内存区域对象.
