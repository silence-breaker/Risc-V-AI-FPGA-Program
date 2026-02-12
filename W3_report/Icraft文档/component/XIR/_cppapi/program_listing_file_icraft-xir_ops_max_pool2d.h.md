# Program Listing for File max_pool2d.h



↰ [Return to documentation for file](file_icraft-xir_ops_max_pool2d.h.md#file-icraft-xir-ops-max-pool2d-h) (`icraft-xir\ops\max_pool2d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class MaxPool2dNode : public OpNodeBase<MaxPool2dNode> {
    public:
        int64_t pool_width;
        int64_t pool_height;
        int64_t stride_width;
        int64_t stride_height;
        int64_t pad_top;
        int64_t pad_bottom;
        int64_t pad_left;
        int64_t pad_right;
        int64_t dilation_width;
        int64_t dilation_height;

        ICRAFT_DECLARE_ATTRS(MaxPool2dNode) {
            ICRAFT_ATTR_FIELD(pool_width).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pool_height).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_height).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pad_top).set_default(0);
            ICRAFT_ATTR_FIELD(pad_bottom).set_default(0);
            ICRAFT_ATTR_FIELD(pad_left).set_default(0);
            ICRAFT_ATTR_FIELD(pad_right).set_default(0);
            ICRAFT_ATTR_FIELD(dilation_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(dilation_height).set_default(1).set_lower_bound(1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class MaxPool2d : public OpBase<MaxPool2d, MaxPool2dNode> {
    public:
        MaxPool2d() = default;

        XIR_DLL MaxPool2d(
            Value input,
            int64_t pool_width,
            int64_t pool_height,
            int64_t stride_width,
            int64_t stride_height,
            int64_t pad_top,
            int64_t pad_bottom,
            int64_t pad_left,
            int64_t pad_right,
            int64_t dilation_width,
            int64_t dilation_height
        );

        MaxPool2d(
            Value input,
            int64_t pool_size,
            int64_t stride,
            int64_t pad_top_bottom,
            int64_t pad_left_right,
            int64_t dilation
        ) : MaxPool2d(
            input,
            pool_size,
            pool_size,
            stride,
            stride,
            pad_top_bottom,
            pad_top_bottom,
            pad_left_right,
            pad_left_right,
            dilation,
            dilation
        ) {}

        MaxPool2d(
            Value input,
            int64_t pool_size,
            int64_t stride,
            int64_t pad,
            int64_t dilation
        ) : MaxPool2d(
            input,
            pool_size,
            stride,
            pad,
            pad,
            dilation
        ) {}
    };

    // 兼容旧接口
    using Maxpool = MaxPool2d;
    using MaxpoolNode = MaxPool2dNode;
}
</pre>
```
