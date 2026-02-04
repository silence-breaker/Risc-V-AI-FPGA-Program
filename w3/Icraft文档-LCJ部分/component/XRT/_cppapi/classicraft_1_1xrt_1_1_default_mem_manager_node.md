# Class DefaultMemManagerNode

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 DefaultMemManagerNode,
 MemManagerNode
 >
</code>

## Class Documentation#

```cpp
class DefaultMemManagerNode : public icraft::xir::NodeBase<DefaultMemManagerNode, MemManagerNode>#
```

默认的内存管理器 

## Public Functions

```cpp
inline DefaultMemManagerNode(MemPtr start, uint64_t byte_size)#
```

---

```cpp
virtual MemChunk malloc(uint64_t byte_size, bool auto_free, uint64_t alignment) override#
```

---

```cpp
virtual MemChunk malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter, bool auto_free) override#
```

---

```cpp
virtual void free(const MemPtr &ptr) override#
```

---

```cpp
virtual std::vector<MemChunk> getAllMemChunk() const override#
```

---

```cpp
virtual std::map<std::string, ObjectRef> &getMemRegionInfo() const override#
```

---

## Public Members

```cpp
MemPtr start_#
```

---

```cpp
uint64_t byte_size_#
```

---

```cpp
std::list<std::pair<MemPtr, uint64_t>> chunk_list_#
```

---

```cpp
std::vector<const MemChunkNode*> chunk_node_#
```

---

```cpp
mutable std::map<std::string, ObjectRef> info_#
```

---

```cpp
mutable midware::Mutex mem_mutex_#
```

---

---

                