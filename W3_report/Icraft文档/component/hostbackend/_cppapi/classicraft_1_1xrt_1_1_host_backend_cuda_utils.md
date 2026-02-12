# Class HostBackendCudaUtils[#](#class-hostbackendcudautils "此标题的永久链接")

* Defined in [File utils.h](file_icraft-backends_hostbackend_cuda_utils.h.md#file-icraft-backends-hostbackend-cuda-utils-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Derived Type[#](#derived-type "此标题的永久链接")

* `public HostBkndCudaUtils_impl` ([Class HostBkndCudaUtils\_impl](classicraft_1_1xrt_1_1_host_bknd_cuda_utils__impl.md#exhale-class-classicraft-1-1xrt-1-1-host-bknd-cuda-utils-impl))

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HostBackendCudaUtils[#](#_CPPv4N6icraft3xrt20HostBackendCudaUtilsE "永久链接至目标")
:   Subclassed by [HostBkndCudaUtils\_impl](classicraft_1_1xrt_1_1_host_bknd_cuda_utils__impl.md#classicraft_1_1xrt_1_1_host_bknd_cuda_utils__impl)

    Public Functions

    virtual void freeCuda(char \*ptr) = 0[#](#_CPPv4N6icraft3xrt20HostBackendCudaUtils8freeCudaEPc "永久链接至目标")

    virtual bool DataOnCUDA(char \*data) = 0[#](#_CPPv4N6icraft3xrt20HostBackendCudaUtils10DataOnCUDAEPc "永久链接至目标")

    virtual void readCuda(char \*host\_dst, char \*cuda\_src, uint64\_t byte\_size) = 0[#](#_CPPv4N6icraft3xrt20HostBackendCudaUtils8readCudaEPcPc8uint64_t "永久链接至目标")

    virtual void writeCuda(char \*cuda\_dst, char \*host\_src, uint64\_t byte\_size) = 0[#](#_CPPv4N6icraft3xrt20HostBackendCudaUtils9writeCudaEPcPc8uint64_t "永久链接至目标")

    virtual char \*mallocCuda(uint64\_t byte\_size) = 0[#](#_CPPv4N6icraft3xrt20HostBackendCudaUtils10mallocCudaE8uint64_t "永久链接至目标")

    virtual void copyCuda(char \*cuda\_dst, char \*cuda\_src, uint64\_t byte\_size) = 0[#](#_CPPv4N6icraft3xrt20HostBackendCudaUtils8copyCudaEPcPc8uint64_t "永久链接至目标")
