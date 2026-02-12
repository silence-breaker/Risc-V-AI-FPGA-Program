# Function icraft::SearchDLLByEnvVar
**Defined in:** `File dll.h`

## Function Documentation

<a id="_CPPv4N6icraft17SearchDLLByEnvVarERKNSt6stringERKNSt6stringE"></a>
```cpp
std::optional<std::string> icraft::SearchDLLByEnvVar(const std::string &target_name, const std::string &env_var)
```

在环境变量所指定的路径中搜索目标对应的DLL 

```cpp
参数:
```

<dd class="field-odd">

- target_name – 目标名称，即CMake中的target名称

- env_var – 环境变量的名称

---

---

                