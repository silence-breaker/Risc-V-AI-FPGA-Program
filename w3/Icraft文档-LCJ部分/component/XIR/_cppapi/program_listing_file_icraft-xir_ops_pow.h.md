# Program Listing for File pow.h



↰ [Return to documentation for file](file_icraft-xir_ops_pow.h.md#file-icraft-xir-ops-pow-h) (`icraft-xir\ops\pow.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class PowNode : public OpNodeBase<PowNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(PowNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Pow : public OpBase<Pow, PowNode> {
    public:
        Pow() = default;

        XIR_DLL Pow(Value input, double exponent = 1.0f);

        XIR_DLL Pow(Value input, Params exponent);
    };
}
</pre>
```
