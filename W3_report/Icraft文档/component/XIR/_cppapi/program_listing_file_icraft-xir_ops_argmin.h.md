# Program Listing for File argmin.h



↰ [Return to documentation for file](file_icraft-xir_ops_argmin.h.md#file-icraft-xir-ops-argmin-h) (`icraft-xir\ops\argmin.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ArgminNode : public OpNodeBase<ArgminNode> {
    public:
        Optional<IntImm> dim;
        bool keepdim;

        ICRAFT_DECLARE_ATTRS(ArgminNode) {
            ICRAFT_ATTR_FIELD(dim);
            ICRAFT_ATTR_FIELD(keepdim).set_default(false);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Argmin : public OpBase<Argmin, ArgminNode> {
    public:
        Argmin() = default;

        XIR_DLL Argmin(Value input, Optional<IntImm> dim = NullOpt, bool keepdim = false);
    };
}
</pre>
```
