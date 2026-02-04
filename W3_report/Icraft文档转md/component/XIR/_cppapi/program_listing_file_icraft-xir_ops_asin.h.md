# Program Listing for File asin.h



↰ [Return to documentation for file](file_icraft-xir_ops_asin.h.md#file-icraft-xir-ops-asin-h) (`icraft-xir\ops\asin.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ASinNode : public OpNodeBase<ASinNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(ASinNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class ASin : public OpBase<ASin, ASinNode> {
    public:
        ASin() = default;

        XIR_DLL ASin(Value input);
    };
}
</pre>
```
