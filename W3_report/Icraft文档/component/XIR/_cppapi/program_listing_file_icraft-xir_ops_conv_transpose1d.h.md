# Program Listing for File conv_transpose1d.h



↰ [Return to documentation for file](file_icraft-xir_ops_conv_transpose1d.h.md#file-icraft-xir-ops-conv-transpose1d-h) (`icraft-xir\ops\conv_transpose1d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ConvTranspose1dNode : public OpNodeBase<ConvTranspose1dNode> {
    public:
        int64_t stride_width;
        int64_t pad_left;
        int64_t pad_right;
        int64_t dilation_width;
        int64_t output_pad_width;
        int64_t groups;

        ICRAFT_DECLARE_ATTRS(ConvTranspose1dNode) {
            ICRAFT_ATTR_FIELD(stride_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pad_left).set_default(0);
            ICRAFT_ATTR_FIELD(pad_right).set_default(0);
            ICRAFT_ATTR_FIELD(dilation_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(output_pad_width).set_default(0);
            ICRAFT_ATTR_FIELD(groups).set_default(1).set_lower_bound(1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class ConvTranspose1d : public OpBase<ConvTranspose1d, ConvTranspose1dNode> {
    public:
        ConvTranspose1d() = default;

        XIR_DLL ConvTranspose1d(
            Value input,
            Value weights,
            Optional<Value> bias,
            int64_t stride_width,
            int64_t pad_left,
            int64_t pad_right,
            int64_t dilation_width,
            int64_t output_pad_width,
            int64_t groups = 1
        );
    };

    // 兼容旧接口
    using Conv1dTranspose = ConvTranspose1d;
    using Conv1dTransposeNode = ConvTranspose1dNode;
}
</pre>
```
