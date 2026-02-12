# Class MemManagerNode

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 MemManagerNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class MemManagerNode : public icraft::xir::NodeBase<MemManagerNode, Node>#
```

表示内存管理器的抽象类 

## Protected Functions

```cpp
MemChunk CreateMemChunk(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter = nullptr, bool auto_free = true)#
```

---

## Protected Attributes

```cpp
const MemRegionNode *region = nullptr#
```

---

---

                