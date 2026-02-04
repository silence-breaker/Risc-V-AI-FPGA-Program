# Program Listing for File data_type_attr.h



↰ [Return to documentation for file](file_icraft-xir_core_data_type_attr.h.md#file-icraft-xir-core-data-type-attr-h) (`icraft-xir\core\data_type_attr.h`)


```cpp
#pragma once
#include <icraft-xir/utils/wise_enum.h>

namespace icraft::xir {
     /*enum class DistrUnvalidValue {
        ZERO,
        NONE
     };*/
    WISE_ENUM_CLASS(DistrUnvalidValue, ZERO, NONE);

    class MergedAxisDistrNode : public NodeBase<MergedAxisDistrNode, Node> {
    public:
        Array<int64_t> merged_axis;
        Array<bool> valid_mask;
        DistrUnvalidValue uvalue;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(MergedAxisDistrNode* other, const ReduceVisitor& reduce) const;
    };

    class MergedAxisDistr : public HandleBase<MergedAxisDistr, Handle, MergedAxisDistrNode> {
    public:
        MergedAxisDistr() = default;

        XIR_DLL MergedAxisDistr(Array<int64_t> merged_axis, int64_t element_num = 0, bool init = true);

        XIR_DLL MergedAxisDistr& setMergedAxis(Array<int64_t> merged_axis);

        XIR_DLL MergedAxisDistr& append(int64_t element_num, bool valid);

        XIR_DLL MergedAxisDistr& append(const Array<bool>& other_valid_mask);

        XIR_DLL MergedAxisDistr& setValid(int64_t start, int64_t end);

        XIR_DLL MergedAxisDistr& setUnvalid(int64_t start, int64_t end);

        XIR_DLL MergedAxisDistr& setUValue(DistrUnvalidValue uvalue);

        XIR_DLL std::vector<std::tuple<uint64_t, uint64_t, bool>> allSections() const;

        XIR_DLL std::vector<std::pair<uint64_t, uint64_t>> validSections() const;

        XIR_DLL std::vector<std::pair<uint64_t, uint64_t>> unvalidSections() const;

        XIR_DLL uint64_t totalValidNum() const;

        XIR_DLL uint64_t totalUnvalidNum() const;

        XIR_DLL uint64_t totalNum() const;

        XIR_DLL bool isValid(int64_t index) const;
    };

    class NormratioArrayNode : public NodeBase<NormratioArrayNode, Node> {

    public:
        int64_t axis = -1;
        Array<float> data;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(NormratioArrayNode* other, const ReduceVisitor& reduce) const;
    };

    class NormratioArray : public HandleBase<NormratioArray, Handle, NormratioArrayNode> {
    public:
        XIR_DLL NormratioArray();

        XIR_DLL explicit NormratioArray(Array<float> data, int64_t axis = -1);

        XIR_DLL const float operator[](int64_t index) const;

        XIR_DLL NormratioArray& setAxis(int64_t axis);
    };

    class QuantizedScaleNode : public NodeBase<QuantizedScaleNode, Node> {
    public:
        float origin_scale;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(QuantizedScaleNode* other, const ReduceVisitor& reduce) const;
    };

    class QuantizedScale : public HandleBase<QuantizedScale, Handle, QuantizedScaleNode> {
    public:
        QuantizedScale() = default;

        XIR_DLL explicit QuantizedScale(float origin_scale);
    };

    class QuantizedScaleArray;

    class QuantizedScaleArrayNode : public NodeBase<QuantizedScaleArrayNode, Node> {

        friend class QuantizedScaleArray;

    public:
        int64_t axis = -1;
        Array<float> origin_scale;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(QuantizedScaleArrayNode* other, const ReduceVisitor& reduce) const;

    private:
        XIR_DLL virtual const QuantizedScale operator[](int64_t index) const;

        XIR_DLL virtual const QuantizedScale front() const;

        XIR_DLL virtual const QuantizedScale back() const;

        XIR_DLL virtual QuantizedScaleArray split(int64_t begin, int64_t end, int64_t stride = 1) const;
    };

    class QuantizedScaleArray : public HandleBase<QuantizedScaleArray, Handle, QuantizedScaleArrayNode> {
    public:
        XIR_DLL QuantizedScaleArray();

        XIR_DLL explicit QuantizedScaleArray(Array<float> origin_scale, int64_t axis = -1);

        XIR_DLL QuantizedScaleArray(QuantizedScaleArray lhs, QuantizedScaleArray rhs);

        XIR_DLL QuantizedScaleArray(const size_t n, const QuantizedScale& val);

        XIR_DLL const size_t size() const;

        XIR_DLL bool empty() const;

        XIR_DLL const QuantizedScale operator[](int64_t index) const;

        XIR_DLL const QuantizedScale front() const;

        XIR_DLL const QuantizedScale back() const;

        XIR_DLL QuantizedScaleArray split(int64_t begin, int64_t end, int64_t stride = 1) const;

        XIR_DLL QuantizedScaleArray& setAxis(int64_t axis);
    };

    class ExpQuantizedScaleNode : public NodeBase<ExpQuantizedScaleNode, QuantizedScaleNode> {
    public:
        int64_t m;
        int64_t exp;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(ExpQuantizedScaleNode* other, const ReduceVisitor& reduce) const;
    };

    class ExpQuantizedScale : public HandleBase<ExpQuantizedScale, QuantizedScale, ExpQuantizedScaleNode> {
    public:
        ExpQuantizedScale() = default;

        XIR_DLL ExpQuantizedScale(int64_t m, int64_t exp, float origin_scale);
    };

    class ExpQuantizedScaleArrayNode : public NodeBase<ExpQuantizedScaleArrayNode, QuantizedScaleArrayNode> {
    public:
        Array<int64_t> m;
        Array<int64_t> exp;

        friend class QuantizedScaleArrayNode;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(ExpQuantizedScaleArrayNode* other, const ReduceVisitor& reduce) const;

        XIR_DLL virtual const QuantizedScale operator[](int64_t index) const override;

        XIR_DLL virtual const QuantizedScale front() const override;

        XIR_DLL virtual const QuantizedScale back() const override;

        XIR_DLL virtual QuantizedScaleArray split(int64_t begin, int64_t end, int64_t stride = 1) const override;
    };

    class ExpQuantizedScaleArray : public HandleBase<ExpQuantizedScaleArray, QuantizedScaleArray, ExpQuantizedScaleArrayNode> {
    public:
        XIR_DLL ExpQuantizedScaleArray();

        XIR_DLL ExpQuantizedScaleArray(Array<int64_t> m, Array<int64_t> exp, Array<float> origin_scale, int64_t axis = -1);

        XIR_DLL ExpQuantizedScaleArray(QuantizedScaleArray lhs, QuantizedScaleArray rhs);

        XIR_DLL ExpQuantizedScaleArray(const size_t n, QuantizedScale val);

        XIR_DLL ExpQuantizedScaleArray& setAxis(int64_t axis);
    };
}
</pre>
```
