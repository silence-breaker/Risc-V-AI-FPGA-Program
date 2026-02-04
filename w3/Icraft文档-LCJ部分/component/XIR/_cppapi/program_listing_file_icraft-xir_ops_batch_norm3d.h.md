# Program Listing for File batch_norm3d.h



↰ [Return to documentation for file](file_icraft-xir_ops_batch_norm3d.h.md#file-icraft-xir-ops-batch-norm3d-h) (`icraft-xir\ops\batch_norm3d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class BatchNorm3dNode : public OpNodeBase<BatchNorm3dNode>{
    public:
        Params variance;
        Params mean;

        ICRAFT_DECLARE_ATTRS(BatchNorm3dNode) {
            ICRAFT_ATTR_FIELD(variance);
            ICRAFT_ATTR_FIELD(mean);
        }

        XIR_DLL virtual void validate() const override;
    };

    class BatchNorm3d : public OpBase<BatchNorm3d, BatchNorm3dNode> {
    public:
        BatchNorm3d() = default;

        XIR_DLL BatchNorm3d(Value input, Params variance, Params mean);
    };
}
</pre>
```
