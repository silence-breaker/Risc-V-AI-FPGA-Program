# Template Class lock_guard
**Defined in:** `File mutex.hpp`

<a id="_CPPv4I0EN6icraft7midware4impl10lock_guardE"></a>
```cpp
template<class _Mutex>class lock_guard
```

## Public Types

<a id="_CPPv4N6icraft7midware4impl10lock_guard10mutex_typeE"></a>
```cpp
using mutex_type = _Mutex
```

---

## Public Functions

<a id="_CPPv4N6icraft7midware4impl10lock_guard10lock_guardER6_Mutex"></a>
```cpp
inline explicit lock_guard(_Mutex &_Mtx)
```

---

<a id="_CPPv4N6icraft7midware4impl10lock_guardD0Ev"></a>
```cpp
inline ~lock_guard() noexcept
```

---

<a id="_CPPv4N6icraft7midware4impl10lock_guard10lock_guardERK10lock_guard"></a>
```cpp
lock_guard(const lock_guard&) = delete
```

---

<a id="_CPPv4N6icraft7midware4impl10lock_guardaSERK10lock_guard"></a>
```cpp
lock_guard &operator=(const lock_guard&) = delete
```

---

---

                