# Program Listing for File minimum.h



↰ [Return to documentation for file](file_icraft-xir_ops_minimum.h.md#file-icraft-xir-ops-minimum-h) (`icraft-xir\ops\minimum.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MinimumNode : public OpNodeBase<MinimumNode> {
    public:
        ICRAFT_DECLARE_ATTRS(MinimumNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Minimum : public OpBase<Minimum, MinimumNode> {
    public:
        Minimum() = default;

        XIR_DLL Minimum(Value lhs, Value rhs);
    };
}
</pre>
```
