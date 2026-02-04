# Program Listing for File not.h



↰ [Return to documentation for file](file_icraft-xir_ops_not.h.md#file-icraft-xir-ops-not-h) (`icraft-xir\ops\not.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class NotNode : public OpNodeBase<NotNode> {
    public:
        ICRAFT_DECLARE_ATTRS(NotNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Not : public OpBase<Not, NotNode> {
    public:
        Not() = default;

        XIR_DLL Not(Value input);
    };
}
</pre>
```
