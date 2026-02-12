# Program Listing for File sigmoid.h



↰ [Return to documentation for file](file_icraft-xir_ops_sigmoid.h.md#file-icraft-xir-ops-sigmoid-h) (`icraft-xir\ops\sigmoid.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SigmoidNode : public OpNodeBase<SigmoidNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(SigmoidNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Sigmoid : public OpBase<Sigmoid, SigmoidNode> {
    public:
        Sigmoid() = default;

        XIR_DLL Sigmoid(Value input);
    };
}
</pre>
```
