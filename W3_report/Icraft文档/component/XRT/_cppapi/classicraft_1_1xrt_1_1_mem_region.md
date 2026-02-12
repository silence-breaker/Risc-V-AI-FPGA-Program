# Class MemRegion

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::VirtualBase<
 MemRegion,
 Handle,
 MemRegionNode
 >
</code>

## Class Documentation#

```cpp
class MemRegion : public icraft::xir::VirtualBase<MemRegion, Handle, MemRegionNode>#
```

内存区域引用类 

## Public Functions

```cpp
void free(const MemPtr &src) const#
```

释放指定位置的内存 

备注

除了Device开发，否则不应直接调用该方法，而应该使用MemChunk的free方法 

```cpp
参数:
```

<dd class="field-odd"><strong>src</strong> – 指定的内存位置

---

---

```cpp
void read(char *dest, const MemPtr &src, uint64_t byte_size) const#
```

读取指定位置的数据. 

备注

除了Device开发，否则不应直接调用该方法，而应该使用MemChunk的read方法 

```cpp
参数:
```

<dd class="field-odd">
<strong>dest</strong> – 数据被读取到char*表示的缓存 

<strong>src</strong> – 从该位置开始读取数据 

<strong>byte_size</strong> – 读取数据的字节大小

---

---

```cpp
void write(const MemPtr &dest, char *src, uint64_t byte_size) const#
```

将数据写到指定位置. 

备注

除了Device开发，否则不应直接调用该方法，而应该使用MemChunk的write方法 

```cpp
参数:
```

<dd class="field-odd">
<strong>dest</strong> – 数据被写入的位置 

<strong>src</strong> – char*表示的数据缓存 

<strong>byte_size</strong> – 写入数据的字节大小

---

---

```cpp
void memcpy(const MemPtr &dest, const MemPtr &src, uint64_t byte_size) const#
```

在指定的内存位置间复制数据 

备注

除了Device开发，否则不应直接调用该方法，而应该使用MemChunk的memcpy方法 

```cpp
参数:
```

<dd class="field-odd">
<strong>dest</strong> – 内存复制的目的位置 

<strong>src</strong> – 内存复制的源位置 

<strong>byte_size</strong> – 内存复制的字节大小

---

---

```cpp
void memcpy(const MemPtr &dest_ptr, const MemRegion &src_region, const MemPtr &src_ptr, uint64_t byte_size) const#
```

跨MemRegion复制数据 

备注

除了Device开发，否则不应直接调用该方法，而应该使用MemChunk的memcpy方法 

```cpp
参数:
```

<dd class="field-odd">
<strong>dest_ptr</strong> – 内存复制的目的位置 

<strong>src_region</strong> – 内存复制的源MemRegion 

<strong>src_ptr</strong> – 内存复制的源位置 

<strong>byte_size</strong> – 内存复制的字节大小

---

---

```cpp
MemRegion() = default#
```

---

```cpp
MemChunk malloc(uint64_t byte_size, bool auto_free = true, uint64_t alignment = 1) const#
```

申请分配指定大小的内存. 

```cpp
参数:
```

<dd class="field-odd">
<strong>byte_size</strong> – 分配内存的大小 

<strong>auto_free</strong> – 指定分配的内存是否会被自动释放 

<strong>alignment</strong> – 指定分配的内存地址字节对齐 

---

---

```cpp
MemChunk malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter = nullptr, bool auto_free = true) const#
```

申请分配指定位置开始的内存. 

```cpp
参数:
```

<dd class="field-odd">
<strong>byte_size</strong> – 分配内存的大小 

<strong>deleter</strong> – 内存释放的自定义函数，若指定了FChunkDeleter，则调用该函数来释放内存 

<strong>auto_free</strong> – 指定分配的内存是否会被自动释放 

---

---

```cpp
MemRegion &_bindDevice(const DeviceNode *dev)#
```

绑定所在的设备 

---

```cpp
void _bindMemmanager(const MemManagerNode *manager)#
```

绑定内存分配器 

---

```cpp
Device device() const#
```

获取所在的Device 

---

```cpp
const MemManager memManager() const#
```

获取所属的MemManager 

---

---

                