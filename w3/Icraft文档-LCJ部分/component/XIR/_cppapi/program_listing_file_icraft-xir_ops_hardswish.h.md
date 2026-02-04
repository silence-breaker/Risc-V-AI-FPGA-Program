# Program Listing for File hardswish.h



↰ [Return to documentation for file](file_icraft-xir_ops_hardswish.h.md#file-icraft-xir-ops-hardswish-h) (`icraft-xir\ops\hardswish.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class HardswishNode : public OpNodeBase<HardswishNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(HardswishNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Hardswish : public OpBase<Hardswish, HardswishNode> {
    public:
        Hardswish() = default;

        XIR_DLL Hardswish(Value input);
    };
}
</pre>
```
