# host\_backend.Cast[#](#host-backend-cast "此标题的永久链接")

Cast(*input: xrt.Tensor*, *input\_type: xir.TensorType*, *output\_type: xir.TensorType*, *backend: [host\_backend.HostBackend](host_backend.HostBackend.md#host_backend.HostBackend "host_backend.HostBackend")*) → xrt.Tensor[#](#host_backend.Cast "永久链接至目标")
:   将input Tensor转化为output\_type所对应的Tensor。

    参数:
    :   * **input** – 输入Tensor
        * **input\_type** – 输入Tensor的data type
        * **output\_type** – 期望的Tensor data type
        * **backend** – 执行该操作的hostbackend
