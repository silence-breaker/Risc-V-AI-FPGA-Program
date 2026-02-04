# Program Listing for File roll.h



↰ [Return to documentation for file](file_icraft-xir_ops_roll.h.md#file-icraft-xir-ops-roll-h) (`icraft-xir\ops\roll.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class RollNode : public OpNodeBase<RollNode> {
    public:
        Array<int64_t> shifts;
        Optional<Array<int64_t>> dims;

        ICRAFT_DECLARE_ATTRS(RollNode) {
            ICRAFT_ATTR_FIELD(shifts);
            ICRAFT_ATTR_FIELD(dims);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Roll : public OpBase<Roll, RollNode> {
    public:
        Roll() = default;

        XIR_DLL Roll(Value input, int64_t shift, std::optional<int64_t> dim = std::nullopt);

        XIR_DLL Roll(Value input, Array<int64_t> shifts, Optional<Array<int64_t>> dims = NullOpt);
    };
}
</pre>
```
