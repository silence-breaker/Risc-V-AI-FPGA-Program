# host\_backend.Ftmp2Tensor[#](#host-backend-ftmp2tensor "此标题的永久链接")

Ftmp2Tensor(*ftmp\_path: str*, *value: xir.Value*) → xrt.Tensor[#](#host_backend.Ftmp2Tensor "永久链接至目标")
:   将ftmp\_path上的ftmp二进制文件的数据转化为value对应的Tensor。

    参数:
    :   * **ftmp\_path** – ftmp文件路径
        * **value** – ftmp对应的xir value

    返回:
    :   ftmp转化而来的Tensor
