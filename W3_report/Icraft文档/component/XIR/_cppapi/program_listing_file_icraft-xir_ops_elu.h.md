# Program Listing for File elu.h



↰ [Return to documentation for file](file_icraft-xir_ops_elu.h.md#file-icraft-xir-ops-elu-h) (`icraft-xir\ops\elu.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ELUNode : public OpNodeBase<ELUNode, IsActivate> {
    public:
        float alpha;

        ICRAFT_DECLARE_ATTRS(ELUNode) {
            ICRAFT_ATTR_FIELD(alpha).set_default(1.0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class ELU : public OpBase<ELU, ELUNode> {
    public:
        ELU() = default;

        XIR_DLL ELU(Value input, float alpha = 1.0);
    };

    // 兼容旧接口
    using Elu = ELU;
    using EluNode = ELUNode;
}
</pre>
```
