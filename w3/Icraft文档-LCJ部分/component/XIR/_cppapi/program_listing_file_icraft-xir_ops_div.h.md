# Program Listing for File div.h



↰ [Return to documentation for file](file_icraft-xir_ops_div.h.md#file-icraft-xir-ops-div-h) (`icraft-xir\ops\div.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class DivNode : public OpNodeBase<DivNode> {
    public:
        /*  enum class Mode {
            NONE,       ///<
            TRUNC,      ///<
            FLOOR       ///<
        };*/
        WISE_ENUM_CLASS_MEMBER(Mode, NONE, TRUNC, FLOOR);

        Mode rounding_mode;

        ICRAFT_DECLARE_ATTRS(DivNode) {
            ICRAFT_ATTR_FIELD(rounding_mode).set_default(Mode::NONE);
        }

        XIR_DLL virtual void validate() const override;
    };

    class Div : public OpBase<Div, DivNode> {
    public:
        using Mode = DivNode::Mode;

        Div() = default;

        XIR_DLL Div(Value lhs, Value rhs, Mode rounding_mode = Mode::NONE);
    };
}
</pre>
```
