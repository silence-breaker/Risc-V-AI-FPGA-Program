# Program Listing for File cos.h



↰ [Return to documentation for file](file_icraft-xir_ops_cos.h.md#file-icraft-xir-ops-cos-h) (`icraft-xir\ops\cos.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class CosNode : public OpNodeBase<CosNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(CosNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Cos : public OpBase<Cos, CosNode> {
    public:
        Cos() = default;

        XIR_DLL Cos(Value input);
    };
}
</pre>
```
