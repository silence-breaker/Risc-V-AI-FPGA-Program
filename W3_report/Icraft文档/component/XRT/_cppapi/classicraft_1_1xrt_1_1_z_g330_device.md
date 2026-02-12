# Class ZG330Device

**Defined in:** `File zg330_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 ZG330Device,
 Device,
 ZG330DeviceNode
 >
</code>

## Class Documentation#

```cpp
class ZG330Device : public icraft::xir::HandleBase<ZG330Device, Device, ZG330DeviceNode>#
```

ZG330架构设备的引用类. 

## Public Functions

```cpp
std::pair<int, int> getRowsCols() const#
```

获取设备使能的MPE的行数和列数. 

```cpp
返回:
```

<dd class="field-odd">std::pair表示的行数和列数 

---

---

```cpp
uint32_t readReg(uint32_t cid, uint32_t rid, uint32_t offset) const#
```

读指定行列位置的寄存器. 

```cpp
参数:
```

<dd class="field-odd">
<strong>cid</strong> – 列ID 

<strong>rid</strong> – 行ID 

<strong>offset</strong> – 偏移地址 

---

```cpp
返回:
```

<dd class="field-even">读取的寄存器值 

---

---

```cpp
void writeReg(uint32_t cid, uint32_t rid, uint32_t offset, uint32_t data) const#
```

写指定行列位置的寄存器. 

```cpp
参数:
```

<dd class="field-odd">
<strong>cid</strong> – 列ID 

<strong>rid</strong> – 行ID 

<strong>offset</strong> – 偏移地址 

<strong>data</strong> – 写入的数据 

---

---

```cpp
void icoreCalc(uint64_t addr, uint64_t size)#
```

启动Icore计算. 

```cpp
参数:
```

<dd class="field-odd">
<strong>addr</strong> – 指令地址 

<strong>size</strong> – 指令长度 

---

---

```cpp
uint32_t layerCount() const#
```

获取当前的执行计数 

---

```cpp
uint32_t wTileCount(int cid) const#
```

获取当前的写Tile计数 

---

```cpp
uint32_t rTileCount(int cid) const#
```

获取当前的读Tile计数 

---

```cpp
float calcTime() const#
```

获取执行时间（ms） 

---

```cpp
void configTimer(const MemChunk &chunk)#
```

配置计时器的空间 

---

```cpp
void configProfiler(const MemChunk &chunk)#
```

配置Profiler的空间 

---

```cpp
void setMasterCID(int master_cid)#
```

设置master_cid 

---

```cpp
void setIcoreClkFreq(uint64_t freq_hz)#
```

设置Icore的时钟频率(Hz) 

---

```cpp
void setDDRClkFreq(uint64_t freq_hz)#
```

设置DDR的时钟频率(Hz) 

---

```cpp
void setOpWait(int reg_idx, uint32_t data)#
```

设置握手状态 

---

```cpp
uint32_t getOpWait(int reg_idx)#
```

获得握手状态 

---

```cpp
void setMMUMode(bool enable)#
```

设置mmu使能状态 

---

```cpp
bool getMMUMode()#
```

获取mmu使能状态 

---

```cpp
void updateMMU(const MMUMapTable &mmu_map_table)#
```

更新mmu映射表基址 

---

```cpp
void clearMMUCache()#
```

清除mmu缓存表 

---

```cpp
void showLayerTime(int from_idx, int op_cnt) const#
```

输出显示计时结果 

---

```cpp
std::vector<double> getLayerTime(int layer_cnt)#
```

获取计时结果，单位毫秒 

---

---

                