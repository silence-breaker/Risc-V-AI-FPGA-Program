# Program Listing for File silu.h



↰ [Return to documentation for file](file_icraft-xir_ops_silu.h.md#file-icraft-xir-ops-silu-h) (`icraft-xir\ops\silu.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SiLUNode : public OpNodeBase<SiLUNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(SiLUNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class SiLU : public OpBase<SiLU, SiLUNode> {
    public:
        SiLU() = default;

        XIR_DLL SiLU(Value input);
    };

    // 兼容旧接口
    using Silu = SiLU;
    using SiluNode = SiLUNode;
}
</pre>
```
