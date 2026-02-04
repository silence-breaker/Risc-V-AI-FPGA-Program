# Program Listing for File acos.h



↰ [Return to documentation for file](file_icraft-xir_ops_acos.h.md#file-icraft-xir-ops-acos-h) (`icraft-xir\ops\acos.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ACosNode : public OpNodeBase<ACosNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(ACosNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class ACos : public OpBase<ACos, ACosNode> {
    public:
        ACos() = default;

        XIR_DLL ACos(Value input);
    };
}
</pre>
```
