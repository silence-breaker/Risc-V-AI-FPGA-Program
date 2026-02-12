# Class BuyiDeviceNode

**Defined in:** `File buyi_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 BuyiDeviceNode,
 DeviceNode
 >
</code>

## Class Documentation#

```cpp
class BuyiDeviceNode : public icraft::xir::NodeBase<BuyiDeviceNode, DeviceNode>#
```

表示布衣架构设备的类型. 

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
float calcTime() const#
```

---

---

                