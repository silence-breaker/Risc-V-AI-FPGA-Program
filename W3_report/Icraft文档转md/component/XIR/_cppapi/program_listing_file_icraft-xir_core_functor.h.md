# Program Listing for File functor.h



↰ [Return to documentation for file](file_icraft-xir_core_functor.h.md#file-icraft-xir-core-functor-h) (`icraft-xir\core\functor.h`)


```cpp
#pragma once
#include <functional>
#include <unordered_map>
#include <icraft-utils/logging.h>

namespace icraft::xir {

    template <typename FType>
    class NodeFunctor;

    template <typename R, typename H, typename... Args>
    class NodeFunctor<R(H n, Args...)> {
    public:
        using FType = std::function<R(H n, Args... args)>;
        using result_type = R;

    private:
        using TSelf = NodeFunctor<R(H n, Args...)>;
        std::unordered_map<std::string_view, FType> func_;

    public:
        bool canDispatch(H n) const {
            auto type_key = n->typeKey();
            return func_.find(type_key) != func_.end() && func_.at(type_key) != nullptr;
        }

        R operator()(H n, Args... args) const {
            if (!canDispatch(n)) {
                ICRAFT_LOG(EXCEPT) << "NodeFunctor calls un-registered function on type " << n->typeKey();
            }
            return func_.at(n->typeKey())(n, std::forward<Args>(args)...);
        }

        template <typename TNode>
        TSelf& setDispatch(std::function<R(H n, Args... args)> f) {  // NOLINT(*)
            auto type_key = TNode::NodeType::type_key;
            func_[type_key] = f;
            return *this;
        }

        template <typename TNode>
        TSelf& clearDispatch() {  // NOLINT(*)
            auto type_key = TNode::type_key;
            func_.erase(type_key);
            return *this;
        }

        const std::unordered_map<std::string_view, FType>& _getFuncMap() const {
            return func_;
        }
    };

    template <typename ConcreteType, typename HandleType, typename FType>
    class TraitFunctor;

    template <typename ConcreteType, typename HandleType, typename R, typename... Args>
    class TraitFunctor<ConcreteType, HandleType, R(const HandleType&, Args...)> {
    public:
        TraitFunctor(const TraitFunctor&) = default;

        TraitFunctor(TraitFunctor&&) = default;

        TraitFunctor& operator=(const TraitFunctor&) = default;

        TraitFunctor& operator=(TraitFunctor&&) = default;

        explicit TraitFunctor(HandleType t) : container(std::move(t)) {}

        using FunctorType = NodeFunctor<R(const HandleType&, Args...)>;

    private:
        HandleType container;

    public:
        template <typename TNode>
        static bool Impl(std::function<R(const TNode& n, Args... args)> f) {
            auto func = [=](const HandleType& n, Args... args) -> R {
                auto& t = static_cast<const TNode&>(n);
                return f(t, std::forward<Args>(args)...);
            };
            Accessor::VTable().template setDispatch<TNode>(func);
            return true;
        }

        static bool HasImplOf(const HandleType& n) {
            return Accessor::VTable().canDispatch(n);
        }

        bool hasImpl() {
            return Accessor::VTable().canDispatch(container);
        }

        R operator()(Args... args) const {
            return Accessor::VTable()(container, std::forward<Args>(args)...);
        }

        static const auto& _GetFuncMap() {
            return Accessor::VTable()._getFuncMap();
        }

    private:
        struct Accessor : ConcreteType {
            using ConcreteType::VTable;
        };
        static FunctorType& VTable() {
            static FunctorType vtable;
            return vtable;
        }
    };

    template <typename ConcreteType, typename FType>
    class OpTraitFunctor;

    class Operation;

    template <typename ConcreteType, typename R, typename... Args>
    class OpTraitFunctor<ConcreteType, R(const Operation& op, Args...)>
        : public TraitFunctor<ConcreteType, Operation, R(const Operation& op, Args...)> {
    public:
        using TParent = TraitFunctor<ConcreteType, Operation, R(const Operation& op, Args...)>;
        OpTraitFunctor(const OpTraitFunctor&) = default;
        OpTraitFunctor(OpTraitFunctor&&) = default;
        OpTraitFunctor& operator=(const OpTraitFunctor&) = default;
        OpTraitFunctor& operator=(OpTraitFunctor&&) = default;

        template <typename T>
        OpTraitFunctor(T t) : TParent(std::move(t)) {}
    };

#define ICRAFT_TRAIT_IMPL_VAR_DEF \
  static ICRAFT_ATTRIBUTE_UNUSED auto __make_functor_impl

#define ICRAFT_IMPL_FUNCTOR(FunctorType) \
ICRAFT_STR_CONCAT(ICRAFT_TRAIT_IMPL_VAR_DEF, __COUNTER__) = FunctorType::Impl
}
</pre>
```
