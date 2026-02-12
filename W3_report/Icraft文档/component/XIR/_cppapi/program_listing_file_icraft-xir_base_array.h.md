# Program Listing for File array.h



↰ [Return to documentation for file](file_icraft-xir_base_array.h.md#file-icraft-xir-base-array-h) (`icraft-xir\base\array.h`)


```cpp
#pragma once
#include <unordered_set>
#include <icraft-utils/logging.h>
#include <icraft-xir/base/object.h>
#include <icraft-xir/base/optional.h>

#include <vector>

namespace icraft::xir {

    namespace detail {

        template <typename T>
        class BaseArrayNode : public Object {
        public:
            BaseArrayNode() = default;

            BaseArrayNode(uint64_t n) : data_(std::vector<T>(n)) {}

            BaseArrayNode(uint64_t n, const T& val) : data_(std::vector<T>(n, val)) {}

            const T& operator[](size_t index) const {

                // 检查：下标越界
                ICRAFT_CHECK(index < data_.size()).append("Index {} out of bounds {}", index, data_.size());

                return *(data_.begin() + index);
            }

            T& operator[](size_t index) {

                // 检查：下标越界
                ICRAFT_CHECK(index < data_.size()).append("Index {} out of bounds {}", index, data_.size());

                return *(data_.begin() + index);
            }

            const T& at(size_t index) const {
                return data_[index];
            }

            T& at(size_t index) {
                return data_[index];
            }

        protected:
            std::vector<T> data_;
        };

        template <>
        class BaseArrayNode<bool> : public Object {
        public:
            using reference = std::vector<bool>::reference;
            using const_reference = std::vector<bool>::const_reference;

            BaseArrayNode() = default;

            BaseArrayNode(uint64_t n) : data_(std::vector<bool>(n)) {}

            BaseArrayNode(uint64_t n, const bool& val) : data_(std::vector<bool>(n, val)) {}

            const_reference operator[](size_t index) const {

                // 检查：下标越界
                ICRAFT_CHECK(index < data_.size()).append("Index {} out of bounds {}", index, data_.size());

                return *(data_.begin() + index);
            }

            reference operator[](size_t index) {

                // 检查：下标越界
                ICRAFT_CHECK(index < data_.size()).append("Index {} out of bounds {}", index, data_.size());

                return *(data_.begin() + index);
            }

            const_reference at(size_t index) const {
                return data_[index];
            }

            reference at(size_t index) {
                return data_[index];
            }

        protected:
            std::vector<bool> data_;
        };
    }

    template <typename T>
    class ArrayNode : public detail::BaseArrayNode<T> {
    public:

        using ContainerType = std::vector<T>;

        using iterator = typename ContainerType::iterator;

        using const_iterator = typename ContainerType::const_iterator;

        ArrayNode() = default;

        ArrayNode(uint64_t n) : detail::BaseArrayNode<T>(n) {}

        ArrayNode(uint64_t n, const T& val) : detail::BaseArrayNode<T>(n, val) {}

        size_t size() const {
            return this->data_.size();
        }

        size_t capacity() const {
            return this->data_.capacity();
        }

        const_iterator begin() const {
            return this->data_.begin();
        }

        iterator begin() {
            return this->data_.begin();
        }

        const_iterator end() const {
            return this->data_.end();
        }

        iterator end() {
            return this->data_.end();
        }

        void clear() {
            this->data_.clear();
        }

        void setItem(int64_t index, T item) {
            this->data_[index] = std::move(item);
        }

        static ObjectPtr<ArrayNode> CopyFrom(int64_t cap, const ArrayNode* from) {

            // 检查：
            ICRAFT_CHECK_GE(cap, from->size()).append("ValueError: not enough capacity");

            ObjectPtr<ArrayNode> p = make_object<ArrayNode>(cap);
            std::copy_n(from->begin(), from->size(), p->begin());

            return p;
        }

        static ObjectPtr<ArrayNode> MoveFrom(int64_t cap, ArrayNode* from) {

            // 检查：
            ICRAFT_CHECK_GE(cap, from->size()).append("ValueError: not enough capacity");

            ObjectPtr<ArrayNode> p = make_object<ArrayNode>(cap);
            std::copy_n(std::make_move_iterator(from->begin()), from->size(), p->begin());

            from->clear();

            return p;
        }

        static ObjectPtr<ArrayNode> CreateRepeated(int64_t n, const T& val) {
            return make_object<ArrayNode>(n, val);
        }

        bool operator==(const ArrayNode& other) const { return this->data_ == other.data_; }

        bool operator!=(const ArrayNode& other) const { return this->data_ != other.data_; }

        static constexpr std::string_view type_key = "ArrayNode";

        virtual std::string_view typeKey() const override { return type_key; }

    private:
        static ObjectPtr<ArrayNode> Empty(uint64_t n = kInitSize) {

            auto p = make_object<ArrayNode>();

            p->data_.reserve(n);

            return p;
        }

        template <typename IterType>
        ArrayNode* initRange(int64_t index, IterType first, IterType last) {
            auto itr = this->begin() + index;
            std::copy(first, last, itr);
            return this;
        }

        ArrayNode* moveElementsLeft(int64_t dst, int64_t src_begin, int64_t src_end) {

            auto from = this->begin() + src_begin;
            auto to = this->end() + dst;

            while (src_begin++ != src_end) {
                *to++ = std::move(*from++);
            }

            return this;
        }

        ArrayNode* moveElementsRight(int64_t dst, int64_t src_begin, int64_t src_end) {

            auto from = this->begin() + src_end;
            auto to = this->end() + (src_end - src_begin + dst);

            while (src_begin++ != src_end) {
                *--to = std::move(*--from);
            }

            return this;
        }

        ArrayNode* enlargeBy(int64_t delta, const T& val = T{}) {

            while (delta-- > 0) {
                this->data_.push_back(val);
            }

            return this;
        }

        ArrayNode* shrinkBy(int64_t delta) {

            while (delta-- > 0) {
                this->data_.pop_back();
            }

            return this;
        }

        static constexpr int64_t kInitSize = 4;
        static constexpr int64_t kIncFactor = 2;

        template <typename>
        friend class Array;
    };

    template <class _Ty, class = void>
    inline constexpr bool is_iterator_v = false;

    template <class _Ty>
    inline constexpr bool is_iterator_v<
        _Ty,
        std::void_t<typename std::iterator_traits<_Ty>::iterator_category>
    > = true;

    template <typename T, typename IterType>
    struct is_valid_iterator
        : std::bool_constant<std::is_convertible_v<
        T, std::remove_cv_t<std::remove_reference_t<decltype(*std::declval<IterType>())>>>> {};

    template <typename T, typename IterType>
    struct is_valid_iterator<Optional<T>, IterType> : is_valid_iterator<T, IterType> {};

    template <typename T, typename IterType>
    inline constexpr bool is_valid_iterator_v = is_valid_iterator<T, IterType>::value;

    template <typename Converter, typename TIter>
    class ConstIterAdapter {
    public:
        using difference_type = typename std::iterator_traits<TIter>::difference_type;
        using value_type = const typename Converter::ResultType;
        using pointer = const typename Converter::ResultType*;
        using reference = const typename Converter::ResultType&;
        using iterator_category = typename std::iterator_traits<TIter>::iterator_category;

        explicit ConstIterAdapter() : iter_() {}

        explicit ConstIterAdapter(TIter iter) : iter_(iter) {}

        ConstIterAdapter& operator++() {
            ++iter_;
            return *this;
        }

        ConstIterAdapter& operator--() {
            --iter_;
            return *this;
        }

        ConstIterAdapter operator++(int) {
            auto copy = *this;
            ++iter_;
            return copy;
        }

        ConstIterAdapter operator--(int) {
            auto copy = *this;
            --iter_;
            return copy;
        }

        ConstIterAdapter& operator+=(difference_type offset) {
            iter_ += offset;
            return *this;
        }

        ConstIterAdapter operator+(difference_type offset) const {
            auto copy = *this;
            copy += offset;
            return copy;
        }

        ConstIterAdapter& operator-=(difference_type offset) {
            iter_ -= offset;
            return *this;
        }

        ConstIterAdapter operator-(difference_type offset) const {
            auto copy = *this;
            copy -= offset;
            return copy;
        }

        inline difference_type operator-(const ConstIterAdapter& rhs) const {
            return iter_ - rhs.iter_;
        }

        bool operator==(const ConstIterAdapter& other) const { return iter_ == other.iter_; }
        bool operator!=(const ConstIterAdapter& other) const { return !(*this == other); }
        bool operator<(const ConstIterAdapter& other) const { return iter_ < other.iter_; }
        bool operator>(const ConstIterAdapter& other) const { return iter_ > other.iter_; }
        value_type operator*() const { return Converter::convert(*iter_); }

        const TIter& iter() const { return iter_; }

    protected:
        TIter iter_;
    };

    template <typename Converter, typename TIter>
    class IterAdapter : public ConstIterAdapter<Converter, TIter> {
    public:
        using difference_type = typename std::iterator_traits<TIter>::difference_type;
        using value_type = typename Converter::ResultType;
        using pointer = typename Converter::ResultType*;
        using reference = typename Converter::ResultType&;
        using iterator_category = typename std::iterator_traits<TIter>::iterator_category;

        using _BaseType = ConstIterAdapter<Converter, TIter>;

        explicit IterAdapter() : _BaseType() {}

        explicit IterAdapter(TIter iter) : _BaseType(iter) {}

        explicit IterAdapter(_BaseType const_iter) : _BaseType(const_iter) {}

        IterAdapter& operator++() {
            _BaseType::operator++();
            return *this;
        }

        IterAdapter& operator--() {
            _BaseType::operator--();
            return *this;
        }

        IterAdapter operator++(int) {
            auto copy = *this;
            _BaseType::operator++();
            return copy;
        }

        IterAdapter operator--(int) {
            auto copy = *this;
            _BaseType::operator--();
            return copy;
        }

        IterAdapter& operator+=(difference_type offset) {
            _BaseType::operator+=(offset);
            return *this;
        }

        IterAdapter operator+(difference_type offset) const {
            auto copy = *this;
            copy += offset;
            return copy;
        }

        IterAdapter& operator-=(difference_type offset) {
            _BaseType::operator-=(offset);
            return *this;
        }

        IterAdapter operator-(difference_type offset) const {
            auto copy = *this;
            copy -= offset;
            return copy;
        }

        value_type operator*() const { return Converter::convert(*this->iter_); }

        inline difference_type operator-(const IterAdapter& rhs) const {
            return _BaseType::operator-(rhs);
        }
    };

    template <typename Converter, typename TIter>
    class ConstReverseIterAdapter {
    public:
        using difference_type = typename std::iterator_traits<TIter>::difference_type;
        using value_type = const typename Converter::ResultType;
        using pointer = const typename Converter::ResultType*;
        using reference = const typename Converter::ResultType&;                // NOLINT(*)
        using iterator_category = typename std::iterator_traits<TIter>::iterator_category;

        explicit ConstReverseIterAdapter() : iter_() {}

        explicit ConstReverseIterAdapter(const TIter iter) : iter_(iter) {}

        ConstReverseIterAdapter& operator++() {
            --iter_;
            return *this;
        }

        ConstReverseIterAdapter& operator--() {
            ++iter_;
            return *this;
        }

        ConstReverseIterAdapter& operator++(int) {
            auto copy = *this;
            --iter_;
            return copy;
        }

        ConstReverseIterAdapter& operator--(int) {
            auto copy = *this;
            ++iter_;
            return copy;
        }

        ConstReverseIterAdapter& operator+=(difference_type offset) {
            iter_ += offset;
            return *this;
        }

        ConstReverseIterAdapter operator+(difference_type offset) const {
            auto copy = *this;
            copy += offset;
            return copy;
        }

        ConstReverseIterAdapter& operator-=(difference_type offset) {
            iter_ -= offset;
            return *this;
        }

        ConstReverseIterAdapter operator-(difference_type offset) const {
            auto copy = *this;
            copy -= offset;
            return copy;
        }

        inline difference_type operator-(const ConstReverseIterAdapter& rhs) const {
            return rhs.iter_ - iter_;
        }

        bool operator==(const ConstReverseIterAdapter& other) const { return iter_ == other.iter_; }
        bool operator!=(const ConstReverseIterAdapter& other) const { return !(*this == other); }
        bool operator<(const ConstReverseIterAdapter& other) const { return iter_ < other.iter_; }
        bool operator>(const ConstReverseIterAdapter& other) const { return iter_ > other.iter_; }
        value_type operator*() const { return Converter::convert(*iter_); }

        const TIter& iter() const { return iter_; }

    protected:
        TIter iter_;
    };

    template <typename Converter, typename TIter>
    class ReverseIterAdapter : public ConstReverseIterAdapter<Converter, TIter> {
    public:
        using difference_type = typename std::iterator_traits<TIter>::difference_type;
        using value_type = typename Converter::ResultType;
        using pointer = typename Converter::ResultType*;
        using reference = typename Converter::ResultType&;
        using iterator_category = typename std::iterator_traits<TIter>::iterator_category;

        using _BaseType = ConstReverseIterAdapter<Converter, TIter>;

        explicit ReverseIterAdapter() : _BaseType() {}

        explicit ReverseIterAdapter(TIter iter) : _BaseType(iter) {}

        explicit ReverseIterAdapter(_BaseType const_iter) : _BaseType(const_iter) {}

        ReverseIterAdapter& operator++() {
            _BaseType::operator++();
            return *this;
        }

        ReverseIterAdapter& operator--() {
            _BaseType::operator--();
            return *this;
        }

        ReverseIterAdapter operator++(int) {
            auto copy = *this;
            _BaseType::operator++();
            return copy;
        }

        ReverseIterAdapter operator--(int) {
            auto copy = *this;
            _BaseType::operator--();
            return copy;
        }

        ReverseIterAdapter& operator+=(difference_type offset) {
            _BaseType::operator+=(offset);
            return *this;
        }

        ReverseIterAdapter operator+(difference_type offset) const {
            auto copy = *this;
            copy += offset;
            return copy;
        }

        ReverseIterAdapter& operator-=(difference_type offset) {
            _BaseType::operator-=(offset);
            return *this;
        }

        ReverseIterAdapter operator-(difference_type offset) const {
            auto copy = *this;
            copy -= offset;
            return copy;
        }

        value_type operator*() const { return Converter::convert(*this->iter_); }

        inline difference_type operator-(const ReverseIterAdapter& rhs) const {
            return _BaseType::operator-(rhs);
        }
    };

    template <typename T>
    class Array : public ObjectRef {
    public:
        using value_type = T;
        using ElementNodeType = std::conditional_t<std::is_base_of_v<ObjectRef, T>, ObjectRef, T>;
        using NodeType = ArrayNode<ElementNodeType>;

        Array(ObjectPtr<Object> n) {
            static_assert(std::is_base_of_v<ObjectRef, T> || std::is_pod_v<T>, "T must inherit from ObjectRef");
            data_ = std::move(n);
        }

        Array() : Array(NodeType::Empty()) {}

        Array(Array<T>&& other) {                   // NOLINT(*)
            data_ = std::move(other.data_);
        }

        Array(const Array<T>& other) {              // NOLINT(*)
            data_ = other.data_;
        }

        template <typename U, typename = typename std::enable_if_t<std::is_convertible_v<U, T>>>
        Array(const Array<U>& init) : Array() {     // NOLINT(*)
            assign(init.begin(), init.end());
        }

        template <typename IterType, typename = typename std::enable_if_t<is_iterator_v<IterType>>>
        Array(IterType first, IterType last) : Array() {
            static_assert(is_valid_iterator_v<T, IterType>, "IterType cannot be inserted into a Array<T>");
            assign(first, last);
        }

        Array(std::initializer_list<T> init) : Array() {        // NOLINT(*)
            assign(init.begin(), init.end());
        }

        Array(const std::vector<T>& init) : Array() {           // NOLINT(*)
            assign(init.begin(), init.end());
        }

        template <typename U, typename = typename std::enable_if_t<std::is_convertible_v<U, T>>>
        Array(const std::vector<U>& init) : Array() {           // NOLINT(*)
            assign(init.begin(), init.end());
        }

        template <typename U, typename = typename std::enable_if_t<std::is_convertible_v<U, T>>>
        explicit Array(const size_t n, const U& val) : Array(NodeType::CreateRepeated(n, val)) {}

        Array<T>& operator=(Array<T>&& other) {
            data_ = std::move(other.data_);
            return *this;
        }

        Array<T>& operator=(const Array<T>& other) {
            data_ = other.data_;
            return *this;
        }

        static Array Get(ObjectPtr<Object> n) {
            return Array(n);
        }

        static Array Init() {
            return {};
        }

        operator std::vector<T>() const {
            return std::vector<T>(this->begin(), this->end());
        }

        template <typename U, typename = typename std::enable_if_t<std::is_convertible_v<T, U>>>
        operator std::vector<U>() const {
            return std::vector<U>(this->begin(), this->end());
        }

        Array<T> clone(int64_t depth = 1) const {
            return Downcast<Array<T>>(ObjectRef::clone(depth));
        }

    public:
        struct ValueConverter {
            using ResultType = T;
            static T convert(const ElementNodeType& n) {
                if constexpr (std::is_same_v<ElementNodeType, T>) {
                    return n;
                }
                else {
                    return DowncastNoCheck<T>(n);
                }
            }
        };

        using iterator = IterAdapter<ValueConverter, typename NodeType::iterator>;
        using const_iterator = ConstIterAdapter<ValueConverter, typename NodeType::iterator>;
        using reverse_iterator = ReverseIterAdapter<ValueConverter, typename NodeType::iterator>;
        using const_reverse_iterator = ConstReverseIterAdapter<ValueConverter, typename NodeType::iterator>;

        iterator begin() { return iterator(getArrayNode()->begin()); }

        const_iterator begin() const { return const_iterator(getArrayNode()->begin()); }

        iterator end() { return iterator(getArrayNode()->end()); }

        const_iterator end() const { return const_iterator(getArrayNode()->end()); }

        reverse_iterator rbegin() {
            return reverse_iterator(getArrayNode()->end() - 1);
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(getArrayNode()->end() - 1);
        }

        reverse_iterator rend() {
            return reverse_iterator(getArrayNode()->begin() - 1);
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(getArrayNode()->begin() - 1);
        }

    public:
        T operator[](int64_t index) const {

            // 检查：下标越界
            ICRAFT_CHECK(-(int64_t)size() <= index && index < (int64_t)size())
                .append("Index {} out of bounds {}", index, size());

            index = index >= 0 ? index : size() + index;

            auto p = getArrayNode();

            // 检查：
            ICRAFT_CHECK(p != nullptr).append("ValueError: cannot index a null array");

            return ValueConverter::convert(*(p->begin() + index));
        }

        size_t size() const {
            return getArrayNode() == nullptr ? 0 : getArrayNode()->size();
        }

        size_t capacity() const {
            return getArrayNode() == nullptr ? 0 : getArrayNode()->capacity();
        }

        bool empty() const {
            return size() == 0;
        }

        T front() const {
            auto p = getArrayNode();

            // 检查：
            ICRAFT_CHECK(p != nullptr).append("ValueError: cannot index a null array");

            // 检查：
            ICRAFT_CHECK_GT(p->size(), 0).append("IndexError: cannot index an empty array");

            return ValueConverter::convert(*(p->begin()));
        }

        T back() const {
            auto p = getArrayNode();

            // 检查：
            ICRAFT_CHECK(p != nullptr).append("ValueError: cannot index a null array");

            // 检查：
            ICRAFT_CHECK(p->size() > 0).append("IndexError: cannot index an empty array");

            return ValueConverter::convert(*(p->end() - 1));
        }

    public:
        void push_back(const T& item) {
            getArrayNode()->data_.push_back(item);
        }

        void insert(const_iterator position, const T& val) {

            // 检查：
            ICRAFT_CHECK(data_ != nullptr).append("ValueError: cannot insert a null array");

            getArrayNode()->data_.insert(position.iter(), val);
        }

        void insert(int64_t index, const T& val) {
            auto i = getUIndex(index, true);
            insert(this->begin() + i, val);
        }

        template <typename IterType>
        void insert(const_iterator position, IterType first, IterType last) {

            static_assert(is_valid_iterator_v<T, IterType>, "IterType cannot be inserted into a Array<T>");

            if (first == last) {
                return;
            }

            // 检查：
            ICRAFT_CHECK(data_ != nullptr).append("ValueError: cannot insert a null array");

            getArrayNode()->data_.insert(position.iter(), first, last);
        }

        void pop_back() {

            // 检查：
            ICRAFT_CHECK(data_ != nullptr).append("ValueError: cannot pop_back because array is null");

            // 检查：
            ICRAFT_CHECK(getArrayNode()->size() > 0).append("ValueError: cannot pop_back because array is empty");

            getArrayNode()->data_.pop_back();
        }

        iterator erase(const_iterator position) {

            // 检查：
            ICRAFT_CHECK(data_ != nullptr).append("ValueError: cannot erase a null array");

            int64_t st = position - begin();
            int64_t size = getArrayNode()->size();

            // 检查：
            ICRAFT_CHECK(0 <= st && st < size)
                .append("ValueError: cannot erase at index {}, because Array size is {}", st, size);

            return iterator(getArrayNode()->data_.erase(position.iter()));
        }

        uint64_t erase(int64_t index) {
            auto i = getUIndex(index);
            return erase(this->begin() + i) - begin();
        }

        iterator erase(const_iterator first, const_iterator last) {

            if (first == last) {
                return iterator(last);
            }

            // 检查：
            ICRAFT_CHECK(data_ != nullptr).append("ValueError: cannot erase a null array");

            int64_t size = getArrayNode()->size();
            int64_t st = first - begin();
            int64_t ed = last - begin();

            // 检查：
            ICRAFT_CHECK(st < ed).append("ValueError: cannot erase array in range [{},{})", st, ed);

            // 检查：
            ICRAFT_CHECK(0 <= st && st <= size && 0 <= ed && ed <= size)
                .append("ValueError: cannot erase array in range [{},{}), because array size is {}",
                st, ed, size);

            return iterator(getArrayNode()->data_.erase(first.iter(), last.iter()));
        }

        void resize(int64_t n) {

            ICRAFT_CHECK_GE(n, 0).append("ValueError: cannot resize an Array to negative size");

            if (data_ == nullptr) {
                data_ = NodeType::Empty(capacity());
                return;
            }

            getArrayNode()->data_.resize(n);
        }

        void reserve(int64_t n) {

            if (data_ == nullptr) {
                data_ = NodeType::Empty(capacity());
                return;
            }

            getArrayNode()->data_.reserve(n);
        }

        void clear() {
            if (data_ != nullptr) {
                getArrayNode()->data_.clear();
            }
        }

    public:
        void set(int64_t index, T value) {

            // 检查：下标越界
            ICRAFT_CHECK(-(int64_t)size() <= index && index < (int64_t)size())
                .append("Index {} out of bounds {}", index, size());

            index = index >= 0 ? index : size() + index;

            getArrayNode()->data_[index] = std::move(value);
        }

        NodeType* getArrayNode() const { return static_cast<NodeType*>(data_.get()); }

        template <typename F, typename U = std::invoke_result_t<F, T>>
        Array<U> map(F fmap) const {

            auto arr = static_cast<NodeType*>(data_.get());

            Array<U> ans;

            for (auto it = arr->begin(); it != arr->end(); it++) {
                U mapped = fmap(ValueConverter::convert(*it));
                ans.push_back(mapped);
            }

            return ans;
        }

        template <typename F, typename = std::enable_if_t<std::is_same_v<bool, std::invoke_result_t<F, T>>>>
        Array<T> filter(F ffilter) const {

            auto node = getArrayNode();
            auto data = NodeType::CopyFrom(node->size(), node);
            FilterHelper(data, ffilter);

            return Array<T>::Get(std::move(data));
        }

        template <typename F, typename = std::enable_if_t<std::is_same_v<bool, std::invoke_result_t<F, T>>>>
        void remove(F fremove) {

            auto ffilter = [&fremove](T t) {
                return !fremove(std::move(t));
            };

            FilterHelper(data_, ffilter);
        }

        bool contains(T value) const {
            return std::any_of(begin(), end(), [&](auto i) { return i == value; });
        }

        bool exactContains(T value) const {
            return std::any_of(begin(), end(), [&](auto i) { return i.same_as(value); });
        }

        void reverse() {
            auto array_node = getArrayNode();
            std::reverse(array_node->begin(), array_node->end());
        }

        void swap(int64_t lhs_index, int64_t rhs_index) {
            auto array_node = getArrayNode();
            std::swap(array_node->data_[getUIndex(lhs_index)], array_node->data_[getUIndex(rhs_index)]);
        }

        template <typename IterType>
        void assign(IterType first, IterType last) {
            int64_t cap = std::distance(first, last);

            // 检查：
            ICRAFT_CHECK_GE(cap, 0).append("ValueError: cannot construct an Array of negative size");

            auto p = getArrayNode();
            if (p != nullptr && data_.unique() && p->capacity() >= cap) {
                // do not have to make new space
                p->clear();
            }
            else {
                // create new space
                data_ = NodeType::Empty(cap);
                p = getArrayNode();
            }

            for (auto it = first; it != last; it++) {
                p->data_.push_back(ElementNodeType(T(*it)));
            }
        }

        void concat(const Array<T>& rhs) {
            for (const auto& x : rhs) {
                this->push_back(x);
            }
        }

        void sort(std::function<bool(T, T)> comp) {

            if constexpr (std::is_pod_v<T>) {
                std::sort(getArrayNode()->data_.begin(), getArrayNode()->data_.end(), comp);
            }
            else {
                std::sort(getArrayNode()->data_.begin(), getArrayNode()->data_.end(),
                    [&](ObjectRef a, ObjectRef b) {
                        return comp(Downcast<T>(a), Downcast<T>(b));
                    }
                );
            }
        }

    private:
        uint64_t getUIndex(int64_t index, bool insert = false) const {

            auto array_size = this->size();

            if (insert) {
                array_size++;
            }

            // 检查：下标越界
            ICRAFT_CHECK(index >= -(int64_t)array_size && index < (int64_t)array_size)
                .append("index out of range, index = {} vs. size = {}", index, array_size);

            if (index < 0) {
                index += array_size;
            }

            return index;
        }

        template <typename F, typename = std::enable_if_t<std::is_same_v<bool, std::invoke_result_t<F, T>>>>
        static void FilterHelper(ObjectPtr<Object> data, F ffilter) {

            if (data == nullptr) {
                return;
            }

            // 检查：
            ICRAFT_CHECK(data->isInstance<NodeType>());

            auto arr = static_cast<NodeType*>(data.get());
            auto arr_size = arr->size();
            auto keep_map = std::vector<bool>(arr_size, false);
            size_t keep_num = 0;

            for (auto it = arr->begin(); it != arr->end(); it++) {
                if (ffilter(ValueConverter::convert(*it))) {
                    keep_map[it - arr->begin()] = true;
                    keep_num++;
                }
            }

            if (keep_num == arr_size) {
                return;
            }

            size_t keep_count = 0;
            for (auto i = 0; i < keep_map.size(); i++) {

                if (keep_map[i]) {

                    if (keep_count != i) {
                        arr->setItem(keep_count, std::move(arr->at(i)));
                    }

                    keep_count++;
                }
            }

            arr->shrinkBy(arr_size - keep_num);
        }
    };
}
</pre>
```
