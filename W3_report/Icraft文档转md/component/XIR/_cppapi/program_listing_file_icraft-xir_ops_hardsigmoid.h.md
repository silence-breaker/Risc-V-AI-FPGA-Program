# Program Listing for File hardsigmoid.h



↰ [Return to documentation for file](file_icraft-xir_ops_hardsigmoid.h.md#file-icraft-xir-ops-hardsigmoid-h) (`icraft-xir\ops\hardsigmoid.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class HardsigmoidNode : public OpNodeBase<HardsigmoidNode, IsActivate> {
    public:
        float alpha;
        float beta;

        ICRAFT_DECLARE_ATTRS(HardsigmoidNode) {
            ICRAFT_ATTR_FIELD(alpha).set_default(1.f / 6.f);
            ICRAFT_ATTR_FIELD(beta).set_default(0.5f);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Hardsigmoid : public OpBase<Hardsigmoid, HardsigmoidNode> {
    public:
        Hardsigmoid() = default;

        XIR_DLL Hardsigmoid(Value input, float alpha = 1.f / 6.f, float beta = 0.5f);
    };
}
</pre>
```
