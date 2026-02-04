# Program Listing for File neg.h



↰ [Return to documentation for file](file_icraft-xir_ops_neg.h.md#file-icraft-xir-ops-neg-h) (`icraft-xir\ops\neg.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class NegNode : public OpNodeBase<NegNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(NegNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Neg : public OpBase<Neg, NegNode> {
    public:
        Neg() = default;

        XIR_DLL Neg(Value input);
    };
}
</pre>
```
