# Class SegTableNode

**Defined in:** `File buyi_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 SegTableNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class SegTableNode : public icraft::xir::NodeBase<SegTableNode, Node>#
```

段表类，记录段表中的逻辑地址和物理地址等相关数据 

## Public Functions

```cpp
inline virtual void accept(AttrVisitor &visitor) override#
```

---

```cpp
inline virtual bool reduceAccept(Node *other, const ReduceVisitor &reduce) const override#
```

---

## Public Members

```cpp
std::array<uint32_t, 32> logic_bases_#
```

---

```cpp
std::array<uint32_t, 32> phy_bases_#
```

---

```cpp
uint32_t size = 0#
```

---

---

                