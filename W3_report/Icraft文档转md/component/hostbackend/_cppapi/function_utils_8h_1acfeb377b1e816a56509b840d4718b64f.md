# Function icraft::hostbackend::utils::Ftmp2Tensor[#](#function-icraft-hostbackend-utils-ftmp2tensor "此标题的永久链接")

* Defined in [File utils.h](file_icraft-backends_hostbackend_utils.h.md#file-icraft-backends-hostbackend-utils-h)

## Function Documentation[#](#function-documentation "此标题的永久链接")

xrt::Tensor icraft::hostbackend::utils::Ftmp2Tensor(const std::string &ftmp\_path, const xir::Value &value)[#](#_CPPv4N6icraft11hostbackend5utils11Ftmp2TensorERKNSt6stringERKN3xir5ValueE "永久链接至目标")
:   将ftmp文件解析为HostDevice上的Xrt Tensor

    参数:
    :   * **ftmp\_path** – ftmp文件路径
        * **value** – ftmp对应的Xir Value

    返回:
    :   转自ftmp的xrtTensor
