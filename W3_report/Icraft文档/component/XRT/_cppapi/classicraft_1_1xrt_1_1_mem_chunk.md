# Class MemChunk

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 MemChunk,
 Handle,
 MemChunkNode
 >
</code>

## Class Documentation#

```cpp
class MemChunk : public icraft::xir::HandleBase<MemChunk, Handle, MemChunkNode>#
```

内存块引用类 

## Public Functions

```cpp
MemChunk() = default#
```

默认构造函数 

---

```cpp
void read(char *dest, uint64_t src_offset, uint64_t byte_size) const#
```

读取指定偏移的数据. 

```cpp
参数:
```

<dd class="field-odd">
<strong>dest</strong> – 数据被读取到char*表示的缓存 

<strong>src_offset</strong> – 从该偏移开始读取数据 

<strong>byte_size</strong> – 读取数据的字节大小 

---

---

```cpp
void write(uint64_t dest_offset, char *src, uint64_t byte_size) const#
```

将数据写到指定偏移位置. 

```cpp
参数:
```

<dd class="field-odd">
<strong>dest_offset</strong> – 数据被写入的偏移位置 

<strong>src</strong> – char*表示的数据缓存 

<strong>byte_size</strong> – 写入数据的字节大小 

---

---

```cpp
void copyFrom(uint64_t dest_offset, const MemChunk &src_chunk, uint64_t src_offset, uint64_t byte_size) const#
```

从其它MemChunk复制数据. 

```cpp
参数:
```

<dd class="field-odd">
<strong>dest_offset</strong> – 目的偏移位置 

<strong>src_chunk</strong> – 源MemChunk 

<strong>src_offset</strong> – 源偏移位置 

<strong>byte_size</strong> – 复制的字节大小 

---

---

```cpp
void free()#
```

释放该MemChunk所占用的内存 

---

```cpp
bool isOn(const MemRegion ®ion) const#
```

检查该MemChunk是否位于某个MemRegion上 

---

```cpp
void setDeleter(FChunkDeleter deleter_) const#
```

设置自定义删除函数 

---

```cpp
void setAutoFree(bool auto_free) const#
```

设置是否autofree 

---

---

                