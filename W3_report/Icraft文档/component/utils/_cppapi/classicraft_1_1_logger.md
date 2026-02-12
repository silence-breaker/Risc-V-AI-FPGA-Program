# Class Logger
**Defined in:** `File logging.h`

[https://github.com/gabime/spdlog/wiki/3.-Custom-formatting/](自定义格式)

---

---

<a id="_CPPv4N6icraft6Logger8setLevelE8LogLevel"></a>
```cpp
void setLevel(LogLevel level)
```

设置日志等级 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>level</strong> – 日志等级 

---

---

<a id="_CPPv4NK6icraft6Logger5levelEv"></a>
```cpp
LogLevel level() const
```

获取日志等级 * 

```cpp
返回:
```

<dd class="field-odd">
日志等级 

---

---

<a id="_CPPv4N6icraft6Logger3logE8LogLevelNSt11string_viewE"></a>
```cpp
void log(LogLevel level, std::string_view msg)
```

记录日志信息 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>level</strong> – 日志等级 &#64;msg msg 日志信息 

---

---

<a id="_CPPv4IDpEN6icraft6Logger5debugEvNSt6stringEDpRR4Args"></a>
```cpp
template<typename ...Args>inline void debug(std::string fmt, Args&&... args)
```

记录日志debug信息 

---

<a id="_CPPv4IDpEN6icraft6Logger4infoEvNSt6stringEDpRR4Args"></a>
```cpp
template<typename ...Args>inline void info(std::string fmt, Args&&... args)
```

记录日志info信息 

---

<a id="_CPPv4IDpEN6icraft6Logger4warnEvNSt6stringEDpRR4Args"></a>
```cpp
template<typename ...Args>inline void warn(std::string fmt, Args&&... args)
```

记录日志warn信息 

---

<a id="_CPPv4IDpEN6icraft6Logger5errorEvNSt6stringEDpRR4Args"></a>
```cpp
template<typename ...Args>inline void error(std::string fmt, Args&&... args)
```

记录日志error信息 

---

<a id="_CPPv4IDpEN6icraft6Logger5fatalEvNSt6stringEDpRR4Args"></a>
```cpp
template<typename ...Args>inline void fatal(std::string fmt, Args&&... args)
```

记录日志fatal信息 

---

<a id="_CPPv4N6icraft6Logger5debugERKNSt11string_viewE"></a>
```cpp
void debug(const std::string_view &msg)
```

记录日志debug信息 

---

<a id="_CPPv4N6icraft6Logger4infoERKNSt11string_viewE"></a>
```cpp
void info(const std::string_view &msg)
```

记录日志info信息 

---

<a id="_CPPv4N6icraft6Logger4warnERKNSt11string_viewE"></a>
```cpp
void warn(const std::string_view &msg)
```

记录日志warn信息 

---

<a id="_CPPv4N6icraft6Logger5errorERKNSt11string_viewE"></a>
```cpp
void error(const std::string_view &msg)
```

记录日志error信息 

---

<a id="_CPPv4N6icraft6Logger5fatalERKNSt11string_viewE"></a>
```cpp
void fatal(const std::string_view &msg)
```

记录日志fatal信息 

---

## Public Static Functions

<a id="_CPPv4N6icraft6Logger6GlobalEv"></a>
```cpp
static Logger &Global()
```

获取全局默认Logger单例 * 

备注

不建议直接使用，请使用LOG(level)宏 

---

---

                