# Program Listing for File max_pool1d.h



↰ [Return to documentation for file](file_icraft-xir_ops_max_pool1d.h.md#file-icraft-xir-ops-max-pool1d-h) (`icraft-xir\ops\max_pool1d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MaxPool1dNode : public OpNodeBase<MaxPool1dNode> {
    public:
        int64_t pool_width;
        int64_t stride_width;
        int64_t pad_left;
        int64_t pad_right;
        int64_t dilation_width;

        ICRAFT_DECLARE_ATTRS(MaxPool1dNode) {
            ICRAFT_ATTR_FIELD(pool_width).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pad_left).set_default(0);
            ICRAFT_ATTR_FIELD(pad_right).set_default(0);
            ICRAFT_ATTR_FIELD(dilation_width).set_default(1).set_lower_bound(1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class MaxPool1d : public OpBase<MaxPool1d, MaxPool1dNode> {
    public:
        MaxPool1d() = default;

        XIR_DLL MaxPool1d(
            Value input,
            int64_t pool_width,
            int64_t stride_width,
            int64_t pad_left,
            int64_t pad_right,
            int64_t dilation_width
        );
    };
}
</pre>
```
