# Program Listing for File utils.h[#](#program-listing-for-file-utils-h "此标题的永久链接")

↰ [Return to documentation for file](file_icraft-backends_hostbackend_cuda_utils.h.md#file-icraft-backends-hostbackend-cuda-utils-h) (`icraft-backends\hostbackend\cuda\utils.h`)

```
#pragma once
#include <cstdint>

#ifdef _WIN32
#define REGISTER_CUDAUTILS(CLASS_NAME) \
    extern "C" __declspec(dllexport) icraft::xrt::HostBackendCudaUtils* newCudaUtils() { return new CLASS_NAME(); }\
    extern "C" __declspec(dllexport) void deleteCudaUtils (icraft::xrt::HostBackendCudaUtils* cudautils) noexcept { delete cudautils; }
#else
#define REGISTER_CUDAUTILS(CLASS_NAME) \
    extern "C" icraft::xrt::HostBackendCudaUtils* newCudaUtils() { return new CLASS_NAME(); }\
    extern "C" void deleteCudaUtils (icraft::xrt::HostBackendCudaUtils* cudautils) noexcept { delete cudautils; }

#endif

namespace icraft::xrt {
    class HostBackendCudaUtils {
    public:
        virtual void freeCuda(char* ptr) = 0;
        virtual bool DataOnCUDA(char* data) = 0;
        virtual void readCuda(char* host_dst, char* cuda_src, uint64_t byte_size) = 0;
        virtual void writeCuda(char* cuda_dst, char* host_src, uint64_t byte_size) = 0;
        virtual char* mallocCuda(uint64_t byte_size) = 0;
        virtual void copyCuda(char* cuda_dst, char* cuda_src, uint64_t byte_size) = 0;
    };

    class HostBkndCudaUtils_impl : public HostBackendCudaUtils {
    public:
        void freeCuda(char* ptr) override;
        bool DataOnCUDA(char* data) override;
        void readCuda(char* host_dst, char* cuda_src, uint64_t byte_size) override;
        void writeCuda(char* cuda_dst, char* host_src, uint64_t byte_size) override;
        char* mallocCuda(uint64_t byte_size) override;
        void copyCuda(char* cuda_dst, char* cuda_src, uint64_t byte_size) override;
    };
}
```
