# Program Listing for File tanhshrink.h



↰ [Return to documentation for file](file_icraft-xir_ops_tanhshrink.h.md#file-icraft-xir-ops-tanhshrink-h) (`icraft-xir\ops\tanhshrink.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class TanhshrinkNode : public OpNodeBase<TanhshrinkNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(TanhshrinkNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Tanhshrink : public OpBase<Tanhshrink, TanhshrinkNode> {
    public:
        Tanhshrink() = default;

        XIR_DLL Tanhshrink(Value input);
    };
}
</pre>
```
