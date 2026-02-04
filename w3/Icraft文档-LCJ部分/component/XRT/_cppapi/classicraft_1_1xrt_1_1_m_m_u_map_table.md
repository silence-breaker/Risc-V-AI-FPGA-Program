# Class MMUMapTable

**Defined in:** `File zg330_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 MMUMapTable,
 Handle,
 MMUMapTableNode
 >
</code>

## Class Documentation#

```cpp
class MMUMapTable : public icraft::xir::HandleBase<MMUMapTable, Handle, MMUMapTableNode>#
```

mmu地址映射表引用类 

## Public Functions

```cpp
MMUMapTable() = default#
```

---

```cpp
MMUMapTable(std::shared_ptr<uint32_t[]> buffer_, uint64_t max_id_)#
```

---

```cpp
MMUMapTable(const std::map<uint16_t, uint64_t> &map_table_)#
```

---

```cpp
void setMemChunkAddr(uint64_t addr)#
```

---

```cpp
void updateBuffer(uint16_t chunkid, uint64_t addr) const#
```

---

---

                