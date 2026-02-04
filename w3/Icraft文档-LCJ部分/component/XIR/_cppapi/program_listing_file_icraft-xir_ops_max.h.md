# Program Listing for File max.h



↰ [Return to documentation for file](file_icraft-xir_ops_max.h.md#file-icraft-xir-ops-max-h) (`icraft-xir\ops\max.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MaxNode : public OpNodeBase<MaxNode> {
    public:
        Optional<IntImm> dim;
        bool keepdim;

        ICRAFT_DECLARE_ATTRS(MaxNode) {
            ICRAFT_ATTR_FIELD(dim);
            ICRAFT_ATTR_FIELD(keepdim).set_default(false);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Max : public OpBase<Max, MaxNode> {
    public:
        Max() = default;

        XIR_DLL Max(Value input, Optional<IntImm> dim = NullOpt, bool keepdim = false);
    };
}
</pre>
```
