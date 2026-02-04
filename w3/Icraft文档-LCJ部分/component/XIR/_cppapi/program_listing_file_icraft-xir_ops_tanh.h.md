# Program Listing for File tanh.h



↰ [Return to documentation for file](file_icraft-xir_ops_tanh.h.md#file-icraft-xir-ops-tanh-h) (`icraft-xir\ops\tanh.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class TanhNode : public OpNodeBase<TanhNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(TanhNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Tanh : public OpBase<Tanh, TanhNode> {
    public:
        Tanh() = default;

        XIR_DLL Tanh(Value input);
    };
}
</pre>
```
