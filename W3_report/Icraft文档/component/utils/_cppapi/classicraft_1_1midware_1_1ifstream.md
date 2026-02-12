# Class ifstream
**Defined in:** `File filestream.hpp`

## Inheritance Relationships

### Base Type

- public istream

<a id="_CPPv4N6icraft7midware8ifstreamE"></a>
```cpp
class ifstream : public istream
```

## Public Functions

<a id="_CPPv4N6icraft7midware8ifstream8ifstreamEv"></a>
```cpp
ifstream()
```

---

<a id="_CPPv4N6icraft7midware8ifstream8ifstreamENSt11string_viewEb"></a>
```cpp
explicit ifstream(std::string_view path, bool binary = true)
```

---

<a id="_CPPv4N6icraft7midware8ifstream8ifstreamERKN6icraft7midware4pathEb"></a>
```cpp
inline explicit ifstream(const icraft::midware::path &p, bool binary = true)
```

---

<a id="_CPPv4N6icraft7midware8ifstreamD0Ev"></a>
```cpp
~ifstream()
```

---

<a id="_CPPv4N6icraft7midware8ifstream8ifstreamERK8ifstream"></a>
```cpp
ifstream(const ifstream&) = delete
```

---

<a id="_CPPv4N6icraft7midware8ifstreamaSERK8ifstream"></a>
```cpp
ifstream &operator=(const ifstream&) = delete
```

---

<a id="_CPPv4N6icraft7midware8ifstream8ifstreamERR8ifstream"></a>
```cpp
ifstream(ifstream&&) noexcept
```

---

<a id="_CPPv4N6icraft7midware8ifstreamaSERR8ifstream"></a>
```cpp
ifstream &operator=(ifstream&&) noexcept
```

---

<a id="_CPPv4N6icraft7midware8ifstream4openENSt11string_viewEb"></a>
```cpp
bool open(std::string_view path, bool binary = true)
```

---

<a id="_CPPv4N6icraft7midware8ifstream5closeEv"></a>
```cpp
void close()
```

---

<a id="_CPPv4N6icraft7midware8ifstream4readEPvNSt6size_tE"></a>
```cpp
std::size_t read(void *dst, std::size_t bytes)
```

---

<a id="_CPPv4NK6icraft7midware8ifstream9gcount_exEv"></a>
```cpp
inline std::size_t gcount_ex() const noexcept
```

---

<a id="_CPPv4N6icraft7midware8ifstream4seekE7int64_ti"></a>
```cpp
bool seek(int64_t offset, int origin)
```

---

<a id="_CPPv4NK6icraft7midware8ifstream4tellEv"></a>
```cpp
int64_t tell() const
```

---

<a id="_CPPv4NK6icraft7midware8ifstream4sizeEv"></a>
```cpp
int64_t size() const
```

---

<a id="_CPPv4NK6icraft7midware8ifstream7is_openEv"></a>
```cpp
bool is_open() const noexcept
```

---

<a id="_CPPv4NK6icraft7midware8ifstream4goodEv"></a>
```cpp
bool good() const noexcept
```

---

<a id="_CPPv4NK6icraft7midware8ifstream3eofEv"></a>
```cpp
bool eof() const noexcept
```

---

---

                