# Program Listing for File clamp_scalar.h



↰ [Return to documentation for file](file_icraft-xir_ops_clamp_scalar.h.md#file-icraft-xir-ops-clamp-scalar-h) (`icraft-xir\ops\clamp_scalar.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ClampScalarNode : public OpNodeBase<ClampScalarNode, IsActivate> {
    public:
        float min;
        float max;

        ICRAFT_DECLARE_ATTRS(ClampScalarNode) {
            ICRAFT_ATTR_FIELD(min).set_default(-std::numeric_limits<float>::infinity());
            ICRAFT_ATTR_FIELD(max).set_default(std::numeric_limits<float>::infinity());
        }

        XIR_DLL virtual void validate() const override;
    };

    class ClampScalar : public OpBase<ClampScalar, ClampScalarNode> {
    public:
        ClampScalar() = default;

        XIR_DLL ClampScalar(
            Value input,
            float min = -std::numeric_limits<float>::infinity(),
            float max = std::numeric_limits<float>::infinity()
        );
    };
}
</pre>
```
