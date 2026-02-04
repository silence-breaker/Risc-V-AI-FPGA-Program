# Class MemManager

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::VirtualBase<
 MemManager,
 Handle,
 MemManagerNode
 >
</code>

## Class Documentation#

```cpp
class MemManager : public icraft::xir::VirtualBase<MemManager, Handle, MemManagerNode>#
```

内存管理器的引用类 

## Public Functions

```cpp
void _bindMemRegion(const MemRegionNode *region)#
```

绑定所属的Memregion 

---

```cpp
MemChunk malloc(uint64_t byte_size, bool auto_free, uint64_t alignment)#
```

---

```cpp
MemChunk malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter, bool auto_free)#
```

---

```cpp
void free(const MemPtr &ptr)#
```

---

```cpp
std::vector<MemChunk> getAllMemChunk() const#
```

获得当前已分配的所有MemChunk 

---

```cpp
std::optional<MemChunk> getMemChunk(const MemPtr &ptr, uint64_t byte_size) const#
```

获取指定的已分配内存. 

```cpp
参数:
```

<dd class="field-odd">
<strong>ptr</strong> – 内存起始位置 

<strong>byte_size</strong> – 内存大小 

---

```cpp
返回:
```

<dd class="field-even">若指定起始位置和大小的内存存在，返回对应的MemChunk，否则返回nullopt 

---

---

```cpp
std::map<std::string, ObjectRef> &getMemRegionInfo() const#
```

获得设备信息，不同设备保存的信息不同，详见具体设备的内存管理器使用说明 

---

---

                