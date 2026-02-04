# Program Listing for File hardshrink.h



↰ [Return to documentation for file](file_icraft-xir_ops_hardshrink.h.md#file-icraft-xir-ops-hardshrink-h) (`icraft-xir\ops\hardshrink.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class HardshrinkNode : public OpNodeBase<HardshrinkNode, IsActivate> {
    public:
        float lambda;

        ICRAFT_DECLARE_ATTRS(HardshrinkNode) {
            ICRAFT_ATTR_FIELD(lambda).set_default(0.5).set_lower_bound(0.0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Hardshrink : public OpBase<Hardshrink, HardshrinkNode> {
    public:
        Hardshrink() = default;

        XIR_DLL Hardshrink(Value input, float lambda = 0.5);
    };
}
</pre>
```
