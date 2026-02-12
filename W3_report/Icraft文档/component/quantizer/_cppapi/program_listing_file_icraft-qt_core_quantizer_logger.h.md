# Program Listing for File quantizer\_logger.h

# Program Listing for File quantizer\_logger.h

↰ [Return to documentation for file](file_icraft-qt_core_quantizer_logger.h.md#file-icraft-qt-core-quantizer-logger-h) (`icraft-qt\core\quantizer_logger.h`)

```
#pragma once
#include <icraft-qt/core/dllexport.h>
#include <icraft-qt/core/quantizer_options.h>

#include <icraft-xir/core/node.h>
//#include "../strategy/autotuning/autotuning_strategy.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <vector>
#include <filesystem>

namespace icraft::qt {
    enum class EvaluationMethod {
        cos,
        dis,
        mae,
        mse,
        manual
    };
    namespace logger {
        struct FtmpInfo {
            std::vector<int64_t> dims;
            std::vector<float> true_min;
            std::vector<float> true_max;
            std::vector<float> max;
            std::vector<float> sat;
            std::vector<float> normratio;
            std::vector<int64_t> zero_point;
            float scale;
            int exp;

            QT_API operator std::string() const;
        };

        struct RawInfo {
            std::vector<int64_t> dims;
            std::vector<float> max;
            std::vector<float> sat;
            std::vector<float> scale;
            std::vector<int> exp;

            QT_API operator std::string() const;
        };

        inline static constexpr auto FTMP_CSV_SUFFIX = "_ftmps.csv";
        inline static constexpr auto RAW_CSV_SUFFIX = "_raws.csv";
        inline static constexpr auto SM_SUFFIX = "_sm_scale.csv";
        inline static constexpr auto MIX_SUFFIX = "_mix_config.csv";
        inline static constexpr auto AUTOTUNE_SUFFIX = "_autotune_record.csv";
        inline static constexpr auto CSV_SPLIT = ",";

        inline static constexpr auto FTMP_SHEET_HEADER = std::array<const char*, 7>{
            "ftmp_id",
            "size",
            "max",
            "sat",
            "normratio",
            "scale",
            "exp"
        };
        inline static constexpr auto RAW_SHEET_HEADER = std::array<const char*, 6>{
            "raw_id",
            "size",
            "max",
            "sat",
            "scale",
            "exp"
        };

        inline static constexpr auto SM_SHEET_HEADER = std::array<const char*, 2>{
            "ftmp_id",
            "sm_scale"
        };
        inline static std::string MIX_SHEET_HEADER = "op_id,op_type,dtype,value_range_in_bits,saturation,per,order";
        inline static std::string AUTOTUNE_SHEET_HEADER = "round,measure_type,avg_value";
        /*inline static constexpr auto MIX_SHEET_HEADER = std::array<const char*, 6>{
            "op_id",
            "op_type",
            "dtype",
            "value_range_in_bits",
            "saturation",
            "per"
            "order"
        };*/
    }

    class QuantizerLoggerNode : public xir::NodeBase<QuantizerLoggerNode, xir::Node> {
    public:
        QuantizerLoggerNode() :
            info_("quantizer_log", icraft::FileSink(std::filesystem::temp_directory_path() / "temp.log")),
            info_autotuning("quantize_autotuning_log", icraft::FileSink(std::filesystem::temp_directory_path() / "temp.log"))
        {
        }

        virtual void accept(xir::AttrVisitor& visitor) override {};

        std::map<int, float> output_avg_cossimilarity_op_list;
        std::map<int, float> output_avg_dis_op_list;
        std::map<int, float> output_avg_mae_op_list;
        std::map<int, float> output_avg_mse_op_list;

        std::map<int, std::vector<float>> output_channels_cossimilarity_op_list;
        std::map<int, std::vector<float>> output_channels_dis_op_list;
        std::map<int, std::vector<float>> output_channels_mae_op_list;
        std::map<int, std::vector<float>> output_channels_mse_op_list;

        std::map<int, float> best_precision_op_list;

        std::map<int, std::vector<float>> a_scale_;
        std::map<int, std::vector<float>> w_scale_;
        std::map<int, std::vector<float>> sm_scale_;
        std::map<int, std::pair<xir::ScalarType, xir::ScalarType>> cast_type;

        std::map<int, std::string> mix_op_list;
        std::map<int, xir::ScalarType> qdtype_op_list;
        std::map<int, int> qdtype_value_op_list;
        std::map<int, std::vector<int>> value_range_op_list;

        std::map<int, std::vector<options::Saturation>> sat_op_list;
        std::map<int, std::vector<std::string>> per_op_list;

    private:
        std::map<int, logger::FtmpInfo> ftmp_sheet_;
        std::map<int, logger::RawInfo> raw_sheet_;
        std::filesystem::path log_path_;
        std::string network_name_;
        bool verbose_ = false;
        icraft::Logger info_autotuning;
        icraft::Logger info_;

        friend class QuantizerLogger;
    };

    class QuantizerLogger : public xir::MutableHandleBase<QuantizerLogger, xir::Handle, QuantizerLoggerNode> {
    public:
        QuantizerLogger() = default;
        QuantizerLogger(xir::Network& network, QuantizerOptions& options) {
            auto node = xir::make_object<QuantizerLoggerNode>();
            data_ = std::move(node);
            auto network_log_path = std::filesystem::path(options->log_path) / network->name;
            if (!std::filesystem::exists(network_log_path)) {
                std::filesystem::create_directories(network_log_path);
            }
            if (!std::filesystem::exists(options->jr_path)) {
                std::filesystem::create_directories(options->jr_path);
            }
            auto log_file = network_log_path / (network->name + "_quantize.log");
            auto logger_sink = icraft::FileSink(log_file);
            auto debug_info = icraft::Logger("quantize_log", logger_sink);
            setDebugInfo(debug_info);
            setLogPath(network_log_path, network->name);
            //autotuning用的log
            auto log_file_autotuning = network_log_path / (network->name + "_quantize_autotuning.log");
            auto logger_sink_autotuning = icraft::FileSink(log_file_autotuning);
            auto debug_info_autotuning = icraft::Logger("quantize_autotuning_log", logger_sink_autotuning);
            setDebugInfo_autotuning(debug_info_autotuning);

        }

        void setDebugInfo(icraft::Logger debug_info) { get_mutable()->info_ = debug_info; };
        void setDebugInfo_autotuning(icraft::Logger debug_info) { get_mutable()->info_autotuning = debug_info; };
        void setLogPath(const std::filesystem::path& log_path, std::string network_name) {
            auto mptr = get_mutable();
            mptr->log_path_ = log_path;
            mptr->network_name_ = network_name;
        };
        std::string getLogPath() { return get_mutable()->log_path_.string(); };
        void setVerbose(bool verbose) { get_mutable()->verbose_ = verbose; };
        bool isVerbose() const { return (*this)->verbose_; }

        void logFtmpInfo(const int& id, const logger::FtmpInfo& ftmp_info) { get_mutable()->ftmp_sheet_[id] = ftmp_info; }
        void logFtmpDims(const int& id, const std::vector<int64_t>& dims) { get_mutable()->ftmp_sheet_[id].dims = dims; }
        void logFtmpMax(const int& id, const std::vector<float>& max) { get_mutable()->ftmp_sheet_[id].max = max; }
        void logFtmpTrueMin(const int& id, const std::vector<float>& min) { get_mutable()->ftmp_sheet_[id].true_min = min; }
        void logFtmpTrueMax(const int& id, const std::vector<float>& max) { get_mutable()->ftmp_sheet_[id].true_max = max; }
        void logFtmpSat(const int& id, const std::vector<float>& sat) { get_mutable()->ftmp_sheet_[id].sat = sat; }
        void logAvgFtmpMax(const int& id, const std::vector<float>& max, const int& batch) {
            auto& ftmp_sheet = get_mutable()->ftmp_sheet_;

            if (ftmp_sheet[id].max.size() == 0) {
                for (int i = 0; i < max.size(); i++) {
                    ftmp_sheet[id].max.push_back(max[i] / batch);
                }
            }
            else {
                for (int i = 0; i < max.size(); i++) {
                    ftmp_sheet[id].max[i] += (max[i] / batch);
                }
            }
        }
        void logAvgFtmpSat(const int& id, const std::vector<float>& sat, const int& batch) {
            auto& ftmp_sheet = get_mutable()->ftmp_sheet_;

            if (ftmp_sheet[id].sat.size() == 0) {
                for (int i = 0; i < sat.size(); i++) {
                    ftmp_sheet[id].sat.push_back(sat[i] / batch);
                }
            }
            else {
                for (int i = 0; i < sat.size(); i++) {
                    ftmp_sheet[id].sat[i] += (sat[i] / batch);
                }
            }
        }
        void logFtmpZeroPoint(const int& id, const std::vector<int64_t>& zero_point) {
            get_mutable()->ftmp_sheet_[id].zero_point = zero_point;
        }
        void logFtmpNormratio(const int& id, const std::vector<float>& normratio) {
            get_mutable()->ftmp_sheet_[id].normratio = normratio;
        }
        void logFtmpScale(const int& id, const float& scale) { get_mutable()->ftmp_sheet_[id].scale = scale; }
        void logFtmpExp(const int& id, const int& exp) { get_mutable()->ftmp_sheet_[id].exp = exp; }
        const logger::FtmpInfo getFtmpInfo(const int& id)  const {
            if ((*this)->ftmp_sheet_.count(id)) return (*this)->ftmp_sheet_.at(id);
            else {
                ICRAFT_LOG(EXCEPT, 21013).append("Quantizer logger ftmp_sheet error: ftmp id = {} not exist!", id);
                return logger::FtmpInfo();
            };
        }
        std::vector<float> getFtmpMax(const int& id)  const {
            if ((*this)->ftmp_sheet_.count(id)) return (*this)->ftmp_sheet_.at(id).max;
            else {
                ICRAFT_LOG(EXCEPT, 21013).append("Quantizer logger ftmp_sheet error: ftmp id = {} not exist!", id);
                return std::vector<float>();
            }
        }
        std::vector<float> getFtmpSat(const int& id)  const {
            if ((*this)->ftmp_sheet_.count(id)) return (*this)->ftmp_sheet_.at(id).sat;
            else {
                ICRAFT_LOG(EXCEPT, 21013).append("Quantizer logger ftmp_sheet error: ftmp id = {} not exist!", id);
                return std::vector<float>();
            }
        }
        const std::vector<float> getFtmpNormratio(const int& id) const {
            if ((*this)->ftmp_sheet_.count(id)) return (*this)->ftmp_sheet_.at(id).normratio;
            else {
                ICRAFT_LOG(EXCEPT, 21013).append("Quantizer logger ftmp_sheet error: ftmp id = {} not exist!", id);
                return std::vector<float>();
            }
        }

        std::map<int, logger::FtmpInfo>& getFtmpSheet() const { return get_mutable()->ftmp_sheet_; }
        std::map<int, logger::RawInfo>& getRawSheet() const { return get_mutable()->raw_sheet_; }

        void logRawInfo(const int& id, const logger::RawInfo& raw_info) { get_mutable()->raw_sheet_[id] = raw_info; }
        void logRawDims(const int& id, const std::vector<int64_t>& dims) { get_mutable()->raw_sheet_[id].dims = dims; }
        void logRawMax(const int& id, const std::vector<float>& max) { get_mutable()->raw_sheet_[id].max = max; }
        void logRawSat(const int& id, const std::vector<float>& sat) { get_mutable()->raw_sheet_[id].sat = sat; }
        void logRawScale(const int& id, const std::vector<float>& scale) { get_mutable()->raw_sheet_[id].scale = scale; }
        void logRawExp(const int& id, const std::vector<int>& exp) { get_mutable()->raw_sheet_[id].exp = exp; }
        const logger::RawInfo& getRawInfo(const int& id)  const {
            if ((*this)->raw_sheet_.count(id)) return (*this)->raw_sheet_.at(id);
            else {
                ICRAFT_LOG(EXCEPT, 21013).append("Quantizer logger raw_sheet error: raw id = {} not exist!", id);
                return logger::RawInfo();
            }
        }
        std::vector<float> getRawSat(const int& id) const {
            if ((*this)->raw_sheet_.count(id)) return (*this)->raw_sheet_.at(id).sat;
            else {
                ICRAFT_LOG(EXCEPT, 21013).append("Quantizer logger raw_sheet error: raw id = {} not exist!", id);
                return std::vector<float>();
            }
        }
        std::vector<float> getRawMax(const int& id)  const {
            if ((*this)->raw_sheet_.count(id)) return (*this)->raw_sheet_.at(id).max;
            else {
                ICRAFT_LOG(EXCEPT, 21013).append("Quantizer logger raw_sheet error: raw id = {} not exist!", id);
                return std::vector<float>();
            }
        }

        // 封装icraft::Logger的函数info
        template<typename... Args>
        void info(std::string fmt, Args&&... args) {
            get_mutable()->info_.info(fmt, std::forward<Args>(args)...);
        }

        void info(const std::string_view& msg) {
            get_mutable()->info_.info(msg);
        }

        // 封装icraft::Logger的函数info_autotuning
        template<typename... Args>
        void info_autotuning(std::string fmt, Args&&... args) {
            get_mutable()->info_autotuning.info(fmt, std::forward<Args>(args)...);
        }

        void info_autotuning(const std::string_view& msg) {
            get_mutable()->info_autotuning.info(msg);
        }

        QT_API void dumpFtmpSheet();
        QT_API void dumpRawSheet();
        QT_API void dumpSmoothScale();
        QT_API void dumpMixConfig();
        QT_API void dumpAutoTuneSheet(icraft::qt::EvaluationMethod eva_method);
        QT_API void loadFtmpSheet(const std::string& ftmp_csv);
        QT_API void loadRawSheet(const std::string& raw_csv);
        QT_API void dumpJR(icraft::xir::Network& network, const std::string& jr_path, std::string stage);
        QT_API void clear();
    };
}
```