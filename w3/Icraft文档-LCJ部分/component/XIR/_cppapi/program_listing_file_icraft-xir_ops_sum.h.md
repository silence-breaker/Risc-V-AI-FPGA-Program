# Program Listing for File sum.h



↰ [Return to documentation for file](file_icraft-xir_ops_sum.h.md#file-icraft-xir-ops-sum-h) (`icraft-xir\ops\sum.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SumNode : public OpNodeBase<SumNode> {
    public:
        Array<int64_t> dim;
        bool keepdim;

        ICRAFT_DECLARE_ATTRS(SumNode) {
            ICRAFT_ATTR_FIELD(dim);
            ICRAFT_ATTR_FIELD(keepdim).set_default(false);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Sum : public OpBase<Sum, SumNode> {
    public:
        Sum() = default;

        XIR_DLL Sum(Value input);

        XIR_DLL Sum(Value input, int64_t dim, bool keepdim = false);

        XIR_DLL Sum(Value input, Array<int64_t> dim, bool keepdim = false);
    };
}
</pre>
```
