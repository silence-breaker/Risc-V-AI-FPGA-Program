# Program Listing for File sinh.h



↰ [Return to documentation for file](file_icraft-xir_ops_sinh.h.md#file-icraft-xir-ops-sinh-h) (`icraft-xir\ops\sinh.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SinhNode : public OpNodeBase<SinhNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(SinhNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Sinh : public OpBase<Sinh, SinhNode> {
    public:
        Sinh() = default;

        XIR_DLL Sinh(Value input);
    };
}
</pre>
```
