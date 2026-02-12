# Function icraft::fp32ToEmxx
**Defined in:** `File numeric.h`

## Function Documentation

<a id="_CPPv4N6icraft10fp32ToEmxxEf8uint32_t8uint32_t"></a>
```cpp
uint16_t icraft::fp32ToEmxx(float value, uint32_t e_bits, uint32_t m_bits)
```

float32数据转成任意自定义的16bit的emxx格式数据; 其中emxx的要求是sign(1bit) + e(指数位bit) + m(尾数位bit数) == 16 bf16、fp16、em78、em69等等都可以用该通用的函数; 该函数为后补充(for fp16、em69等等)，所以上述的fp32ToBf16等等也依旧进行了保留; 

```cpp
参数:
```

<dd class="field-odd">

- value – 输入的float数据

- e_bits – 转换的em格式数据的指数位bit数，比如fp16，则是5

- m_bits – 转换的em格式数据的尾数位bit数，比如fp16，则是10

---

---

                