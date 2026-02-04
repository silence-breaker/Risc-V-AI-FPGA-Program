# Program Listing for File map.h



↰ [Return to documentation for file](file_icraft-xir_base_map.h.md#file-icraft-xir-base-map-h) (`icraft-xir\base\map.h`)


```cpp
#pragma once
#include <unordered_map>
#include <icraft-xir/base/optional.h>

namespace icraft::xir {

    class MapNode : public Object {
    public:

        using key_type = ObjectRef;

        using mapped_type = ObjectRef;

        using ContainerType = std::unordered_map<ObjectRef, ObjectRef, ObjectHash, ObjectEqual>;

        using iterator = ContainerType::iterator;

        using const_iterator = ContainerType::const_iterator;

        using KVType = ContainerType::value_type;

        static_assert(std::is_standard_layout<KVType>::value, "KVType is not standard layout");
        static_assert(sizeof(KVType) == 32 || sizeof(KVType) == 16 || sizeof(KVType) == 8, "sizeof(KVType) incorrect");

        size_t size() const { return data_.size(); }

        size_t count(const key_type& key) const { return data_.count(key); }

        const mapped_type& at(const key_type& key) const { return data_.at(key); }

        mapped_type& at(const key_type& key) { return data_.at(key); }

        iterator begin() { return data_.begin(); }

        const_iterator begin() const { return data_.begin(); }

        iterator end() { return data_.end(); }

        const_iterator end() const { return data_.end(); }

        const_iterator find(const key_type& key) const { return data_.find(key); }

        iterator find(const key_type& key) { return data_.find(key); }

        void erase(const iterator& position) { data_.erase(position); }

        void erase(const key_type& key) { data_.erase(key); }

        static ObjectPtr<MapNode> Empty() { return make_object<MapNode>(); }

        static ObjectPtr<MapNode> CopyFrom(const MapNode* from) {
            ObjectPtr<MapNode> p = make_object<MapNode>();
            p->data_ = ContainerType(from->data_.begin(), from->data_.end());
            return p;
        }

    protected:

        template <typename IterType>
        static ObjectPtr<Object> CreateFromRange(IterType first, IterType last) {
            ObjectPtr<MapNode> p = make_object<MapNode>();
            p->data_ = ContainerType(first, last);
            return p;
        }

        ContainerType data_;
        template <typename, typename, typename, typename>
        friend class Map;
    };

    template <typename K, typename V,
        typename = typename std::enable_if_t<std::is_base_of_v<ObjectRef, K>>,
        typename = typename std::enable_if_t<std::is_base_of_v<ObjectRef, V>>>
    class Map : public ObjectRef {
    public:
        using key_type = K;
        using mapped_type = V;

        class iterator;

        Map() { data_ = MapNode::Empty(); }

        Map(Map<K, V>&& other) { data_ = std::move(other.data_); }

        Map(const Map<K, V>& other) : ObjectRef(other.data_) {}

        Map<K, V>& operator=(Map<K, V>&& other) {
            data_ = std::move(other.data_);
            return *this;
        }

        Map<K, V>& operator=(const Map<K, V>& other) {
            data_ = other.data_;
            return *this;
        }

        explicit Map(ObjectPtr<Object> n) : ObjectRef(n) {}

        template <typename IterType>
        Map(IterType begin, IterType end) {
            data_ = MapNode::CreateFromRange(begin, end);
        }

        Map(std::initializer_list<std::pair<K, V>> init) {
            data_ = MapNode::CreateFromRange(init.begin(), init.end());
        }

        template <typename Hash, typename Equal>
        Map(const std::unordered_map<K, V, Hash, Equal>& init) {                // NOLINT(*)
            data_ = MapNode::CreateFromRange(init.begin(), init.end());
        }

        V at(const K& key) const { return DowncastNoCheck<V>(getMapNode()->at(key)); }

        V operator[](const K& key) const { return this->at(key); }

        size_t size() const {
            MapNode* n = getMapNode();
            return n == nullptr ? 0 : n->size();
        }

        size_t count(const K& key) const {
            MapNode* n = getMapNode();
            return n == nullptr ? 0 : getMapNode()->count(key);
        }

        bool empty() const {
            return size() == 0;
        }

        void clear() {
            if (getMapNode() != nullptr) {
                data_ = MapNode::Empty();
            }
        }

        void set(const K& key, const V& value) {
            getMapNode()->data_[key] = value;
        }

        iterator begin() const { return iterator(getMapNode()->begin()); }

        iterator end() const { return iterator(getMapNode()->end()); }

        iterator find(const K& key) const { return iterator(getMapNode()->find(key)); }

        Optional<V> get(const K& key) const {
            MapNode::iterator iter = getMapNode()->find(key);
            if (iter == getMapNode()->end()) {
                return NullOptType{};
            }

            return DowncastNoCheck<V>(iter->second);
        }

        void erase(const K& key) {
            getMapNode()->erase(key);
        }

        void merge(const Map<K, V>& rhs) {
            for (const auto& p : rhs) {
                this->set(p.first, p.second);
            }
        }

        Map<K, V> clone(int64_t depth = 1) const {
            return Downcast<Map<K, V>>(ObjectRef::clone(depth));
        }

        using NodeType = MapNode;

        class iterator {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = int64_t;
            using value_type = const std::pair<K, V>;
            using pointer = value_type*;
            using reference = value_type;

            iterator() : itr() {}

            bool operator==(const iterator& other) const { return itr == other.itr; }
            bool operator!=(const iterator& other) const { return itr != other.itr; }
            pointer operator->() const = delete;

            reference operator*() const {
                auto& kv = *itr;
                return std::make_pair(DowncastNoCheck<K>(kv.first), DowncastNoCheck<V>(kv.second));
            }

            iterator& operator++() {
                ++itr;
                return *this;
            }

            iterator operator++(int) {
                iterator copy = *this;
                ++(*this);
                return copy;
            }

        private:
            iterator(const MapNode::iterator& itr) : itr(itr) {}                    // NOLINT(*)

            template <typename, typename, typename, typename>
            friend class Map;

            MapNode::iterator itr;
        };

        static Map Get(ObjectPtr<Object> node) { return Map(node);}

    private:
        MapNode* getMapNode() const { return static_cast<MapNode*>(data_.get()); }
    };
}
</pre>
```
