# Class Tensor

**Defined in:** `File tensor.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 Tensor,
 Handle,
 TensorNode
 >
</code>

## Class Documentation#

```cpp
class Tensor : public icraft::xir::HandleBase<Tensor, Handle, TensorNode>#
```

张量的引用类. 

## Public Types

```cpp
using CheckFunc = std::function<bool(const Device &device)>#
```

Tensor的检查函数，用于检查是否ready 

---

## Public Functions

```cpp
Tensor() = default#
```

默认构造函数 

---

```cpp
Tensor(TensorType dtype, MemChunk chunk, uint64_t offset = 0, CheckFunc check_func = nullptr)#
```

构造函数. 

```cpp
参数:
```

<dd class="field-odd">
<strong>dtype</strong> – 数据类型 

<strong>chunk</strong> – 数据所在的内存块 

<strong>offset</strong> – 数据在内存块中的偏移 

<strong>check_func</strong> – 状态检查函数 

---

---

```cpp
Tensor(TensorType dtype, CheckFunc func = nullptr)#
```

构造函数，构造一个没有数据的Tensor. 

```cpp
参数:
```

<dd class="field-odd">
<strong>dtype</strong> – 数据类型 

<strong>check_func</strong> – 状态检查函数 

---

---

```cpp
Tensor(const icraft::xir::Value &value)#
```

构造函数，从xir::Value构造. 

---

```cpp
Tensor(const icraft::xir::Params ¶ms)#
```

构造函数，从xir::Params构造. 

---

```cpp
Tensor &setDType(TensorType dtype)#
```

设置张量的数据类型. 

```cpp
参数:
```

<dd class="field-odd"><strong>dtype</strong> – 被设置的数据类型 

---

---

```cpp
Tensor &setData(MemChunk chunk, uint64_t offset = 0)#
```

设置张量数据所在的内存块. 

```cpp
参数:
```

<dd class="field-odd">
<strong>chunk</strong> – 数据所在内存块 

<strong>offset</strong> – 数据在内存块中的偏移 

---

---

```cpp
Tensor &setCheckFunc(CheckFunc check_func)#
```

设置张量的数据检查函数. 

```cpp
参数:
```

<dd class="field-odd"><strong>check_func</strong> – 状态检查函数 

---

---

```cpp
Tensor &setReady(bool ready)#
```

设置张量的的状态. 

```cpp
参数:
```

<dd class="field-odd"><strong>ready</strong> – 状态是否ready 

---

---

```cpp
Tensor &mallocOn(const MemRegion &mregion)#
```

在指定的MemRegion上分配Tensor所需要的内存. 

备注

如果Tensor已经分配了内存块，该方法会覆盖原有的内存块 

```cpp
参数:
```

<dd class="field-odd"><strong>mregion</strong> – 指定的MemRegion

---

---

```cpp
void copyFrom(uint64_t dest_offset, const Tensor &src_tensor, uint64_t src_offset, uint64_t byte_size)#
```

从指定的Tensor复制数据. 

```cpp
参数:
```

<dd class="field-odd">
<strong>dest_offset</strong> – 目标偏移位置 

<strong>src_tensor</strong> – 源Tensor 

<strong>src_offset</strong> – 源偏移位置 

<strong>byte_size</strong> – 字节大小 

---

---

```cpp
MemPtr data() const#
```

获取该Tensor数据的起始位置指针 

---

```cpp
const MemChunk &chunk() const#
```

获取该Tensor数据所在的内存块 

---

```cpp
uint64_t offset() const#
```

获取该Tensor数据在内存块中的偏移 

---

```cpp
const TensorType &dtype() const#
```

获取该Tensor的数据类型 

---

```cpp
bool isReady() const#
```

检查该Tensor是否ready 

---

```cpp
bool hasData() const#
```

检查该Tensor是否具有数据 

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
Tensor to(const MemRegion &mregion) const#
```

@biref 将Tensor复制到指定的MemRegion的上. 

备注

如果该Tensor已经在指定的MemRegion上，则复制不会发生，而是直接返回原Tensor 

```cpp
参数:
```

<dd class="field-odd"><strong>mregion</strong> – 指定的MemRegion 

---

```cpp
返回:
```

<dd class="field-even">在指定MemRegion复制得到的Tensor

---

---

```cpp
bool isOn(const MemRegion &mregion) const#
```

检查该Tensor是否在指定的MemRegion上. 

```cpp
模板参数:
```

<dd class="field-odd"><strong>mregion</strong> – 指定的MemRegion 

---

---

```cpp
const MemRegion &memRegion() const#
```

获取该Tensor所在的MemRegion 

---

```cpp
void dump(std::ostream &os, const std::string &format = "") const#
```

将Tensor的数据按指定格式导出到指定的输出流中. 

若一个Tensor原本的排布时H，那么可以转为S；若原本的数值为Q，那么可以转为F；反之不可 

备注

支持的格式由三个字母表示：
第一个字母表示排布，H表示硬件，S表示软件

第二个字母表示数值，F表示浮点，Q表示定点

第三个字母表示序列化形式，B表示二进制，T表示文本

```cpp
参数:
```

<dd class="field-odd">
<strong>os</strong> – 指定的输出流 

<strong>format</strong> – 指定的输出格式

---

---

```cpp
template<typename Rep, typename Period>inline bool waitForReady(std::chrono::duration<Rep, Period> timeout, std::chrono::duration<Rep, Period> sleep = std::chrono::duration<Rep, Period>::zero()) const#
```

等待Tensor的状态ready. 

```cpp
参数:
```

<dd class="field-odd">
<strong>timeout</strong> – 等待的超时时间，超时则返回false 

<strong>sleep</strong> – 两次查询之间的休眠时间，默认为0 

---

```cpp
返回:
```

<dd class="field-even">若timeout时间内查询到状态ready则返回true，否则返回false 

---

---

```cpp
template<typename T, typename = typename std::enable_if_t<std::is_pod_v<T>>>inline Tensor &fill(std::function<T(uint64_t)> f)#
```

填充数据 

```cpp
模板参数:
```

<dd class="field-odd"><strong>T</strong> – 被填充数据的类型，必须是POD 

---

```cpp
参数:
```

<dd class="field-even"><strong>f</strong> – 数据的生成函数，以index作为参数返回对应的T 

---

---

---

                