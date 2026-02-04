# Program Listing for File netparams.h

# Program Listing for File netparams.h

↰ [Return to documentation for file](file_icraft-parserapi_netparams.h.md#file-icraft-parserapi-netparams-h) (`icraft-parserapi\netparams.h`)

```
#pragma once
#include <map>
#include <string>
#include <vector>
#include <icraft-parserapi/netparam.h>

namespace icraft {
    namespace parser {

        struct NetParams {
            std::string net_name;
            std::string framework;
            std::string network;
            std::string network_exdata;
            std::string jr_path;
            std::string log_path;
            std::string weights;
            std::map<int, std::string> pre_method;
            std::string frame_version;
            std::map<int, std::vector<float>> pre_scale;
            std::map<int, std::vector<float>> pre_mean;
            std::map<int, std::vector<int>> channel_swap;
            std::map<int, std::vector<int>> input;
            std::map<int, std::string> input_layout;
            std::string image_channel_order = "bgr";

        };

        NetParam transferNetParam(const NetParams& net_params) {

            std::vector<CustomInfo> custom_infos;
            std::vector<ExParamInfo> exparam_infos;
            PreMethodInfo pre_method_infor;
            std::vector<std::tuple<std::string, std::string, std::string>> custom_dlls;
            std::string post_method = "nop";
            //std::string image_channel_order = "bgr";

            return NetParam { net_params.net_name, net_params.framework, custom_infos,exparam_infos,net_params.network,net_params.network_exdata,
            net_params.jr_path, net_params.log_path, net_params.weights, net_params.image_channel_order, net_params.pre_method,pre_method_infor, post_method,
            net_params.frame_version, net_params.pre_scale, net_params.pre_mean, net_params.channel_swap,
            net_params.input, custom_dlls,net_params.input_layout };
        }
    }
}
```