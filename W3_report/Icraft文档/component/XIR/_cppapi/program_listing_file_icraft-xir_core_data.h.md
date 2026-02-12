# Program Listing for File data.h



↰ [Return to documentation for file](file_icraft-xir_core_data.h.md#file-icraft-xir-core-data-h) (`icraft-xir\core\data.h`)


```cpp
#pragma once
#include <icraft-xir/base/array.h>
#include <icraft-xir/base/map.h>
#include <icraft-xir/base/string.h>
#include <icraft-xir/core/data_type.h>
#include <icraft-xir/core/mem_type.h>

namespace icraft::xir {

    class DataNode : public NodeBase<DataNode, Node> {
    public:
        DataType dtype;
        MemType mtype;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(DataNode* other, const ReduceVisitor& reduce) const;

    private:
        virtual uint64_t storageBits() const { return 0; };

        friend class Data;
    };

    class Data : public VirtualBase<Data, Handle, DataNode> {
    public:
        Data() = default;

        XIR_DLL Data& setDType(DataType dtype);

        XIR_DLL Data& setMType(MemType mtype);

        XIR_DLL uint64_t storageBits() const;

        XIR_DLL uint64_t storageBytes() const;
    };

    class ScalarImmNode : public NodeBase<ScalarImmNode, DataNode> {
    public:
        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

    private:
        XIR_DLL virtual uint64_t storageBits() const override;
    };

    class ScalarImm : public HandleBase<ScalarImm, Data, ScalarImmNode> {
    public:
        ScalarImm() = default;

        XIR_DLL ScalarImm(int64_t value);

        XIR_DLL ScalarImm(float value);

        XIR_DLL ScalarType scalarType() const;
    };

    class BoolNode : public NodeBase<BoolNode, ScalarImmNode> {
    public:
        bool value;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(BoolNode* other, const ReduceVisitor& reduce) const;
    };

    class Bool : public HandleBase<Bool, ScalarImm, BoolNode> {
    public:
        Bool() = default;

        XIR_DLL Bool(bool value);

        XIR_DLL Bool operator!() const;

        XIR_DLL operator bool() const;
    };

    inline Bool operator||(const Bool& a, bool b) { return Bool(a.operator bool() || b); }
    inline Bool operator||(bool a, const Bool& b) { return Bool(a || b.operator bool()); }
    inline Bool operator||(const Bool& a, const Bool& b) {
        return Bool(a.operator bool() || b.operator bool());
    }

    inline Bool operator&&(const Bool& a, bool b) { return Bool(a.operator bool() && b); }
    inline Bool operator&&(bool a, const Bool& b) { return Bool(a && b.operator bool()); }
    inline Bool operator&&(const Bool& a, const Bool& b) {
        return Bool(a.operator bool() && b.operator bool());
    }

    inline bool operator==(const Bool& a, bool b) { return a.operator bool() == b; }
    inline bool operator==(bool a, const Bool& b) { return a == b.operator bool(); }
    inline bool operator==(const Bool& a, const Bool& b) {
        return a.operator bool() == b.operator bool();
    }

    class IntImmNode : public NodeBase<IntImmNode, ScalarImmNode> {
    public:
        int64_t value;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(IntImmNode* other, const ReduceVisitor& reduce) const;
    };

    class IntImm : public HandleBase<IntImm, ScalarImm, IntImmNode> {
    public:
        IntImm() = default;

        XIR_DLL IntImm(int64_t value, ScalarType dtype, MemType mtype = HostMem::Init());

        IntImm(int64_t value, MemType mtype = HostMem::Init()) : IntImm(value, IntegerType::SInt64(), mtype) {}

        XIR_DLL operator int64_t() const;
    };

    class FloatImmNode : public NodeBase<FloatImmNode, ScalarImmNode> {
    public:
        float value;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(FloatImmNode* other, const ReduceVisitor& reduce) const;
    };

    class FloatImm : public HandleBase<FloatImm, ScalarImm, FloatImmNode> {
    public:
        FloatImm() = default;

        XIR_DLL FloatImm(float value, ScalarType dtype, MemType mtype = HostMem::Init());

        FloatImm(float value, MemType mtype = HostMem::Init()) : FloatImm(value, FloatType::FP64(), mtype) {}

        XIR_DLL operator float() const;
    };

    class OperationNode;
    class Operation;
    class Network;

    class ValueNode : public NodeBase<ValueNode, DataNode> {
    public:
        int64_t v_id = -1;
        std::string name;

        Map<String, ObjectRef> tags;

        uint64_t _index;
        const OperationNode* _op = nullptr;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(ValueNode* other, const ReduceVisitor& reduce) const;

    private:
        XIR_DLL virtual uint64_t storageBits() const override;
    };

    class Value : public HandleBase<Value, Data, ValueNode> {
    public:
        Value() = default;

        XIR_DLL Value(std::string name, TensorType dtype, MemType mtype = HostMem::Init());

        Value(TensorType dtype, MemType mtype = HostMem::Init()) : Value("", dtype, mtype) {}

        XIR_DLL TensorType tensorType() const;

        XIR_DLL bool isParams() const;

        XIR_DLL Value& setId(int64_t v_id);

        XIR_DLL Value& setName(std::string name);

        XIR_DLL Value& setTag(const std::string& key, ObjectRef value);

        XIR_DLL Value& setTags(Map<String, ObjectRef> tags);

        XIR_DLL std::optional<ObjectRef> getTag(const std::string& key) const;

        XIR_DLL bool removeTag(const std::string& key);

        XIR_DLL Value& bindOp(const Operation& op, uint64_t index);

        XIR_DLL bool isBoundToOp() const;

        XIR_DLL Operation op() const;

        XIR_DLL uint64_t index() const;

        XIR_DLL bool isBoundToNetwork() const;

        XIR_DLL Network network() const;

        XIR_DLL Array<Operation> getUsesOp() const;

        XIR_DLL size_t getUsesNum() const;

        XIR_DLL void validate() const;

    protected:
        XIR_DLL static int64_t genId();
    };

    class NetworkNode;

    class ParamsNode : public NodeBase<ParamsNode, ValueNode> {
    public:
        std::shared_ptr<void> _data = nullptr;
        bool _lazy = false;
        bool _allow_no_data = false;
        const NetworkNode* network = nullptr;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(ParamsNode* other, const ReduceVisitor& reduce) const;
    };

    class Params : public HandleBase<Params, Value, ParamsNode> {
    public:
        Params() = default;

        template <typename T, typename = typename std::enable_if_t<std::is_pod_v<T>>>
        Params(std::shared_ptr<T[]> data, std::string name, TensorType dtype, MemType mtype = HostMem::Init()) {

            auto node = make_object<ParamsNode>();

            node->_data = data;
            node->v_id = genId();
            node->name = std::move(name);
            node->dtype = std::move(dtype);
            node->mtype = std::move(mtype);

            data_ = std::move(node);
        }

        Params(std::string name, TensorType dtype, MemType mtype = HostMem::Init())
            : Params(std::shared_ptr<char[]>(), std::move(name), std::move(dtype), std::move(mtype)) {}

        Params(TensorType dtype) : Params(std::shared_ptr<char[]>(), "", std::move(dtype)) {}

        template <typename T, typename = typename std::enable_if_t<std::is_pod_v<T>>>
        Params& setData(std::shared_ptr<T[]> data) {
            get_mutable()->_data = data;
            return *this;
        }

        template <typename T, typename = typename std::enable_if_t<std::is_pod_v<T>>>
        Params& setData(std::unique_ptr<T[]> data) {
            get_mutable()->_data = std::move(data);
            return *this;
        }

        XIR_DLL Params& setData(nullptr_t data);

        XIR_DLL uint64_t copyData(void* data);

        template <typename T, typename = typename std::enable_if_t<std::is_pod_v<T>>>
        std::shared_ptr<T[]> data() const {
            return std::static_pointer_cast<T[]>((*this)->_data);
        }

        XIR_DLL Params& clearData();

        XIR_DLL Params& setLazy(bool lazy);

        XIR_DLL bool isLazyLoaded() const;

        XIR_DLL Params& setAllowNoData(bool allow_no_data);

        XIR_DLL bool isAllowNoData() const;

        XIR_DLL Params& bindNetwork(const Network& network);

        XIR_DLL void load();

        template <typename T, typename = typename std::enable_if_t<std::is_pod_v<T>>>
        Params& fill(std::function<T(uint64_t)> f) {

            auto dtype = this->tensorType();
            auto etype = dtype->element_dtype;
            auto tbits = sizeof(T) * 8;
            auto sbits = (*this)->mtype->getStorageBits(etype.bits());

            // 检查：
            ICRAFT_CHECK(tbits == sbits)
                .append("sizeof(T) not match element_dtype, {} vs. {}", tbits, sbits);

            auto num_elements = dtype.numElements();
            auto filled_data = new T[num_elements];

            for (uint64_t i = 0; i < num_elements; i++) {
                filled_data[i] = f(i);
            }

            get_mutable()->_data = std::shared_ptr<T[]>(filled_data);

            return *this;
        }

        XIR_DLL bool hasData() const;
    };
}
</pre>
```
