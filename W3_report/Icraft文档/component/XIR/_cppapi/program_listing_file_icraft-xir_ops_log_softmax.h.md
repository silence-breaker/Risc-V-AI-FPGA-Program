# Program Listing for File log_softmax.h



↰ [Return to documentation for file](file_icraft-xir_ops_log_softmax.h.md#file-icraft-xir-ops-log-softmax-h) (`icraft-xir\ops\log_softmax.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class LogSoftmaxNode : public OpNodeBase<LogSoftmaxNode> {
    public:
        int64_t axis;

        ICRAFT_DECLARE_ATTRS(LogSoftmaxNode) {
            ICRAFT_ATTR_FIELD(axis).set_default(-1);
        }

        XIR_DLL virtual void validate() const override;
    };

    class LogSoftmax : public OpBase<LogSoftmax, LogSoftmaxNode> {
    public:
        LogSoftmax() = default;

        XIR_DLL LogSoftmax(Value input, int64_t axis = -1);
    };
}
</pre>
```
