# Program Listing for File less.h



↰ [Return to documentation for file](file_icraft-xir_ops_less.h.md#file-icraft-xir-ops-less-h) (`icraft-xir\ops\less.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class LessNode : public OpNodeBase<LessNode> {
    public:
        ICRAFT_DECLARE_ATTRS(LessNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Less : public OpBase<Less, LessNode> {
    public:
        Less() = default;

        XIR_DLL Less(Value lhs, Value rhs);
    };
}
</pre>
```
