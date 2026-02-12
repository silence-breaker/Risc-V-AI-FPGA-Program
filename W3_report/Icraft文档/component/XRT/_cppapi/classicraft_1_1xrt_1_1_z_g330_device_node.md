# Class ZG330DeviceNode

**Defined in:** `File zg330_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 ZG330DeviceNode,
 DeviceNode
 >
</code>

## Class Documentation#

```cpp
class ZG330DeviceNode : public icraft::xir::NodeBase<ZG330DeviceNode, DeviceNode>#
```

表示ZG330架构的设备. 

## Public Members

```cpp
uint64_t timer_addr = 0#
```

---

```cpp
uint64_t timer_bytes = 0#
```

---

```cpp
uint64_t profiler_addr = 0#
```

---

```cpp
uint64_t profiler_bytes = 0#
```

---

```cpp
MMUMapTable mmu_table#
```

---

```cpp
int master_cid = 1#
```

---

```cpp
int sub_cols = 2#
```

---

```cpp
uint64_t icore_clk_freq = 1000E6#
```

---

```cpp
uint64_t ddr_clk_freq = 333E6#
```

---

## Protected Functions

```cpp
virtual void initAfterRegions() override#
```

---

```cpp
virtual void reset(int level) override#
```

---

```cpp
virtual bool check(int level) const override#
```

---

```cpp
virtual void showStatus(int level) const override#
```

---

```cpp
virtual std::unordered_map<std::string, std::string> version() const override#
```

---

```cpp
uint32_t readReg(uint32_t cid, uint32_t rid, uint32_t offset) const#
```

---

```cpp
void writeReg(uint32_t cid, uint32_t rid, uint32_t offset, uint32_t data) const#
```

---

```cpp
std::pair<int, int> getRowsCols() const#
```

---

```cpp
double calcTime() const#
```

---

```cpp
void dmaMemcpy(uint64_t dest, uint64_t src, uint64_t byte_size, int timeout) const#
```

PL间数据拷贝，地址和数据长度需64字节对齐 

---

```cpp
std::shared_ptr<char[]> readOcmData() const#
```

获取ocm上所有的数据. 

```cpp
返回:
```

<dd class="field-odd">ocm上的数据，数据长度2MB 

---

---

```cpp
void writeOcmData(const std::shared_ptr<char[]> data, uint64_t byte_size) const#
```

写ocm上的数据. 

```cpp
参数:
```

<dd class="field-odd">
<strong>data</strong> – 写ocm的数据 

<strong>byte_size</strong> – 数据长度，需小于2MB 

---

---

---

                