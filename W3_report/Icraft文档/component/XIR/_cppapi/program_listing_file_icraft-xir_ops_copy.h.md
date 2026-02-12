# Program Listing for File copy.h



↰ [Return to documentation for file](file_icraft-xir_ops_copy.h.md#file-icraft-xir-ops-copy-h) (`icraft-xir\ops\copy.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class CopyNode : public OpNodeBase<CopyNode> {
    public:
        ICRAFT_DECLARE_ATTRS(CopyNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Copy : public OpBase<Copy, CopyNode> {
    public:
        Copy() = default;

        XIR_DLL Copy(Value input);
    };
}
</pre>
```
