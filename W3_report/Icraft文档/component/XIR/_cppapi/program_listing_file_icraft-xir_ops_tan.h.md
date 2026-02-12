# Program Listing for File tan.h



↰ [Return to documentation for file](file_icraft-xir_ops_tan.h.md#file-icraft-xir-ops-tan-h) (`icraft-xir\ops\tan.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class TanNode : public OpNodeBase<TanNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(TanNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Tan : public OpBase<Tan, TanNode> {
    public:
        Tan() = default;

        XIR_DLL Tan(Value input);
    };
}
</pre>
```
