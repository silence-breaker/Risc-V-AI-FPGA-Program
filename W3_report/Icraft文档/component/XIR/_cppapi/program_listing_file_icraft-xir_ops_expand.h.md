# Program Listing for File expand.h



↰ [Return to documentation for file](file_icraft-xir_ops_expand.h.md#file-icraft-xir-ops-expand-h) (`icraft-xir\ops\expand.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ExpandNode : public OpNodeBase<ExpandNode> {
    public:
        Array<int64_t> sizes;

        ICRAFT_DECLARE_ATTRS(ExpandNode) {
            ICRAFT_ATTR_FIELD(sizes);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Expand : public OpBase<Expand, ExpandNode> {
    public:
        Expand() = default;

        XIR_DLL Expand(Value input, Array<int64_t> sizes);
    };
}
</pre>
```
