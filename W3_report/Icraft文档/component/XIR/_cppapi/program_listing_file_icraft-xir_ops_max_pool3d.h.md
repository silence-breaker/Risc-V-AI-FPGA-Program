# Program Listing for File max_pool3d.h



↰ [Return to documentation for file](file_icraft-xir_ops_max_pool3d.h.md#file-icraft-xir-ops-max-pool3d-h) (`icraft-xir\ops\max_pool3d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MaxPool3dNode : public OpNodeBase<MaxPool3dNode> {
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
        int64_t dilation_depth;
        int64_t dilation_width;
        int64_t dilation_height;

        ICRAFT_DECLARE_ATTRS(MaxPool3dNode) {
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
            ICRAFT_ATTR_FIELD(dilation_depth).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(dilation_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(dilation_height).set_default(1).set_lower_bound(1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class MaxPool3d : public OpBase<MaxPool3d, MaxPool3dNode> {
    public:
        MaxPool3d() = default;

        XIR_DLL MaxPool3d(
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
            int64_t dilation_depth,
            int64_t dilation_width,
            int64_t dilation_height
        );

        MaxPool3d(
            Value input,
            int64_t pool_size,
            int64_t stride,
            int64_t pad_front_top_bottom,
            int64_t pad_back_left_right,
            int64_t dilation
        ) : MaxPool3d(
            input,
            pool_size,
            pool_size,
            pool_size,
            stride, stride, stride,
            pad_front_top_bottom,
            pad_front_top_bottom,
            pad_front_top_bottom,
            pad_back_left_right,
            pad_back_left_right,
            pad_back_left_right,
            dilation,
            dilation,
            dilation
        ) {}

        MaxPool3d(
            Value input,
            int64_t pool_size,
            int64_t stride,
            int64_t pad,
            int64_t dilation
        ) : MaxPool3d(
            input,
            pool_size,
            stride,
            pad,
            pad,
            dilation
        ) {}
    };
}
</pre>
```
