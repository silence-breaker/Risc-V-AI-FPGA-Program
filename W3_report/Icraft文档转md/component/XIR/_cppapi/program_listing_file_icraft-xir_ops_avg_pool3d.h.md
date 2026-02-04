# Program Listing for File avg_pool3d.h



↰ [Return to documentation for file](file_icraft-xir_ops_avg_pool3d.h.md#file-icraft-xir-ops-avg-pool3d-h) (`icraft-xir\ops\avg_pool3d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class AvgPool3dNode : public OpNodeBase<AvgPool3dNode> {
    public:
        int64_t pool_depth;
        int64_t pool_width;
        int64_t pool_height;
        int64_t stride_depth;
        int64_t stride_width;
        int64_t stride_height;
        int64_t pad_front;
        int64_t pad_back;
        int64_t pad_top;
        int64_t pad_bottom;
        int64_t pad_left;
        int64_t pad_right;
        bool count_include_pad;
        int64_t divisor_override;

        ICRAFT_DECLARE_ATTRS(AvgPool3dNode) {
            ICRAFT_ATTR_FIELD(pool_depth).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pool_width).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pool_height).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_depth).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_height).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pad_front).set_default(0);
            ICRAFT_ATTR_FIELD(pad_back).set_default(0);
            ICRAFT_ATTR_FIELD(pad_top).set_default(0);
            ICRAFT_ATTR_FIELD(pad_bottom).set_default(0);
            ICRAFT_ATTR_FIELD(pad_left).set_default(0);
            ICRAFT_ATTR_FIELD(pad_right).set_default(0);
            ICRAFT_ATTR_FIELD(count_include_pad).set_default(false);
            ICRAFT_ATTR_FIELD(divisor_override).set_default(0);
        }

        XIR_DLL virtual void validate() const override;
    };

    class AvgPool3d : public OpBase<AvgPool3d, AvgPool3dNode> {
    public:
        AvgPool3d() = default;

        XIR_DLL AvgPool3d(
            Value input,
            int64_t pool_depth,
            int64_t pool_width,
            int64_t pool_height,
            int64_t stride_depth,
            int64_t stride_width,
            int64_t stride_height,
            int64_t pad_front,
            int64_t pad_back,
            int64_t pad_top,
            int64_t pad_bottom,
            int64_t pad_left,
            int64_t pad_right,
            bool count_include_pad = false,
            int64_t divisor_override = 0
        );

        AvgPool3d(
            Value input,
            int64_t pool_size,
            int64_t stride,
            int64_t pad_front_top_bottom,
            int64_t pad_back_left_right,
            bool count_include_pad = false,
            int64_t divisor_override = 0
        ) : AvgPool3d(
            input,
            pool_size, pool_size, pool_size,
            stride, stride, stride,
            pad_front_top_bottom,
            pad_front_top_bottom,
            pad_front_top_bottom,
            pad_back_left_right,
            pad_back_left_right,
            pad_back_left_right,
            count_include_pad,
            divisor_override
        ) {}

        AvgPool3d(
            Value input,
            int64_t pool_size,
            int64_t stride,
            int64_t pad,
            bool count_include_pad = false,
            int64_t divisor_override = 0
        ) : AvgPool3d(
            input,
            pool_size,
            stride,
            pad, pad,
            count_include_pad,
            divisor_override
        ) {}
    };
}
</pre>
```
