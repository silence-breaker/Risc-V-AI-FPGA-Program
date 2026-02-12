# Program Listing for File normalize.h



↰ [Return to documentation for file](file_icraft-xir_ops_normalize.h.md#file-icraft-xir-ops-normalize-h) (`icraft-xir\ops\normalize.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class NormalizeNode : public OpNodeBase<NormalizeNode> {
    public:
        Array<int64_t> axis;
        float p;
        float eps;

        ICRAFT_DECLARE_ATTRS(NormalizeNode) {
            ICRAFT_ATTR_FIELD(axis);
            ICRAFT_ATTR_FIELD(p).set_default(2);
            ICRAFT_ATTR_FIELD(eps).set_default(1e-12);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Normalize : public OpBase<Normalize, NormalizeNode> {
    public:
        Normalize() = default;

        XIR_DLL Normalize(Value input, Array<int64_t> axis, float p = 2, float eps = 1e-12);
    };
}
</pre>
```
