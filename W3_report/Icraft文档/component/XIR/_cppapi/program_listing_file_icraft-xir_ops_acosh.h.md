# Program Listing for File acosh.h



↰ [Return to documentation for file](file_icraft-xir_ops_acosh.h.md#file-icraft-xir-ops-acosh-h) (`icraft-xir\ops\acosh.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ACoshNode : public OpNodeBase<ACoshNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(ACoshNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class ACosh : public OpBase<ACosh, ACoshNode> {
    public:
        ACosh() = default;

        XIR_DLL ACosh(Value input);
    };
}
</pre>
```
