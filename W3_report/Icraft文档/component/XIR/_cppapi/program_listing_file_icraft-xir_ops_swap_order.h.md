# Program Listing for File swap_order.h



↰ [Return to documentation for file](file_icraft-xir_ops_swap_order.h.md#file-icraft-xir-ops-swap-order-h) (`icraft-xir\ops\swap_order.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class SwapOrderNode : public OpNodeBase<SwapOrderNode> {
    public:
        Array<int64_t> order;
        int64_t axis;

        ICRAFT_DECLARE_ATTRS(SwapOrderNode) {
            ICRAFT_ATTR_FIELD(order);
            ICRAFT_ATTR_FIELD(axis).set_default(-1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class SwapOrder : public OpBase<SwapOrder, SwapOrderNode> {
    public:
        SwapOrder() = default;

        XIR_DLL SwapOrder(Value input, Array<int64_t> order, int64_t axis = -1);
    };
}
</pre>
```
