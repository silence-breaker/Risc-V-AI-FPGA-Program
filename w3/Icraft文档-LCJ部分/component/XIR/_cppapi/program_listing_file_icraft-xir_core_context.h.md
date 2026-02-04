# Program Listing for File context.h



↰ [Return to documentation for file](file_icraft-xir_core_context.h.md#file-icraft-xir-core-context-h) (`icraft-xir\core\context.h`)


```cpp
#pragma once
#include <unordered_map>
#include <icraft-xir/core/node.h>
#include <icraft-xir/core/reflection.h>

namespace icraft::xir {

    using OverriveFunc = std::function<bool(const Node*, Node*, const ReduceVisitor&)>;

    class ContextNode : public NodeBase<ContextNode, Node> {
    public:
        std::unordered_map<std::string_view, OverriveFunc> overrive_func_map;

        virtual void accept(AttrVisitor& visitor) override {}
    };

    class Context : public HandleBase<Context, Handle, ContextNode> {
    public:
        Context() = default;

        template <typename T>
        Context& setFunction(std::function<bool(const T*, T*, const ReduceVisitor&)> func) {

            if (func) {
                auto wrapped_func = [=](const Node* lhs, Node* rhs, const ReduceVisitor& reduce) {
                    return func(static_cast<const T*>(lhs), static_cast<T*>(rhs), reduce);
                };

                get_mutable()->overrive_func_map[T::type_key] = wrapped_func;
            }
            else {
                get_mutable()->overrive_func_map[T::type_key] = nullptr;
            }

            return *this;
        }

        template <typename T>
        OverriveFunc getFunction() const {
            return getFunction<T::type_key>();
        }

        OverriveFunc getFunction(std::string_view key) const {

            if ((*this)->overrive_func_map.count(key)) {
                return (*this)->overrive_func_map.at(key);
            }

            return nullptr;
        }
    };

    class CloneContextNode : public NodeBase<CloneContextNode, ContextNode> {
    public:
        virtual void accept(AttrVisitor& visitor) override {};

        inline static std::unordered_map<std::string_view, OverriveFunc> default_overrive_func_map;
    };

    class CloneContext : public HandleBase<CloneContext, Context, CloneContextNode> {
    public:
        XIR_DLL CloneContext();

        XIR_DLL static CloneContext Init();

        XIR_DLL static CloneContext& Current();

        XIR_DLL void _enterWithScope();
        XIR_DLL void _exitWithScope();
    };

    class EqualContextNode : public NodeBase<EqualContextNode, ContextNode> {
    public:
        virtual void accept(AttrVisitor& visitor) override {};

        inline static std::unordered_map<std::string_view, OverriveFunc> default_overrive_func_map;
    };

    class EqualContext : public HandleBase<EqualContext, Context, EqualContextNode> {
    public:
        XIR_DLL EqualContext();

        XIR_DLL static EqualContext Init();

        XIR_DLL static EqualContext& Current();

        XIR_DLL void _enterWithScope();
        XIR_DLL void _exitWithScope();
    };

    template <typename T, typename U>
    bool OverideFunction(std::function<bool(const T*, T*, const ReduceVisitor&)> func) {

        auto wrapped_func = [=](const Node* lhs, Node* rhs, const ReduceVisitor& reduce) {
            return func(static_cast<const T*>(lhs), static_cast<T*>(rhs), reduce);
        };

        U::default_overrive_func_map[T::type_key] = wrapped_func;
        return true;
    }
}

#define ICRAFT_OVERRIDE_EQUAL(T)                                                            \
     ICRAFT_STR_CONCAT(static auto equal, __COUNTER__) = icraft::xir::OverideFunction<T, icraft::xir::EqualContextNode>

#define ICRAFT_OVERRIDE_CLONE(T)                                                            \
     ICRAFT_STR_CONCAT(static auto clone, __COUNTER__) = icraft::xir::OverideFunction<T, icraft::xir::CloneContextNode>
</pre>
```
