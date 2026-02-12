# Function icraft::emxxToFp32
**Defined in:** `File numeric.h`

## Function Documentation

<a id="_CPPv4N6icraft10emxxToFp32E8uint16_t8uint32_t8uint32_t"></a>
```cpp
float icraft::emxxToFp32(uint16_t em_bits, uint32_t e_bits, uint32_t m_bits)
```

任意自定义的16bit的emxx格式数据 转换成 float32数据; 其中emxx的要求是sign(1bit) + e(指数位bit) + m(尾数位bit数) == 16 bf16、fp16、em78、em69等等都可以用该通用的函数; 该函数为后补充(for fp16、em69等等)，所以一些如bf16ToFp32也进行了保留; 

```cpp
参数:
```

<dd class="field-odd">

- em_bits – 输入的emxx数据

- e_bits – 输入的em格式数据的指数位bit数，比如fp16，则是5

- m_bits – 输入的em格式数据的尾数位bit数，比如fp16，则是10

---

```cpp
返回:
```

<dd class="field-even">
返回转换后的float数据 

---

---

                