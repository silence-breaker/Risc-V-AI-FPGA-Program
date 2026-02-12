# Program Listing for File softplus.h



↰ [Return to documentation for file](file_icraft-xir_ops_softplus.h.md#file-icraft-xir-ops-softplus-h) (`icraft-xir\ops\softplus.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SoftplusNode : public OpNodeBase<SoftplusNode, IsActivate> {
    public:
        float beta;
        float threshold;

        ICRAFT_DECLARE_ATTRS(SoftplusNode) {
            ICRAFT_ATTR_FIELD(beta).set_default(1.0);
            ICRAFT_ATTR_FIELD(threshold).set_default(20.0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Softplus : public OpBase<Softplus, SoftplusNode> {
    public:
        Softplus() = default;

        XIR_DLL Softplus(Value input, float beta = 1.0, float threshold = 20.0);
    };
}
</pre>
```
