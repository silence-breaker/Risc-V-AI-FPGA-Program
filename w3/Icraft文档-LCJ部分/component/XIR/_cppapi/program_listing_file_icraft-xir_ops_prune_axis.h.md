# Program Listing for File prune_axis.h



↰ [Return to documentation for file](file_icraft-xir_ops_prune_axis.h.md#file-icraft-xir-ops-prune-axis-h) (`icraft-xir\ops\prune_axis.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class PruneAxisNode : public OpNodeBase<PruneAxisNode> {
    public:
        Array<int64_t> index;

        ICRAFT_DECLARE_ATTRS(AlignAxisNode) {
            ICRAFT_ATTR_FIELD(index);
        }

        XIR_DLL virtual void validate() const override;
    };

    class PruneAxis : public OpBase<PruneAxis, PruneAxisNode> {
    public:
        PruneAxis() = default;

        XIR_DLL PruneAxis(Value input, Array<int64_t> index);
    };
}
</pre>
```
