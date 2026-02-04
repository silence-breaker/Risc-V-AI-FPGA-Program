# host\_backend.DecodeWithDecoder[#](#host-backend-decodewithdecoder "此标题的永久链接")

DecodeWithDecoder(*dll\_path: str*, *file\_path: str*, *data\_type: List[xir.TensorType]*) → List[xrt.Tensor][#](#host_backend.DecodeWithDecoder "永久链接至目标")
:   将数据文件使用用户提供的CustomDecoder模块解析为HostDevice上的Xrt Tensor。

    参数:
    :   * **dll\_path** – dll或so路径
        * **file\_path** – 数据文件路径
        * **data\_type** – 输出Tensors的TensorTypes，表示Tensor信息

    返回:
    :   转自数据文件的Tensors
