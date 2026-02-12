# Class BasicSink
**Defined in:** `File logging.h`

## Inheritance Relationships

### Derived Types

- public FileSink ([Class FileSink](classicraft_1_1_file_sink.md#exhale-class-classicraft-1-1-file-sink))

- public StderrSink ([Class StderrSink](classicraft_1_1_stderr_sink.md#exhale-class-classicraft-1-1-stderr-sink))

- public StdoutSink ([Class StdoutSink](classicraft_1_1_stdout_sink.md#exhale-class-classicraft-1-1-stdout-sink))

[FileSink](classicraft_1_1_file_sink.md#classicraft_1_1_file_sink), [StderrSink](classicraft_1_1_stderr_sink.md#classicraft_1_1_stderr_sink), [StdoutSink](classicraft_1_1_stdout_sink.md#classicraft_1_1_stdout_sink)

## Public Functions

[https://github.com/gabime/spdlog/wiki/3.-Custom-formatting/](自定义格式)

---

---

<a id="_CPPv4N6icraft9BasicSink8setLevelE8LogLevel"></a>
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

<a id="_CPPv4NK6icraft9BasicSink5levelEv"></a>
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

<a id="_CPPv4N6icraft9BasicSink8setColorE8LogLevel8LogColor"></a>
```cpp
virtual void setColor(LogLevel level, LogColor color)
```

设置某日志等级对应的颜色 * 

```cpp
参数:
```

<dd class="field-odd">

- level – 日志等级

- color – 日志颜色

---

---

---

                