# Class MemPtr

**Defined in:** `File device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 MemPtr,
 Handle,
 MemPtrNode
 >
</code>

## Class Documentation#

```cpp
class MemPtr : public icraft::xir::HandleBase<MemPtr, Handle, MemPtrNode>#
```

表示XRT中的内存指针 

表示XRT中内存指针的引用类型 

## Public Functions

```cpp
MemPtr() = default#
```

默认构造函数 

---

```cpp
MemPtr(void *cptr, uint64_t addr)#
```

构造函数，构造一个PtrType::BOTH类型的MemPtr. 

```cpp
参数:
```

<dd class="field-odd">
<strong>cptr</strong> – C指针的值 

<strong>addr</strong> – 物理地址的值 

---

---

```cpp
explicit MemPtr(void *cptr)#
```

构造函数，构造一个PtrType::CPTR类型的MemPtr. 

```cpp
参数:
```

<dd class="field-odd"><strong>cptr</strong> – C指针的值 

---

---

```cpp
explicit MemPtr(uint64_t addr)#
```

构造函数，构造一个PtrType::ADDR类型的MemPtr. 

```cpp
参数:
```

<dd class="field-odd"><strong>addr</strong> – 物理地址的值 

---

---

```cpp
bool isNull() const#
```

检查该MemPtr是否是空指针 

---

```cpp
char *cptr() const#
```

获取该MemPtr的C指针. 

```cpp
抛出:
```

<dd class="field-odd">如果MemPtr为PtrType::ADDR类型时，抛出异常

 – 

---

---

```cpp
uint64_t addr() const#
```

获取该MemPtr的物理地址. 

```cpp
抛出:
```

<dd class="field-odd">如果MemPtr为PtrType::CPTR类型时，抛出异常

 – 

---

---

```cpp
PtrType ptype() const#
```

获取该MemPtr的类型 

---

## Public Static Functions

```cpp
static MemPtr NullPtr()#
```

创建一个空指针. 

备注

在XRT中，当且仅当MemPtr为PtrType::CPTR且cptr的值为nullptr时，认为这个MemPtr为空指针 

---

---

                