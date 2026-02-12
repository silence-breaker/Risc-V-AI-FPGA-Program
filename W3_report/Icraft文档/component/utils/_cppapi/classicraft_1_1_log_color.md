# Class LogColor
**Defined in:** `File logging.h`

<a id="_CPPv4N6icraft8LogColorE"></a>
```cpp
class LogColor
```

表示日志颜色的类 * 

对ANSI Color做了封装，可以获取常见颜色对应的控制字符串 

## Public Functions

<a id="_CPPv4N6icraft8LogColor8LogColorE9ColorName9ColorName"></a>
```cpp
LogColor(ColorName fg_color, ColorName bg_color)
```

构造函数，从前景和背景的颜色名构造对象 * 

```cpp
参数:
```

<dd class="field-odd">

- fg_color – 前景颜色名

- bg_color – 背景颜色名

---

---

## Public Static Functions

<a id="_CPPv4N6icraft8LogColor9ForegroudE9ColorName"></a>
```cpp
static LogColor Foregroud(ColorName name)
```

从颜色名获取对应的前景色 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>name</strong> – 颜色名 

---

```cpp
返回:
```

<dd class="field-even">
表示前景色的LogColor对象 

---

---

<a id="_CPPv4N6icraft8LogColor10BackgroundE9ColorName"></a>
```cpp
static LogColor Background(ColorName name)
```

从颜色名获取对应的背景色 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>name</strong> – 颜色名 

---

```cpp
返回:
```

<dd class="field-even">
表示背景色的LogColor对象 

---

---

---

                