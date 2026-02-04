# Class SegTable

**Defined in:** `File buyi_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 SegTable,
 Handle,
 SegTableNode
 >
</code>

## Class Documentation#

```cpp
class SegTable : public icraft::xir::HandleBase<SegTable, Handle, SegTableNode>#
```

段表引用类 

## Public Functions

```cpp
SegTable() = default#
```

---

```cpp
inline SegTable(const std::array<uint32_t, 32> &logi_bases, const std::array<uint32_t, 32> &phy_bases, uint32_t size)#
```

---

---

                