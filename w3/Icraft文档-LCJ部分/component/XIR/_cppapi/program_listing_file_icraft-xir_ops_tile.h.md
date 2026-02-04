# Program Listing for File tile.h



↰ [Return to documentation for file](file_icraft-xir_ops_tile.h.md#file-icraft-xir-ops-tile-h) (`icraft-xir\ops\tile.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class TileNode : public OpNodeBase<TileNode> {
    public:
        Array<int64_t> dims;

        ICRAFT_DECLARE_ATTRS(TileNode) {
            ICRAFT_ATTR_FIELD(dims);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Tile : public OpBase<Tile, TileNode> {
    public:
        Tile() = default;

        XIR_DLL Tile(Value input, Array<int64_t> dims);
    };
}
</pre>
```
