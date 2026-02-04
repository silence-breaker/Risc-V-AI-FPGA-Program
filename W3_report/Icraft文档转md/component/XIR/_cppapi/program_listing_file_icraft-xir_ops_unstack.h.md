# Program Listing for File unstack.h



↰ [Return to documentation for file](file_icraft-xir_ops_unstack.h.md#file-icraft-xir-ops-unstack-h) (`icraft-xir\ops\unstack.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class UnstackNode : public OpNodeBase<UnstackNode> {
    public:
        int64_t dim;

        ICRAFT_DECLARE_ATTRS(UnstackNode) {
            ICRAFT_ATTR_FIELD(dim).set_default(0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Unstack : public OpBase<Unstack, UnstackNode> {
    public:
        Unstack() = default;

        XIR_DLL Unstack(Value input, int64_t dim = 0);
    };
}
</pre>
```
