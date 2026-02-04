# Program Listing for File avg_pool1d.h



↰ [Return to documentation for file](file_icraft-xir_ops_avg_pool1d.h.md#file-icraft-xir-ops-avg-pool1d-h) (`icraft-xir\ops\avg_pool1d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class AvgPool1dNode : public OpNodeBase<AvgPool1dNode> {
    public:

        int64_t pool_width;
        int64_t stride_width;
        int64_t pad_left;
        int64_t pad_right;
        bool count_include_pad;
        int64_t divisor_override;

        ICRAFT_DECLARE_ATTRS(AvgPool1dNode) {
            ICRAFT_ATTR_FIELD(pool_width).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pad_left).set_default(0);
            ICRAFT_ATTR_FIELD(pad_right).set_default(0);
            ICRAFT_ATTR_FIELD(count_include_pad).set_default(false);
            ICRAFT_ATTR_FIELD(divisor_override).set_default(0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class AvgPool1d : public OpBase<AvgPool1d, AvgPool1dNode> {
    public:
        AvgPool1d() = default;

        XIR_DLL AvgPool1d(
            Value input,
            int64_t pool_width,
            int64_t stride_width,
            int64_t pad_left,
            int64_t pad_right,
            bool count_include_pad = false,
            int64_t divisor_override = 0
        );
    };
}
</pre>
```
