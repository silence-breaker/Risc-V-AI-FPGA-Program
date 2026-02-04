# Class DeviceRegistry

**Defined in:** `File device.h`


                  
  

## Class Documentation#

```cpp
class DeviceRegistry#
```

Device的注册辅助类型 

## Public Types

```cpp
using FCreator = std::function<Device()>#
```

Device创建函数的原型 

---

## Public Functions

```cpp
DeviceRegistry &set_creator(FCreator f)#
```

设置Device创建函数 

---

```cpp
std::vector<std::string_view> ListNames()#
```

获取所有注册Device的名称列表 

---

## Public Static Functions

```cpp
static DeviceRegistry &Register(std::string_view name, bool can_override = false)#
```

注册Device. 

```cpp
参数:
```

<dd class="field-odd">
<strong>name</strong> – Device的名字 

<strong>can_override</strong> – 是否允许覆盖, 默认为否 

---

---

```cpp
static bool Remove(const std::string &name)#
```

移除注册的Device. 

```cpp
参数:
```

<dd class="field-odd"><strong>name</strong> – Device的名字 

---

```cpp
返回:
```

<dd class="field-even">如果Device不存在返回false, 否则返回true 

---

---

```cpp
static std::optional<FCreator> Get(const std::string &name)#
```

获取注册的Device. 

```cpp
参数:
```

<dd class="field-odd"><strong>name</strong> – Device的名字 

---

```cpp
返回:
```

<dd class="field-even">Device创建函数的Optional 

---

---

---

                