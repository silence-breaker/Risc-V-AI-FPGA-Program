# Program Listing for File atanh.h



↰ [Return to documentation for file](file_icraft-xir_ops_atanh.h.md#file-icraft-xir-ops-atanh-h) (`icraft-xir\ops\atanh.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ATanhNode : public OpNodeBase<ATanhNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(ATanhNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class ATanh : public OpBase<ATanh, ATanhNode> {
    public:
        ATanh() = default;

        XIR_DLL ATanh(Value input);
    };
}
</pre>
```
