# Program Listing for File einsum.h



↰ [Return to documentation for file](file_icraft-xir_ops_einsum.h.md#file-icraft-xir-ops-einsum-h) (`icraft-xir\ops\einsum.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class EinsumNode : public OpNodeBase<EinsumNode> {
    public:
        std::string equation;

        ICRAFT_DECLARE_ATTRS(EinsumNode) {
            ICRAFT_ATTR_FIELD(equation);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Einsum : public OpBase<Einsum, EinsumNode> {
    public:
        Einsum() = default;

        XIR_DLL Einsum(Array<Value> inputs, std::string equation);
    };
}
</pre>
```
