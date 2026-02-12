# Program Listing for File pixel_shuffle.h



↰ [Return to documentation for file](file_icraft-xir_ops_pixel_shuffle.h.md#file-icraft-xir-ops-pixel-shuffle-h) (`icraft-xir\ops\pixel_shuffle.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class PixelShuffleNode : public OpNodeBase<PixelShuffleNode> {
    public:
        int64_t upscale_factor;

        ICRAFT_DECLARE_ATTRS(PixelShuffleNode) {
            ICRAFT_ATTR_FIELD(upscale_factor).set_default(1).set_lower_bound(1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class PixelShuffle : public OpBase<PixelShuffle, PixelShuffleNode> {
    public:
        PixelShuffle() = default;

        XIR_DLL PixelShuffle(Value input, int64_t upscale_factor);
    };
}
</pre>
```
