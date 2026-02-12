# Function icraft::getKVfromTomlFile
**Defined in:** `File toml.h`

## Function Documentation

<a id="_CPPv4N6icraft17getKVfromTomlFileERKNSt6stringERKNSt6stringE"></a>
```cpp
std::map<std::string, std::string> icraft::getKVfromTomlFile(const std::string &filename, const std::string &command)
```

从TOML文件获取某个section下的键值对 

```cpp
参数:
```

<dd class="field-odd">

- filename – 文件名

- command – section名称

---

```cpp
抛出:
```

<dd class="field-even">
<span class="cpp-expr sig sig-inline cpp">如果没有此section则抛出异常</span> – 

---

```cpp
返回:
```

<dd class="field-odd">
TOML文件对应的toml::table 

---

---

                