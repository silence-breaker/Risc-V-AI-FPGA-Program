# Program Listing for File conv1d.h



↰ [Return to documentation for file](file_icraft-xir_ops_conv1d.h.md#file-icraft-xir-ops-conv1d-h) (`icraft-xir\ops\conv1d.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>
#include <icraft-xir/ops/conv2d.h>

namespace icraft::xir {

    class Conv1dNode : public OpNodeBase<Conv1dNode> {
    public:
        int64_t stride_width;
        int64_t pad_left;
        int64_t pad_right;
        int64_t dilation_width;
        int64_t groups;
        PaddingMode padding_mode;

        QuantizedScaleArray cut_scale;

        ICRAFT_DECLARE_ATTRS(Conv1dNode) {
            ICRAFT_ATTR_FIELD(stride_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(pad_left).set_default(0);
            ICRAFT_ATTR_FIELD(pad_right).set_default(0);
            ICRAFT_ATTR_FIELD(dilation_width).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(groups).set_default(1).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(padding_mode).set_default(PaddingMode::ZEROS);
            ICRAFT_ATTR_FIELD(cut_scale);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Conv1d : public OpBase<Conv1d, Conv1dNode> {
    public:
        Conv1d() = default;

        XIR_DLL Conv1d(
            Value input,
            Value weights,
            Optional<Value> bias,
            int64_t stride_width,
            int64_t pad_left,
            int64_t pad_right,
            int64_t dilation_width,
            int64_t groups = 1,
            PaddingMode padding_mode = PaddingMode::ZEROS
        );
    };
}
</pre>
```
