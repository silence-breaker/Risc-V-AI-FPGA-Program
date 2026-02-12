# Struct NetParams

## 目录

# Struct NetParams

* Defined in [File netparams.h](file_icraft-parserapi_netparams.h.md#file-icraft-parserapi-netparams-h)

## Struct Documentation

struct NetParams
:   NetParams网络参数

    Public Members

    std::string net\_name
    :   网络名称

    std::string framework
    :   神经网络框架

    std::string network
    :   网络模型文件

    std::string network\_exdata
    :   网络模型的external data文件，如有

    std::string jr\_path
    :   parse后网络存放路径

    std::string log\_path
    :   parse网络log存放路径

    std::string weights
    :   网络参数文件

    std::map<int, std::string> pre\_method
    :   前处理pre\_method

    std::string frame\_version
    :   神经网络框架版本

    std::map<int, std::vector<float>> pre\_scale
    :   前处理pre\_scale

    std::map<int, std::vector<float>> pre\_mean
    :   前处理pre\_mean

    std::map<int, std::vector<int>> channel\_swap
    :   前处理channel\_swap

    std::map<int, std::vector<int>> input
    :   网络输入尺寸

    std::map<int, std::string> input\_layout
    :   网络输入layout

    std::string image\_channel\_order = "bgr"
    :   输入图片通道顺序

目录