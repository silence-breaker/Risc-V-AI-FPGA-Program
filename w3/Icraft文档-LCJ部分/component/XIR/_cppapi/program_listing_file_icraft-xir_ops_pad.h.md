# Program Listing for File pad.h



↰ [Return to documentation for file](file_icraft-xir_ops_pad.h.md#file-icraft-xir-ops-pad-h) (`icraft-xir\ops\pad.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class PadNode : public OpNodeBase<PadNode> {
    public:

        // enum class Mode {
        //  CONSTANT,       ///< 常量
        //  REFLECTION,     ///< 反射
        //  REPLICATION,    ///< 复制
        //  SYMMETRIC       ///< 对称
        // };
        WISE_ENUM_CLASS_MEMBER(Mode, CONSTANT, REFLECTION, REPLICATION, SYMMETRIC);

        Array<int64_t> padding;
        Mode mode;
        ScalarImm value;

        ICRAFT_DECLARE_ATTRS(PadNode) {
            ICRAFT_ATTR_FIELD(padding);
            ICRAFT_ATTR_FIELD(mode).set_default(Mode::CONSTANT);
            ICRAFT_ATTR_FIELD(value).set_default(IntImm(0));
        }

        XIR_DLL virtual void validate() const override;
    };

    class Pad : public OpBase<Pad, PadNode> {
    public:
        using Mode = PadNode::Mode;

        Pad() = default;

        XIR_DLL Pad(Value input, Array<int64_t> padding, Mode mode = Mode::CONSTANT, ScalarImm value = IntImm(0));
    };
}
</pre>
```
