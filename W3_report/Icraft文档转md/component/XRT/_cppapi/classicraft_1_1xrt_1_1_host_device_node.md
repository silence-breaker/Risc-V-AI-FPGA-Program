# Class HostDeviceNode

**Defined in:** `File host_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 HostDeviceNode,
 DeviceNode
 >
</code>

## Class Documentation#

```cpp
class HostDeviceNode : public icraft::xir::NodeBase<HostDeviceNode, DeviceNode>#
```

表示Host设备的类型. 

## Public Functions

```cpp
inline ICRAFT_DECLARE_DEVICE_NODE(HostDeviceNode)#
```

---

```cpp
inline virtual void initBeforeRegions() override#
```

实现init接口 

---

```cpp
inline virtual void initAfterRegions() override#
```

---

```cpp
inline virtual void deinitBeforeRegions() override#
```

实现deinit接口 

---

```cpp
inline virtual void deinitAfterRegions() override#
```

---

```cpp
inline virtual void reset(int level) override#
```

实现reset接口 

---

```cpp
inline virtual bool check(int level) const override#
```

实现check接口 

---

```cpp
inline virtual void showStatus(int level) const override#
```

实现showStatus接口 

---

```cpp
inline virtual std::unordered_map<std::string, std::string> version() const override#
```

实现version接口 

---

---

                