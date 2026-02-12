# Program Listing for File reshape.h



↰ [Return to documentation for file](file_icraft-xir_ops_reshape.h.md#file-icraft-xir-ops-reshape-h) (`icraft-xir\ops\reshape.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ReshapeNode : public OpNodeBase<ReshapeNode> {
    public:
        Array<int64_t> shape;
        Layout layout;

        ICRAFT_DECLARE_ATTRS(ReshapeNode) {
            ICRAFT_ATTR_FIELD(shape);
            ICRAFT_ATTR_FIELD(layout);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Reshape : public OpBase<Reshape, ReshapeNode> {
    public:
        Reshape() = default;

        XIR_DLL Reshape(Value input, Array<int64_t> shape, Layout layout);
    };
}
</pre>
```
