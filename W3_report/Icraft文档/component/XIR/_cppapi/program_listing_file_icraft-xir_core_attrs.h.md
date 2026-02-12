# Program Listing for File attrs.h



↰ [Return to documentation for file](file_icraft-xir_core_attrs.h.md#file-icraft-xir-core-attrs-h) (`icraft-xir\core\attrs.h`)


```cpp
#pragma once
#include <map>
#include <icraft-xir/base/any.h>
#include <icraft-xir/base/array.h>
#include <icraft-xir/base/optional.h>

#include <icraft-xir/core/node.h>
#include <icraft-xir/core/data.h>
#include <icraft-xir/utils/wise_enum.h>

namespace icraft::xir {

    class AttrFieldInfoNode : public NodeBase<AttrFieldInfoNode, Node> {
    public:
        std::string name;
        std::string type_info;
        std::string description;

        virtual void accept(AttrVisitor& v) override {
            v.visit("name", name);
            v.visit("type_info", type_info);
            v.visit("description", description);
        }

        bool reduceAccept(AttrFieldInfoNode* other, const ReduceVisitor& reduce) const {
            return reduce(name, other->name)
                && reduce(type_info, other->type_info)
                && reduce(description, other->description);
        }
    };

    class AttrFieldInfo : public HandleBase<AttrFieldInfo, Handle, AttrFieldInfoNode> {};

    struct AttrNopEntry {
        AttrNopEntry& describe(const char* str) { return *this; }

        template <typename T>
        AttrNopEntry& set_default(const T& value) {
            return *this;
        }

        template <typename T>
        AttrNopEntry& set_lower_bound(const T& begin) {
            return *this;
        }

        template <typename T>
        AttrNopEntry& set_upper_bound(const T& end) {
            return *this;
        }
    };

    namespace detail {
        template <typename T>
        struct is_array : std::false_type {};

        template <typename U>
        struct is_array<Array<U>> : std::true_type {};

        template <typename U>
        struct is_array<Optional<Array<U>>> : std::true_type {};

        template <typename T>
        inline constexpr bool is_array_v = is_array<T>::value;
    }

    class AttrNormalVisitor {
    public:
        explicit AttrNormalVisitor(AttrVisitor& visitor) : visitor_(visitor) {}

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& value) {

            visitor_.visit(key, value);

            return AttrNopEntry();
        }

    private:
        AttrVisitor& visitor_;
    };

    class AttrDocEntry {
    public:
        using TSelf = AttrDocEntry;

        explicit AttrDocEntry(ObjectPtr<AttrFieldInfoNode> info) : info_(info) {}

        TSelf& describe(const char* str) {
            info_->description = str;
            return *this;
        }

        template <typename T>
        TSelf& set_default(const T& value) {
            std::ostringstream os;
            os << info_->type_info << ", default=";
            if constexpr (std::is_enum_v<T>) os << wise_enum::to_string(value);

            else os << value;
            info_->type_info = os.str();
            return *this;
        }

        template <typename T>
        TSelf& set_lower_bound(T begin) {
            return *this;
        }

        template <typename T>
        TSelf& set_upper_bound(T end) {
            return *this;
        }

    private:
        ObjectPtr<AttrFieldInfoNode> info_;
    };

    class AttrDocVisitor {
    public:
        template <typename T>
        AttrDocEntry operator()(std::string_view key, T& v) {
            ObjectPtr<AttrFieldInfoNode> info = make_object<AttrFieldInfoNode>();
            info->name = key;
            info->type_info = TypeName<T>();
            _fields.push_back(AttrFieldInfo::Get(info));
            return AttrDocEntry(info);
        }

        Array<AttrFieldInfo> _fields;
    };

    template <typename T>
    class AttrBoundEntry {
    public:
        using TSelf = AttrBoundEntry<T>;

        std::string_view _type_key;
        std::string_view _key;
        T& _value;

        TSelf& set_lower_bound(const T& begin) {

            // 检查：
            ICRAFT_CHECK(begin <= _value)
                .append("{}.{}: vaule {} is smaller than the lower bound {}",
                    _type_key, _key, _value, begin);

            return *this;
        }

        TSelf& set_upper_bound(const T& end) {

            // 检查：
            ICRAFT_CHECK(end >= _value)
                .append("{}.{}: vaule {} is bigger than the upper bound {}",
                    _type_key, _key, _value, end);

            return *this;
        }

        TSelf& set_default(const T& value) { return *this; }

        TSelf& describe(std::string_view str) { return *this; }
    };

    class AttrBoundVisitor {
    public:
        AttrBoundVisitor(std::string_view type_key) : type_key_(type_key) {}

        template <typename T>
        AttrBoundEntry<T> operator()(std::string_view key, T& value) {
            return { type_key_ , key, value };
        }

    private:
        std::string_view type_key_;
    };

    template <typename T>
    class AttrInitEntry {
    public:
        using TSelf = AttrInitEntry<T>;
        T& _value;

        TSelf& set_lower_bound(const T& begin) { return *this; }

        TSelf& set_upper_bound(const T& end) { return *this; }

        TSelf& set_default(const T& value) {
            this->_value = value;
            return *this;
        }

        TSelf& describe(const char* str) { return *this; }
    };

    class AttrInitVisitor {
    public:
        AttrInitVisitor(std::string_view type_key) : type_key_(type_key) {}

        template <typename T>
        AttrInitEntry<T> operator()(std::string_view key, T& value) {
            return { value };
        }

    private:
        std::string_view type_key_;
    };

    class AttrExistVisitor {
    public:
        const std::string& _key;
        const Any& _value;
        bool _exist{ false };
        bool _visit{ false };

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {

            if (_visit) {
                return AttrNopEntry();
            }

            if (key == _key) {
                _visit = true;
                if (!_value.has_value()) {
                    _exist = true;
                }
                else if (auto opt_v = _value.cast_opt<T>(); opt_v.has_value()) {
                    _exist = opt_v.value() == v;
                }
                else {
                    _exist = false;
                }
            };
            return AttrNopEntry();
        }
    };

    class AttrGetVisitor {
    public:
        const std::string& _key;
        Any _value;

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {
            if (key == _key) {
                _value = v;
            }
            return AttrNopEntry();
        }
    };

    class AttrSetVisitor {
    public:
        const std::string& _key;
        const Any& _value;
        bool _exist{ false };

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {
            if (key == _key) {
                _exist = true;
                v = _value.cast<T>();
            }
            return AttrNopEntry();
        }
    };

    class AttrNullVisitor {
    public:
        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {
            if constexpr (std::is_same_v<T, ObjectRef>) {
                if (!is_optional(v)) {
                    // 检查：
                    ICRAFT_CHECK(v.defined()).append("Attr {} is null", key);
                }
            }
            return AttrNopEntry();
        }
    };

    class AttrMapVisitor {
    public:
        std::map<std::string_view, Any> _attrs;

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {
            _attrs[key] = v;
            return AttrNopEntry();
        }
    };

    template <typename V>
    class VAttrMapVisitor {
    public:
        std::map<std::string_view, Array<V>> _attrs;

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {
            if constexpr (std::is_same_v<Array<V>, T>) {
                _attrs[key] = v;
            }
            else if constexpr (std::is_base_of_v<V, T>) {
                _attrs[key] = { v };
            }

            return AttrNopEntry();
        }

        template <typename T>
        AttrNopEntry operator()(std::string_view key, Optional<T>& v) {
            if constexpr (std::is_same_v<Array<V>, T>) {
                if (v.has_value()) {
                    _attrs[key] = v.value();
                }
            }
            else if constexpr (std::is_base_of_v<V, T>) {
                if (v.has_value()) {
                    _attrs[key] = { v.value() };
                }
            }

            return AttrNopEntry();
        }
    };

    class AttrPtrMapVisitor {
    public:
        std::unordered_map<std::string_view, void*> _attrs;

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {
            _attrs[key] = &v;
            return AttrNopEntry();
        }
    };

    class AttrReduceVisitor {
    public:
        bool result = true;

        AttrReduceVisitor(
            std::unordered_map<std::string_view, void*>& attrs,
            const ReduceVisitor& reduce
        ) : attrs_(attrs), reduce_(reduce) {}

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {
            result = result && reduce_(v, *static_cast<T*>(attrs_[key]));
            return AttrNopEntry();
        }

    private:
        std::unordered_map<std::string_view, void*>& attrs_;
        const ReduceVisitor& reduce_;
    };

    class AttrCloneVisitor {
    public:
        explicit AttrCloneVisitor(
            const std::unordered_map<std::string_view, Any>& attrs
        ) : attrs_(attrs) {}

        template <typename T>
        AttrNopEntry operator()(std::string_view key, T& v) {
            v = attrs_.at(key).cast<T&>();
            return AttrNopEntry();
        }

    private:
        const std::unordered_map<std::string_view, Any>& attrs_;
        // const std::pair<std::string_view, icraft::xir::Any> pair_ = { "example", icraft::xir::Any() };
    };
}
</pre>
```
