# Program Listing for File log_sigmoid.h



↰ [Return to documentation for file](file_icraft-xir_ops_log_sigmoid.h.md#file-icraft-xir-ops-log-sigmoid-h) (`icraft-xir\ops\log_sigmoid.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class LogSigmoidNode : public OpNodeBase<LogSigmoidNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(LogSigmoidNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class LogSigmoid : public OpBase<LogSigmoid, LogSigmoidNode> {
    public:
        LogSigmoid() = default;

        XIR_DLL LogSigmoid(Value input);
    };
}
</pre>
```
