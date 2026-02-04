# Program Listing for File mean.h



↰ [Return to documentation for file](file_icraft-xir_ops_mean.h.md#file-icraft-xir-ops-mean-h) (`icraft-xir\ops\mean.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MeanNode : public OpNodeBase<MeanNode> {
    public:
        Array<int64_t> dim;
        bool keepdim;

        ICRAFT_DECLARE_ATTRS(MeanNode) {
            ICRAFT_ATTR_FIELD(dim);
            ICRAFT_ATTR_FIELD(keepdim).set_default(false);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Mean : public OpBase<Mean, MeanNode> {
    public:
        Mean() = default;

        XIR_DLL Mean(Value input);

        XIR_DLL Mean(Value input, int64_t dim, bool keepdim = false);

        XIR_DLL Mean(Value input, Array<int64_t> dim, bool keepdim = false);
    };
}
</pre>
```
