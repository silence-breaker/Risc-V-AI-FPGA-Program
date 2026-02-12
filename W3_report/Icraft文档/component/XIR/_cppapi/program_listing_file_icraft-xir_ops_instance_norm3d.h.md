# Program Listing for File instance_norm3d.h



↰ [Return to documentation for file](file_icraft-xir_ops_instance_norm3d.h.md#file-icraft-xir-ops-instance-norm3d-h) (`icraft-xir\ops\instance_norm3d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class InstanceNorm3dNode : public OpNodeBase<InstanceNorm3dNode> {
    public:
        float eps;
        Optional<Params> gamma;
        Optional<Params> beta;

        ICRAFT_DECLARE_ATTRS(InstanceNorm3dNode) {
            ICRAFT_ATTR_FIELD(eps).set_default(1e-5);
            ICRAFT_ATTR_FIELD(gamma);
            ICRAFT_ATTR_FIELD(beta);
        }

        XIR_DLL virtual void validate() const override;
    };

    class InstanceNorm3d : public OpBase<InstanceNorm3d, InstanceNorm3dNode> {
    public:
        InstanceNorm3d() = default;

        XIR_DLL InstanceNorm3d(Value input, float eps = 1e-5, Optional<Params> gamma = NullOpt,
            Optional<Params> beta = NullOpt);
    };
}
</pre>
```
