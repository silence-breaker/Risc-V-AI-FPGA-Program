# Program Listing for File slice.h



↰ [Return to documentation for file](file_icraft-xir_ops_slice.h.md#file-icraft-xir-ops-slice-h) (`icraft-xir\ops\slice.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SliceNode : public OpNodeBase<SliceNode> {
    public:
        Array<int64_t> begin;
        Array<int64_t> end;
        Array<int64_t> stride;

        ICRAFT_DECLARE_ATTRS(SliceNode) {
            ICRAFT_ATTR_FIELD(begin);
            ICRAFT_ATTR_FIELD(end);
            ICRAFT_ATTR_FIELD(stride);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Slice : public OpBase<Slice, SliceNode> {
    public:
        Slice() = default;

        XIR_DLL Slice(Value input, Array<int64_t> begin, Array<int64_t> end, Array<int64_t> stride);
    };
}
</pre>
```
