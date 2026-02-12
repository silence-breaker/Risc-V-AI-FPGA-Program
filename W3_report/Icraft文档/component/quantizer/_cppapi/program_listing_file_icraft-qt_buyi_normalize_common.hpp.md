# Program Listing for File common.hpp

# Program Listing for File common.hpp

↰ [Return to documentation for file](file_icraft-qt_buyi_normalize_common.hpp.md#file-icraft-qt-buyi-normalize-common-hpp) (`icraft-qt\buyi\normalize\common.hpp`)

```
#pragma once

#include <icraft-xir/ops/swap_order.h>
#include <icraft-xir/ops/add.h>
#include <icraft-xir/ops/multiply.h>
#include <icraft-xir/ops/conv2d.h>
#include <icraft-xir/ops/cast.h>
#include <icraft-xir/ops/sigmoid.h>
#include <icraft-xir/ops/tanh.h>
#include <icraft-xir/ops/hardsigmoid.h>
#include <icraft-xir/ops/relu.h>
#include <icraft-xir/ops/reshape.h>
#include <icraft-xir/ops/transpose.h>
#include <icraft-xir/ops/expand.h>
#include <icraft-xir/ops/resize.h>
#include <icraft-xir/ops/squeeze.h>
#include <icraft-xir/ops/avg_pool2d.h>
#include <icraft-xir/ops/max_pool2d.h>
#include <icraft-xir/ops/pad.h>
#include <icraft-xir/ops/upsample.h>
#include <icraft-xir/ops/concat.h>
#include <icraft-xir/ops/split.h>
#include <icraft-xir/ops/slice.h>
#include <icraft-xir/ops/roll.h>
#include <icraft-xir/ops/copy.h>

#include <icraft-qt/core/quantizer_logger.h>
#include <icraft-qt/core/quantizer_options.h>

using namespace icraft::xir;
using namespace icraft::qt;

static void PassChangedNormDown(const Operation operation, const QuantizerOptions& options, QuantizerLogger& logger, const int64_t& causeopid);

inline static void CalcNormratio(const Operation& op, const QuantizerOptions& options, QuantizerLogger& logger) {
    auto& value_range_op_list = logger->value_range_op_list;

    auto value_range = value_range_op_list.at(op->op_id)[1];

    auto qt_max = pow(2, value_range - 1) - 1;
    for (auto oftmp : op->outputs) {
        auto oftmp_id = oftmp->v_id;
        auto sat = logger.getFtmpSat(oftmp_id);
        std::vector<float> nr;
        for (int i = 0; i < sat.size(); i++) {
            auto nr_value = sat[i] / qt_max;
            if (nr_value < pow(10, -20)) nr_value = 1;
            nr.push_back(nr_value);
        }
        logger.info("\tftmp id: {}, calculate normratio = {}", oftmp_id, nr[0]);
        logger.logFtmpNormratio(oftmp_id, nr);
    }
}

inline static void CalcBNormratio(
    const Operation& operation,
    bool has_bias,
    const QuantizerOptions& options,
    QuantizerLogger& logger
) {
    auto& qdtype_value_op_list = logger->qdtype_value_op_list;
    auto& value_range_op_list = logger->value_range_op_list;

    auto op_id = operation->op_id;
    auto value_range = value_range_op_list.at(op_id)[1];
    auto qt_max = pow(2, value_range - 1) - 1;
    auto output_ftmp = operation->outputs[0];
    auto output_ftmp_id = output_ftmp->v_id;
    auto output_dims = output_ftmp.tensorType()->shape;
    auto output_chann = output_dims.size() == 4 ? output_dims[3] : output_dims[1];
    auto sat = logger.getFtmpSat(output_ftmp_id);
    std::vector<float> nr;
    for (int i = 0; i < sat.size(); i++) {
        auto nr_value = sat[i] / qt_max;
        if (nr_value < pow(10, -20)) nr_value = 1;
        nr.push_back(nr_value);
        logger.logFtmpNormratio(output_ftmp_id, nr);
        logger.info("\tftmp id: {}, channel {}, calculate normratio = {}", output_ftmp_id, i, nr_value);
        //output_ftmp->normratio(nr);
    }
}

inline static void PassChangedNormUp(const Operation operation, const QuantizerOptions& options, QuantizerLogger& logger, int v_id, const int64_t& causeopid = -1) {
    logger.info("\t PassChangedNormUp from opid: {} to op : {},optype:{}", causeopid, operation->op_id, operation->typeKey());
    if (operation.is<Reshape>() || operation.is<Transpose>() || operation.is<Expand>()
        || operation.is<Resize>() || operation.is<Squeeze>() || operation.is<AvgPool2d>()
        || operation.is<MaxPool2d>() || operation.is<Pad>() || operation.is<SwapOrder>()
        || operation.is<Upsample>() || operation.is<ReLU>() || operation.is<Roll>() || operation.is<Copy>()) {
        auto iftmp = operation->inputs[0];
        auto oftmp = operation->outputs[0];
        auto oftmp_norm = logger.getFtmpNormratio(oftmp->v_id);
        auto onorm0_value = oftmp_norm[0];                              //TODO: 考虑按通道的normratio
        bool onorm_all_same = std::all_of(
            oftmp_norm.begin() + 1,
            oftmp_norm.end(),
            [&](auto x) {return x == onorm0_value; }
        );
        if (!onorm_all_same) ICRAFT_LOG(EXCEPT, 21011).append("PassNormUp: output's normratio must be all same!");
        logger.logFtmpNormratio(iftmp->v_id, std::vector<float>(iftmp.tensorType()->shape[-1], oftmp_norm[0]));
        logger.info("\tftmp id: {}, pass changed normratio from ftmp {} to {}",
            iftmp->v_id, oftmp->v_id, oftmp_norm[0]);
        auto producers = operation.producers();
        for (auto&& producer : producers) {
            PassChangedNormUp(producer, options, logger, iftmp->v_id, operation->op_id);
        }
        auto consumers = iftmp.getUsesOp();
        for (auto consumer : consumers) {
            if (consumer->op_id != operation->op_id) {
                PassChangedNormDown(consumer, options, logger, operation->op_id);
            }
        }
    }
    else if (operation.is<Concat>()) {
        auto iftmps = operation->inputs;
        auto oftmp = operation->outputs[0];
        auto oftmp_norm = logger.getFtmpNormratio(oftmp->v_id);
        auto onorm0_value = oftmp_norm[0];                              //TODO: 考虑按通道的normratio
        bool onorm_all_same = std::all_of(
            oftmp_norm.begin() + 1,
            oftmp_norm.end(),
            [&](auto x) {return x == onorm0_value; }
        );
        if (!onorm_all_same) ICRAFT_LOG(EXCEPT, 21011)
            .append("PassNormUp: output's normratio must be all same!");
        for (auto iftmp : iftmps) {
            if (!iftmp.isParams()) {
                logger.logFtmpNormratio(iftmp->v_id, std::vector<float>(iftmp.tensorType()->shape[-1], oftmp_norm[0]));
                logger.info("\tftmp id: {}, pass changed normratio from ftmp {} to {}",
                    iftmp->v_id, oftmp->v_id, oftmp_norm[0]);
                auto producer = iftmp.op();
                PassChangedNormUp(producer, options, logger, iftmp->v_id, operation->op_id);
                auto consumers = iftmp.getUsesOp();
                for (auto consumer : consumers) {
                    if (consumer->op_id != operation->op_id) {
                        PassChangedNormDown(consumer, options, logger, operation->op_id);
                    }
                }
            }
        }
    }
    else if (operation.is<Cast>()) {
        auto iftmp = operation->inputs[0];
        auto oftmp = operation->outputs[0];
        auto itype = logger.get_mutable()->cast_type[operation->op_id].first;
        auto otype = logger.get_mutable()->cast_type[operation->op_id].second;
        if (itype.isFP32()) {

        }
        else if (otype.isFP32()) {
            auto input_ftmp_id = iftmp->v_id;
            auto output_ftmp_id = oftmp->v_id;
            auto oftmp_norm = logger.getFtmpNormratio(output_ftmp_id);
            logger.logFtmpNormratio(input_ftmp_id, oftmp_norm);
            logger.info("\tftmp id: {}, pass changed normratio from ftmp {} to {}",
                input_ftmp_id, output_ftmp_id, oftmp_norm[0]);
            auto producers = operation.producers();
            for (auto&& producer : producers) {
                PassChangedNormUp(producer, options, logger, iftmp->v_id, operation->op_id);
            }
            auto consumers = iftmp.getUsesOp();
            for (auto consumer : consumers) {
                if (consumer->op_id != operation->op_id) {
                    PassChangedNormDown(consumer, options, logger, operation->op_id);
                }
            }
        }
        else {
            auto input_ftmp_id = operation->inputs[0]->v_id;
            auto output_ftmp = operation->outputs[0];
            auto output_ftmp_id = output_ftmp->v_id;
            auto nr = logger.getFtmpNormratio(output_ftmp_id);
            std::vector<float> nr_value;
            if (itype.isSInt(8)) {
                for (int i = 0; i < nr.size(); i++) {
                    nr_value.push_back(nr[i] * 256);
                }
                logger.logFtmpNormratio(input_ftmp_id, nr_value);
            }
            else {
                for (int i = 0; i < nr.size(); i++) {
                    nr_value.push_back(nr[i] / 256);
                }
                logger.logFtmpNormratio(input_ftmp_id, nr_value);
            }
            logger.info("\tftmp id: {}, pass changed normraito from ftmp {} to {}",
                input_ftmp_id, output_ftmp_id, nr_value[0]);
            auto producers = operation.producers();
            for (auto producer : producers) {
                PassChangedNormUp(producer, options, logger, iftmp->v_id, operation->op_id);
            }
            auto consumers = iftmp.getUsesOp();
            for (auto consumer : consumers) {
                if (consumer->op_id != operation->op_id) {
                    PassChangedNormDown(consumer, options, logger, operation->op_id);
                }
            }
        }
    }
    else if (operation.is<Split>() || operation.is<Slice>()) {
        auto iftmp = operation->inputs[0];
        auto oftmps = operation->outputs;
        auto oftmp_norm = logger.getFtmpNormratio(v_id);
        auto onorm0_value = oftmp_norm[0];                              //TODO: 考虑按通道的normratio
        bool onorm_all_same = std::all_of(oftmp_norm.begin() + 1, oftmp_norm.end(), [&](auto x) {return x == onorm0_value; });
        if (!onorm_all_same) ICRAFT_LOG(EXCEPT, 21011).append("PassNormUp: output's normratio must be all same!");
        logger.logFtmpNormratio(iftmp->v_id, std::vector<float>(iftmp.tensorType()->shape[-1], oftmp_norm[0]));
        logger.info("\tftmp id: {}, pass changed normratio from ftmp {} to {}",
            iftmp->v_id, v_id, oftmp_norm[0]);
        auto producer = iftmp.op();
        PassChangedNormUp(producer, options, logger, iftmp->v_id, operation->op_id);
        auto consumers = iftmp.getUsesOp();
        for (auto consumer : consumers) {
            if (consumer->op_id != operation->op_id) {
                PassChangedNormDown(consumer, options, logger, operation->op_id);
            }
        }

        for (auto oftmp : oftmps) {
            if (logger.getFtmpNormratio(oftmp->v_id)[0] != oftmp_norm[0]) {
                logger.logFtmpNormratio(oftmp->v_id, std::vector<float>(oftmp.tensorType()->shape[-1], oftmp_norm[0]));
                logger.info("\tftmp id: {}, pass changed normratio from ftmp {} to {}",
                    oftmp->v_id, v_id, oftmp_norm[0]);
                auto consumers = oftmp.getUsesOp();
                for (auto consumer : consumers) {
                    if (consumer->op_id != operation->op_id) {
                        PassChangedNormDown(consumer, options, logger, operation->op_id);
                    }
                }
            }
        }
        }
    else {

    }
}

inline static void PassNormratio(const Operation& operation, const QuantizerOptions& options, QuantizerLogger& logger, const int64_t& causeopid = -1) {
    logger.info("\t PassNormratio from opid: {} to op : {},optype:{}", causeopid, operation->op_id, operation->typeKey());
    auto input_ftmp_id = operation->inputs[0]->v_id;
    auto output_ftmp = operation->outputs[0];
    auto output_ftmp_id = output_ftmp->v_id;
    auto& nr = logger.getFtmpNormratio(input_ftmp_id);
    logger.logFtmpNormratio(output_ftmp_id, nr);
    logger.info("\tftmp id: {}, pass normratio from ftmp {}", output_ftmp_id, input_ftmp_id);
}

inline static void CatNormratio(const Operation& operation, int axis, const QuantizerOptions& options, QuantizerLogger& logger, const int64_t& causeopid = -1) {
    logger.info("\t CatNormratio from opid: {} to op : {},optype:{}", causeopid, operation->op_id, operation->typeKey());
    auto input_ftmps = operation->inputs;
    if (axis == -1 || axis == (input_ftmps[0].tensorType()->shape.size() - 1)) {
        std::stringstream ss;
        std::vector<float> nr;
        for (auto&& input_ftmp : input_ftmps) {
            auto input_ftmp_id = input_ftmp->v_id;
            auto& normratio = logger.getFtmpNormratio(input_ftmp_id);
            nr.insert(nr.end(), normratio.begin(), normratio.end());
            ss << input_ftmp_id << " ";
        }
        auto output_ftmp = operation->outputs[0];
        auto output_ftmp_id = output_ftmp->v_id;
        logger.logFtmpNormratio(output_ftmp_id, nr);
        logger.info("\tftmp id: {}, concat normratio from ftmp: {} ", output_ftmp_id, ss.str().c_str());
    }
    else {
        std::vector<std::vector<float>> iftmps_norms;
        auto max_norm = std::vector<float>(operation[0].tensorType()->shape[-1], 0.f);
        float max_value = 0;
        for (auto input_ftmp : input_ftmps) {
            auto iftmp_id = input_ftmp->v_id;
            std::vector<float> new_norm;
            auto i_norm = logger.getFtmpNormratio(iftmp_id);
            iftmps_norms.push_back(i_norm);
            auto max_i = *std::max_element(i_norm.begin(), i_norm.end());
            max_value = max_i > max_value ? max_i : max_value;
            max_norm = std::vector<float>(operation[0].tensorType()->shape[-1], max_value);
        }
        bool all_same = true;
        auto rows = input_ftmps.size();
        auto cols = iftmps_norms[0].size();
        for (int j = 0; j < cols && all_same; j++) {
            auto first = iftmps_norms[0][j];
            for (int i = 0; i < rows; i++) {
                if (iftmps_norms[i][j] != first) {
                    all_same = false;
                    break;
                }
            }
        }
        if (!all_same) {
            for (auto input_ftmp : input_ftmps) {
                auto iftmp_norm = logger.getFtmpNormratio(input_ftmp->v_id);
                if (iftmp_norm != max_norm) {
                    logger.logFtmpNormratio(input_ftmp->v_id, max_norm);
                    ICRAFT_LOG_WARNING().append("ConcatNormratio: change input normratio to same value");
                    logger.info("\tchange input ftmp {}'s normratio to be same", input_ftmp->v_id);
                    auto producer = input_ftmp.op();
                    PassChangedNormUp(producer, options, logger, input_ftmp->v_id, operation->op_id);
                    auto consumers = input_ftmp.getUsesOp();
                    for (auto consumer : consumers) {
                        if (consumer->op_id != operation->op_id) {
                            PassChangedNormDown(consumer, options, logger, operation->op_id);
                        }
                    }
                }
            }
            logger.logFtmpNormratio(operation[0]->v_id, max_norm);
            logger.info("\tset output ftmp {}'s normratio to be same as input", operation[0]->v_id);
        }
        else {
            logger.logFtmpNormratio(operation[0]->v_id, iftmps_norms[0]);
            logger.info("\tset output ftmp {}'s normratio to be same as input", operation[0]->v_id);
        }
    }
}

inline static void ReshapeNormratio(const Operation& operation, const QuantizerOptions& options, QuantizerLogger& logger, const int64_t& causeopid = -1) {
    logger.info("\t ReshapeNormratio from opid: {} to op : {},optype:{}", causeopid, operation->op_id, operation->typeKey());
    auto input_ftmp_id = operation->inputs[0]->v_id;
    auto output_ftmp = operation->outputs[0];
    auto output_ftmp_id = output_ftmp->v_id;
    auto& nr = logger.getFtmpNormratio(input_ftmp_id);
    auto nr_size = nr.size();
    bool all_same = true;
    for (int i = 1; i < nr_size; i++) {
        if (nr[i] != nr[0]) {
            all_same = false;
            break;
        }
    }
    auto& output_dims = output_ftmp.tensorType()->shape;
    auto reshaped_chann = output_dims[output_dims.size() - 1];

    //special transpose
    bool special_transpose = false;
    if (operation.is<Transpose>()) {
        auto transpose = operation.cast<Transpose>();
        auto trans_dims = transpose->dims;
        auto input_shape = transpose->inputs[0].tensorType()->shape;
        auto output_shape = transpose->outputs[0].tensorType()->shape;
        if (trans_dims[-1] != input_shape.size() - 1 &&
            input_shape[-1] == output_shape[-1]) {
            special_transpose = true;
        }
    }
    std::vector<float> reshaped_nr;
    if (all_same) {
        reshaped_nr = std::vector<float>(reshaped_chann, nr[0]);
        logger.logFtmpNormratio(output_ftmp_id, reshaped_nr);
        logger.info("\tftmp id: {}, reshape normratio from ftmp {}", output_ftmp_id, input_ftmp_id);
    }
    else if (reshaped_chann == nr.size() && !special_transpose) {
        logger.logFtmpNormratio(output_ftmp_id, nr);
        logger.info("\tftmp id: {}, reshape normratio from ftmp {}", output_ftmp_id, input_ftmp_id);
    }
    else {
        ICRAFT_LOG_WARNING().append("ReshapeNormratio: change input normratio to same value");
        float max_norm = *std::max_element(nr.begin(), nr.end());
        logger.logFtmpNormratio(input_ftmp_id, std::vector<float>(nr_size, max_norm));
        logger.info("\tftmp id: {}, change input normratio to {}", input_ftmp_id, max_norm);
        //保证输入normratio递归向前传递
        auto input_ftmp = operation->inputs[0];
        auto producer = input_ftmp.op();
        PassChangedNormUp(producer, options, logger, input_ftmp->v_id, operation->op_id);
        auto consumers = input_ftmp.getUsesOp();
        for (auto consumer : consumers) {
            if (consumer->op_id != operation->op_id) {
                PassChangedNormDown(consumer, options, logger, operation->op_id);
            }
        }
        logger.logFtmpNormratio(output_ftmp_id, std::vector<float>(reshaped_chann, max_norm));
        logger.info("\tftmp id: {}, reshape normratio from ftmp {}", output_ftmp_id, input_ftmp_id);
    }
}

inline static void PassChangedNormDown(const Operation operation, const QuantizerOptions& options, QuantizerLogger& logger, const int64_t& causeopid = -1) {
    logger.info("\t PassChangedNormUp from opid: {} to op : {},optype:{}", causeopid, operation->op_id, operation->typeKey());
    if (operation.is<AvgPool2d>()
        || operation.is<MaxPool2d>()
        || operation.is<Pad>()
        || operation.is<SwapOrder>()
        || operation.is<Upsample>()
        || operation.is<ReLU>()
        || operation.is<Copy>()
        ) {
        PassNormratio(operation, options, logger, operation->op_id);

        auto consumers = operation.consumers();
        for (auto consumer : consumers) {
            PassChangedNormDown(consumer, options, logger, operation->op_id);
        }
    }
    else if (operation.is<Reshape>() || operation.is<Transpose>() || operation.is<Expand>()
        || operation.is<Resize>() || operation.is<Squeeze>()) {
        ReshapeNormratio(operation, options, logger, operation->op_id);
        auto consumers = operation.consumers();
        for (auto consumer : consumers) {
            PassChangedNormDown(consumer, options, logger, operation->op_id);
        }
    }
    else if (operation.is<Concat>()) {
        bool concat_const = false;
        for (auto input_value : operation->inputs) {
            if (input_value.isParams()) concat_const = true;
        }
        if (concat_const) {
            if (operation->inputs.size() != 2) ICRAFT_LOG(EXCEPT, 21012)
                .append("concat_const only support 2 inputs!");
            for (auto input_value : operation->inputs) {
                if (!input_value.isParams()) {
                    auto iftmp_id = input_value->v_id;
                    auto oftmp_id = operation[0]->v_id;
                    auto input_norm = logger.getFtmpNormratio(iftmp_id);

                    auto all_same = std::equal(input_norm.begin() + 1, input_norm.end(), input_norm.begin());
                    if (all_same) {
                        auto co = operation[0].tensorType()->shape[-1];
                        auto output_norm = std::vector<float>(co, input_norm[0]);
                        logger.logFtmpNormratio(oftmp_id, output_norm);
                        logger.info("\tftmp id: {}, set normratio by ftmp: {} ", oftmp_id, iftmp_id);
                    }
                    else {
                        if (operation.cast<Concat>()->axis != (operation->inputs[0].tensorType()->shape.size() - 1)) {
                            logger.logFtmpNormratio(oftmp_id, input_norm);
                            logger.info("\tftmp id: {}, set normratio by ftmp: {} ", oftmp_id, iftmp_id);
                        }
                        else {
                            ICRAFT_LOG(EXCEPT).append("Op Id: {}, Not Supported Concat Normratio", operation->op_id);
                        }
                    }
                }
            }
        }
        else {
            CatNormratio(operation, operation.cast<Concat>()->axis, options, logger, operation->op_id);
        }
        auto consumers = operation.consumers();
        for (auto consumer : consumers) {
            PassChangedNormDown(consumer, options, logger, operation->op_id);
        }
    }
    else if (operation.is<Cast>()) {
        auto iftmp = operation->inputs[0];
        auto oftmp = operation->outputs[0];
        auto itype = logger.get_mutable()->cast_type[operation->op_id].first;
        auto otype = logger.get_mutable()->cast_type[operation->op_id].second;
        if (itype.isFP32()) {
            auto input_ftmp_id = iftmp->v_id;
            auto output_ftmp_id = oftmp->v_id;
            auto iftmp_norm = logger.getFtmpNormratio(iftmp->v_id);
            logger.logFtmpNormratio(output_ftmp_id, iftmp_norm);
            logger.info("\tftmp id: {}, pass changed normratio from ftmp {} to {}",
                output_ftmp_id, input_ftmp_id, iftmp_norm[0]);
            auto consumers = operation.consumers();
            for (auto consumer : consumers) {
                PassChangedNormDown(consumer, options, logger, operation->op_id);
            }
        }
        else if (otype.isFP32()) {
        }
        else {
            auto input_ftmp_id = operation->inputs[0]->v_id;
            auto output_ftmp = operation->outputs[0];
            auto output_ftmp_id = output_ftmp->v_id;
            auto nr = logger.getFtmpNormratio(input_ftmp_id);
            std::vector<float> nr_value;
            if (itype.isSInt(8)) {
                for (int i = 0; i < nr.size(); i++) {
                    nr_value.push_back(nr[i] / 256);
                }
                logger.logFtmpNormratio(output_ftmp_id, nr_value);
            }
            else {
                for (int i = 0; i < nr.size(); i++) {
                    nr_value.push_back(nr[i] * 256);
                }
                logger.logFtmpNormratio(output_ftmp_id, nr_value);
            }
            logger.info("\tftmp id: {}, pass changed normraito from ftmp {} to {}",
                output_ftmp_id, input_ftmp_id, nr_value[0]);
            auto consumers = operation.consumers();
            for (auto&& consumer : consumers) {
                PassChangedNormDown(consumer, options, logger, operation->op_id);
            }
        }
    }
    else if (operation.is<Split>()) {
        auto op = operation.cast<Split>();
        auto input_ftmp_id = op->inputs[0]->v_id;
        auto normratio = logger.getFtmpNormratio(input_ftmp_id);
        auto output_ftmps = op->outputs;
        auto oftmp_dim = output_ftmps[0].tensorType()->shape;
        auto axis = op->axis;
        if (axis == (oftmp_dim.size() - 1) || axis == -1) {
            auto it = normratio.begin();
            for (auto&& output_ftmp : output_ftmps) {
                auto output_ftmp_id = output_ftmp->v_id;
                auto output_chann = output_ftmp.tensorType()->shape[axis];
                auto nr = std::vector<float>(it, it + output_chann);
                logger.logFtmpNormratio(output_ftmp_id, nr);

                auto start = it - normratio.begin();
                auto end = start + output_chann;
                logger.info("Splited from ftmp {} at axis {}, normratio is slice[{}, {})", input_ftmp_id, axis, start, end);
                it += output_chann;
            }
        }
        else {
            for (auto&& output_ftmp : output_ftmps) {
                auto output_ftmp_id = output_ftmp->v_id;
                auto nr = normratio;
                logger.logFtmpNormratio(output_ftmp_id, nr);
                logger.info("Splited from ftmp {} at axis {}, pass normratio from ftmp {}", input_ftmp_id, axis, input_ftmp_id);
            }
        }
        auto consumers = operation.consumers();
        for (auto consumer : consumers) {
            PassChangedNormDown(consumer, options, logger, operation->op_id);
        }
        }
    else if (operation.is<Slice>()) {
        auto op = operation.cast<Slice>();
        auto iftmp_id = op->inputs[0]->v_id;
        auto iftmp_nr = logger.getFtmpNormratio(iftmp_id);
        auto iftmp_shape = op->inputs[0].tensorType()->shape;
        auto begin = op->begin;
        auto end = op->end;
        auto stride = op->stride;
        if (end[-1] - begin[-1] != iftmp_shape[-1] || stride[-1] != 1) {
            auto inorm0_value = iftmp_nr[0];
            bool inorm_all_same = std::all_of(iftmp_nr.begin() + 1, iftmp_nr.end(), [&](auto x) {return x == inorm0_value; });
            if (!inorm_all_same) ICRAFT_LOG(EXCEPT, 21011).append("Slice: input normratio must be all same!");
            auto oftmp_nr = std::vector<float>(op[0].tensorType()->shape[-1], iftmp_nr[0]);
            logger.logFtmpNormratio(op[0]->v_id, oftmp_nr);
            logger.info("\tftmp id: {}, pass normratio = {}", op[0]->v_id, oftmp_nr[0]);
        }
        else {
            logger.logFtmpNormratio(op[0]->v_id, iftmp_nr);
            logger.info("\tftmp id: {}, pass normratio = {}", op[0]->v_id, iftmp_nr[0]);
        }
        auto consumers = operation.consumers();
        for (auto consumer : consumers) {
            PassChangedNormDown(consumer, options, logger, operation->op_id);
        }
    }
    else {

    }
}

inline static void ChangeNetworkInputNorm(Network& network, const QuantizerOptions& options, QuantizerLogger& logger) {
    auto splitWith = [](std::string filename, std::string sep) {
        if (filename.back() != *sep.c_str()) filename += sep;
        auto size = filename.size();
        std::vector<int> result;
        for (int i = 0; i < size; i++) {
            auto pos = filename.find(sep, i);
            if (pos < size) {
                auto input_i = filename.substr(i, pos - i);
                result.push_back(stoi(input_i));
                i = pos + sep.size() - 1;
            }
        }
        return result;
    };

    logger.info("Change input normratio");
    auto norm_id = splitWith(options->input_norm, ";");
    auto input = network->ops.front().cast<Input>();
    auto outftmps = input->outputs;
    for (int i = 0; i < norm_id.size(); i++) {
        auto id = outftmps[i]->v_id;
        auto sat = logger.getFtmpSat(norm_id[i]);
        auto norm = logger.getFtmpNormratio(norm_id[i]);
        logger.logFtmpNormratio(id, norm);
        logger.logFtmpSat(id, sat);
        logger.info("\tftmp id: {}, changed to ftmp id: {}, changed normratio = {}", id, norm_id[i], norm[0]);
    }
    //保证输出normratio递归向后传递
    auto consumers = input.consumers();
    for (auto&& consumer : consumers) {
        PassChangedNormDown(consumer, options, logger);
    }
}
```