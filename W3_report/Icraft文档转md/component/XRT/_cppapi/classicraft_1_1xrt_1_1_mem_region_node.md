# Class MemRegionNode

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 MemRegionNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class MemRegionNode : public icraft::xir::NodeBase<MemRegionNode, Node>#
```

表示内存区域的类. 内存区域表示一块受管理的内存空间，比如NPU的PLDDR或者PS上的UDMABuf区域 

## Public Functions

```cpp
inline virtual void accept(AttrVisitor &visitor) override#
```

---

## Protected Attributes

```cpp
const DeviceNode *dev_ = nullptr#
```

---

```cpp
mutable MemManager mm_#
```

---

## Protected Static Functions

```cpp
static MemChunk CreateMemChunk(MemPtr begin, uint64_t byte_size, MemRegion region, FChunkDeleter deleter = nullptr, bool auto_free = true)#
```

---

---

                