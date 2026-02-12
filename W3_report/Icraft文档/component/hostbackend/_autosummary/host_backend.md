# host\_backend[#](#module-host_backend "此标题的永久链接")

icraft host\_backend python interface

Functions

|  |  |
| --- | --- |
| [`Cast`](host_backend.Cast.md#host_backend.Cast "host_backend.Cast") | 将input Tensor转化为output\_type所对应的Tensor。 |
| [`DecodeWithDecoder`](host_backend.DecodeWithDecoder.md#host_backend.DecodeWithDecoder "host_backend.DecodeWithDecoder") | 将数据文件使用用户提供的CustomDecoder模块解析为HostDevice上的Xrt Tensor。 |
| [`Ftmp2Tensor`](host_backend.Ftmp2Tensor.md#host_backend.Ftmp2Tensor "host_backend.Ftmp2Tensor") | 将ftmp\_path上的ftmp二进制文件的数据转化为value对应的Tensor。 |
| [`Image2Tensor`](host_backend.Image2Tensor.md#host_backend.Image2Tensor "host_backend.Image2Tensor") | Overloaded function. |

Classes

|  |  |
| --- | --- |
| [`CudaDevice`](host_backend.CudaDevice.md#host_backend.CudaDevice "host_backend.CudaDevice") |  |
| [`CudaMemRegion`](host_backend.CudaMemRegion.md#host_backend.CudaMemRegion "host_backend.CudaMemRegion") |  |
| [`HostBackend`](host_backend.HostBackend.md#host_backend.HostBackend "host_backend.HostBackend") | 表示Host类型的后端 |
