# Class MMUMapTableNode

**Defined in:** `File zg330_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 MMUMapTableNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class MMUMapTableNode : public icraft::xir::NodeBase<MMUMapTableNode, Node>#
```

mmu地址映射表 

## Public Functions

```cpp
inline virtual void accept(AttrVisitor &visitor) override#
```

---

## Public Members

```cpp
std::map<uint16_t, uint64_t> map_table#
```

---

```cpp
uint64_t chunk_addr = 0#
```

---

```cpp
uint64_t max_id = 0#
```

---

```cpp
uint64_t bytesize = 0#
```

---

```cpp
std::shared_ptr<uint32_t[]> buffer = nullptr#
```

---

---

                