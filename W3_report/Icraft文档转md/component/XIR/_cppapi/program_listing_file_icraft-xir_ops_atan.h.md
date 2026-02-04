# Program Listing for File atan.h



↰ [Return to documentation for file](file_icraft-xir_ops_atan.h.md#file-icraft-xir-ops-atan-h) (`icraft-xir\ops\atan.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ATanNode : public OpNodeBase<ATanNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(ATanNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class ATan : public OpBase<ATan, ATanNode> {
    public:
        ATan() = default;

        XIR_DLL ATan(Value input);
    };
}
</pre>
```
