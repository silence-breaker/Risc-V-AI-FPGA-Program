# Class UrlParser

**Defined in:** `File device.h`


                  
  

## Class Documentation#

```cpp
class UrlParser#
```

解析URL的工具类 

## Public Functions

```cpp
UrlParser(const std::string &url)#
```

构造函数. 

```cpp
参数:
```

<dd class="field-odd"><strong>url</strong> – 被解析的UTL字符串 

---

---

```cpp
const std::string &url() const#
```

获取URL 

---

```cpp
const std::string &protocol() const#
```

获取解析后的协议名 

---

```cpp
const std::string &device() const#
```

获取解析后的设备名 

---

```cpp
const std::string &site() const#
```

获取解析后的位置名 

---

```cpp
const std::unordered_map<std::string, std::string> ¶ms() const#
```

获取解析后的所有参数 

---

```cpp
const std::string &getParam(const std::string &key) const#
```

根据键值获取参数值. 

```cpp
参数:
```

<dd class="field-odd"><strong>key</strong> – 键值 

---

```cpp
返回:
```

<dd class="field-even">参数值 

---

---

---

                