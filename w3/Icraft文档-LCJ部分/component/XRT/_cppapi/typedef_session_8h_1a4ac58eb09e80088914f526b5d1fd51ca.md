# Typedef icraft::xrt::TimeProfileResults

**Defined in:** `File session.h`


                  
  

## Typedef Documentation#

```cpp
using icraft::xrt::TimeProfileResults = std::unordered_map<int64_t, std::tuple<double, double, double, double>>#
```

表示时间分析结果的类型. 该类型是一个Map，其键表示Op ID，值表示不同的时间类型，依次如下： 

总时间，即墙上时间

数据复制时间

硬件计算时间

其他时间 

---

                