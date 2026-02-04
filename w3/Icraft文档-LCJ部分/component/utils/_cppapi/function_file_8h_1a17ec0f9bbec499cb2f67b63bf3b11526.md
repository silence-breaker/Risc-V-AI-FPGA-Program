# Function icraft::safeLoadFileMidware(const std::filesystem::path&, std::ios_base::openmode)
**Defined in:** `File file.h`

## Function Documentation

<a id="_CPPv4N6icraft19safeLoadFileMidwareERKNSt10filesystem4pathENSt8ios_base8openmodeE"></a>
```cpp
icraft::midware::ifstream icraft::safeLoadFileMidware(const std::filesystem::path &filename, std::ios_base::openmode mode = std::ios_base::in)
```

安全加载文件 

```cpp
参数:
```

<dd class="field-odd">

- filename – 文件名

- mode – 加载模式

---

```cpp
抛出:
```

<dd class="field-even">
<span class="cpp-expr sig sig-inline cpp">如果文件不存在或无法正常打开则抛出异常</span> – 

---

```cpp
返回:
```

<dd class="field-odd">
文件流 

---

---

                