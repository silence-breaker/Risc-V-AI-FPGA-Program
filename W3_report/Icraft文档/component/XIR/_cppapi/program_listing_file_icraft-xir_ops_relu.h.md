# Program Listing for File relu.h



↰ [Return to documentation for file](file_icraft-xir_ops_relu.h.md#file-icraft-xir-ops-relu-h) (`icraft-xir\ops\relu.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ReLUNode : public OpNodeBase<ReLUNode, IsActivate> {
    public:
        float alpha;
        float max_value;
        float threshold;

        ICRAFT_DECLARE_ATTRS(ReLUNode) {
            ICRAFT_ATTR_FIELD(alpha).set_default(0);
            ICRAFT_ATTR_FIELD(max_value).set_default(std::numeric_limits<float>::infinity());
            ICRAFT_ATTR_FIELD(threshold).set_default(0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class ReLU : public OpBase<ReLU, ReLUNode> {
    public:
        ReLU() = default;

        XIR_DLL ReLU(Value input, float alpha = 0, float max_value = std::numeric_limits<float>::infinity(),
            float threshold = 0);
    };

    // 兼容旧接口
    using Relu = ReLU;
    using ReluNode = ReLUNode;
}
</pre>
```
