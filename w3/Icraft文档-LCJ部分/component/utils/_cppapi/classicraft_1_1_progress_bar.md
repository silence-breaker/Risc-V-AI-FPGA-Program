# Class ProgressBar
**Defined in:** `File progress.h`

<a id="_CPPv4N6icraft11ProgressBarE"></a>
```cpp
class ProgressBar
```

表示进度条的类 * 

使用ProgressBar可以在显示一个进度条并控制进度 

## Public Functions

<a id="_CPPv4N6icraft11ProgressBar11ProgressBarEv"></a>
```cpp
ProgressBar()
```

构造函数 

---

<a id="_CPPv4N6icraft11ProgressBar11ProgressBarE9ColorName"></a>
```cpp
explicit ProgressBar(ColorName color)
```

构造函数，从颜色构造 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>color</strong> – 颜色名称 

---

---

<a id="_CPPv4N6icraft11ProgressBar8setColorE9ColorName"></a>
```cpp
void setColor(ColorName color)
```

设置进度条颜色 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>color</strong> – 颜色名称 

---

---

<a id="_CPPv4N6icraft11ProgressBar11setProgressEf"></a>
```cpp
void setProgress(float progress)
```

设置进度条进度 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>progress</strong> – 进度条进度 

---

---

<a id="_CPPv4NK6icraft11ProgressBar8progressEv"></a>
```cpp
float progress() const
```

获取进度条进度 * 

```cpp
返回:
```

<dd class="field-odd">
进度条进度 

---

---

<a id="_CPPv4N6icraft11ProgressBar4tickEv"></a>
```cpp
void tick()
```

进度前进1 

---

<a id="_CPPv4N6icraft11ProgressBar4tickEi"></a>
```cpp
void tick(int progress)
```

进度前进 <em>progress</em> * 

```cpp
参数:
```

<dd class="field-odd">
<strong>progress</strong> – 前进的进度 

---

---

<a id="_CPPv4N6icraft11ProgressBar13setPrefixTextERKNSt6stringE"></a>
```cpp
void setPrefixText(const std::string &text)
```

设置前置文本 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>text</strong> – 前置文本 

---

---

<a id="_CPPv4N6icraft11ProgressBar14setPostfixTextERKNSt6stringE"></a>
```cpp
void setPostfixText(const std::string &text)
```

设置后置文本 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>text</strong> – 后置文本 

---

---

<a id="_CPPv4N6icraft11ProgressBar15showElapsedTimeEb"></a>
```cpp
void showElapsedTime(bool show)
```

是否显示消耗时间 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>show</strong> – 为true时显示消耗时间 

---

---

<a id="_CPPv4N6icraft11ProgressBar17showRemainingTimeEb"></a>
```cpp
void showRemainingTime(bool show)
```

是否显示剩余时间 * 

```cpp
参数:
```

<dd class="field-odd">
<strong>show</strong> – 为true时显示剩余时间 

---

---

<a id="_CPPv4N6icraft11ProgressBar7currentEv"></a>
```cpp
float current()
```

获取当前进度 * 

```cpp
返回:
```

<dd class="field-odd">
当前进度 

---

---

<a id="_CPPv4N6icraft11ProgressBar11isCompletedEv"></a>
```cpp
bool isCompleted()
```

进度条是否完成 * 

```cpp
返回:
```

<dd class="field-odd">
完成时返回true 

---

---

<a id="_CPPv4N6icraft11ProgressBar15markAsCompletedEv"></a>
```cpp
void markAsCompleted()
```

标记进度条已完成 

---

---

                