# Program Listing for File less_equal.h



↰ [Return to documentation for file](file_icraft-xir_ops_less_equal.h.md#file-icraft-xir-ops-less-equal-h) (`icraft-xir\ops\less_equal.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class LessEqualNode : public OpNodeBase<LessEqualNode> {
    public:
        ICRAFT_DECLARE_ATTRS(LessEqualNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class LessEqual : public OpBase<LessEqual, LessEqualNode> {
    public:
        LessEqual() = default;

        XIR_DLL LessEqual(Value lhs, Value rhs);
    };
}
</pre>
```
