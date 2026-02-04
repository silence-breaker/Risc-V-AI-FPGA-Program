# Program Listing for File tensor.h

```cpp
#pragma once
#ifndef XRT_TENSOR_PCH_GUARD
#define XRT_TENSOR_PCH_GUARD
#include "icraft-xir/core/data_type.h"
#include "icraft-xrt/base/dllexport.h"
#include <icraft-xrt/core/device.h>
#include <icraft-xir/core/data.h>


namespace icraft::xrt {
    using icraft::xir::TensorType;

    class TensorNode : public NodeBase<TensorNode, Node> {
    private:
        TensorType dtype_;
        MemChunk chunk_;
        uint64_t offset_;
        bool ready_ = true;
        std::function<bool(const Device& device)> check_func_;

    friend class Tensor;

    public:
        virtual void accept(AttrVisitor& visitor) override {
            visitor.visit("dtype", dtype_);
            visitor.visit("chunk", chunk_);
        };

        bool reduceAccept(TensorNode* other, const ReduceVisitor& reduce) const {
            return reduce(dtype_, other->dtype_)
                && reduce(chunk_, other->chunk_);
        }
    };

    class Tensor : public HandleBase<Tensor, Handle, TensorNode> {
    public:
        using CheckFunc = std::function<bool(const Device& device)>;

        Tensor() = default;

        XRT_DLL Tensor(TensorType dtype, MemChunk chunk, uint64_t offset = 0, CheckFunc check_func = nullptr);

        XRT_DLL Tensor(TensorType dtype, CheckFunc func = nullptr);

        XRT_DLL Tensor(const icraft::xir::Value &value);

        XRT_DLL Tensor(const icraft::xir::Params& params);

        XRT_DLL Tensor& setDType(TensorType dtype);

        XRT_DLL Tensor& setData(MemChunk chunk, uint64_t offset = 0);

        XRT_DLL Tensor& setCheckFunc(CheckFunc check_func);

        XRT_DLL Tensor& setReady(bool ready);

        XRT_DLL Tensor& mallocOn(const MemRegion& mregion);

        XRT_DLL void copyFrom(
            uint64_t dest_offset,
            const Tensor& src_tensor,
            uint64_t src_offset,
            uint64_t byte_size
        );

        XRT_DLL MemPtr data() const;

        XRT_DLL const MemChunk& chunk() const;

        XRT_DLL uint64_t offset() const;

        XRT_DLL const TensorType& dtype() const;

        XRT_DLL bool isReady() const;

        XRT_DLL bool hasData() const;

        XRT_DLL void read(char* dest, uint64_t src_offset, uint64_t byte_size) const;

        XRT_DLL void write(uint64_t dest_offset, char* src, uint64_t byte_size) const;

        XRT_DLL Tensor to(const MemRegion& mregion) const;

        XRT_DLL bool isOn(const MemRegion& mregion) const;

        XRT_DLL const MemRegion& memRegion() const;

        XRT_DLL void dump(std::ostream& os, const std::string& format = "") const;

        template<typename Rep, typename Period>
        bool waitForReady(
            std::chrono::duration<Rep, Period> timeout,
            std::chrono::duration<Rep, Period> sleep = std::chrono::duration<Rep, Period>::zero()
        ) const {
            ICRAFT_CHECK(this->hasData(), 11012).append("The tensor has no chunk allocated!");
            auto mptr = get_mutable();
            if (mptr->ready_) return true;
            auto device = mptr->chunk_->region.device();
            auto milli_timeout = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
            if (milli_timeout.count() < device->wait_time)
            {
                milli_timeout = std::chrono::milliseconds(device->wait_time);
            }
            auto start = std::chrono::system_clock::now();
            while (!mptr->check_func_(device)) {
                if (std::chrono::system_clock::now() - start > milli_timeout) { return false; }
                if (sleep != std::chrono::seconds::zero()) {
                    //std::this_thread::sleep_for(sleep);
                }
            }
            mptr->ready_ = true;
            return true;
        }

        template <typename T, typename = typename std::enable_if_t<std::is_pod_v<T>>>
        Tensor& fill(std::function<T(uint64_t)> f) {
            ICRAFT_CHECK(this->hasData(), 11012).append("The tensor has no chunk allocated!");
            auto dtype = this->dtype();
            auto etype = dtype->element_dtype;
            auto tbits = sizeof(T) * 8;
            auto sbits = etype.bits();
            ICRAFT_CHECK(tbits == sbits, 11010)
                .append("sizeof(T) not match element_dtype, {} vs. {}", tbits, sbits);
            auto num_elements = dtype.numElements();
            auto filled_data = std::make_unique<T[]>(num_elements);
            for (uint64_t i = 0; i < num_elements; i++) {
                filled_data[i] = f(i);
            }
            (*this)->chunk_.write(0, (char*)filled_data.get(), dtype.bytes());
            return *this;
        }
    };
}
#endif //XRT_TENSOR_PCH_GUARD
```

[Return to documentation for file](file_icraft-xrt_core_tensor.h.md#file-icraft-xrt-core-tensor-h)
