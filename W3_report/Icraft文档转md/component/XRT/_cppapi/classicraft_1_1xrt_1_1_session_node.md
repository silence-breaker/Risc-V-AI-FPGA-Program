# Class SessionNode

**Defined in:** `File session.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::NodeBase<
 SessionNode,
 Node
 >
</code>

## Class Documentation#

```cpp
class SessionNode : public icraft::xir::NodeBase<SessionNode, Node>#
```

表示会话的类型. 

## Public Functions

```cpp
inline virtual void accept(AttrVisitor &visitor) override#
```

---

```cpp
~SessionNode()#
```

---

## Public Members

```cpp
std::vector<Backend> backends#
```

会话中的后端 

---

```cpp
NetworkView network_view#
```

会话中的网络视图 

---

---

                