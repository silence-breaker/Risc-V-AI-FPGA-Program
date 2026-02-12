# Class BuyiDevice

**Defined in:** `File buyi_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 BuyiDevice,
 Device,
 BuyiDeviceNode
 >
</code>

## Class Documentation#

```cpp
class BuyiDevice : public icraft::xir::HandleBase<BuyiDevice, Device, BuyiDeviceNode>#
```

布衣架构设备的引用类. 

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
void setDType(int dtype) const#
```

设置NPU计算的数据类型，是8位还是16位. 

```cpp
参数:
```

<dd class="field-odd"><strong>dtype</strong> – 数据类型，可选的有8和16 

---

---

```cpp
void icoreCalc(uint64_t addr, uint64_t size) const#
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
void setClkFreq(float clk_freq)#
```

设置运行频率. 

```cpp
参数:
```

<dd class="field-odd"><strong>clk_freq</strong> – 时钟频率 

---

---

```cpp
float clkFreq() const#
```

获取运行频率 

---

```cpp
uint32_t layerCount() const#
```

获取当前的执行计数 

---

```cpp
float calcTime() const#
```

获取执行时间（ms） 

---

```cpp
void setEnabledMPE(uint32_t rows, uint64_t cols)#
```

设置使能的MPE阵列. 

```cpp
参数:
```

<dd class="field-odd">
<strong>rows</strong> – 使能的行数 

<strong>cols</strong> – 使能的列数 

---

---

```cpp
void updateBuffer(const SegTable &seg_table)#
```

更新mmu段表 

```cpp
参数:
```

<dd class="field-odd"><strong>seg_table</strong> – mmu段表 

---

---

```cpp
void mmuModeSwitch(bool is_on)#
```

配置mmu模式 

```cpp
参数:
```

<dd class="field-odd"><strong>is_on</strong> – 是否打开mmu，true为打开 

---

---

```cpp
uint32_t modeInfo()#
```

获取当前mmu模式状态 

```cpp
返回:
```

<dd class="field-odd">1：mmu模式 

---

---

```cpp
bool isMock()#
```

---

```cpp
int getId()#
```

---

---

                