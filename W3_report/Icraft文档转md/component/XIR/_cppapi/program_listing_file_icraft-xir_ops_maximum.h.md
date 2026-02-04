# Program Listing for File maximum.h



↰ [Return to documentation for file](file_icraft-xir_ops_maximum.h.md#file-icraft-xir-ops-maximum-h) (`icraft-xir\ops\maximum.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MaximumNode : public OpNodeBase<MaximumNode> {
    public:
        ICRAFT_DECLARE_ATTRS(MaximumNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Maximum : public OpBase<Maximum, MaximumNode> {
    public:
        Maximum() = default;

        XIR_DLL Maximum(Value lhs, Value rhs);
    };
}
</pre>
```
