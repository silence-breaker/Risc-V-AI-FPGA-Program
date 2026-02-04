# Program Listing for File min.h



↰ [Return to documentation for file](file_icraft-xir_ops_min.h.md#file-icraft-xir-ops-min-h) (`icraft-xir\ops\min.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MinNode : public OpNodeBase<MinNode> {
    public:
        Optional<IntImm> dim;
        bool keepdim;

        ICRAFT_DECLARE_ATTRS(MinNode) {
            ICRAFT_ATTR_FIELD(dim);
            ICRAFT_ATTR_FIELD(keepdim).set_default(false);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Min : public OpBase<Min, MinNode> {
    public:
        Min() = default;

        XIR_DLL Min(Value input, Optional<IntImm> dim = NullOpt, bool keepdim = false);
    };
}
</pre>
```
