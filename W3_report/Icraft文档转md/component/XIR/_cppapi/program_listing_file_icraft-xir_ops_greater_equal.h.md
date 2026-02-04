# Program Listing for File greater_equal.h



↰ [Return to documentation for file](file_icraft-xir_ops_greater_equal.h.md#file-icraft-xir-ops-greater-equal-h) (`icraft-xir\ops\greater_equal.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class GreaterEqualNode : public OpNodeBase<GreaterEqualNode> {
    public:
        ICRAFT_DECLARE_ATTRS(GreaterEqualNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class GreaterEqual : public OpBase<GreaterEqual, GreaterEqualNode> {
    public:
        GreaterEqual() = default;

        XIR_DLL GreaterEqual(Value lhs, Value rhs);
    };
}
</pre>
```
