# Program Listing for File align_axis.h



↰ [Return to documentation for file](file_icraft-xir_ops_align_axis.h.md#file-icraft-xir-ops-align-axis-h) (`icraft-xir\ops\align_axis.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class AlignedUnitNode : public NodeBase<AlignedUnitNode, Node> {
    public:
        Array<int64_t> index;
        Array<int64_t> unit;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL virtual bool reduceAccept(AlignedUnitNode* other, const ReduceVisitor& reduce) const;
    };

    class AlignedUnit : public HandleBase<AlignedUnit, Handle, AlignedUnitNode> {
    public:
        AlignedUnit() = default;

        XIR_DLL AlignedUnit(Array<int64_t> index, Array<int64_t> unit);
    };

    class AlignAxisNode : public OpNodeBase<AlignAxisNode> {
    public:
        Array<AlignedUnit> aligned_units;

        ICRAFT_DECLARE_ATTRS(AlignAxisNode) {
            ICRAFT_ATTR_FIELD(aligned_units);
        }

        XIR_DLL virtual void validate() const override;
    };

    class AlignAxis : public OpBase<AlignAxis, AlignAxisNode> {
    public:
        AlignAxis() = default;

        XIR_DLL AlignAxis(Value input, Array<AlignedUnit> aligned_units);
    };
}
</pre>
```
