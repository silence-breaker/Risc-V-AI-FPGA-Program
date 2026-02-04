# Program Listing for File unknown.h



↰ [Return to documentation for file](file_icraft-xir_ops_unknown.h.md#file-icraft-xir-ops-unknown-h) (`icraft-xir\ops\unknown.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class UnknownNode : public OpNodeBase<UnknownNode> {
    public:
        std::string msg_info;
        std::string json_info;

        ICRAFT_DECLARE_ATTRS(UnknownNode) {
            ICRAFT_ATTR_FIELD(msg_info);
            ICRAFT_ATTR_FIELD(json_info);
        };

        XIR_DLL virtual void validate() const override;
    };

    class Unknown : public OpBase<Unknown, UnknownNode> {
    public:
        Unknown() = default;

        XIR_DLL Unknown(Array<Value> inputs, std::string info, std::string format);
    };
}
</pre>
```
