# Program Listing for File softshrink.h



↰ [Return to documentation for file](file_icraft-xir_ops_softshrink.h.md#file-icraft-xir-ops-softshrink-h) (`icraft-xir\ops\softshrink.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SoftshrinkNode : public OpNodeBase<SoftshrinkNode, IsActivate> {
    public:
        float lambda;

        ICRAFT_DECLARE_ATTRS(SoftshrinkNode) {
            ICRAFT_ATTR_FIELD(lambda).set_default(0.5).set_lower_bound(0.0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Softshrink : public OpBase<Softshrink, SoftshrinkNode> {
    public:
        Softshrink() = default;

        XIR_DLL Softshrink(Value input, float lambda = 0.5);
    };
}
</pre>
```
