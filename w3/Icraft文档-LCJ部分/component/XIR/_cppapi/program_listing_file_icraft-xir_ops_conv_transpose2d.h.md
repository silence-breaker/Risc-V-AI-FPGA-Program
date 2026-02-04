# Program Listing for File conv_transpose2d.h



↰ [Return to documentation for file](file_icraft-xir_ops_conv_transpose2d.h.md#file-icraft-xir-ops-conv-transpose2d-h) (`icraft-xir\ops\conv_transpose2d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ConvTranspose2dNode : public OpNodeBase<ConvTranspose2dNode> {
    public:
        int64_t stride_width;
        int64_t stride_height;
        int64_t pad_top;
        int64_t pad_bottom;
        int64_t pad_left;
        int64_t pad_right;
        int64_t dilation_width;
        int64_t dilation_height;
        int64_t output_pad_width;
        int64_t output_pad_height;
        int64_t groups;

        ICRAFT_DECLARE_ATTRS(ConvTranspose2dNode) {
            ICRAFT_ATTR_FIELD(stride_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(stride_height).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pad_top).set_default(0);
            ICRAFT_ATTR_FIELD(pad_bottom).set_default(0);
            ICRAFT_ATTR_FIELD(pad_left).set_default(0);
            ICRAFT_ATTR_FIELD(pad_right).set_default(0);
            ICRAFT_ATTR_FIELD(dilation_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(dilation_height).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(output_pad_width).set_default(0);
            ICRAFT_ATTR_FIELD(output_pad_height).set_default(0);
            ICRAFT_ATTR_FIELD(groups).set_default(1).set_lower_bound(1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class ConvTranspose2d : public OpBase<ConvTranspose2d, ConvTranspose2dNode> {
    public:
        ConvTranspose2d() = default;

        XIR_DLL ConvTranspose2d(
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
            int64_t output_pad_width,
            int64_t output_pad_height,
            int64_t groups = 1
        );

        ConvTranspose2d(
            Value input,
            Value weights,
            Optional<Value> bias,
            int64_t stride,
            int64_t pad,
            int64_t dilation,
            int64_t output_pad,
            int64_t groups = 1
        ) : ConvTranspose2d(
            input,
            weights,
            bias,
            stride, stride,
            pad, pad, pad, pad,
            dilation, dilation,
            output_pad, output_pad,
            groups
        ) {}
    };

    // 兼容旧接口
    using Conv2dTranspose = ConvTranspose2d;
    using Conv2dTransposeNode = ConvTranspose2dNode;
}
</pre>
```
