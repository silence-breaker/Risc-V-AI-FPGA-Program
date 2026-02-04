# Program Listing for File sin.h



↰ [Return to documentation for file](file_icraft-xir_ops_sin.h.md#file-icraft-xir-ops-sin-h) (`icraft-xir\ops\sin.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SinNode : public OpNodeBase<SinNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(SinNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Sin : public OpBase<Sin, SinNode> {
    public:
        Sin() = default;

        XIR_DLL Sin(Value input);
    };
}
</pre>
```
