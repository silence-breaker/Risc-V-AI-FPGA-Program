# Program Listing for File any.h



↰ [Return to documentation for file](file_icraft-xir_base_any.h.md#file-icraft-xir-base-any-h) (`icraft-xir\base\any.h`)


```cpp
#pragma once
#include <any>
#include <optional>
#include <icraft-utils/logging.h>
#include <icraft-xir/base/object.h>
#include <icraft-xir/base/type_trait.h>

namespace icraft::xir {

    class AnyNode : public Object {
    public:
        using ContainerType = std::any;

        XIR_DLL std::string_view type_name() const;

        template <typename T>
        void emplace(T&& v) {
            data_ = v;
        }

        template <typename U>
        U cast() {
            try {
                return std::any_cast<U>(data_);
            }
            catch (std::exception& e) {
                ICRAFT_LOG(EXCEPT).append("cast type mismatch, source type is {}, but target type is {}",
                    type_name(), TypeName<U>());

                return std::any_cast<U>(data_);
            }
        }

        template <typename U>
        std::optional<U> cast_opt() {
            try {
                return std::any_cast<U>(data_);
            }
            catch (std::exception& e) {
                return std::nullopt;
            }
        }

        XIR_DLL bool has_value() const;

    private:
        ContainerType data_;
        friend class Any;
    };

    class Any : public ObjectRef {
    public:
        using NodeType = AnyNode;

        XIR_DLL Any();

        template <typename T>
        Any(T v) : Any() {
            getAnyNode()->emplace(std::move(v));
        }

        XIR_DLL explicit Any(std::any v);

        XIR_DLL std::string_view type_name() const;

        template <typename U>
        U cast() const {
            return getAnyNode()->cast<U>();
        }

        template <typename U>
        U cast() {
            return getAnyNode()->cast<U>();
        }

        template <typename U>
        std::optional<U> cast_opt() const {
            return getAnyNode()->cast_opt<U>();
        }

        XIR_DLL bool has_value() const;

        template <typename U>
        U value_or(U v) const {
            if (has_value()) {
                return cast<U>();
            }
            else {
                return v;
            }
        }

    private:
        XIR_DLL AnyNode* getAnyNode() const;
    };
}

namespace std {
    template<>
    struct is_copy_constructible<icraft::xir::Any> : true_type {};

    template<>
    struct is_copy_assignable<icraft::xir::Any> : true_type {};
}
</pre>
```
