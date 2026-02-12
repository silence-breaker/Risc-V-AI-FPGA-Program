# Class File
**Defined in:** `File filesystem.hpp`

<a id="_CPPv44File"></a>
```cpp
class File
```

## Public Functions

<a id="_CPPv4N4File4FileERKNSt6stringE4BYTE"></a>
```cpp
File(const std::string &path, BYTE mode)
```

---

<a id="_CPPv4N4File5writeERKNSt6stringE"></a>
```cpp
void write(const std::string &data)
```

---

<a id="_CPPv4N4File5closeEv"></a>
```cpp
void close()
```

---

<a id="_CPPv4N4File4readE4UINT"></a>
```cpp
std::string read(UINT size)
```

---

<a id="_CPPv4N4File4readEPc4UINT"></a>
```cpp
void read(char *to, UINT size)
```

---

<a id="_CPPv4N4File5writeERKNSt6vectorI4BYTEEE"></a>
```cpp
void write(const std::vector<BYTE> &data)
```

---

<a id="_CPPv4N4File5writeEPKc8uint64_t"></a>
```cpp
void write(const char *data, uint64_t size)
```

---

<a id="_CPPv4N4File10readBinaryE4UINT"></a>
```cpp
std::vector<BYTE> readBinary(UINT size)
```

---

<a id="_CPPv4NK4File4sizeEv"></a>
```cpp
FSIZE_t size() const
```

---

<a id="_CPPv4N4File4seekE7FSIZE_t"></a>
```cpp
void seek(FSIZE_t offset)
```

---

<a id="_CPPv4NK4File4tellEv"></a>
```cpp
FSIZE_t tell() const
```

---

<a id="_CPPv4N4File5flushEv"></a>
```cpp
void flush()
```

---

<a id="_CPPv4N4FileD0Ev"></a>
```cpp
~File()
```

---

---

                