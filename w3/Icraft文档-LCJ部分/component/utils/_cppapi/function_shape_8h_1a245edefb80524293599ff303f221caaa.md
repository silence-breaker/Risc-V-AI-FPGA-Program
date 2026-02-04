# Function icraft::getBroadcastShape
**Defined in:** `File shape.h`

## Function Documentation

<a id="_CPPv4N6icraft17getBroadcastShapeENSt6vectorI7int64_tEENSt6vectorI7int64_tEE"></a>
```cpp
std::vector<int64_t> icraft::getBroadcastShape(std::vector<int64_t> left, std::vector<int64_t> right)
```

计算两个形状广播后的形状 

```cpp
参数:
```

<dd class="field-odd">

- left – 形状1

- right – 形状2

---

```cpp
抛出:
```

<dd class="field-even">
<span class="cpp-expr sig sig-inline cpp">如果不能广播则抛出异常</span> – 

---

```cpp
返回:
```

<dd class="field-odd">
两个形状广播后的形状 

---

---

                