# Program Listing for File matmul.h



↰ [Return to documentation for file](file_icraft-xir_ops_matmul.h.md#file-icraft-xir-ops-matmul-h) (`icraft-xir\ops\matmul.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MatmulNode : public OpNodeBase<MatmulNode> {
    public:
        QuantizedScaleArray cut_scale;

        ICRAFT_DECLARE_ATTRS(MatmulNode) {
            ICRAFT_ATTR_FIELD(cut_scale);
        };

        XIR_DLL virtual void validate() const override;
    };

    class Matmul : public OpBase<Matmul, MatmulNode> {
    public:
        Matmul() = default;

        XIR_DLL Matmul(Value x, Value k, Optional<Value> b);
    };
}
</pre>
```
