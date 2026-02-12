# Program Listing for File netparam.h

# Program Listing for File netparam.h

↰ [Return to documentation for file](file_icraft-parserapi_netparam.h.md#file-icraft-parserapi-netparam-h) (`icraft-parserapi\netparam.h`)

```
#pragma once
#include<map>
#include<string>
#include<vector>
#include "icraft-xir/core/compile_target.h"
#include "icraft-xir/core/data_type.h"

namespace icraft {
    namespace parser {

        struct CustomInfo {
            std::string type;
            std::string dll_name;
            std::string class_name;
            int start_index;
            int end_index;
            std::vector<std::string> inputs;
            std::vector<std::string> outputs;
            std::vector<std::pair<std::string, std::string>> params;
            bool instantiated = false;
        };
        struct PreMethodInfo {
            std::string dll_name;
            std::string class_name;
        };

        struct ParamInfo {
            std::string param_name;
            std::vector<int> dim;
            std::vector<float> data;
        };
        struct ExParamInfo {
            std::string name;
            int start_index;
            int end_index;
            int param_num;
            std::vector<ParamInfo> param_infos;
        };
        struct NetParam {
            std::string net_name;
            std::string framework;
            std::vector<CustomInfo> custom_infos;
            std::vector<ExParamInfo> exparam_infos;
            std::string network;
            std::string network_exdata;
            std::string jr_path;
            std::string log_path;
            std::string weights;
            std::string image_channel_order;
            std::map<int, std::string> pre_method;
            PreMethodInfo pre_method_infor;
            std::string post_method;
            std::string frame_version;
            std::map<int, std::vector<float>> pre_scale;
            std::map<int, std::vector<float>> pre_mean;
            std::map<int, std::vector<int>> channel_swap;
            std::map<int, std::vector<int>> input;
            std::vector<std::tuple<std::string, std::string, std::string>> custom_dlls;
            std::map<int, std::string> input_layout;
            bool pre_check;
            icraft::xir::CompileTarget target;
            std::map<int, icraft::xir::ScalarType> input_dtype;
            std::map<int, std::vector<int>> origin_input_;
        };
    }
}
```