# Program Listing for File unsupport.h



↰ [Return to documentation for file](file_icraft-xir_ops_unsupport.h.md#file-icraft-xir-ops-unsupport-h) (`icraft-xir\ops\unsupport.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class UnsupportNode : public OpNodeBase<UnsupportNode> {
    public:
        ICRAFT_DECLARE_ATTRS(UnsupportNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Unsupport : public OpBase<Unsupport, UnsupportNode> {
    public:
        Unsupport() = default;

        XIR_DLL Unsupport(Array<Value> inputs);
    };
}
</pre>
```
