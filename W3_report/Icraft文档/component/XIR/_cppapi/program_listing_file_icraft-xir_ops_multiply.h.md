# Program Listing for File multiply.h



↰ [Return to documentation for file](file_icraft-xir_ops_multiply.h.md#file-icraft-xir-ops-multiply-h) (`icraft-xir\ops\multiply.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MultiplyNode : public OpNodeBase<MultiplyNode> {
    public:
        QuantizedScaleArray cut_scale;

        ICRAFT_DECLARE_ATTRS(MultiplyNode) {
            ICRAFT_ATTR_FIELD(cut_scale);
        };

        XIR_DLL virtual void validate() const override;
    };

    class Multiply : public OpBase<Multiply, MultiplyNode> {
    public:
        Multiply() = default;

        XIR_DLL Multiply(Value lhs, Value rhs);
    };
}
</pre>
```
