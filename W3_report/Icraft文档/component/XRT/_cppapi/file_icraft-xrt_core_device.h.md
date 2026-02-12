# File device.h


                  
  

↰ [Parent directory](dir_icraft-xrt_core.md#dir-icraft-xrt-core) (<code class="docutils literal notranslate">icraft-xrt\core
</code>)

<nav class="contents local" id="contents">
Contents

[Definition (icraft-xrt\core\device.h)](#definition-icraft-xrt-core-device-h)

[Includes](#includes)

[Included By](#included-by)

[Namespaces](#namespaces)

[Classes](#classes)

[Functions](#functions)

[Defines](#defines)

[Typedefs](#typedefs)

</nav>

## Definition (icraft-xrt\core\device.h)#

[Program Listing for File device.h](program_listing_file_icraft-xrt_core_device.h.md)

## Includes#

<code class="docutils literal notranslate">chrono
</code>

<code class="docutils literal notranslate">cstdint
</code>

<code class="docutils literal notranslate">functional
</code>

<code class="docutils literal notranslate">icraft-utils/midware/mutex.hpp
</code>

<code class="docutils literal notranslate">icraft-xir/base/map.h
</code>

<code class="docutils literal notranslate">icraft-xir/base/string.h
</code>

<code class="docutils literal notranslate">icraft-xir/core/data.h
</code>

<code class="docutils literal notranslate">icraft-xir/core/reflection.h
</code>

<code class="docutils literal notranslate">icraft-xrt/base/dllexport.h
</code>

<code class="docutils literal notranslate">list
</code>

<code class="docutils literal notranslate">map
</code>

<code class="docutils literal notranslate">vector
</code>

## Included By#

[File tensor.h](file_icraft-xrt_core_tensor.h.md#file-icraft-xrt-core-tensor-h)

[File buyi_device.h](file_icraft-xrt_dev_buyi_device.h.md#file-icraft-xrt-dev-buyi-device-h)

[File host_device.h](file_icraft-xrt_dev_host_device.h.md#file-icraft-xrt-dev-host-device-h)

[File zg330_device.h](file_icraft-xrt_dev_zg330_device.h.md#file-icraft-xrt-dev-zg330-device-h)

## Namespaces#

[Namespace icraft](namespace_icraft.md#namespace-icraft)

[Namespace icraft::xrt](namespace_icraft__xrt.md#namespace-icraft-xrt)

[Namespace icraft::xrt::utils](namespace_icraft__xrt__utils.md#namespace-icraft-xrt-utils)

## Classes#

[Class DefaultMemManager](classicraft_1_1xrt_1_1_default_mem_manager.md#exhale-class-classicraft-1-1xrt-1-1-default-mem-manager)

[Class DefaultMemManagerNode](classicraft_1_1xrt_1_1_default_mem_manager_node.md#exhale-class-classicraft-1-1xrt-1-1-default-mem-manager-node)

[Class Device](classicraft_1_1xrt_1_1_device.md#exhale-class-classicraft-1-1xrt-1-1-device)

[Class DeviceNode](classicraft_1_1xrt_1_1_device_node.md#exhale-class-classicraft-1-1xrt-1-1-device-node)

[Class DeviceRegistry](classicraft_1_1xrt_1_1_device_registry.md#exhale-class-classicraft-1-1xrt-1-1-device-registry)

[Class MemChunk](classicraft_1_1xrt_1_1_mem_chunk.md#exhale-class-classicraft-1-1xrt-1-1-mem-chunk)

[Class MemChunkNode](classicraft_1_1xrt_1_1_mem_chunk_node.md#exhale-class-classicraft-1-1xrt-1-1-mem-chunk-node)

[Class MemManager](classicraft_1_1xrt_1_1_mem_manager.md#exhale-class-classicraft-1-1xrt-1-1-mem-manager)

[Class MemManagerNode](classicraft_1_1xrt_1_1_mem_manager_node.md#exhale-class-classicraft-1-1xrt-1-1-mem-manager-node)

[Class MemPtr](classicraft_1_1xrt_1_1_mem_ptr.md#exhale-class-classicraft-1-1xrt-1-1-mem-ptr)

[Class MemRegion](classicraft_1_1xrt_1_1_mem_region.md#exhale-class-classicraft-1-1xrt-1-1-mem-region)

[Class MemRegionNode](classicraft_1_1xrt_1_1_mem_region_node.md#exhale-class-classicraft-1-1xrt-1-1-mem-region-node)

[Class RegRegion](classicraft_1_1xrt_1_1_reg_region.md#exhale-class-classicraft-1-1xrt-1-1-reg-region)

[Class RegRegionNode](classicraft_1_1xrt_1_1_reg_region_node.md#exhale-class-classicraft-1-1xrt-1-1-reg-region-node)

[Class UrlParser](classicraft_1_1xrt_1_1utils_1_1_url_parser.md#exhale-class-classicraft-1-1xrt-1-1utils-1-1-url-parser)

## Functions#

[Function icraft::xrt::operator+(uint64_t, const MemPtr&)](function_device_8h_1ac256b08b4de939f08f66ef2da848cd8e.md#exhale-function-device-8h-1ac256b08b4de939f08f66ef2da848cd8e)

[Function icraft::xrt::operator+(const MemPtr&, uint64_t)](function_device_8h_1ae1a38cb593f243cb21e611d484537628.md#exhale-function-device-8h-1ae1a38cb593f243cb21e611d484537628)

[Function icraft::xrt::operator-(const MemPtr&, uint64_t)](function_device_8h_1a288b7ee752d26955ddfe0921eebc7906.md#exhale-function-device-8h-1a288b7ee752d26955ddfe0921eebc7906)

[Function icraft::xrt::operator-(const MemPtr&, const MemPtr&)](function_device_8h_1a8b74090dfb3075d41129de3976a24270.md#exhale-function-device-8h-1a8b74090dfb3075d41129de3976a24270)

[Function icraft::xrt::operator<](function_device_8h_1aa01f01f51fd179f0d50ed1ea67de9d96.md#exhale-function-device-8h-1aa01f01f51fd179f0d50ed1ea67de9d96)

[Function icraft::xrt::operator<=](function_device_8h_1adc331dcd1e69bc979cf076cbda4e8580.md#exhale-function-device-8h-1adc331dcd1e69bc979cf076cbda4e8580)

[Function icraft::xrt::operator>](function_device_8h_1ae9e08156e1225760d595f320483e0d7b.md#exhale-function-device-8h-1ae9e08156e1225760d595f320483e0d7b)

[Function icraft::xrt::operator>=](function_device_8h_1a2089c7a554ac1b86c3c9944d353251d5.md#exhale-function-device-8h-1a2089c7a554ac1b86c3c9944d353251d5)

[Template Function icraft::xrt::utils::WaitUntil](function_device_8h_1a01ca57d0ab88d81862d5d5210f92222f.md#exhale-function-device-8h-1a01ca57d0ab88d81862d5d5210f92222f)

## Defines#

[Define XRT_DEVICE_PCH_GUARD](define_device_8h_1ae0548dc6d8da27dde92f98f152854253.md#exhale-define-device-8h-1ae0548dc6d8da27dde92f98f152854253)

## Typedefs#

[Typedef icraft::xrt::FChunkDeleter](typedef_device_8h_1a85bf30b5045c0b4dfd06d1d7fa0177db.md#exhale-typedef-device-8h-1a85bf30b5045c0b4dfd06d1d7fa0177db)

                