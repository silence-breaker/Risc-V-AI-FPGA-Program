# Program Listing for File greater.h



↰ [Return to documentation for file](file_icraft-xir_ops_greater.h.md#file-icraft-xir-ops-greater-h) (`icraft-xir\ops\greater.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class GreaterNode : public OpNodeBase<GreaterNode> {
    public:
        ICRAFT_DECLARE_ATTRS(GreaterNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Greater : public OpBase<Greater, GreaterNode> {
    public:
        Greater() = default;

        XIR_DLL Greater(Value lhs, Value rhs);
    };
}
</pre>
```
