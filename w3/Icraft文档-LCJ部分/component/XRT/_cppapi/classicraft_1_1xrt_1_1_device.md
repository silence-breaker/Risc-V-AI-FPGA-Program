# Class Device

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::VirtualBase<
 Device,
 Handle,
 DeviceNode
 >
</code>

## Class Documentation#

```cpp
class Device : public icraft::xir::VirtualBase<Device, Handle, DeviceNode>#
```

设备的引用类 

## Public Functions

```cpp
const MemRegion &defaultMemRegion() const#
```

获取设备默认的MemRegion 

---

```cpp
Device &setDefaultMemRegion(const std::string ®ion_name)#
```

将指定的MemRegion设置为默认MemRegion. 

```cpp
参数:
```

<dd class="field-odd"><strong>region_name</strong> – 指定的MemRegion名字 

---

---

```cpp
const MemRegion &getMemRegion(const std::string &name) const#
```

根据名字获取设备的MemRegion. 

```cpp
参数:
```

<dd class="field-odd"><strong>name</strong> – MemRegion的名字 

---

```cpp
返回:
```

<dd class="field-even">相对应的MemRegion对象 

---

---

```cpp
MemChunk malloc(uint64_t byte_size) const#
```

在默认的MemRegion上申请分配内存. 

```cpp
参数:
```

<dd class="field-odd"><strong>byte_size</strong> – 申请的内存大小 

---

```cpp
返回:
```

<dd class="field-even">申请得到的MemChunk对象 

---

---

```cpp
MemChunk malloc(const std::string &mem_region, uint64_t byte_size) const#
```

在指定的MemRegion上申请分配内存. 

```cpp
参数:
```

<dd class="field-odd">
<strong>mem_region</strong> – 指定的MemRegion的名字 

<strong>byte_size</strong> – 申请的内存大小 

---

```cpp
返回:
```

<dd class="field-even">申请得到的MemChunk对象 

---

---

```cpp
const RegRegion &defaultRegRegion() const#
```

获取设备默认的RegRegion 

---

```cpp
Device &setDefaultRegRegion(const std::string ®ion_name)#
```

将指定的RegRegion设置为默认RegRegion. 

```cpp
参数:
```

<dd class="field-odd"><strong>region_name</strong> – 指定的RegRegion名字 

---

---

```cpp
const RegRegion &getRegRegion(const std::string &name) const#
```

根据名字获取设备的RegRegion. 

```cpp
参数:
```

<dd class="field-odd"><strong>name</strong> – RegRegion的名字 

---

```cpp
返回:
```

<dd class="field-even">相对应的RegRegion对象 

---

---

```cpp
uint64_t readReg(uint64_t addr, bool relative = false) const#
```

在默认的RegRegion上读取寄存器. 

```cpp
参数:
```

<dd class="field-odd">
<strong>addr</strong> – 读取的地址 

<strong>relative</strong> – 是否以相对地址读取寄存器 

---

```cpp
返回:
```

<dd class="field-even">读取得到的寄存器数据 

---

---

```cpp
uint64_t readReg(const std::string ®ion_name, uint64_t addr, bool relative = false) const#
```

在指定的的RegRegion上读取寄存器. 

```cpp
参数:
```

<dd class="field-odd">
<strong>region_name</strong> – 指定的RegRegion的名字 

<strong>addr</strong> – 读取的地址 

<strong>relative</strong> – 是否以相对地址读取寄存器 

---

```cpp
返回:
```

<dd class="field-even">读取得到的寄存器数据 

---

---

```cpp
void writeReg(uint64_t addr, uint64_t data, bool relative = false) const#
```

将数据写入默认的RegRegion上的寄存器. 

```cpp
参数:
```

<dd class="field-odd">
<strong>addr</strong> – 写入的地址 

<strong>relative</strong> – 是否以相对地址写入寄存器 

---

---

```cpp
void writeReg(const std::string ®ion_name, uint64_t addr, uint64_t data, bool relative = false) const#
```

将数据写入指定的RegRegion上的寄存器. 

```cpp
参数:
```

<dd class="field-odd">
<strong>region_name</strong> – 指定的RegRegion的名字 

<strong>addr</strong> – 写入的地址 

<strong>data</strong> – 写入的数据 

<strong>relative</strong> – 是否以相对地址写入寄存器 

---

---

```cpp
void reset(int level)#
```

　复位设备. 

备注

复位等级，不同的设备具有不同的定义和实现，详见具体设备的使用说明 

```cpp
参数:
```

<dd class="field-odd"><strong>level</strong> – 复位等级

---

---

```cpp
bool check(int level) const#
```

　检查设备. 

备注

检查等级，不同的设备具有不同的定义和实现，详见具体设备的使用说明 

```cpp
参数:
```

<dd class="field-odd"><strong>level</strong> – 检查等级

---

---

```cpp
void showStatus(int level) const#
```

　显示设备状态. 

备注

状态等级，不同的设备具有不同的定义和实现，详见具体设备的使用说明 

```cpp
参数:
```

<dd class="field-odd"><strong>level</strong> – 状态等级

---

---

```cpp
std::unordered_map<std::string, std::string> version() const#
```

获取设备的版本. 

```cpp
返回:
```

<dd class="field-odd">表示设备各个版本信息的Map 

---

---

```cpp
void setWaitTime(uint64_t wait_time)#
```

设置同步tensor的最长等待时间 

```cpp
参数:
```

<dd class="field-odd"><strong>wait_time</strong> – 等待时间，单位ms 

---

---

## Public Static Functions

```cpp
static Device Open(const std::string &url)#
```

打开设备. 

```cpp
参数:
```

<dd class="field-odd"><strong>url</strong> – 设备的URL 

---

```cpp
返回:
```

<dd class="field-even">打开的设备对象 

---

---

```cpp
static void Close(Device &device)#
```

关闭设备. 

```cpp
参数:
```

<dd class="field-odd"><strong>被关闭的设备对象</strong> – 

---

---

---

                