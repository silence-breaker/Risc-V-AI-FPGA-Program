# Class HostBkndCudaUtils\_impl[#](#class-hostbkndcudautils-impl "此标题的永久链接")

* Defined in [File utils.h](file_icraft-backends_hostbackend_cuda_utils.h.md#file-icraft-backends-hostbackend-cuda-utils-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HostBackendCudaUtils` ([Class HostBackendCudaUtils](classicraft_1_1xrt_1_1_host_backend_cuda_utils.md#exhale-class-classicraft-1-1xrt-1-1-host-backend-cuda-utils))

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HostBkndCudaUtils\_impl : public [HostBackendCudaUtils](classicraft_1_1xrt_1_1_host_backend_cuda_utils.md#_CPPv4N6icraft3xrt20HostBackendCudaUtilsE "icraft::xrt::HostBackendCudaUtils")[#](#_CPPv4N6icraft3xrt22HostBkndCudaUtils_implE "永久链接至目标")
:   Public Functions

    virtual void freeCuda(char \*ptr) override[#](#_CPPv4N6icraft3xrt22HostBkndCudaUtils_impl8freeCudaEPc "永久链接至目标")

    virtual bool DataOnCUDA(char \*data) override[#](#_CPPv4N6icraft3xrt22HostBkndCudaUtils_impl10DataOnCUDAEPc "永久链接至目标")

    virtual void readCuda(char \*host\_dst, char \*cuda\_src, uint64\_t byte\_size) override[#](#_CPPv4N6icraft3xrt22HostBkndCudaUtils_impl8readCudaEPcPc8uint64_t "永久链接至目标")

    virtual void writeCuda(char \*cuda\_dst, char \*host\_src, uint64\_t byte\_size) override[#](#_CPPv4N6icraft3xrt22HostBkndCudaUtils_impl9writeCudaEPcPc8uint64_t "永久链接至目标")

    virtual char \*mallocCuda(uint64\_t byte\_size) override[#](#_CPPv4N6icraft3xrt22HostBkndCudaUtils_impl10mallocCudaE8uint64_t "永久链接至目标")

    virtual void copyCuda(char \*cuda\_dst, char \*cuda\_src, uint64\_t byte\_size) override[#](#_CPPv4N6icraft3xrt22HostBkndCudaUtils_impl8copyCudaEPcPc8uint64_t "永久链接至目标")
