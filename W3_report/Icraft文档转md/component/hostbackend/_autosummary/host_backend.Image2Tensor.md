# host\_backend.Image2Tensor[#](#host-backend-image2tensor "此标题的永久链接")

Image2Tensor(*\*args*, *\*\*kwargs*)[#](#host_backend.Image2Tensor "永久链接至目标")
:   Overloaded function.

    1. Image2Tensor(img\_path: str, height: int, width: int) -> xrt.Tensor

    将img\_path上的图片初始化为一个IcraftTensor并把高和宽resize为height和width对应的数值。

    参数:
    :   * **img\_path** – 图片路径
        * **height** – resize 高
        * **width** – resize 宽

    返回:
    :   图片转化而来的Tensor

    2. Image2Tensor(img\_path: str, value: xir.Value, bgr\_order: bool) -> xrt.Tensor

    将img\_path上的图片初始化为一个IcraftTensor并把高和宽resize为height和width对应的数值。

    参数:
    :   * **img\_path** – 图片路径
        * **value** – 图片对应的xir::Value
        * **bgr\_order** – 图片读取格式

    返回:
    :   图片转化而来的Tensor
