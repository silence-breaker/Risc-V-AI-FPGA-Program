# Program Listing for File string.h



↰ [Return to documentation for file](file_icraft-xir_base_string.h.md#file-icraft-xir-base-string-h) (`icraft-xir\base\string.h`)


```cpp
#pragma once
#include <string>
#include <ostream>
#include <icraft-utils/logging.h>
#include <icraft-xir/base/object.h>

namespace icraft::xir {

    class StringNode : public Object {
    public:
        const char* data;
        uint64_t size;

    private:
        class FromStd;
        friend class String;
    };

    class String : public ObjectRef {
    public:

        String() : String(std::string()) {}

        String(std::string other);                                  // NOLINT(*)

        String(const char* other) : String(std::string(other)) {}   // NOLINT(*)

        String(std::nullptr_t) : ObjectRef(nullptr) {}              // NOLINT(*)

        inline String& operator=(std::string other);

        inline String& operator=(const char* other);

        int compare(const String& other) const {
            return memncmp(data(), other.data(), size(), other.size());
        }

        int compare(const std::string& other) const {
            return memncmp(data(), other.data(), size(), other.size());
        }

        int compare(const char* other) const {
            return memncmp(data(), other, size(), std::strlen(other));
        }

        const char* c_str() const { return get()->data; }

        size_t size() const {
            const auto* ptr = get();
            return ptr->size;
        }

        size_t length() const { return size(); }

        bool empty() const { return size() == 0; }

        char at(int64_t index) const {

            // 检查：下标越界
            ICRAFT_CHECK(-(int64_t)size() <= index && index < (int64_t)size()).append("Index {} out of bounds {}",
                index, size());

            return data()[index];
        }

        const char* data() const { return get()->data; }

        operator std::string() const { return std::string{ get()->data, size() }; }

        operator std::string_view() const { return std::string_view{get()->data, size() }; }

        static size_t HashBytes(const char* data, size_t size) {
            return std::hash<std::string_view>()(std::string_view(data, size));
        }

        const StringNode* operator->() const { return static_cast<const StringNode*>(ObjectRef::get()); }
        const StringNode* get() const { return operator->(); }

        using NodeType = StringNode;
        explicit String(ObjectPtr<Object> n) : ObjectRef(n) {}
        static String Get(ObjectPtr<Object> node) { return String(node); }

    private:
        static int memncmp(const char* lhs, const char* rhs, size_t lhs_count, size_t rhs_count);

        static String Concat(const char* lhs, size_t lhs_size, const char* rhs, size_t rhs_size) {
            std::string ret(lhs, lhs_size);
            ret.append(rhs, rhs_size);
            return String(ret);
        }

        // 重载operator+
        friend String operator+(const String& lhs, const String& rhs);
        friend String operator+(const String& lhs, const std::string& rhs);
        friend String operator+(const std::string& lhs, const String& rhs);
        friend String operator+(const String& lhs, const char* rhs);
        friend String operator+(const char* lhs, const String& rhs);

        friend struct ObjectEqual;
    };

    class StringNode::FromStd : public StringNode {
    public:
        explicit FromStd(std::string other) : data_container{ other } {}

    private:
        std::string data_container;

        friend class String;
    };

    inline String::String(std::string other) {
        auto ptr = make_object<StringNode::FromStd>(std::move(other));
        ptr->size = ptr->data_container.size();
        ptr->data = ptr->data_container.data();
        data_ = std::move(ptr);
    }

    inline String& String::operator=(std::string other) {
        String replace{ std::move(other) };
        data_.swap(replace.data_);
        return *this;
    }

    inline String& String::operator=(const char* other) { return operator=(std::string(other)); }

    inline String operator+(const String& lhs, const String& rhs) {
        size_t lhs_size = lhs.size();
        size_t rhs_size = rhs.size();
        return String::Concat(lhs.data(), lhs_size, rhs.data(), rhs_size);
    }

    inline String operator+(const String& lhs, const std::string& rhs) {
        size_t lhs_size = lhs.size();
        size_t rhs_size = rhs.size();
        return String::Concat(lhs.data(), lhs_size, rhs.data(), rhs_size);
    }

    inline String operator+(const std::string& lhs, const String& rhs) {
        size_t lhs_size = lhs.size();
        size_t rhs_size = rhs.size();
        return String::Concat(lhs.data(), lhs_size, rhs.data(), rhs_size);
    }

    inline String operator+(const char* lhs, const String& rhs) {
        size_t lhs_size = std::strlen(lhs);
        size_t rhs_size = rhs.size();
        return String::Concat(lhs, lhs_size, rhs.data(), rhs_size);
    }

    inline String operator+(const String& lhs, const char* rhs) {
        size_t lhs_size = lhs.size();
        size_t rhs_size = std::strlen(rhs);
        return String::Concat(lhs.data(), lhs_size, rhs, rhs_size);
    }

    inline bool operator<(const String& lhs, const std::string& rhs) { return lhs.compare(rhs) < 0; }
    inline bool operator<(const std::string& lhs, const String& rhs) { return rhs.compare(lhs) > 0; }
    inline bool operator<(const String& lhs, const String& rhs) { return lhs.compare(rhs) < 0; }
    inline bool operator<(const String& lhs, const char* rhs) { return lhs.compare(rhs) < 0; }
    inline bool operator<(const char* lhs, const String& rhs) { return rhs.compare(lhs) > 0; }

    inline bool operator>(const String& lhs, const std::string& rhs) { return lhs.compare(rhs) > 0; }
    inline bool operator>(const std::string& lhs, const String& rhs) { return rhs.compare(lhs) < 0; }
    inline bool operator>(const String& lhs, const String& rhs) { return lhs.compare(rhs) > 0; }
    inline bool operator>(const String& lhs, const char* rhs) { return lhs.compare(rhs) > 0; }
    inline bool operator>(const char* lhs, const String& rhs) { return rhs.compare(lhs) < 0; }

    inline bool operator<=(const String& lhs, const std::string& rhs) { return lhs.compare(rhs) <= 0; }
    inline bool operator<=(const std::string& lhs, const String& rhs) { return rhs.compare(lhs) >= 0; }
    inline bool operator<=(const String& lhs, const String& rhs) { return lhs.compare(rhs) <= 0; }
    inline bool operator<=(const String& lhs, const char* rhs) { return lhs.compare(rhs) <= 0; }
    inline bool operator<=(const char* lhs, const String& rhs) { return rhs.compare(lhs) >= 0; }

    inline bool operator>=(const String& lhs, const std::string& rhs) { return lhs.compare(rhs) >= 0; }
    inline bool operator>=(const std::string& lhs, const String& rhs) { return rhs.compare(lhs) <= 0; }
    inline bool operator>=(const String& lhs, const String& rhs) { return lhs.compare(rhs) >= 0; }
    inline bool operator>=(const String& lhs, const char* rhs) { return lhs.compare(rhs) >= 0; }
    inline bool operator>=(const char* lhs, const String& rhs) { return rhs.compare(rhs) <= 0; }

    inline bool operator==(const String& lhs, const std::string& rhs) { return lhs.compare(rhs) == 0; }
    inline bool operator==(const std::string& lhs, const String& rhs) { return rhs.compare(lhs) == 0; }
    inline bool operator==(const String& lhs, const String& rhs) { return lhs.compare(rhs) == 0; }
    inline bool operator==(const String& lhs, const char* rhs) { return lhs.compare(rhs) == 0; }
    inline bool operator==(const char* lhs, const String& rhs) { return rhs.compare(lhs) == 0; }

    inline bool operator!=(const String& lhs, const std::string& rhs) { return lhs.compare(rhs) != 0; }
    inline bool operator!=(const std::string& lhs, const String& rhs) { return rhs.compare(lhs) != 0; }
    inline bool operator!=(const String& lhs, const String& rhs) { return lhs.compare(rhs) != 0; }
    inline bool operator!=(const String& lhs, const char* rhs) { return lhs.compare(rhs) != 0; }
    inline bool operator!=(const char* lhs, const String& rhs) { return rhs.compare(lhs) != 0; }

    inline std::ostream& operator<<(std::ostream& out, const String& input) {
        out.write(input.data(), input.size());
        return out;
    }

    inline int String::memncmp(const char* lhs, const char* rhs, size_t lhs_count, size_t rhs_count) {

        if (lhs == rhs && lhs_count == rhs_count) {
            return 0;
        }

        for (size_t i = 0; i < lhs_count && i < rhs_count; ++i) {
            if (lhs[i] < rhs[i]) return -1;
            if (lhs[i] > rhs[i]) return 1;
        }

        if (lhs_count < rhs_count) {
            return -1;
        }
        else if (lhs_count > rhs_count) {
            return 1;
        }
        else {
            return 0;
        }
    }

    inline size_t ObjectHash::operator()(const ObjectRef& a) const {
        if (const auto* str = a.as<StringNode>()) {
            return String::HashBytes(str->data, str->size);
        }

        return ObjectPtrHash()(a);
    }

    inline bool ObjectEqual::operator()(const ObjectRef& a, const ObjectRef& b) const {
        if (a.same_as(b)) {
            return true;
        }

        if (const auto* str_a = a.as<StringNode>()) {
            if (const auto* str_b = b.as<StringNode>()) {
                return String::memncmp(str_a->data, str_b->data, str_a->size, str_b->size) == 0;
            }
        }

        return false;
    }
}
</pre>
```
