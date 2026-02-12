# Program Listing for File optional.h



↰ [Return to documentation for file](file_icraft-xir_base_optional.h.md#file-icraft-xir-base-optional-h) (`icraft-xir\base\optional.h`)


```cpp
#pragma once
#include <optional>
#include <icraft-utils/logging.h>
#include <icraft-xir/base/object.h>

namespace icraft::xir{

    struct NullOptType {};

    template <typename T>
    class Optional : public ObjectRef {
    public:
        using ContainerType = typename T::NodeType;
        using NodeType = typename T::NodeType;
        static_assert(std::is_base_of_v<ObjectRef, T>, "Optional is only defined for ObjectRef");

        Optional() = default;

        Optional(const std::optional<T>& opt) : ObjectRef(opt.value_or(T())) {}

        Optional(const Optional<T>&) = default;

        Optional(Optional<T>&&) = default;

        Optional<T>& operator=(const Optional<T>&) = default;

        Optional<T>& operator=(Optional<T>&&) = default;

        explicit Optional(ObjectPtr<Object> ptr) : ObjectRef(ptr) {}
        static Optional Get(ObjectPtr<Object> ptr) { return Optional(ptr); }

        Optional(NullOptType) {}

        explicit Optional(std::nullptr_t) {}

        Optional<T>& operator=(std::nullptr_t) {
            data_ = nullptr;
            return *this;
        }

        Optional(T other)
            : ObjectRef(std::move(other)) {}

        Optional<T>& operator=(T other) {
            ObjectRef::operator=(std::move(other));
            return *this;
        }

        explicit Optional(int val) = delete;
        Optional<T>& operator=(int val) = delete;

        T value() const {

            // 检查：
            ICRAFT_CHECK(data_ != nullptr);

            return T::Get(data_);
        }

        const ContainerType* get() const { return static_cast<ContainerType*>(data_.get()); }

        bool has_value() const { return data_ != nullptr; }

        operator std::optional<T>() const { return has_value() ? std::optional<T>(value()) : std::nullopt; }

        T value_or(T v) const { return data_ != nullptr ? T::Get(data_) : v; }

        explicit operator bool() const { return *this != nullptr; }

        bool operator==(std::nullptr_t) const { return data_ == nullptr; }

        bool operator!=(std::nullptr_t) const { return data_ != nullptr; }

        auto operator==(const Optional<T>& other) const {
            using RetType = decltype(value() == other.value());
            if (same_as(other)) return RetType(true);
            if (*this != nullptr && other != nullptr) {
                return value() == other.value();
            }
            else {
                return RetType(false);
            }
        }

        auto operator!=(const Optional<T>& other) const {
            // support case where sub-class returns a symbolic ref type
            using RetType = decltype(value() != other.value());
            if (same_as(other)) return RetType(false);
            if (*this != nullptr && other != nullptr) {
                return value() != other.value();
            }
            else {
                return RetType(true);
            }
        }

        auto operator==(const T& other) const {
            using RetType = decltype(value() == other);
            if (same_as(other)) return RetType(true);
            if (*this != nullptr) return value() == other;
            return RetType(false);
        }

        auto operator!=(const T& other) const { return !(*this == other); }

        template <typename U>
        auto operator==(const U& other) const {
            using RetType = decltype(value() == other);
            if (*this == nullptr) return RetType(false);
            return value() == other;
        }

        template <typename U>
        auto operator!=(const U& other) const {
            using RetType = decltype(value() != other);
            if (*this == nullptr) return RetType(true);
            return value() != other;
        }
    };

    constexpr NullOptType NullOpt{};

    template <typename T>
    constexpr bool is_optional(T const&) { return false; }

    template <typename T>
    constexpr bool is_optional(std::optional<T> const&) { return true; }

    template <typename T>
    constexpr bool is_optional(Optional<T> const&) { return true; }
}
</pre>
```
