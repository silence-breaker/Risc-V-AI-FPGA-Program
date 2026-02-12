# Program Listing for File unfold.h



↰ [Return to documentation for file](file_icraft-xir_ops_unfold.h.md#file-icraft-xir-ops-unfold-h) (`icraft-xir\ops\unfold.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class UnfoldNode : public OpNodeBase<UnfoldNode> {
    public:
        int64_t kernel_width;
        int64_t kernel_height;
        int64_t stride_width;
        int64_t stride_height;
        int64_t pad_top;
        int64_t pad_bottom;
        int64_t pad_left;
        int64_t pad_right;
        int64_t dilation_width;
        int64_t dilation_height;

        ICRAFT_DECLARE_ATTRS(UnfoldNode) {
            ICRAFT_ATTR_FIELD(kernel_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(kernel_height).set_default(1).set_lower_bound(1);
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

    class Unfold : public OpBase<Unfold, UnfoldNode> {
    public:
        Unfold() = default;

        XIR_DLL Unfold(
            Value input,
            int64_t kernel_width,
            int64_t kernel_height,
            int64_t stride_width,
            int64_t stride_height,
            int64_t pad_top,
            int64_t pad_bottom,
            int64_t pad_left,
            int64_t pad_right,
            int64_t dilation_width,
            int64_t dilation_height
        );

        Unfold(
            Value input,
            int64_t kernel,
            int64_t stride,
            int64_t pad,
            int64_t dilation
        ) : Unfold(
            input,
            kernel, kernel,
            stride, stride,
            pad, pad, pad, pad,
            dilation, dilation
        ) {}
    };
}
</pre>
```
