# Class path
**Defined in:** `File path.hpp`

<a id="_CPPv4N6icraft7midware4pathE"></a>
```cpp
class path
```

## Public Types

<a id="_CPPv4N6icraft7midware4path8native_tE"></a>
```cpp
using native_t = std::filesystem::path
```

---

## Public Functions

<a id="_CPPv4N6icraft7midware4path4pathEv"></a>
```cpp
path() = default
```

---

<a id="_CPPv4N6icraft7midware4path4pathEPKc"></a>
```cpp
inline explicit path(const char *s)
```

---

<a id="_CPPv4N6icraft7midware4path4pathENSt6stringE"></a>
```cpp
inline explicit path(std::string s)
```

---

<a id="_CPPv4N6icraft7midware4path4pathENSt11string_viewE"></a>
```cpp
inline explicit path(std::string_view s)
```

---

<a id="_CPPv4N6icraft7midware4path4pathERKNSt10filesystem4pathE"></a>
```cpp
inline explicit path(const std::filesystem::path &p)
```

---

<a id="_CPPv4N6icraft7midware4path4pathERRNSt10filesystem4pathE"></a>
```cpp
inline explicit path(std::filesystem::path &&p)
```

---

<a id="_CPPv4I_6size_tEN6icraft7midware4path4pathERA1N_Kc"></a>
```cpp
template<size_t N>inline explicit path(const char (&s)[N])
```

---

<a id="_CPPv4N6icraft7midware4pathdVERK4path"></a>
```cpp
inline path &operator/=(const path &other)
```

---

<a id="_CPPv4N6icraft7midware4pathaSERKNSt10filesystem4pathE"></a>
```cpp
inline path &operator=(const std::filesystem::path &p)
```

---

<a id="_CPPv4N6icraft7midware4pathaSERRNSt10filesystem4pathE"></a>
```cpp
inline path &operator=(std::filesystem::path &&p)
```

---

<a id="_CPPv4NK6icraft7midware4path11parent_pathEv"></a>
```cpp
inline path parent_path() const
```

---

<a id="_CPPv4NK6icraft7midware4path8filenameEv"></a>
```cpp
inline path filename() const
```

---

<a id="_CPPv4NK6icraft7midware4path4stemEv"></a>
```cpp
inline path stem() const
```

---

<a id="_CPPv4NK6icraft7midware4path9extensionEv"></a>
```cpp
inline path extension() const
```

---

<a id="_CPPv4N6icraft7midware4path17replace_extensionERK4path"></a>
```cpp
inline path &replace_extension(const path &ext)
```

---

<a id="_CPPv4NK6icraft7midware4path6stringEv"></a>
```cpp
inline std::string string() const
```

---

<a id="_CPPv4NK6icraft7midware4path5emptyEv"></a>
```cpp
inline bool empty() const
```

---

<a id="_CPPv4NK6icraft7midware4path6nativeEv"></a>
```cpp
inline const native_t &native() const
```

---

## Friends

<a id="_CPPv4N6icraft7midware4pathdvE4pathRK4path"></a>
```cpp
inline friend path operator/(path lhs, const path &rhs)
```

---

<a id="_CPPv4N6icraft7midware4patheqERK4pathRK4path"></a>
```cpp
inline friend bool operator==(const path &a, const path &b)
```

---

<a id="_CPPv4N6icraft7midware4pathneERK4pathRK4path"></a>
```cpp
inline friend bool operator!=(const path &a, const path &b)
```

---

---

                