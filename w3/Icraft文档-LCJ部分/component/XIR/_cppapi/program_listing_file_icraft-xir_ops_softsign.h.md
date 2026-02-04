# Program Listing for File softsign.h



↰ [Return to documentation for file](file_icraft-xir_ops_softsign.h.md#file-icraft-xir-ops-softsign-h) (`icraft-xir\ops\softsign.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SoftsignNode : public OpNodeBase<SoftsignNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(SoftsignNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Softsign : public OpBase<Softsign, SoftsignNode> {
    public:
        Softsign() = default;

        XIR_DLL Softsign(Value input);
    };
}
</pre>
```
