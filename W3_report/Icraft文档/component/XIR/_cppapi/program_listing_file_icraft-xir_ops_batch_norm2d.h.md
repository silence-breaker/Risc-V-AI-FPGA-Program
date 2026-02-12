# Program Listing for File batch_norm2d.h



↰ [Return to documentation for file](file_icraft-xir_ops_batch_norm2d.h.md#file-icraft-xir-ops-batch-norm2d-h) (`icraft-xir\ops\batch_norm2d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class BatchNorm2dNode : public OpNodeBase<BatchNorm2dNode>{
    public:
        Params variance;
        Params mean;

        ICRAFT_DECLARE_ATTRS(BatchNorm2dNode) {
            ICRAFT_ATTR_FIELD(variance);
            ICRAFT_ATTR_FIELD(mean);
        }

        XIR_DLL virtual void validate() const override;
    };

    class BatchNorm2d : public OpBase<BatchNorm2d, BatchNorm2dNode> {
    public:
        BatchNorm2d() = default;

        XIR_DLL BatchNorm2d(Value input, Params variance, Params mean);
    };

    // 兼容旧接口
    using Batchnorm = BatchNorm2d;
    using BatchnormNode = BatchNorm2dNode;
}
</pre>
```
