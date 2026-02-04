# Struct NetParam

## 目录

# Struct NetParam

* Defined in [File netparam.h](file_icraft-parserapi_netparam.h.md#file-icraft-parserapi-netparam-h)

## Struct Documentation

struct NetParam
:   NetParam网络参数。将弃用。

    Public Members

    std::string net\_name
    :   弃用

    std::string framework
    :   弃用

    std::vector<[CustomInfo](structicraft_1_1parser_1_1_custom_info.md#_CPPv4N6icraft6parser10CustomInfoE "icraft::parser::CustomInfo")> custom\_infos
    :   弃用

    std::vector<[ExParamInfo](structicraft_1_1parser_1_1_ex_param_info.md#_CPPv4N6icraft6parser11ExParamInfoE "icraft::parser::ExParamInfo")> exparam\_infos
    :   弃用

    std::string network
    :   弃用

    std::string network\_exdata

    std::string jr\_path
    :   弃用

    std::string log\_path
    :   弃用

    std::string weights
    :   弃用

    std::string image\_channel\_order

    std::map<int, std::string> pre\_method
    :   弃用

    [PreMethodInfo](structicraft_1_1parser_1_1_pre_method_info.md#_CPPv4N6icraft6parser13PreMethodInfoE "icraft::parser::PreMethodInfo") pre\_method\_infor
    :   弃用

    std::string post\_method
    :   弃用

    std::string frame\_version
    :   弃用

    std::map<int, std::vector<float>> pre\_scale
    :   弃用

    std::map<int, std::vector<float>> pre\_mean
    :   弃用

    std::map<int, std::vector<int>> channel\_swap
    :   弃用

    std::map<int, std::vector<int>> input
    :   弃用

    std::vector<std::tuple<std::string, std::string, std::string>> custom\_dlls
    :   弃用

    std::map<int, std::string> input\_layout
    :   弃用

    bool pre\_check

    icraft::xir::CompileTarget target

    std::map<int, icraft::xir::ScalarType> input\_dtype

    std::map<int, std::vector<int>> origin\_input\_

目录