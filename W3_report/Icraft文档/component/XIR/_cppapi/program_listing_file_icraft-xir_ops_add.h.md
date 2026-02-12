# Program Listing for File add.h



↰ [Return to documentation for file](file_icraft-xir_ops_add.h.md#file-icraft-xir-ops-add-h) (`icraft-xir\ops\add.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class AddNode : public OpNodeBase<AddNode> {
    public:
        Array<ScalarImm> alpha = Array<ScalarImm>{ 1.f };
        Array<ScalarImm> beta = Array<ScalarImm>{ 1.f };

        QuantizedScaleArray cut_scale;

        ICRAFT_DECLARE_ATTRS(AddNode) {
            ICRAFT_ATTR_FIELD(alpha);
            ICRAFT_ATTR_FIELD(beta);
            ICRAFT_ATTR_FIELD(cut_scale);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Add : public OpBase<Add, AddNode> {
    public:
        Add() = default;

        XIR_DLL Add(Value lhs, Value rhs, ScalarImm alpha, ScalarImm beta);

        XIR_DLL Add(Value lhs, Value rhs, Array<ScalarImm> alpha = { 1.f }, Array <ScalarImm> beta = { 1.f });
    };
}
</pre>
```
