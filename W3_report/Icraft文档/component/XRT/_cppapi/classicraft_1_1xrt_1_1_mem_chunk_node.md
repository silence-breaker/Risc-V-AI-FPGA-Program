# Class MemChunkNode

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 MemChunkNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class MemChunkNode : public icraft::xir::NodeBase<MemChunkNode, Node>#
```

表示一块连续的内存块 

## Public Functions

```cpp
virtual void accept(AttrVisitor &visitor) override#
```

---

```cpp
inline bool reduceAccept(MemChunkNode *other, const ReduceVisitor &reduce) const#
```

---

```cpp
~MemChunkNode() noexcept#
```

析构函数 

---

## Public Members

```cpp
MemPtr begin#
```

内存块开始的位置 

---

```cpp
uint64_t byte_size#
```

内存块的字节大小 

---

```cpp
MemRegion region#
```

内存块所在的内存区域 

---

---

                