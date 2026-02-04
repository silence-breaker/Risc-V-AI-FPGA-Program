# Program Listing for File stack.h



↰ [Return to documentation for file](file_icraft-xir_ops_stack.h.md#file-icraft-xir-ops-stack-h) (`icraft-xir\ops\stack.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class StackNode : public OpNodeBase<StackNode> {
    public:
        int64_t dim;

        ICRAFT_DECLARE_ATTRS(StackNode) {
            ICRAFT_ATTR_FIELD(dim).set_default(0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Stack : public OpBase<Stack, StackNode> {
    public:
        Stack() = default;

        XIR_DLL Stack(Array<Value> inputs, int64_t dim = 0);
    };
}
</pre>
```
