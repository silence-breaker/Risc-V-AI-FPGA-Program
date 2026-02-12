# Program Listing for File where.h



↰ [Return to documentation for file](file_icraft-xir_ops_where.h.md#file-icraft-xir-ops-where-h) (`icraft-xir\ops\where.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class WhereNode : public OpNodeBase<WhereNode> {
    public:
        ICRAFT_DECLARE_ATTRS(WhereNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Where : public OpBase<Where, WhereNode> {
    public:
        Where() = default;

        XIR_DLL Where(Value lhs, Value rhs, Value condition);
    };
}
</pre>
```
