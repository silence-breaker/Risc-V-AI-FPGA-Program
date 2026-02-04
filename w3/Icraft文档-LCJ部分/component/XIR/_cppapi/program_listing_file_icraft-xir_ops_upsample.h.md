# Program Listing for File upsample.h



↰ [Return to documentation for file](file_icraft-xir_ops_upsample.h.md#file-icraft-xir-ops-upsample-h) (`icraft-xir\ops\upsample.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class UpsampleNode : public OpNodeBase<UpsampleNode> {
    public:
        // enum class Interpolation {
        //  NEAREST,        ///< 最近邻插值
        //  BILINEAR,       ///< 双线性插值
        //  BICUBIC         ///< 双三次插值
        // };
        WISE_ENUM_CLASS_MEMBER(Interpolation, NEAREST, BILINEAR, BICUBIC);

        int64_t height;
        int64_t width;
        Interpolation interpolation;
        bool align_corners;

        ICRAFT_DECLARE_ATTRS(UpsampleNode) {
            ICRAFT_ATTR_FIELD(height).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(width).set_lower_bound(1);
            ICRAFT_ATTR_FIELD(interpolation).set_default(Interpolation::NEAREST);
            ICRAFT_ATTR_FIELD(align_corners).set_default(false);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Upsample : public OpBase<Upsample, UpsampleNode> {
    public:
        using Interpolation = UpsampleNode::Interpolation;

        Upsample() = default;

        XIR_DLL Upsample(
            Value input,
            int64_t height,
            int64_t width,
            Interpolation interpolation = Interpolation::NEAREST,
            bool align_corners = false
        );
    };
}
</pre>
```
