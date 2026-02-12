# Program Listing for File concat.h



↰ [Return to documentation for file](file_icraft-xir_ops_concat.h.md#file-icraft-xir-ops-concat-h) (`icraft-xir\ops\concat.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ConcatNode : public OpNodeBase<ConcatNode> {
    public:
        int64_t axis;

        ICRAFT_DECLARE_ATTRS(ConcatNode) {
            ICRAFT_ATTR_FIELD(axis).set_default(-1).set_lower_bound(-1);
        };

        XIR_DLL virtual void validate() const override;
    };

    class Concat : public OpBase<Concat, ConcatNode> {
    public:
        Concat() = default;

        XIR_DLL Concat(Array<Value> inputs, int64_t axis = -1);
    };
}
</pre>
```
