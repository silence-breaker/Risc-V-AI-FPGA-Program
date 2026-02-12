# Class ofstream
**Defined in:** `File filestream.hpp`

## Inheritance Relationships

### Base Type

- public ostream

<a id="_CPPv4N6icraft7midware8ofstreamE"></a>
```cpp
class ofstream : public ostream
```

## Public Functions

<a id="_CPPv4N6icraft7midware8ofstream8ofstreamEv"></a>
```cpp
ofstream()
```

---

<a id="_CPPv4N6icraft7midware8ofstream8ofstreamENSt11string_viewEbb"></a>
```cpp
explicit ofstream(std::string_view path, bool binary = true, bool append = false)
```

---

<a id="_CPPv4N6icraft7midware8ofstream8ofstreamERKN6icraft7midware4pathEbb"></a>
```cpp
inline explicit ofstream(const icraft::midware::path &p, bool binary = true, bool append = false)
```

---

<a id="_CPPv4N6icraft7midware8ofstreamD0Ev"></a>
```cpp
~ofstream()
```

---

<a id="_CPPv4N6icraft7midware8ofstream8ofstreamERK8ofstream"></a>
```cpp
ofstream(const ofstream&) = delete
```

---

<a id="_CPPv4N6icraft7midware8ofstreamaSERK8ofstream"></a>
```cpp
ofstream &operator=(const ofstream&) = delete
```

---

<a id="_CPPv4N6icraft7midware8ofstream8ofstreamERR8ofstream"></a>
```cpp
ofstream(ofstream&&) noexcept
```

---

<a id="_CPPv4N6icraft7midware8ofstreamaSERR8ofstream"></a>
```cpp
ofstream &operator=(ofstream&&) noexcept
```

---

<a id="_CPPv4N6icraft7midware8ofstream4openENSt11string_viewEbb"></a>
```cpp
bool open(std::string_view path, bool binary = true, bool append = false)
```

---

<a id="_CPPv4N6icraft7midware8ofstream5closeEv"></a>
```cpp
void close()
```

---

<a id="_CPPv4N6icraft7midware8ofstream5writeEPKvNSt6size_tE"></a>
```cpp
std::size_t write(const void *src, std::size_t bytes)
```

---

<a id="_CPPv4N6icraft7midware8ofstream5flushEv"></a>
```cpp
void flush()
```

---

<a id="_CPPv4N6icraft7midware8ofstream4seekE7int64_ti"></a>
```cpp
bool seek(int64_t offset, int origin)
```

---

<a id="_CPPv4NK6icraft7midware8ofstream4tellEv"></a>
```cpp
int64_t tell() const
```

---

<a id="_CPPv4NK6icraft7midware8ofstream7is_openEv"></a>
```cpp
bool is_open() const noexcept
```

---

<a id="_CPPv4NK6icraft7midware8ofstream4goodEv"></a>
```cpp
bool good() const noexcept
```

---

---

                