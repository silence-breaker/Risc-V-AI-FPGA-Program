# Function icraft::GetDLLFileName
**Defined in:** `File dll.h`

## Function Documentation

<a id="_CPPv4N6icraft14GetDLLFileNameERKNSt6stringE"></a>
```cpp
std::string icraft::GetDLLFileName(const std::string &target_name)
```

根据目标名称获取其动态链接库的文件名 

```cpp
参数:
```

<dd class="field-odd">
<strong>target_name</strong> – 目标名称 

---

```cpp
返回:
```

<dd class="field-even">
Windows下为 target_name + “.dll”; Linux下为 “lib” + target_name + “.so”; 

---

---

                