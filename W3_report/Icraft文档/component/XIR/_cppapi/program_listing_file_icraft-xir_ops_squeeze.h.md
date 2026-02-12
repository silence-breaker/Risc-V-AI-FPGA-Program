# Program Listing for File squeeze.h



↰ [Return to documentation for file](file_icraft-xir_ops_squeeze.h.md#file-icraft-xir-ops-squeeze-h) (`icraft-xir\ops\squeeze.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SqueezeNode : public OpNodeBase<SqueezeNode> {
    public:
        Array<int64_t> axis;

        ICRAFT_DECLARE_ATTRS(SqueezeNode) {
            ICRAFT_ATTR_FIELD(axis);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Squeeze : public OpBase<Squeeze, SqueezeNode> {
    public:
        Squeeze() = default;

        XIR_DLL Squeeze(Value input, Array<int64_t> axis);
    };
}
</pre>
```
