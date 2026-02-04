# Program Listing for File object.h



↰ [Return to documentation for file](file_icraft-xir_base_object.h.md#file-icraft-xir-base-object-h) (`icraft-xir\base\object.h`)


```cpp
#pragma once
#include <atomic>
#include <string>
#include <string_view>
#include <icraft-xir/base/dllexport.h>

namespace icraft::xir {

    class Object {
    public:
        Object() = default;

        Object(const Object& other) {}

        Object& operator=(const Object& other) noexcept { return *this; }

        Object& operator=(Object&& other) noexcept { return *this; }

        template <typename TargetType>
        inline bool isInstance() const {
            if (this != nullptr) {
                if (std::is_same_v<TargetType, Object>) {
                    return true;
                }
                else {
                    return dynamic_cast<const TargetType*>(this);
                }
            }

            return false;
        }

        virtual std::string_view typeKey() const { return type_key; }

        bool isArray() const { return this->typeKey() == "ArrayNode"; }

        virtual ~Object() = default;

        static constexpr std::string_view type_key = "Object";

    protected:
        inline void incref() {
            ++count_;
        }

        inline void decref() {
            if ((--count_) == 0) {
                delete this;
            }
        }
    private:
        std::atomic<int> count_{0};

        template <class>
        friend class ObjectPtr;
    };

    template <class T>
    class ObjectPtr {
    public:
        ObjectPtr() = default;

        ObjectPtr(std::nullptr_t) {}

        ObjectPtr(const ObjectPtr<T>& other) : ObjectPtr(other.data_,other.no_ref_count_) {}

        ObjectPtr(ObjectPtr<T>&& other) : data_(other.data_),no_ref_count_(other.no_ref_count_) {
            other.data_ = nullptr;
        }

        template <typename U>
        ObjectPtr(const ObjectPtr<U>& other) : ObjectPtr(other.data_) {
            static_assert(std::is_base_of_v<T, U>,
                "can only assign of child class ObjectPtr to parent");
        }

        template <typename U>
        ObjectPtr(ObjectPtr<U>&& other) : data_(other.data_),no_ref_count_(other.no_ref_count_) {
            static_assert(std::is_base_of_v<T, U>,
                "can only assign of child class ObjectPtr to parent");
            other.data_ = nullptr;
        }

        ObjectPtr<T>& operator=(const ObjectPtr<T>& other) {
            ObjectPtr(other).swap(*this);
            return *this;
        }

        ObjectPtr<T>& operator=(ObjectPtr<T>&& other) {
            ObjectPtr(std::move(other)).swap(*this);
            return *this;
        }

        void reset() {
            if (data_ && !no_ref_count_) { data_->decref(); }
            data_ = nullptr;
        }

        explicit operator bool() const { return get() != nullptr; }

        void swap(ObjectPtr<T>& other) { std::swap(data_, other.data_); }

        T* get() const { return static_cast<T*>(data_); }

        T* operator->() const { return get(); }

        T& operator*() const { return *get(); }

        int use_count() const { return data_ != nullptr ? (int)data_->count_ : 0; }

        bool unique() const { return data_ != nullptr && data_->count_ == 1; }

        bool operator==(const ObjectPtr<T>& other) const { return data_ == other.data_; }

        bool operator!=(const ObjectPtr<T>& other) const { return data_ != other.data_; }

        bool operator==(std::nullptr_t null) const { return data_ == nullptr; }

        bool operator!=(std::nullptr_t null) const { return data_ != nullptr; }

        ~ObjectPtr() { this->reset(); }

    private:
        Object* data_{ nullptr };
        bool no_ref_count_=false;

        explicit ObjectPtr(Object* data, bool noRefCnt=false) : data_(data),no_ref_count_(noRefCnt) {
            if (data_ && !no_ref_count_) {
                data_->incref();
            }
        }

        friend class Object;
        friend class ObjectRef;
        friend struct ObjectPtrHash;
        template <typename>
        friend class ObjectPtr;
        template <typename RelayRefType, typename ObjType>
        friend RelayRefType GetRef(const ObjType* ptr, bool noRefCnt);
        template <typename RelayRefType, typename ObjType>
        friend RelayRefType GetRef(const ObjType* ptr);
        template <typename BaseType, typename ObjType>
        friend ObjectPtr<BaseType> GetObjectPtr(ObjType* ptr);
        template <typename U, typename... Args>
        friend ObjectPtr<U> make_object(Args&&... args);
    };

    class ObjectRef {
    public:
        ObjectRef() = default;

        explicit ObjectRef(ObjectPtr<Object> data) : data_(data) {}

        XIR_DLL bool operator==(const ObjectRef& other) const;

        XIR_DLL bool operator!=(const ObjectRef& other) const;

        XIR_DLL ObjectRef clone(int64_t depth = 1) const;

        XIR_DLL bool same_as(const ObjectRef& other) const;

        XIR_DLL bool operator<(const ObjectRef& other) const;

        XIR_DLL bool defined() const;

        XIR_DLL const Object* get() const;

        XIR_DLL const Object* operator->() const;

        XIR_DLL bool unique() const;

        XIR_DLL int use_count() const;

        XIR_DLL std::string toString() const;

        template <typename ObjectType>
        inline const ObjectType* as() const {
            if (data_ != nullptr && data_->isInstance<ObjectType>()) {
                return static_cast<const ObjectType*>(data_.get());
            }
            else {
                return nullptr;
            }
        }

        template <typename ObjectType>
        inline ObjectType* as_mutable() const {
            if (data_ != nullptr && data_->isInstance<ObjectType>()) {
                return static_cast<ObjectType*>(data_.get());
            }
            else {
                return nullptr;
            }
        }

        using NodeType = Object;

        static ObjectRef Get(ObjectPtr<Object> data) { return ObjectRef(data); }

    protected:

        Object* get_mutable() const { return data_.get(); }

        template <typename ObjectType>
        static ObjectPtr<ObjectType> GetDataPtr(const ObjectRef& ref) {
            return ObjectPtr<ObjectType>(ref.data_.data_);
        }

        template <typename T>
        static T DowncastNoCheck(ObjectRef ref) {
            return T::Get(std::move(ref.data_));
        }

        ObjectPtr<Object> data_;

        friend struct ObjectPtrHash;
        template <typename SubRef, typename BaseRef>
        friend SubRef Downcast(BaseRef ref);
        friend class ReduceVisitor;
    };

    template <typename T, typename... Args>
    inline ObjectPtr<T> make_object(Args&&... args) {
        T* ptr = new T(std::forward<Args>(args)...);
        return ObjectPtr<T>(ptr);
    }

    template <typename BaseType, typename ObjType>
    inline ObjectPtr<BaseType> GetObjectPtr(ObjType* ptr) {
        static_assert(std::is_base_of_v<BaseType, ObjType>,
            "Can only cast to the ref of same container type");
        return ObjectPtr<BaseType>(static_cast<Object*>(ptr));
    }

    template <typename RefType, typename ObjType>
    inline RefType GetRef(const ObjType* ptr, bool noRefCnt) {
        static_assert(std::is_base_of_v<typename RefType::NodeType, ObjType>,
            "Can only cast to the ref of same container type");
        return RefType::Get(ObjectPtr<Object>(const_cast<Object*>(static_cast<const Object*>(ptr)),noRefCnt));
    }

    template <typename RefType, typename ObjType>
    inline RefType GetRef(const ObjType* ptr) {
        static_assert(std::is_base_of_v<typename RefType::NodeType, ObjType>,
            "Can only cast to the ref of same container type");
        return RefType::Get(ObjectPtr<Object>(const_cast<Object*>(static_cast<const Object*>(ptr)),false));
    }

    struct ObjectPtrHash {
        size_t operator()(const ObjectRef& a) const { return operator()(a.data_); }

        template <typename T>
        size_t operator()(const ObjectPtr<T>& a) const {
            return std::hash<Object*>()(a.get());
        }
    };

    struct ObjectPtrEqual {
        bool operator()(const ObjectRef& a, const ObjectRef& b) const { return a.same_as(b); }

        template <typename T>
        size_t operator()(const ObjectPtr<T>& a, const ObjectPtr<T>& b) const {
            return a == b;
        }
    };

    struct ObjectHash {
        size_t operator()(const ObjectRef& a) const;
    };

    struct ObjectEqual {
        bool operator()(const ObjectRef& a, const ObjectRef& b) const;
    };

    template <typename SubRef, typename BaseRef>
    inline SubRef Downcast(BaseRef ref) {
        if (ref.defined()) {
            if (ref->template isInstance<typename SubRef::NodeType>()) {
                return SubRef::Get(std::move(ref.data_));
            }
        }

        return SubRef::Get(nullptr);
    }
}

#if defined(__GNUC__) || defined(__IAR_SYSTEMS_ICC__)
#define ICRAFT_ATTRIBUTE_UNUSED __attribute__((unused))
#else
#define ICRAFT_ATTRIBUTE_UNUSED
#endif

#define ICRAFT_STR(x) #x
#define ICRAFT_STR_CONCAT_(__x, __y) __x##__y
#define ICRAFT_STR_CONCAT(__x, __y) ICRAFT_STR_CONCAT_(__x, __y)
</pre>
```
