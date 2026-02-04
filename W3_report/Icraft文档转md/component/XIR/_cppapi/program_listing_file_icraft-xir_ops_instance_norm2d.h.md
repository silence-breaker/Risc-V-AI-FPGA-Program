# Program Listing for File instance_norm2d.h



↰ [Return to documentation for file](file_icraft-xir_ops_instance_norm2d.h.md#file-icraft-xir-ops-instance-norm2d-h) (`icraft-xir\ops\instance_norm2d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class InstanceNorm2dNode : public OpNodeBase<InstanceNorm2dNode> {
    public:
        float eps;
        Optional<Params> gamma;
        Optional<Params> beta;

        ICRAFT_DECLARE_ATTRS(InstanceNorm2dNode) {
            ICRAFT_ATTR_FIELD(eps).set_default(1e-5);
            ICRAFT_ATTR_FIELD(gamma);
            ICRAFT_ATTR_FIELD(beta);
        }

        XIR_DLL virtual void validate() const override;
    };

    class InstanceNorm2d : public OpBase<InstanceNorm2d, InstanceNorm2dNode> {
    public:
        InstanceNorm2d() = default;

        XIR_DLL InstanceNorm2d(
            Value input,
            float eps = 1e-5,
            Optional<Params> gamma = NullOpt,
            Optional<Params> beta = NullOpt
        );
    };
}
</pre>
```
