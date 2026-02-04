# Template Function icraft::xrt::utils::WaitUntil

**Defined in:** `File device.h`


                  
  

## Function Documentation#

```cpp
template<typename predicate, typename Rep, typename Period>static bool icraft::xrt::utils::WaitUntil(predicate check, std::chrono::duration<Rep, Period> timeout)#
```

不断查询某个条件是否满足，若满足则返回true，若一段时间不满足则停止查询且返回false. 

```cpp
参数:
```

<dd class="field-odd">
<strong>check</strong> – 被查询的条件函数，该函数返回true时认为条件满足 

<strong>timeout</strong> – 超过timeout时间仍不满足则返回false 

---

---

                