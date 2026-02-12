# Program Listing for File argmax.h



↰ [Return to documentation for file](file_icraft-xir_ops_argmax.h.md#file-icraft-xir-ops-argmax-h) (`icraft-xir\ops\argmax.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ArgmaxNode : public OpNodeBase<ArgmaxNode> {
    public:
        Optional<IntImm> dim;
        bool keepdim;

        ICRAFT_DECLARE_ATTRS(ArgmaxNode) {
            ICRAFT_ATTR_FIELD(dim);
            ICRAFT_ATTR_FIELD(keepdim).set_default(false);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Argmax : public OpBase<Argmax, ArgmaxNode> {
    public:
        Argmax() = default;

        XIR_DLL Argmax(Value input, Optional<IntImm> dim = NullOpt, bool keepdim = false);
    };
}
</pre>
```
