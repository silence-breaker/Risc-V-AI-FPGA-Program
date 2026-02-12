# Class FileSink
**Defined in:** `File logging.h`

## Inheritance Relationships

### Base Type

- public BasicSink ([Class BasicSink](classicraft_1_1_basic_sink.md#exhale-class-classicraft-1-1-basic-sink))

<a id="_CPPv4N6icraft8FileSinkE"></a>
```cpp
class FileSink : public BasicSink
```

表示文件Sink的类 * 

使用FileSink可以将日志输出到指定文件中 

## Public Functions

<a id="_CPPv4N6icraft8FileSink8FileSinkERKNSt10filesystem4pathE"></a>
```cpp
explicit FileSink(const std::filesystem::path &file_path)
```

构造函数，从fs::path构造 

```cpp
参数:
```

<dd class="field-odd">
<strong>file_path</strong> – 表示文件路径的fs::path类型 

---

---

---

                