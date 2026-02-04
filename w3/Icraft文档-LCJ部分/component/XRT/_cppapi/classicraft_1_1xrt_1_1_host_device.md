# Class HostDevice

**Defined in:** `File host_device.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 HostDevice,
 Device,
 HostDeviceNode
 >
</code>

## Class Documentation#

```cpp
class HostDevice : public icraft::xir::HandleBase<HostDevice, Device, HostDeviceNode>#
```

## Public Static Functions

```cpp
static HostDevice &Default()#
```

获取全局默认的HostDevice对象. 

---

```cpp
static HostMemRegion &MemRegion()#
```

获取全局默认的HostDevice的内存区域对象. 

---

---

                