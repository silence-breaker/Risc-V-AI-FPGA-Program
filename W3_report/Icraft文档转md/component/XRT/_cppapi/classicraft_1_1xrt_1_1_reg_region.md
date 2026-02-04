# Class RegRegion

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 RegRegion,
 Handle,
 RegRegionNode
 >
</code>

## Class Documentation#

```cpp
class RegRegion : public icraft::xir::HandleBase<RegRegion, Handle, RegRegionNode>#
```

## Public Functions

```cpp
uint64_t read(uint64_t addr, bool relative = false) const#
```

读取指定地址的数据. 

```cpp
参数:
```

<dd class="field-odd">
<strong>addr</strong> – 读取的地址 

<strong>relative</strong> – 是否以相对地址读取数据 

---

```cpp
返回:
```

<dd class="field-even">读取到的寄存器数据 

---

---

```cpp
void write(uint64_t addr, uint64_t data, bool relative = false) const#
```

将数据写入指定地址. 

```cpp
参数:
```

<dd class="field-odd">
<strong>addr</strong> – 写入的地址 

<strong>data</strong> – 写入的数据 

<strong>relative</strong> – 是否以相对地址写入数据 

---

---

```cpp
Device device() const#
```

获取该RegRegion所在的Device 

---

```cpp
RegRegion &_bindDevice(const DeviceNode *dev)#
```

绑定到所在的Device 

---

---

                