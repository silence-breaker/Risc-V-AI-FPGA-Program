# Class CustomDecoder[#](#class-customdecoder "此标题的永久链接")

* Defined in [File decode\_custom.h](file_icraft-backends_hostbackend_decode_custom.h.md#file-icraft-backends-hostbackend-decode-custom-h)

## Class Documentation[#](#class-documentation "此标题的永久链接")

class CustomDecoder[#](#_CPPv413CustomDecoder "永久链接至目标")
:   CustomDecoder使用方法: CustomDecoder提供接口帮助用户实现数据文件到xrt::Tensor的自定义转换功能。 构造方法: 用户需要在dll(或so)中继承CustomDecoder虚类实现自定义decode方法，再使用REGISTER\_CUSTOM\_DECODER导出。 使用方法: 通过icraft::hostbackend::utils::DecodeWithDecoder调用自定义decode函数。

    Public Functions

    virtual std::vector<xrt::Tensor> decode(const std::string &file\_path, const std::vector<xrt::TensorType> &data\_type) = 0[#](#_CPPv4N13CustomDecoder6decodeERKNSt6stringERKNSt6vectorIN3xrt10TensorTypeEEE "永久链接至目标")
