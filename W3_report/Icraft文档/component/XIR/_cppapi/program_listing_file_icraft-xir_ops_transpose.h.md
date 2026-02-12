# Program Listing for File transpose.h



↰ [Return to documentation for file](file_icraft-xir_ops_transpose.h.md#file-icraft-xir-ops-transpose-h) (`icraft-xir\ops\transpose.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class TransposeNode : public OpNodeBase<TransposeNode> {
    public:
        Array<int64_t> dims;
        Layout layout;

        ICRAFT_DECLARE_ATTRS(TransposeNode) {
            ICRAFT_ATTR_FIELD(dims);
            ICRAFT_ATTR_FIELD(layout);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Transpose : public OpBase<Transpose, TransposeNode> {
    public:
        Transpose() = default;

        XIR_DLL Transpose(Value input, Array<int64_t> dims, Layout layout);

        XIR_DLL Transpose(Value input, Array<int64_t> dims);
    };
}
</pre>
```
