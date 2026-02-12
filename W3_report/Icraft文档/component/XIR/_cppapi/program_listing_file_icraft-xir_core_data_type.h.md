# Program Listing for File data_type.h



↰ [Return to documentation for file](file_icraft-xir_core_data_type.h.md#file-icraft-xir-core-data-type-h) (`icraft-xir\core\data_type.h`)


```cpp
#pragma once
#include <icraft-xir/core/layout.h>
#include <icraft-xir/core/data_type_attr.h>

namespace icraft::xir {

    class DataTypeNode : public NodeBase<DataTypeNode, Node> {
    public:
        virtual void accept(AttrVisitor& visitor) override {}

    private:
        virtual uint64_t bits() const { return 0; };

        virtual uint64_t numElements() const { return 0; };

        friend class DataType;
    };

    class ScalarType;
    class QuantizedScaleArray;

    class DataType : public VirtualBase<DataType, Handle, DataTypeNode> {
    public:
        XIR_DLL uint64_t bits() const;

        XIR_DLL uint64_t bytes() const;

        XIR_DLL uint64_t numElements() const;

        XIR_DLL Optional<NormratioArray> getNormratio() const;

        XIR_DLL bool setNormratio(Array<float> normratio);

        XIR_DLL bool setNormratio(NormratioArray normratio);

        XIR_DLL Optional<QuantizedScaleArray> getScale() const;

        XIR_DLL bool setScale(QuantizedScaleArray scale);

        XIR_DLL Optional<Array<int64_t>> getZeroPoints() const;

        XIR_DLL bool setZeroPoints(Array<int64_t> zero_points);

        XIR_DLL ScalarType getStorageType() const;

        XIR_DLL void setStorageType(ScalarType type);
    };

    class ScalarTypeNode : public NodeBase<ScalarTypeNode, DataTypeNode> {
    public:
        XIR_DLL virtual uint64_t numElements() const override;
    };

    class ScalarType : public VirtualBase<ScalarType, DataType, ScalarTypeNode> {
    public:
        XIR_DLL bool isSigned() const;

        XIR_DLL bool isSInt(uint64_t N) const;

        XIR_DLL bool isUInt(uint64_t N) const;

        XIR_DLL bool isSInt8() const;

        XIR_DLL bool isUInt8() const;

        XIR_DLL bool isSInt16() const;

        XIR_DLL bool isUInt16() const;

        XIR_DLL bool isSInt32() const;

        XIR_DLL bool isUInt32() const;

        XIR_DLL bool isSInt64() const;

        XIR_DLL bool isUInt64() const;

        XIR_DLL bool isBool() const;

        XIR_DLL bool isBF16() const;

        XIR_DLL bool isFPE7M8() const;

        XIR_DLL bool isFPE6M9() const;

        XIR_DLL bool isFP16() const;

        XIR_DLL bool isFP32() const;

        XIR_DLL bool isFP64() const;

        XIR_DLL bool isTF32() const;
    };

    class BoolTypeNode : public NodeBase<BoolTypeNode, ScalarTypeNode> {
    public:
        friend class BoolType;

    public:
        BoolTypeNode() = default;

        virtual void accept(AttrVisitor& visitor) override {};
    };

    class BoolType : public HandleBase<BoolType, ScalarType, BoolTypeNode> {
    public:
        BoolType() = default;
    };

    class IntegerTypeNode : public NodeBase<IntegerTypeNode, ScalarTypeNode> {
    public:
        bool sign;
        uint64_t ibits;

        friend class IntegerType;

    public:
        IntegerTypeNode() = default;
        IntegerTypeNode(bool sign, uint64_t ibits) : sign(sign), ibits(ibits) {}

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(IntegerTypeNode* other, const ReduceVisitor& reduce) const;

    private:
        XIR_DLL virtual uint64_t bits() const override;
    };

    class IntegerType : public HandleBase<IntegerType, ScalarType, IntegerTypeNode> {
    public:
        IntegerType() = default;

        XIR_DLL IntegerType(bool sign, int bits);

        XIR_DLL static IntegerType SInt(uint64_t N);

        XIR_DLL static IntegerType UInt(uint64_t N);

        XIR_DLL static IntegerType SInt8();

        XIR_DLL static IntegerType UInt8();

        XIR_DLL static IntegerType SInt16();

        XIR_DLL static IntegerType UInt16();

        XIR_DLL static IntegerType SInt32();

        XIR_DLL static IntegerType UInt32();

        XIR_DLL static IntegerType SInt64();

        XIR_DLL static IntegerType UInt64();
    };

    class FloatTypeNode : public NodeBase<FloatTypeNode, ScalarTypeNode> {
    public:
        int64_t emax;
        int64_t emin;
        uint64_t precision;
        uint64_t fbits;

        friend class FloatType;

    public:
        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(FloatTypeNode* other, const ReduceVisitor& reduce) const;

    private:
        XIR_DLL virtual uint64_t bits() const override;
    };

    class FloatType : public HandleBase<FloatType, ScalarType, FloatTypeNode> {
    public:
        class Semantics {
        public:
            int64_t emax;
            int64_t emin;
            uint64_t precision;
            uint64_t bits;

            XIR_DLL bool operator==(const Semantics& other);
        };

        FloatType() = default;

        XIR_DLL FloatType(int emax, int emin, int precision, int bits);

        FloatType(const Semantics& sem) : FloatType(sem.emax, sem.emin, sem.precision, sem.bits) {}

        XIR_DLL Semantics semantics() const;

        XIR_DLL static FloatType BF16();

        XIR_DLL static FloatType FPE7M8();

        XIR_DLL static FloatType FPE6M9();

        XIR_DLL static FloatType FP16();

        XIR_DLL static FloatType FP32();

        XIR_DLL static FloatType FP64();

        XIR_DLL static FloatType TF32();

        inline static const Semantics BF16_SEM = { 127, -126, 8, 16 };

        inline static const Semantics FPE7M8_SEM = { 63, -64, 9, 16 };
        inline static const Semantics FPE6M9_SEM = { 31, -32, 10, 16 };

        inline static const Semantics FP16_SEM = { 15, -14, 11, 16 };
        inline static const Semantics FP32_SEM = { 127, -126, 24, 32 };
        inline static const Semantics FP64_SEM = { 1023, -1022, 53, 64 };

        inline static const Semantics TF32_SEM = { 127, -126, 11, 19 };
    };

    class TensorTypeNode : public NodeBase<TensorTypeNode, DataTypeNode> {
    public:
        ScalarType element_dtype;
        Array<int64_t> shape;
        Layout layout;
        Array<MergedAxisDistr> merged_distrs;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(TensorTypeNode* other, const ReduceVisitor& reduce) const;

    private:
        XIR_DLL virtual uint64_t bits() const override;

        XIR_DLL virtual uint64_t numElements() const override;
    };

    class TensorType : public HandleBase<TensorType, DataType, TensorTypeNode> {
    public:
        TensorType() = default;

        XIR_DLL TensorType(ScalarType element_type, Array<int64_t> shape, Layout layout, Array<MergedAxisDistr> merged_distrs = {});

        XIR_DLL uint64_t dimSize(bool combine = false) const;

        XIR_DLL int64_t getDim(int64_t index, bool combine = false) const;

        XIR_DLL int64_t getDimByAxis(char c, bool combine = false) const;

        XIR_DLL TensorType& setDimByAxis(char c, int64_t dim);

        XIR_DLL TensorType& setElementDtype(ScalarType dtype);

        XIR_DLL TensorType& setShape(Array<int64_t> shape);

        XIR_DLL TensorType& setLayout(Layout layout);

        XIR_DLL TensorType& setMergedDistrs(Array<MergedAxisDistr> merged_distrs);

        XIR_DLL MergedAxisDistr createAddMergedDistr(Array<int64_t> merged_axis);

        XIR_DLL Optional<MergedAxisDistr> getMergedDistr(const Array<int64_t>& merged_axis) const;

        XIR_DLL std::optional<int64_t> getMergedDistrIndex(const Array<int64_t>& merged_axis) const;

        XIR_DLL TensorType& mutateMergedDistr(const Array<int64_t>& merged_axis, int64_t start, int64_t end, bool value);

        XIR_DLL bool hasNegativeDim() const;

        XIR_DLL bool isLayouted() const;

        XIR_DLL int64_t getChannel() const;

        XIR_DLL void validate() const;

    private:
        int64_t getNoneNuminDim(int64_t axis) const;
    };

    /* ---- 以下数据类型量化相关 ----*/

    class BaseQuantizedTypeNode : public NodeBase<BaseQuantizedTypeNode, ScalarTypeNode> {
    public:
        ScalarType storage_dtype;
        ScalarType expressed_dtype;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(BaseQuantizedTypeNode* other, const ReduceVisitor& reduce) const;
    };

    class BaseQuantizedType : public HandleBase<BaseQuantizedType, ScalarType, BaseQuantizedTypeNode> {};

    class CalibratedTypeNode : public NodeBase<CalibratedTypeNode, BaseQuantizedTypeNode> {
    public:
        Array<float> min;
        Array<float> max;
        Array<float> sat;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(CalibratedTypeNode* other, const ReduceVisitor& reduce) const;

        XIR_DLL virtual uint64_t bits() const override;
    };

    class CalibratedType : public HandleBase<CalibratedType, BaseQuantizedType, CalibratedTypeNode> {
    public:
        CalibratedType() = default;

        XIR_DLL CalibratedType(float min, float max, float sat, ScalarType storage_dtype, ScalarType expressed_dtype = FloatType::FP32());

        XIR_DLL CalibratedType(Array<float> min, Array<float> max, Array<float> sat, ScalarType storage_dtype, ScalarType expressed_dtype = FloatType::FP32());

        XIR_DLL CalibratedType(ScalarType storage_dtype, ScalarType expressed_dtype = FloatType::FP32())
            : CalibratedType(Array<float>(), Array<float>(), Array<float>(), std::move(storage_dtype), std::move(expressed_dtype)) {}
    };

    class NormalizedTypeNode : public NodeBase<NormalizedTypeNode, BaseQuantizedTypeNode> {
    public:
        NormratioArray normratio;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(NormalizedTypeNode* other, const ReduceVisitor& reduce) const;

        XIR_DLL virtual uint64_t bits() const override;
    };

    class NormalizedType : public HandleBase<NormalizedType, BaseQuantizedType, NormalizedTypeNode> {
    public:
        NormalizedType() = default;

        XIR_DLL NormalizedType(Array<float> normratio, ScalarType storage_dtype, ScalarType expressed_dtype = FloatType::FP32());

        XIR_DLL NormalizedType(NormratioArray normratio, ScalarType storage_dtype, ScalarType expressed_dtype = FloatType::FP32());
    };

    class QuantizedTypeNode : public NodeBase<QuantizedTypeNode, BaseQuantizedTypeNode> {
    public:
        QuantizedScaleArray scale;
        Array<int64_t> zero_points;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(QuantizedTypeNode* other, const ReduceVisitor& reduce) const;

        XIR_DLL virtual uint64_t bits() const override;
    };

    class QuantizedType : public HandleBase<QuantizedType, BaseQuantizedType, QuantizedTypeNode> {
    public:
        QuantizedType() = default;

        XIR_DLL QuantizedType(QuantizedScaleArray scale, ScalarType storage_dtype, ScalarType expressed_dtype = FloatType::FP32());

        XIR_DLL QuantizedType(
            QuantizedScaleArray scale,
            Array<int64_t> zero_points,
            ScalarType storage_dtype,
            ScalarType expressed_dtype = FloatType::FP32()
        );
    };

    class NormalizedQuantizedTypeNode : public NodeBase<NormalizedQuantizedTypeNode, QuantizedTypeNode> {
    public:
        NormratioArray normratio;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(NormalizedQuantizedTypeNode* other, const ReduceVisitor& reduce) const;
    };

    class NormalizedQuantizedType : public HandleBase<NormalizedQuantizedType, QuantizedType, NormalizedQuantizedTypeNode> {
    public:
        NormalizedQuantizedType() = default;

        XIR_DLL NormalizedQuantizedType(Array<float> normratio, QuantizedScaleArray scale,
            ScalarType storage_dtype, ScalarType expressed_dtype = FloatType::FP32());

        XIR_DLL NormalizedQuantizedType(NormratioArray normratio, QuantizedScaleArray scale,
            ScalarType storage_dtype, ScalarType expressed_dtype = FloatType::FP32());

        XIR_DLL NormalizedQuantizedType(NormalizedType nomalized, QuantizedScaleArray scale);

        XIR_DLL operator NormalizedType();
    };
}
</pre>
```
