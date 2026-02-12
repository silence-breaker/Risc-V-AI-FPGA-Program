# Program Listing for File not_equal.h



↰ [Return to documentation for file](file_icraft-xir_ops_not_equal.h.md#file-icraft-xir-ops-not-equal-h) (`icraft-xir\ops\not_equal.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class NotEqualNode : public OpNodeBase<NotEqualNode> {
    public:
        ICRAFT_DECLARE_ATTRS(NotEqualNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class NotEqual : public OpBase<NotEqual, NotEqualNode> {
    public:
        NotEqual() = default;

        XIR_DLL NotEqual(Value lhs, Value rhs);
    };
}
</pre>
```
