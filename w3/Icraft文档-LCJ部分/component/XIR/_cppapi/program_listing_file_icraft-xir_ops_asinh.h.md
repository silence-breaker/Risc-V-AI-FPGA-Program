# Program Listing for File asinh.h



↰ [Return to documentation for file](file_icraft-xir_ops_asinh.h.md#file-icraft-xir-ops-asinh-h) (`icraft-xir\ops\asinh.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ASinhNode : public OpNodeBase<ASinhNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(ASinhNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class ASinh : public OpBase<ASinh, ASinhNode> {
    public:
        ASinh() = default;

        XIR_DLL ASinh(Value input);
    };
}
</pre>
```
