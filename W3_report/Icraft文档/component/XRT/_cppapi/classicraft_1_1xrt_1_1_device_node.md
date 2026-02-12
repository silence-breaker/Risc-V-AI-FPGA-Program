# Class DeviceNode

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 DeviceNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class DeviceNode : public icraft::xir::NodeBase<DeviceNode, Node>#
```

表示设备的类型 

## Public Functions

```cpp
inline virtual void accept(AttrVisitor &visitor) override#
```

---

## Public Members

```cpp
std::string url#
```

设备的URL 

---

```cpp
std::string protocol#
```

设备的协议名 

---

```cpp
std::string device#
```

设备的设备名 

---

```cpp
std::string site#
```

设备的位置名 

---

```cpp
std::unordered_map<std::string, std::string> params#
```

设备的参数 

---

```cpp
uint64_t wait_time = 10000#
```

---

## Protected Attributes

```cpp
std::unordered_map<std::string_view, MemRegion> mem_regions#
```

---

```cpp
std::unordered_map<std::string_view, RegRegion> reg_regions#
```

---

```cpp
MemRegion default_mem_region#
```

---

```cpp
RegRegion default_reg_region#
```

---

```cpp
std::vector<std::string_view> mregion_names#
```

---

```cpp
std::vector<std::string_view> rregion_names#
```

---

## Friends

```cpp
friend class Device
```

---

                