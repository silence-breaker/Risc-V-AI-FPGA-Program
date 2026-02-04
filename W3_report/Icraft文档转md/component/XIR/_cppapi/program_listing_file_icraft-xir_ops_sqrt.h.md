# Program Listing for File sqrt.h



↰ [Return to documentation for file](file_icraft-xir_ops_sqrt.h.md#file-icraft-xir-ops-sqrt-h) (`icraft-xir\ops\sqrt.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SqrtNode : public OpNodeBase<SqrtNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(SqrtNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Sqrt : public OpBase<Sqrt, SqrtNode> {
    public:
        Sqrt() = default;

        XIR_DLL Sqrt(Value input);
    };
}
</pre>
```
