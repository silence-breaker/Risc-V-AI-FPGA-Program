# Program Listing for File quantizer\_options.h

# Program Listing for File quantizer\_options.h

↰ [Return to documentation for file](file_icraft-qt_core_quantizer_options.h.md#file-icraft-qt-core-quantizer-options-h) (`icraft-qt\core\quantizer_options.h`)

```
#pragma once
#include <string>

#include <icraft-xir/core/data_type.h>

namespace icraft::qt {
    namespace options {
        /*enum class ForwardMode {
            ftmp,
            image
        };

        enum class Saturation {
            null,
            kld,
            ems,
            nsigma
        };

        enum class Per {
            tensor,
            channel
        };

        enum class Target {
            buyi,
            zhuge
        };*/
        WISE_ENUM_CLASS(ForwardMode, ftmp, image);
        WISE_ENUM_CLASS(Saturation, null, kld, ems, nsigma);
        WISE_ENUM_CLASS(Per, tensor, channel);
        WISE_ENUM_CLASS(Target, buyi, zhuge);

    }

    class QuantizerOptionsNode : public xir::NodeBase<QuantizerOptionsNode, xir::Node> {
    public:
        virtual void accept(xir::AttrVisitor& visitor) override {};

        options::ForwardMode forward_mode;
        std::string forward_dir;
        std::string forward_list;
        std::string ftmp_csv;
        std::string raw_csv;
        std::string decode_dll;
        std::string input_norm;
        options::Target target;
        std::string mix_precision;
        std::string log_path;
        std::string jr_path;
        options::Saturation saturation;
        options::Per per;
        xir::ScalarType qdtype;
        int axis = 0;
        int batch = 1;
        int bin_num = 4096;
        int autoqset_num = 0;
        float smooth_alpha = 0;
        bool before_relu = false;
        bool normalize = false;
        bool debug = false;
        bool precheck = false;
        bool variance_strategy = false;
        bool cosimilarity_strategy = false;
        bool lstm_strategy = false;
        bool autotuning_strategy = false;
        std::string quant_autotune_config = "";
        bool asymmetric = false;
        int n = 1;
        std::string no_transinput = "";
        std::string no_imgmake = "";
        bool no_imk = false;
        bool no_trans = false;
        std::vector<int> no_trans_ids = {};
        std::vector<int> no_imk_ids = {};
        std::vector<int> splitbias_ids = {};
    };

    class QuantizerOptions : public xir::MutableHandleBase<QuantizerOptions, xir::Handle, QuantizerOptionsNode> {
    public:
        QuantizerOptions() = default;
        QuantizerOptions(
            options::ForwardMode forward_mode,
            std::string forward_dir,
            std::string forward_list,
            options::Target target,
            std::string log_path,
            std::string jr_path,
            options::Saturation saturation,
            options::Per per,
            xir::ScalarType qdtype,

            std::string mix_precision = "",
            std::string ftmp_csv = "",
            std::string raw_csv = "",
            std::string decode_dll = "",
            std::string input_norm = "",
            int n = 1,
            int axis = 0,
            int batch = 1,
            int bin_num = 4096,
            float smooth_alpha = 0,
            bool before_relu = false,
            bool debug = false,
            bool precheck = false,
            bool variance_strategy = false,
            bool cosimilarity_strategy = false,
            bool lstm_strategy = false,
            bool asymmetric = false,
            bool normalize = false,
            std::string no_transinput = "",
            std::string no_imgmake = "",
            int autoqset_num = 0
        ) {
            auto node = xir::make_object<QuantizerOptionsNode>();
            node->forward_mode = forward_mode;
            node->forward_dir = forward_dir;
            node->forward_list = forward_list;
            node->ftmp_csv = ftmp_csv;
            node->raw_csv = raw_csv;
            node->decode_dll = decode_dll;
            node->input_norm = input_norm;
            node->target = target;
            node->mix_precision = mix_precision;
            node->log_path = log_path;
            node->jr_path = jr_path;
            node->saturation = saturation;
            node->per = per;
            node->qdtype = qdtype;
            node->axis = axis;
            node->batch = batch;
            node->bin_num = bin_num;
            node->autoqset_num = autoqset_num;
            node->smooth_alpha = smooth_alpha;
            node->before_relu = before_relu;
            node->normalize = normalize;
            node->debug = debug;
            node->precheck = precheck;
            node->variance_strategy = variance_strategy;
            node->cosimilarity_strategy = cosimilarity_strategy;
            node->lstm_strategy = lstm_strategy;
            node->asymmetric = asymmetric;
            node->n = n;
            node->no_transinput = no_transinput;
            node->no_imgmake = no_imgmake;
            node->no_trans = false;
            node->no_imk = false;
            node->no_trans_ids = {};
            node->no_imk_ids = {};
            node->splitbias_ids = {};

            data_ = std::move(node);
        }
    };
}
```