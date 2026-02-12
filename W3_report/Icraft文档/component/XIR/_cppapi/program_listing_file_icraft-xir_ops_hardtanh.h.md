# Program Listing for File hardtanh.h



↰ [Return to documentation for file](file_icraft-xir_ops_hardtanh.h.md#file-icraft-xir-ops-hardtanh-h) (`icraft-xir\ops\hardtanh.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class HardtanhNode : public OpNodeBase<HardtanhNode, IsActivate> {
    public:
        float min_val ;
        float max_val;

        ICRAFT_DECLARE_ATTRS(HardtanhNode) {
            ICRAFT_ATTR_FIELD(min_val).set_default(-1.0);
            ICRAFT_ATTR_FIELD(max_val).set_default(1.0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Hardtanh : public OpBase<Hardtanh, HardtanhNode> {
    public:
        Hardtanh() = default;

        XIR_DLL Hardtanh(Value input, float min_val = -1.0, float max_val = 1.0);
    };
}
</pre>
```
