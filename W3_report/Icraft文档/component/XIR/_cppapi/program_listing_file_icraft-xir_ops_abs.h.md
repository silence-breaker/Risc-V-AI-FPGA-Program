# Program Listing for File abs.h



↰ [Return to documentation for file](file_icraft-xir_ops_abs.h.md#file-icraft-xir-ops-abs-h) (`icraft-xir\ops\abs.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class AbsNode : public OpNodeBase<AbsNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(AbsNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Abs : public OpBase<Abs, AbsNode> {
    public:
        Abs() = default;

        XIR_DLL Abs(Value input);
    };
}
</pre>
```
