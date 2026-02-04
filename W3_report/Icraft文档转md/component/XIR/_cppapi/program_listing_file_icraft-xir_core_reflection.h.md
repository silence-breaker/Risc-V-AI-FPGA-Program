# Program Listing for File reflection.h



↰ [Return to documentation for file](file_icraft-xir_core_reflection.h.md#file-icraft-xir-core-reflection-h) (`icraft-xir\core\reflection.h`)


```cpp
#pragma once
#include <icraft-xir/base/array.h>
#include <icraft-xir/base/dllexport.h>
#include <icraft-xir/base/type_trait.h>
#include <icraft-xir/core/node.h>
#include <icraft-xir/core/functor.h>
#include <icraft-xir/utils/wise_enum.h>

#include <cstdint>
#include <string>

namespace icraft::xir {

    class AttrVisitor {
    private:
        virtual void _visit(std::string_view key, float& value) = 0;
        virtual void _visit(std::string_view key, int64_t& value) = 0;
        virtual void _visit(std::string_view key, uint64_t& value) = 0;
        virtual void _visit(std::string_view key, int& value) = 0;
        virtual void _visit(std::string_view key, bool& value) = 0;
        virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "") = 0;
        virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo = TypeName<ObjectRef>()) = 0;

    public:
        template<typename E>
        void visit(std::string_view key, E& value) {
            if constexpr (std::is_base_of_v<ObjectRef, E>) {
                this->_visit(key, value, TypeName<E>());
            }
            else {
                this->_visit(key, value);
            }
        }

        template <typename  Enum, typename = typename std::enable_if_t<std::is_enum_v<Enum>>>
        void _visit(std::string_view key, Enum& value) {

            auto enum_name = std::string(wise_enum::to_string(value));
            this->_visit(key, enum_name, TypeName<Enum>());

            auto v = wise_enum::from_string<Enum>(enum_name.c_str());

            // 检查：
            ICRAFT_CHECK(v.has_value())
                .append("can't cast {}", enum_name);

            value = v.value();
        }

        virtual ~AttrVisitor() = default;
    };

    class Context;

    class ReduceVisitor {
    public:
        virtual const Context& getContext() const = 0;
        virtual bool operator()(const float& lhs, float& rhs) const = 0;
        virtual bool operator()(const int64_t& lhs, int64_t& rhs) const = 0;
        virtual bool operator()(const uint64_t& lhs, uint64_t& rhs) const = 0;
        virtual bool operator()(const int& lhs, int& rhs) const = 0;
        virtual bool operator()(const bool& lhs, bool& rhs) const = 0;
        virtual bool operator()(const std::string& lhs, std::string& rhs) const = 0;
        virtual bool operator()(const ObjectRef& lhs, ObjectRef& rhs) const = 0;

        template <typename ENum, typename = typename std::enable_if_t<std::is_enum_v<ENum>>>
        bool operator()(const ENum& lhs, ENum& rhs) const {
            return  operator()(reinterpret_cast<const int&>(lhs), reinterpret_cast<int&>(rhs));
        }

        virtual ~ReduceVisitor() = default;

        mutable int64_t clone_depth = 1;
    };

    class OperationNode;
    class TensorType;
    class Pass;

    class ReflectionTable {
    public:
        using FDefaultCreate = std::function<ObjectPtr<Node>()>;
        using FReprCreate = std::function<ObjectPtr<Node>(const std::string&)>;
        using FRepr = std::function<std::string(const Object*)>;
        using FTypeInfer = std::function<Array<TensorType>(const OperationNode*)>;

        XIR_DLL ObjectPtr<Node> createInitObject(std::string_view type_key) const;

        XIR_DLL ObjectPtr<Node> createReprObject(const std::string& repr_bytes) const;

        XIR_DLL std::string getReprBytes(const Node* self) const;

        XIR_DLL bool hasReprOf(const Node* self) const;

        XIR_DLL bool hasDefaultCreatorOf(const std::string& type_key) const;

        XIR_DLL Array<TensorType> typeInfer(const OperationNode* self) const;

        XIR_DLL bool hasTypeInfer(const OperationNode* self) const;

        XIR_DLL static ReflectionTable& Global();

        class Registry;

        template <typename T>
        inline Registry _register();

        /* ---- 以下方法只用于开发调试 ---- */
        XIR_DLL const std::unordered_map<std::string_view, FDefaultCreate>& _getDefaultCreateTable() const;
        XIR_DLL const std::unordered_map<std::string_view, FReprCreate>& _getReprCreateTable() const;
        XIR_DLL const std::unordered_map<std::string_view, FRepr>& _getReprTable() const;
        XIR_DLL const std::unordered_map<std::string_view, std::string_view>& _getAliasTable() const;
        XIR_DLL const std::unordered_map<std::string_view, std::string_view>& _getParentTable() const;
        XIR_DLL const std::unordered_map<std::string_view, std::vector<std::string_view>>& _getChildTable() const;
        XIR_DLL const std::unordered_map<
            std::string_view,
            std::unordered_map<std::string_view, FTypeInfer>
        >& _getTInferTable() const;

    private:
        std::unordered_map<std::string_view, FDefaultCreate> fdefault_create_;
        std::unordered_map<std::string_view, FReprCreate> frepr_create_;
        std::unordered_map<std::string_view, FRepr> frepr_;
        std::unordered_map<std::string_view, std::string_view> alias_;
        std::unordered_map<std::string_view, std::string_view> parent_table_;
        std::unordered_map<std::string_view, std::vector<std::string_view>> child_table_;
        std::unordered_map<
            std::string_view,
            std::unordered_map<std::string_view, FTypeInfer>
        > ftinfer_;
    };

    class ReflectionTable::Registry {
    public:
        Registry(ReflectionTable* parent, std::string_view type_key, std::string_view parent_type_key)
            : parent_(parent), type_key_(type_key), parent_type_key_(parent_type_key) {}

        template <typename TNode>
        Registry& set_creator(std::function<ObjectPtr<TNode>(const std::string&)> f) {

            auto fcreate = [=](const std::string& repr_bytes) {
                ObjectPtr<Node> node = f(repr_bytes);
                return node;
            };

            parent_->frepr_create_[type_key_] = fcreate;

            return *this;
        }

        template <typename TNode>
        Registry& set_default_creator(std::function<ObjectPtr<TNode>()> f) {

            auto fcreate = [=]() {
                ObjectPtr<Node> node = f();
                return node;
            };

            parent_->fdefault_create_[type_key_] = fcreate;
            parent_->parent_table_[type_key_] = parent_type_key_;

            // 如果是空的，新建一个
            if (parent_->child_table_.find(parent_type_key_) == parent_->child_table_.end()) {
                parent_->child_table_[parent_type_key_] = { type_key_ };
            }
            else {
                parent_->child_table_[parent_type_key_].push_back(type_key_);
            }

            return *this;
        }

        template <typename TNode>
        Registry& set_repr(std::function<std::string(const TNode*)> f) {  // NOLINT(*)

            auto frepr = [=](const Object* object) {
                auto node = static_cast<const TNode*>(object);
                return f(node);
            };

            parent_->frepr_[type_key_] = frepr;

            return *this;
        }

        XIR_DLL Registry& set_alias(std::string_view alias_name);

        template <typename TOpNode, typename TTarget>
        Registry& set_tinfer(std::function<Array<TensorType>(const TOpNode*)> f) {

            auto target = TTarget::NodeType::type_key;
            auto ftinter = [=](const OperationNode* op) {
                auto op_node = static_cast<const TOpNode*>(op);
                return f(op_node);
            };

            parent_->ftinfer_[type_key_][target] = ftinter;

            return *this;
        }

    private:
        ReflectionTable* parent_;
        std::string_view type_key_;
        std::string_view parent_type_key_;
    };

    template <typename T>
    inline ReflectionTable::Registry ReflectionTable::_register() {

        std::string_view type_key = T::type_key;
        std::string_view parent_type_key = T::ParentNode::type_key;

        return Registry(this, type_key, parent_type_key);
    }

    XIR_DLL std::string GetReprBytes(const Handle& ref);

    XIR_DLL bool HasReprOf(const Handle& ref);

    class Pass;

    class PassRegistry {
    public:
        class Manager;

        using FCreator = std::function<Pass()>;

        XIR_DLL PassRegistry& set_creator(FCreator f);

        XIR_DLL static PassRegistry& Register(const std::string& name, bool can_override = false);

        XIR_DLL static PassRegistry& Register(FCreator f, bool can_override = false);

        XIR_DLL static bool Remove(const std::string& name);

        XIR_DLL static std::optional<FCreator> Get(const std::string& name);

        XIR_DLL std::vector<std::string_view> ListNames();

    private:
        std::string name_;
        FCreator fcreator_;
    };
}

#define ICRAFT_REFLECTION_REG_VAR_DEF                                                       \
static ICRAFT_ATTRIBUTE_UNUSED ::icraft::xir::ReflectionTable::Registry __make_reflection

#define ICRAFT_REGISTER_REFLECTION_VTABLE(TypeName)                                         \
 ICRAFT_STR_CONCAT(ICRAFT_REFLECTION_REG_VAR_DEF, __COUNTER__) =                            \
      ::icraft::xir::ReflectionTable::Global()._register<TypeName>()

#define ICRAFT_REGISTER_NODE(NodeName)                                                      \
ICRAFT_REGISTER_REFLECTION_VTABLE(NodeName)                                                 \
    .set_default_creator<NodeName>([]() {                                                   \
        return ::icraft::xir::make_object<NodeName>();                                      \
    })

#define ICRAFT_PASS_REG_VAR_DEF                                                             \
static ICRAFT_ATTRIBUTE_UNUSED ::icraft::xir::PassRegistry __make_pass

#define ICRAFT_REGISTER_PASS(FuncName)                                                      \
 ICRAFT_STR_CONCAT(ICRAFT_PASS_REG_VAR_DEF, __COUNTER__) =                                  \
      ::icraft::xir::PassRegistry::Register(FuncName)
</pre>
```
