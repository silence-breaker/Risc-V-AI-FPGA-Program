# Program Listing for File operation.h



↰ [Return to documentation for file](file_icraft-xir_core_operation.h.md#file-icraft-xir-core-operation-h) (`icraft-xir\core\operation.h`)


```cpp
#pragma once
#include <map>
#include <set>
#include <icraft-xir/base/map.h>
#include <icraft-xir/base/string.h>
#include <icraft-xir/core/attrs.h>
#include <icraft-xir/core/data.h>
#include <icraft-xir/core/compile_target.h>
#include <icraft-utils/midware/path.hpp>

#define ICRAFT_DECLARE_ATTRS(TypeKey)                   \
  template <typename FVisit>                            \
  void _accept(FVisit& _fvisit)

#define ICRAFT_ATTR_FIELD(FieldName) _fvisit(#FieldName, FieldName)

namespace icraft::xir {

    class NetworkNode;
    class Network;

    class OperationNode : public NodeBase<OperationNode, Node> {
    public:
        int64_t op_id = -1;
        std::string name;
        Array<Value> inputs;
        Array<Value> outputs;
        CompileTarget compile_target;
        Map<String, ObjectRef> tags;

    private:
        std::map<int64_t, std::set<int64_t>> inputs_index_map_;

        const NetworkNode* network = nullptr;

        friend class Operation;
        template <typename, template <typename> typename...>
        friend class OpNodeBase;

    public:
        virtual void accept(AttrVisitor& visitor) override {}

        bool reduceAccept(OperationNode* other, const ReduceVisitor& reduce) const {

            // 克隆时考虑，但判断相等时不考虑
            for (auto&& [k, v] : this->inputs_index_map_) {
                other->inputs_index_map_[k] = v;
            }

            return reduce(this->op_id, other->op_id)
                && reduce(this->name, other->name)
                && reduce(this->inputs, other->inputs)
                && reduce(this->outputs, other->outputs)
                && reduce(this->compile_target, other->compile_target)
                && reduce(this->tags, other->tags);
        }
        virtual bool hasAttr(const std::string& key, const Any& value = Any()) const { return true; };

        virtual Any getAttr(const std::string& key) const { return 0; };

        #ifndef _BAREME
        virtual std::map<std::string_view, Any> attrs() const { return {}; };
        #endif

        virtual Array<Params> paramsAttrs(bool is_defined = false) const { return {}; };

        virtual void setAttr(const std::string& key, Any value) {};

        virtual void setAttrs(const std::unordered_map<std::string_view, Any>& attrs) {};

        virtual Array<AttrFieldInfo> listFieldInfo() const { return {}; };

        virtual void checkBound() const {};

        virtual void checkNull() const {};

        XIR_DLL virtual void validate() const;

        virtual bool isActivate() const { return false; }

        virtual ~OperationNode() noexcept {}

    protected:
        ICRAFT_DECLARE_ATTRS(OperationNode) {
            _fvisit("op_id", op_id);
            _fvisit("name", name);
            _fvisit("inputs", inputs);
            _fvisit("outputs", outputs);
            _fvisit("compile_target", compile_target);
            _fvisit("tags", tags);
        }
    };

    class Operation : public VirtualBase<Operation, Handle, OperationNode> {
    public:
        XIR_DLL Array<Value> nonParamsInputs() const;

        XIR_DLL Array<Params> paramsInputs() const;

        XIR_DLL Value operator[](int64_t index) const;

        XIR_DLL Operation& setCompileTarget(CompileTarget target);

        XIR_DLL Operation& setTag(const std::string& key, ObjectRef value);

        XIR_DLL std::optional<ObjectRef> getTag(const std::string& key) const;

        XIR_DLL bool removeTag(const std::string& key);

        XIR_DLL Operation& addInput(Value v);

        XIR_DLL Operation& removeInputById(int64_t v_id);

        XIR_DLL Operation& setInput(int64_t index, Value v);

        XIR_DLL Operation& insertInput(int64_t index, Value v);

        XIR_DLL Operation& replaceInput(Value old_input, Value new_input);

        XIR_DLL void connectInput(int64_t index, const Value& v);

        XIR_DLL Operation& setInputs(Array<Value> inputs);

        XIR_DLL Operation& clearInputs();

        XIR_DLL std::set<int64_t> getInputIndex(const Value& v) const;
        XIR_DLL std::set<int64_t> getInputIndex(int64_t v_id) const;

        XIR_DLL const Array<Value>& inferResults(bool override = false) const;

        XIR_DLL const Array<Value>& inferResults(const Array<TensorType>& dtypes, bool override = false) const;

        XIR_DLL Operation& setOutputs(Array<Value> outputs);

        XIR_DLL Operation& setOutput(int64_t index, Value v);

        XIR_DLL Operation& setName(std::string name);

        XIR_DLL Operation& setId(int64_t op_id);

        XIR_DLL Operation& bindNetwork(const Network& network);

        XIR_DLL bool isBoundToNetwork() const;

        XIR_DLL Network network() const;

        XIR_DLL uint64_t index() const;

        XIR_DLL Operation preOp() const;

        XIR_DLL Operation nextOp() const;

        XIR_DLL bool isFirstOpOfNetwork() const;

        XIR_DLL bool isLastOpOfNetwork() const;

        XIR_DLL Array<Operation> producers(bool sorted = false) const;

        XIR_DLL Array<Operation> consumers(bool sorted = false) const;

#if !defined(_BAREME)
        XIR_DLL static Operation Create(const std::string& name, const std::filesystem::path& dll_file = {});
#endif
        XIR_DLL static Operation Create(const std::string& name, const icraft::midware::path& dll_file = {});
        XIR_DLL void setAttr(const std::string& key, Any value);

    private:
        void unRefPreValues();

        void reRefCurValues();

        void changeInputIndex(int64_t old_id, int64_t new_id);
        void setInputIndex(int64_t index, int64_t new_id);
        void setInputIndex(std::set<int64_t> index, int64_t new_id);

        void removeInputIndex(int64_t v_id);

        void clearInputIndex();

        friend class Value;
        friend class Network;
    };

    template <typename OpType>
    class OpTrait {};

    template <typename OpType>
    class IsActivate : public OpTrait<OpType> {};

    template <typename ConcreteType, template <typename> typename... Traits>
    class OpNodeBase : public NodeBase<ConcreteType, OperationNode>, public Traits<ConcreteType>... {
    public:
        using ParentNode = OperationNode;

        OpNodeBase() {

            auto visitor = AttrInitVisitor(ConcreteType::type_key);
            self()->_accept(visitor);
            this->compile_target = HostTarget::Init();
        }

        virtual void accept(AttrVisitor& v) override {

            AttrNormalVisitor visitor(v);
            self()->_accept(visitor);
            this->_accept(visitor);
        }

        bool reduceAccept(ConcreteType* other, const ReduceVisitor& reduce) const {

            auto map_visitor = AttrPtrMapVisitor();
            other->_accept(map_visitor);
            auto visitor = AttrReduceVisitor(map_visitor._attrs, reduce);
            self()->_accept(visitor);

            return visitor.result;
        }

        virtual bool hasAttr(const std::string& key, const Any& value = Any()) const override {
            auto visitor = AttrExistVisitor{ key, value };
            self()->_accept(visitor);
            return visitor._exist;
        }

        virtual Any getAttr(const std::string& key) const override {
            auto visitor = AttrGetVisitor{ key };
            self()->_accept(visitor);
            return visitor._value;
        }

        #ifndef _BAREME
        virtual std::map<std::string_view, Any> attrs() const {
            auto visitor = AttrMapVisitor();
            self()->_accept(visitor);
            return visitor._attrs;
        }
        #endif

        virtual Array<Params> paramsAttrs(bool is_defined = false) const {
            auto visitor = VAttrMapVisitor<Params>();
            self()->_accept(visitor);

            Array<Params> ans;

            for (auto&& [k, v] : visitor._attrs) {
                for (auto&& p : v) {
                    if (is_defined == false || p.defined()) {
                        ans.push_back(p);
                    }
                }
            }

            return ans;
        }

        virtual void setAttr(const std::string& key, Any value) override {
            auto visitor = AttrSetVisitor{ key, value };
            self()->_accept(visitor);

            // 检查：
            ICRAFT_CHECK(visitor._exist).append("attr key: {} does not exist!", key);
        }

        virtual void setAttrs(const std::unordered_map<std::string_view, Any>& attrs) override {
            auto visitor = AttrCloneVisitor(attrs);
            self()->_accept(visitor);
        }

        virtual Array<AttrFieldInfo> listFieldInfo() const override {

            AttrDocVisitor visitor;
            self()->_accept(visitor);

            return visitor._fields;
        }

        virtual void checkBound() const override {
            auto visitor = AttrBoundVisitor(ConcreteType::type_key);
            self()->_accept(visitor);
        }

        virtual void checkNull() const override {
            auto visitor = AttrNullVisitor();
            self()->_accept(visitor);
        }

        template <typename T,
            typename = typename std::enable_if_t<std::is_base_of_v<OpTrait<ConcreteType>, T>>>
            constexpr static bool HasOpTrait() {

            return std::is_base_of_v<T, ConcreteType>;
        }

        virtual bool isActivate() const override { using ActivateTrait = IsActivate<ConcreteType>; return HasOpTrait<ActivateTrait>(); }

    private:
        ConcreteType* self() const {
            return const_cast<ConcreteType*>(static_cast<const ConcreteType*>(this));
        }
    };

    template <typename OpType, typename OpNodeType>
    class OpBase : public HandleBase<OpType, Operation, OpNodeType> {
    public:
        using HandleBase<OpType, Operation, OpNodeType>::get_mutable;
    };
}

#define ICRAFT_REGISTER_OP_NODE(OpNodeName)                                                 \
ICRAFT_REGISTER_NODE(OpNodeName)

#define ICRAFT_REGISTER_TINFER(OpNodeName, TargetType, F)                                   \
ICRAFT_REGISTER_REFLECTION_VTABLE(OpNodeName).set_tinfer<OpNodeName, TargetType>(F);

namespace icraft::xir {

    class InputNode : public OpNodeBase<InputNode> {
    public:
        ICRAFT_DECLARE_ATTRS(InputNode) {}
    };

    class Input : public OpBase<Input, InputNode> {
    public:
        Input() = default;

        XIR_DLL Input(const Array<TensorType>& dtypes);

        template <typename... Args,
            typename = typename std::enable_if_t<(std::is_base_of_v<TensorType, Args> && ...)>>
        Input(Args... dtypes) : Input(Array<TensorType>{ std::forward<Args>(dtypes)... }) {}
    };

    class OutputNode : public OpNodeBase<OutputNode> {
    public:
        ICRAFT_DECLARE_ATTRS(OutputNode) {}
    };

    class Output : public OpBase<Output, OutputNode> {
    public:
        Output() = default;

        XIR_DLL Output(Array<Value> values);

        template <typename... Args>
        Output(Args... values) : Output(Array<Value>{ std::forward<Args>(values)... }) {}
    };
}
</pre>
```
