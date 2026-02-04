# Program Listing for File softmax.h



↰ [Return to documentation for file](file_icraft-xir_ops_softmax.h.md#file-icraft-xir-ops-softmax-h) (`icraft-xir\ops\softmax.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SoftmaxNode : public OpNodeBase<SoftmaxNode> {
    public:
        int64_t axis;

        ICRAFT_DECLARE_ATTRS(SoftmaxNode) {
            ICRAFT_ATTR_FIELD(axis).set_default(-1).set_lower_bound(-1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Softmax : public OpBase<Softmax, SoftmaxNode> {
    public:
        Softmax() = default;

        XIR_DLL Softmax(Value input, int64_t axis = -1);
    };
}
</pre>
```
