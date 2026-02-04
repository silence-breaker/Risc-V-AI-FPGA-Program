# Class DynamicProgressBars
**Defined in:** `File progress.h`

<a id="_CPPv4N6icraft19DynamicProgressBarsE"></a>
```cpp
class DynamicProgressBars
```

表示动态进度条的类 * 

DynamicProgressBars可以动态的添加和减少进度条 

## Public Functions

<a id="_CPPv4N6icraft19DynamicProgressBars19DynamicProgressBarsENSt6vectorI11ProgressBarEE"></a>
```cpp
DynamicProgressBars(std::vector<ProgressBar> bars)
```

构造函数，从ProgressBar的初始化列表构造 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>bars</strong> – ProgressBar的初始化列表 

---

---

<a id="_CPPv4N6icraft19DynamicProgressBarsixE6size_t"></a>
```cpp
ProgressBar &operator[](size_t index)
```

获取第 <em>index</em> 个进度条 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>index</strong> – 进度条的索引 

---

```cpp
返回:
```

<dd class="field-even">
<em>index</em> 处的进度条 

---

---

<a id="_CPPv4N6icraft19DynamicProgressBars6appendER11ProgressBar"></a>
```cpp
size_t append(ProgressBar &bar)
```

添加进度条 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>bar</strong> – 被添加的进度条 

---

```cpp
返回:
```

<dd class="field-even">
添加后总进度条的个数 

---

---

<a id="_CPPv4N6icraft19DynamicProgressBars19hideBarWhenCompleteEb"></a>
```cpp
void hideBarWhenComplete(bool hide)
```

是否隐藏完成的进度条 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>hide</strong> – 为true时隐藏 

---

---

---

                