# Program Listing for File divide_scalar.h



↰ [Return to documentation for file](file_icraft-xir_ops_divide_scalar.h.md#file-icraft-xir-ops-divide-scalar-h) (`icraft-xir\ops\divide_scalar.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class DivideScalarNode : public OpNodeBase<DivideScalarNode> {
    public:
        // /**
        // * @enum      RoundingMode
        // * @brief 取整模式
        // */
        // enum class RoundingMode {
        //  NONE,       ///< 对应true divide
        //  TRUNC,      ///< 对应c语言风格的整除
        //  FLOOR       ///< 对应python风格"//"符合，或floor divide
        // };
        WISE_ENUM_CLASS_MEMBER(RoundingMode, NONE, TRUNC, FLOOR);

        float divisor;
        RoundingMode rounding_mode;

        ICRAFT_DECLARE_ATTRS(DivideScalarNode) {
            ICRAFT_ATTR_FIELD(divisor);
            ICRAFT_ATTR_FIELD(rounding_mode).set_default(RoundingMode::NONE);
        }

        XIR_DLL virtual void validate() const override;
    };

    class DivideScalar : public OpBase<DivideScalar, DivideScalarNode> {
    public:
        using RoundingMode = DivideScalarNode::RoundingMode;

        DivideScalar() = default;

        XIR_DLL DivideScalar(Value input, float divisor, RoundingMode rounding_mode = RoundingMode::NONE);
    };
}
</pre>
```
