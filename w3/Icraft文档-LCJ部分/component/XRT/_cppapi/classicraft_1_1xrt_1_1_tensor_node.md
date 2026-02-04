# Class TensorNode

**Defined in:** `File tensor.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 TensorNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class TensorNode : public icraft::xir::NodeBase<TensorNode, Node>#
```

表示张量的类型. 

## Public Functions

```cpp
inline virtual void accept(AttrVisitor &visitor) override#
```

---

```cpp
inline bool reduceAccept(TensorNode *other, const ReduceVisitor &reduce) const#
```

---

---

                