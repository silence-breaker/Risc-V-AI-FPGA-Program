# Class InternalError
**Defined in:** `File logging.h`

## Inheritance Relationships

### Base Type

- public Error ([Class Error](classicraft_1_1_error.md#exhale-class-classicraft-1-1-error))

<a id="_CPPv4N6icraft13InternalErrorE"></a>
```cpp
class InternalError : public Error
```

内部错误，由LOG(FATAL)产生，携带backtrace信息 

## Public Functions

<a id="_CPPv4N6icraft13InternalError13InternalErrorENSt6stringEiNSt6stringEiN12system_clock10time_pointENSt6stringE"></a>
```cpp
InternalError(std::string file, int lineno, std::string msg, int err_code, system_clock::time_point time = system_clock::now(), std::string backtrace = BackTrace::Get())
```

InternalError构造函数，不建议直接使用，请使用`LOG(EXCEPT)` *. 

```cpp
参数:
```

<dd class="field-odd">

- file – 错误发生的源文件

- lineno – 错误发生的行号

- msg – 错误信息

- time – 错误发生的时间

- backtrace – 错误发生时的backtrace

---

---

<a id="_CPPv4NK6icraft13InternalError4fileEv"></a>
```cpp
const std::string &file() const
```

```cpp
返回:
```

<dd class="field-odd">
错误发生的源文件路径 

---

---

<a id="_CPPv4NK6icraft13InternalError3msgEv"></a>
```cpp
const std::string &msg() const
```

```cpp
返回:
```

<dd class="field-odd">
错误信息 

---

---

<a id="_CPPv4NK6icraft13InternalError7fullMsgEv"></a>
```cpp
const std::string &fullMsg() const
```

```cpp
返回:
```

<dd class="field-odd">
包含文件、行号、backtrace和错误信息的格式化字符串 

---

---

<a id="_CPPv4NK6icraft13InternalError9backtraceEv"></a>
```cpp
const std::string &backtrace() const
```

```cpp
返回:
```

<dd class="field-odd">
错误发生时的backtrace 

---

---

<a id="_CPPv4NK6icraft13InternalError4timeEv"></a>
```cpp
const system_clock::time_point &time() const
```

```cpp
返回:
```

<dd class="field-odd">
错误发生的时间 

---

---

<a id="_CPPv4NK6icraft13InternalError6linenoEv"></a>
```cpp
int lineno() const
```

```cpp
返回:
```

<dd class="field-odd">
错误发生的行号 

---

---

<a id="_CPPv4NK6icraft13InternalError4whatEv"></a>
```cpp
virtual const char *what() const noexcept
```

---

<a id="_CPPv4NK6icraft13InternalError9errorCodeEv"></a>
```cpp
const int errorCode() const
```

```cpp
返回:
```

<dd class="field-odd">
错误码 

---

---

<a id="_CPPv4N6icraft13InternalError7rethrowENSt6stringENSt6stringEii"></a>
```cpp
void rethrow(std::string info, std::string file, int line, int err_code)
```

---

---

                