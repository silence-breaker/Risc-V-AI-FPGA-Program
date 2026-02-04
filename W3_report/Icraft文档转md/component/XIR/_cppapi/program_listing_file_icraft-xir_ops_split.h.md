# Program Listing for File split.h



↰ [Return to documentation for file](file_icraft-xir_ops_split.h.md#file-icraft-xir-ops-split-h) (`icraft-xir\ops\split.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SplitNode : public OpNodeBase<SplitNode> {
    public:
        Array<int64_t> sections;
        int64_t axis;

        ICRAFT_DECLARE_ATTRS(SplitNode) {
            ICRAFT_ATTR_FIELD(sections);
            ICRAFT_ATTR_FIELD(axis).set_default(-1);
        };

        XIR_DLL virtual void validate() const override;
    };

    class Split : public OpBase<Split, SplitNode> {
    public:
        Split() = default;

        XIR_DLL Split(Value input, Array<int64_t> sections, int64_t axis = -1);
    };
}
</pre>
```
