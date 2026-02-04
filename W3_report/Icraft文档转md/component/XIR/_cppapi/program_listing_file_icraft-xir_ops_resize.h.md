# Program Listing for File resize.h



↰ [Return to documentation for file](file_icraft-xir_ops_resize.h.md#file-icraft-xir-ops-resize-h) (`icraft-xir\ops\resize.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    // enum class ResizeInterpolation {
    //  INTER_NEAREST,      ///< 最近邻插值
    //  INTER_LINEAR        ///< 双线性插值
    // };

    WISE_ENUM_CLASS(ResizeInterpolation, INTER_NEAREST, INTER_LINEAR);

    class ResizeNode : public OpNodeBase<ResizeNode> {
    public:
        Array<int64_t> dsize;
        ResizeInterpolation interpolation;

        ICRAFT_DECLARE_ATTRS(ResizeNode) {
            ICRAFT_ATTR_FIELD(dsize);
            ICRAFT_ATTR_FIELD(interpolation).set_default(ResizeInterpolation::INTER_LINEAR);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Resize : public OpBase<Resize, ResizeNode> {
    public:
        Resize() = default;

        XIR_DLL Resize(Value input, Array<int64_t> dsize, ResizeInterpolation interpolation = ResizeInterpolation::INTER_LINEAR);
    };
}
</pre>
```
