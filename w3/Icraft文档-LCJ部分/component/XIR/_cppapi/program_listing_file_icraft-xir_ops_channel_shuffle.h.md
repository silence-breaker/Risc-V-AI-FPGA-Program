# Program Listing for File channel_shuffle.h



↰ [Return to documentation for file](file_icraft-xir_ops_channel_shuffle.h.md#file-icraft-xir-ops-channel-shuffle-h) (`icraft-xir\ops\channel_shuffle.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class ChannelShuffleNode : public OpNodeBase<ChannelShuffleNode> {
    public:
        int64_t groups;

        ICRAFT_DECLARE_ATTRS(ChannelShuffleNode) {
            ICRAFT_ATTR_FIELD(groups).set_lower_bound(1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class ChannelShuffle : public OpBase<ChannelShuffle, ChannelShuffleNode> {
    public:
        ChannelShuffle() = default;

        XIR_DLL ChannelShuffle(Value input, int64_t groups);
    };
}
</pre>
```
