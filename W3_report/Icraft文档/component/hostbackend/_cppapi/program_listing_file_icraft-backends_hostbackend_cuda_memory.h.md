# Program Listing for File memory.h[#](#program-listing-for-file-memory-h "此标题的永久链接")

↰ [Return to documentation for file](file_icraft-backends_hostbackend_cuda_memory.h.md#file-icraft-backends-hostbackend-cuda-memory-h) (`icraft-backends\hostbackend\cuda\memory.h`)

```
#pragma once
#include <icraft-xrt/core/backend.h>
#include "icraft-backends/hostbackend/cuda/utils.h"

namespace icraft {
    namespace xrt {
        class CudaMemRegionNode : public NodeBase<CudaMemRegionNode, MemRegionNode> {
        private:
            virtual void init() override {};

            virtual void deinit() override {};

            virtual void read(char* dest, const MemPtr& src, uint64_t byte_size) const override {
                ICRAFT_CHECK(!src.isNull())
                    .append("Cuda data read failed, src ptr is null");
                getUtils()->readCuda((char*)dest, (char*)src.cptr(), byte_size);
            }

            virtual void write(const MemPtr& dest, char* src, uint64_t byte_size) const override {
                ICRAFT_CHECK(src != nullptr)
                    .append("Cuda data write failed, src is nullptr.");
                char* dest_cuda_ptr = (char*)dest.cptr();
                ICRAFT_CHECK(getUtils()->DataOnCUDA(dest_cuda_ptr))
                    .append("Cuda data write failed, dest is not a valid cuda memory ptr.");
                getUtils()->writeCuda(dest_cuda_ptr, (char*)src, byte_size);
            }

            virtual MemChunk malloc(uint64_t byte_size, bool auto_free, uint64_t alignment) const override {
                MemPtr begin;
                if (byte_size != 0) { begin = MemPtr(getUtils()->mallocCuda(byte_size)); }
                else { begin = MemPtr(nullptr); }
                return  CreateMemChunk(std::move(begin), byte_size, GetRef<MemRegion>(this), nullptr, auto_free);
            }

            virtual MemChunk malloc(MemPtr begin, uint64_t byte_size, xrt::FChunkDeleter deleter, bool auto_free) const override {
                ICRAFT_CHECK(begin.ptype() == PtrType::CPTR).append("Only PtrType::CPTR is supported!");
                ICRAFT_CHECK(getUtils()->DataOnCUDA(begin.cptr()))
                    .append("Cuda MemChunk malloc failed, dest is not a valid cuda memory ptr.");
                return  CreateMemChunk(std::move(begin), byte_size, GetRef<MemRegion>(this), deleter, auto_free);
            }

            virtual void free(const MemPtr& src) const override {
                auto cuda_data_ptr = (char*)src.cptr();
                if (getUtils()->DataOnCUDA(cuda_data_ptr)) {
                    getUtils()->freeCuda(cuda_data_ptr);
                }
            }

            virtual void memcpy(const MemPtr& dest, const MemPtr& src, uint64_t byte_size) const override {
                char* dest_cuda_ptr = (char*)dest.cptr();
                ICRAFT_CHECK(getUtils()->DataOnCUDA(dest_cuda_ptr))
                    .append("Cuda data memcpy failed, dest ptr is not a valid cuda memory ptr.");
                char* src_cuda_ptr = (char*)src.cptr();
                ICRAFT_CHECK(getUtils()->DataOnCUDA(src_cuda_ptr))
                    .append("Cuda data memcpy failed, src ptr is not a valid cuda memory ptr.");
                getUtils()->copyCuda(dest_cuda_ptr, src_cuda_ptr, byte_size);
            }
        private:
            static std::shared_ptr<HostBackendCudaUtils> Utils;
            static std::shared_ptr<HostBackendCudaUtils> getUtils();
        };

        class CudaMemRegion : public HandleBase<CudaMemRegion, MemRegion, CudaMemRegionNode> {};
    }
}
```
