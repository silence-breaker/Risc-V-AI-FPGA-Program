# Program Listing for File layer_norm.h



↰ [Return to documentation for file](file_icraft-xir_ops_layer_norm.h.md#file-icraft-xir-ops-layer-norm-h) (`icraft-xir\ops\layer_norm.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class LayerNormNode : public OpNodeBase<LayerNormNode> {
    public:
        Array<int64_t> axis;
        float eps;
        Optional<Params> gamma;
        Optional<Params> beta;

        ICRAFT_DECLARE_ATTRS(LayerNormNode) {
            ICRAFT_ATTR_FIELD(axis);
            ICRAFT_ATTR_FIELD(eps).set_default(1e-5);
            ICRAFT_ATTR_FIELD(gamma);
            ICRAFT_ATTR_FIELD(beta);
        }

        XIR_DLL virtual void validate() const override;
    };

    class LayerNorm : public OpBase<LayerNorm, LayerNormNode> {
    public:
        LayerNorm() = default;

        XIR_DLL LayerNorm(
            Value input,
            Array<int64_t> axis,
            float eps = 1e-5,
            Optional<Params> gamma = NullOpt,
            Optional<Params> beta = NullOpt
        );
    };

    // 兼容旧接口
    using Layernorm = LayerNorm;
    using LayernormNode = LayerNormNode;
}
</pre>
```
