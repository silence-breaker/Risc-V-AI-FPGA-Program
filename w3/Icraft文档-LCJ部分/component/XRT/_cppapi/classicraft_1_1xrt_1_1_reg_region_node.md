# Class RegRegionNode

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 RegRegionNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class RegRegionNode : public icraft::xir::NodeBase<RegRegionNode, Node>#
```

表示寄存器区域的类 

## Public Functions

```cpp
inline virtual void accept(AttrVisitor &visitor) override#
```

---

## Protected Attributes

```cpp
const DeviceNode *dev_ = nullptr#
```

---

---

                