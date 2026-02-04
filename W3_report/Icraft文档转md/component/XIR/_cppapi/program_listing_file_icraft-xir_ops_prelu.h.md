# Program Listing for File prelu.h



↰ [Return to documentation for file](file_icraft-xir_ops_prelu.h.md#file-icraft-xir-ops-prelu-h) (`icraft-xir\ops\prelu.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class PReLUNode : public OpNodeBase<PReLUNode, IsActivate> {
    public:
        Params alpha;

        ICRAFT_DECLARE_ATTRS(PReLUNode) {
            ICRAFT_ATTR_FIELD(alpha);
        }

        XIR_DLL virtual void validate() const override;
    };

    class PReLU : public OpBase<PReLU, PReLUNode> {
    public:
        PReLU() = default;

        XIR_DLL PReLU(Value input, Params alpha);
    };

    // 兼容旧接口
    using Prelu = PReLU;
    using PreluNode = PReLUNode;
}
</pre>
```
