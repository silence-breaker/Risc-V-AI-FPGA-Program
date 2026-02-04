# Class FileStreamBuf
**Defined in:** `File filesystem.hpp`

## Inheritance Relationships

### Base Type

- public streambuf

<a id="_CPPv413FileStreamBuf"></a>
```cpp
class FileStreamBuf : public streambuf
```

## Public Functions

<a id="_CPPv4N13FileStreamBuf13FileStreamBufER4File"></a>
```cpp
FileStreamBuf(File &file)
```

---

## Protected Functions

<a id="_CPPv4N13FileStreamBuf9underflowEv"></a>
```cpp
int_type underflow() override
```

---

<a id="_CPPv4N13FileStreamBuf8overflowE8int_type"></a>
```cpp
int_type overflow(int_type ch) override
```

---

<a id="_CPPv4N13FileStreamBuf4syncEv"></a>
```cpp
int sync() override
```

---

<a id="_CPPv4N13FileStreamBuf7seekoffE8off_typeNSt8ios_base7seekdirENSt8ios_base8openmodeE"></a>
```cpp
pos_type seekoff(off_type off, std::ios_base::seekdir way, std::ios_base::openmode which) override
```

---

<a id="_CPPv4N13FileStreamBuf7seekposE8pos_typeNSt8ios_base8openmodeE"></a>
```cpp
pos_type seekpos(pos_type pos, std::ios_base::openmode which) override
```

---

---

                