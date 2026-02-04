# Program Listing for File conv2d.h



↰ [Return to documentation for file](file_icraft-xir_ops_conv2d.h.md#file-icraft-xir-ops-conv2d-h) (`icraft-xir\ops\conv2d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    // enum class PaddingMode {
    //  ZEROS,      ///< 填充0
    //  REFLECT,    ///< 反射
    //  REPLICATE,  ///< 重复
    //  CIRCULAR    ///< 环形
    // };
    WISE_ENUM_CLASS(PaddingMode, ZEROS, REFLECT, REPLICATE, CIRCULAR);

    class Conv2dNode : public OpNodeBase<Conv2dNode> {
    public:
        int64_t stride_width;
        int64_t stride_height;
        int64_t pad_top;
        int64_t pad_bottom;
        int64_t pad_left;
        int64_t pad_right;
        int64_t dilation_width;
        int64_t dilation_height;
        int64_t groups;
        PaddingMode padding_mode;

        QuantizedScaleArray cut_scale;

        ICRAFT_DECLARE_ATTRS(Conv2dNode) {
            ICRAFT_ATTR_FIELD(stride_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_height).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pad_top).set_default(0);
            ICRAFT_ATTR_FIELD(pad_bottom).set_default(0);
            ICRAFT_ATTR_FIELD(pad_left).set_default(0);
            ICRAFT_ATTR_FIELD(pad_right).set_default(0);
            ICRAFT_ATTR_FIELD(dilation_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(dilation_height).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(groups).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(padding_mode).set_default(PaddingMode::ZEROS);
            ICRAFT_ATTR_FIELD(cut_scale);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Conv2d : public OpBase<Conv2d, Conv2dNode> {
    public:
        Conv2d() = default;

        XIR_DLL Conv2d(
            Value input,
            Value weights,
            Optional<Value> bias,
            int64_t stride_width,
            int64_t stride_height,
            int64_t pad_top,
            int64_t pad_bottom,
            int64_t pad_left,
            int64_t pad_right,
            int64_t dilation_width,
            int64_t dilation_height,
            int64_t groups = 1,
            PaddingMode padding_mode = PaddingMode::ZEROS
        );

        Conv2d(
            Value input,
            Value weights,
            Optional<Value> bias,
            int64_t stride,
            int64_t pad,
            int64_t dilation,
            int64_t groups = 1,
            PaddingMode padding_mode = PaddingMode::ZEROS
        ) : Conv2d(
            input,
            weights,
            bias,
            stride, stride,
            pad, pad, pad, pad,
            dilation, dilation,
            groups,
            padding_mode
        ) {}
    };
}
</pre>
```
