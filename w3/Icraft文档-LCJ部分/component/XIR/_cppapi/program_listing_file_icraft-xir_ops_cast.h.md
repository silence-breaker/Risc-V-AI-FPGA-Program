# Program Listing for File cast.h



↰ [Return to documentation for file](file_icraft-xir_ops_cast.h.md#file-icraft-xir-ops-cast-h) (`icraft-xir\ops\cast.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class CastNode : public OpNodeBase<CastNode> {
    public:
        TensorType target_dtype;

        ICRAFT_DECLARE_ATTRS(CastNode) {
            ICRAFT_ATTR_FIELD(target_dtype);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Cast : public OpBase<Cast, CastNode> {
    public:
        Cast() = default;

        XIR_DLL Cast(Value input, TensorType target_dtype);
    };
}
</pre>
```
