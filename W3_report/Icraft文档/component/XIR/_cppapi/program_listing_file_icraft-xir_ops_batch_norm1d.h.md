# Program Listing for File batch_norm1d.h



↰ [Return to documentation for file](file_icraft-xir_ops_batch_norm1d.h.md#file-icraft-xir-ops-batch-norm1d-h) (`icraft-xir\ops\batch_norm1d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class BatchNorm1dNode : public OpNodeBase<BatchNorm1dNode>{
    public:
        Params variance;
        Params mean;

        ICRAFT_DECLARE_ATTRS(BatchNorm1dNode) {
            ICRAFT_ATTR_FIELD(variance);
            ICRAFT_ATTR_FIELD(mean);
        }

        XIR_DLL virtual void validate() const override;
    };

    class BatchNorm1d : public OpBase<BatchNorm1d, BatchNorm1dNode> {
    public:
        BatchNorm1d() = default;

        XIR_DLL BatchNorm1d(Value input, Params variance, Params mean);
    };
}
</pre>
```
