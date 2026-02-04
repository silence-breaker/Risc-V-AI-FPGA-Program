# Program Listing for File log.h



↰ [Return to documentation for file](file_icraft-xir_ops_log.h.md#file-icraft-xir-ops-log-h) (`icraft-xir\ops\log.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class LogNode : public OpNodeBase<LogNode, IsActivate> {
    public:
        ICRAFT_DECLARE_ATTRS(LogNode) {}

        XIR_DLL virtual void validate() const override;
    };

    class Log : public OpBase<Log, LogNode> {
    public:
        Log() = default;

        XIR_DLL Log(Value input);
    };
}
</pre>
```
