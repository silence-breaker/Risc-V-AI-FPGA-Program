# Program Listing for File equal.h



↰ [Return to documentation for file](file_icraft-xir_ops_equal.h.md#file-icraft-xir-ops-equal-h) (`icraft-xir\ops\equal.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class EqualNode : public OpNodeBase<EqualNode> {
    public:
        ICRAFT_DECLARE_ATTRS(EqualNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Equal : public OpBase<Equal, EqualNode> {
    public:
        Equal() = default;

        XIR_DLL Equal(Value lhs, Value rhs);
    };
}
</pre>
```
