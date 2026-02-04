# Program Listing for File cosh.h



↰ [Return to documentation for file](file_icraft-xir_ops_cosh.h.md#file-icraft-xir-ops-cosh-h) (`icraft-xir\ops\cosh.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class CoshNode : public OpNodeBase<CoshNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(CoshNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Cosh : public OpBase<Cosh, CoshNode> {
    public:
        Cosh() = default;

        XIR_DLL Cosh(Value input);
    };
}
</pre>
```
