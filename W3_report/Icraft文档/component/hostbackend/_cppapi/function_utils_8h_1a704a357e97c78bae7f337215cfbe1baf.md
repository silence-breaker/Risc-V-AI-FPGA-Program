# Function icraft::hostbackend::utils::Cast[#](#function-icraft-hostbackend-utils-cast "此标题的永久链接")

* Defined in [File utils.h](file_icraft-backends_hostbackend_utils.h.md#file-icraft-backends-hostbackend-utils-h)

## Function Documentation[#](#function-documentation "此标题的永久链接")

xrt::Tensor icraft::hostbackend::utils::Cast(const xrt::Tensor &input, const xrt::TensorType &input\_type, const xrt::TensorType &output\_type, xrt::[HostBackend](classicraft_1_1xrt_1_1_host_backend.md#_CPPv4N6icraft3xrt11HostBackendE "icraft::xrt::HostBackend") &backend)[#](#_CPPv4N6icraft11hostbackend5utils4CastERKN3xrt6TensorERKN3xrt10TensorTypeERKN3xrt10TensorTypeERN3xrt11HostBackendE "永久链接至目标")
:   将input从input\_type cast为output\_type，cast内容包括layout和element data type

    参数:
    :   * **input** – 需要cast的tensor
        * **input\_dtype** – 输入Tensor的dtype
        * **output\_dtype** – 输出Tensor的dtype

    返回:
    :   cast之后的xrt tensor
