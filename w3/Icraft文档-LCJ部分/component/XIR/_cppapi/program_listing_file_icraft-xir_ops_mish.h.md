# Program Listing for File mish.h



↰ [Return to documentation for file](file_icraft-xir_ops_mish.h.md#file-icraft-xir-ops-mish-h) (`icraft-xir\ops\mish.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MishNode : public OpNodeBase<MishNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(MishNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Mish : public OpBase<Mish, MishNode> {
    public:
        Mish() = default;

        XIR_DLL Mish(Value input);
    };
}
</pre>
```
