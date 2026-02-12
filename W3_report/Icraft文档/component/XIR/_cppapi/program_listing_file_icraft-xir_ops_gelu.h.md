# Program Listing for File gelu.h



↰ [Return to documentation for file](file_icraft-xir_ops_gelu.h.md#file-icraft-xir-ops-gelu-h) (`icraft-xir\ops\gelu.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class GELUNode : public OpNodeBase<GELUNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(GELUNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class GELU : public OpBase<GELU, GELUNode> {
    public:
        GELU() = default;

        XIR_DLL GELU(Value input);
    };

    // 兼容旧接口
    using Gelu = GELU;
    using GeluNode = GELUNode;
}
</pre>
```
