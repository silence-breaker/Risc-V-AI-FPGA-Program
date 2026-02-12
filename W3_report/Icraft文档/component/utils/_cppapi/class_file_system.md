# Class FileSystem
**Defined in:** `File filesystem.hpp`

<a id="_CPPv410FileSystem"></a>
```cpp
class FileSystem
```

## Public Functions

<a id="_CPPv4N10FileSystem10FileSystemEv"></a>
```cpp
FileSystem()
```

---

<a id="_CPPv4N10FileSystem10FileSystemERK10FileSystem"></a>
```cpp
FileSystem(const FileSystem&) = delete
```

---

<a id="_CPPv4N10FileSystem10FileSystemERR10FileSystem"></a>
```cpp
FileSystem(FileSystem&&) = delete
```

---

<a id="_CPPv4N10FileSystemaSERK10FileSystem"></a>
```cpp
FileSystem &operator=(const FileSystem&) = delete
```

---

<a id="_CPPv4N10FileSystemaSERR10FileSystem"></a>
```cpp
FileSystem &operator=(FileSystem&&) = delete
```

---

<a id="_CPPv4N10FileSystemD0Ev"></a>
```cpp
~FileSystem()
```

---

<a id="_CPPv4N10FileSystem6existsERKNSt6stringE"></a>
```cpp
bool exists(const std::string &path)
```

---

<a id="_CPPv4N10FileSystem16create_directoryERKNSt6stringE"></a>
```cpp
void create_directory(const std::string &path)
```

---

<a id="_CPPv4N10FileSystem6removeERKNSt6stringE"></a>
```cpp
void remove(const std::string &path)
```

---

<a id="_CPPv4N10FileSystem14list_directoryERKNSt6stringE"></a>
```cpp
std::vector<std::string> list_directory(const std::string &path)
```

---

## Public Static Functions

<a id="_CPPv4N10FileSystem8instanceEv"></a>
```cpp
static inline FileSystem &instance()
```

---

---

                