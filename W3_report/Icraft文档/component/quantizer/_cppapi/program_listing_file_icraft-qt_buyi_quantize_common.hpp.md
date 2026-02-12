# Program Listing for File common.hpp

# Program Listing for File common.hpp

↰ [Return to documentation for file](file_icraft-qt_buyi_quantize_common.hpp.md#file-icraft-qt-buyi-quantize-common-hpp) (`icraft-qt\buyi\quantize\common.hpp`)

```
#pragma once

#include <icraft-xir/core/operation.h>

#include <icraft-xrt/core/session.h>
#include <icraft-xrt/core/tensor.h>
#include <icraft-xrt/dev/host_device.h>
#include <icraft-backends/hostbackend/backend.h>

#include <icraft-qt/core/quantizer_logger.h>
#include <icraft-qt/core/quantizer_options.h>

#include <icraft-qt/internal/observes.hpp>
#include <icraft-qt/internal/utils.hpp>

using namespace icraft::xir;
using namespace icraft::xrt;
using namespace icraft::qt;
using namespace icraft::qt::utils;

inline static TensorType MakeQDtype(
    Array<int64_t> shape,
    Layout layout,
    int bits,
    std::vector<std::pair<int, int>> hard_scale,
    std::vector<float> scale
) {
    ScalarType storage_dtype;
    if (bits == 8) storage_dtype = IntegerType::SInt8();
    else if (bits == 16) storage_dtype = IntegerType::SInt16();
    else if (bits == 32) storage_dtype = IntegerType::SInt32();
    else ICRAFT_LOG(EXCEPT, 21003) << bits << "bit dtype not supported!";

    ExpQuantizedScaleArray scale_c;
    for (int i = 0; i < scale.size(); i++) {
        auto& [m, n] = hard_scale[i];
        ExpQuantizedScale scale_temp(m, n, scale[i]);
        scale_c = ExpQuantizedScaleArray(scale_c, ExpQuantizedScaleArray(1, scale_temp));
    }
    auto q_type = QuantizedType(scale_c, std::move(storage_dtype));
    auto tensor_type = TensorType(q_type, std::move(shape), std::move(layout));
    return tensor_type;
}

inline static TensorType MakeQDtype(Array<int64_t> shape, Layout layout, int bits,
    std::vector<std::pair<int, int>> hard_scale, std::vector<float> scale,
    std::vector<float> normratio) {
    ScalarType storage_dtype;
    if (bits == 8) storage_dtype = IntegerType::SInt8();
    else if (bits == 16) storage_dtype = IntegerType::SInt16();
    else if (bits == 32) storage_dtype = IntegerType::SInt32();
    else ICRAFT_LOG(EXCEPT, 21003) << bits << "bit dtype not supported!";

    ExpQuantizedScaleArray scale_c;
    for (int i = 0; i < scale.size(); i++) {
        auto& [m, n] = hard_scale[i];
        ExpQuantizedScale scale_temp(m, n, scale[i]);
        scale_c = ExpQuantizedScaleArray(scale_c, ExpQuantizedScaleArray(1, scale_temp));
    }
    auto q_type = NormalizedQuantizedType(normratio, std::move(scale_c), std::move(storage_dtype));
    auto tensor_type = TensorType(q_type, std::move(shape), std::move(layout));
    return tensor_type;
}

inline static void QuantizeFtmp(const Operation& operation, const QuantizerOptions& options, QuantizerLogger& logger) {
    auto& qdtype_op_list = logger->qdtype_op_list;
    auto& qdtype_value_op_list = logger->qdtype_value_op_list;

    auto op_id = operation->op_id;
    auto bits = qdtype_value_op_list.at(op_id);
    auto type = qdtype_op_list.at(op_id);
    auto output_ftmps = operation->outputs;
    for (auto&& output_ftmp : output_ftmps) {
        auto output_ftmp_id = output_ftmp->v_id;
        auto norm = logger.getFtmpNormratio(output_ftmp_id);
        auto shape = output_ftmp.tensorType()->shape;
        auto layout = output_ftmp.tensorType()->layout;
        auto co = shape[-1];
        auto hard_scale = std::vector<std::pair<int, int>>(co, { 1, 0 });
        auto scale = std::vector<float>(co, 1);
        auto o_type = MakeQDtype(shape, layout, bits, hard_scale, scale, norm);
        output_ftmp.setDType(o_type);

        logger.logFtmpScale(output_ftmp_id, 1);
        logger.logFtmpExp(output_ftmp_id, 0);
        logger.info("\tQuantizing ftmp id: {}, scale: {}, exp: {}", output_ftmp_id, 1, 0);
    }
}

inline static std::pair<std::vector<float>, std::vector<float>> MeasureWeight(
    const Value& weight,
    std::string per,
    const options::Saturation& saturation,
    const int& axis,
    const QuantizerOptions& options,
    QuantizerLogger& logger
) {
    if (!options->raw_csv.empty()) {
        try {
            std::pair<std::vector<float>, std::vector<float>> sat_max(
                logger.getRawSat(weight->v_id), logger.getRawMax(weight->v_id));
            return sat_max;
        }
        catch (std::exception& e) {
            ICRAFT_LOG(EXCEPT, 21013)
                .append("Read raw CSV: Not find ftmp id = {} in ftmp csv {}", weight->v_id, options->raw_csv);
            return {};                      // 防止编译器报没有返回值
        }
    }
    else {
        auto observe = saturation == options::Saturation::nsigma ? &QuickEms : GetObserveFunction(saturation);
        std::pair<float, float> data_stat;
        std::vector<float> sat;
        std::vector<float> max;
        int raw_id = weight->v_id;
        auto& dims = weight.tensorType()->shape;
        auto dims_size = dims.size();
        auto co = dims[axis];
        auto size = weight.tensorType().numElements();
        //per tensor
        if (per == "tensor") {
            auto data = weight.cast<Params>().data<float>().get();
            data_stat = observe(size, data, options);
            for (int i = 0; i < co; i++) {
                sat.push_back(data_stat.first);
                max.push_back(data_stat.second);
            }
            logger.info("\tMeasuring Weight: sat: {}, max: {}", sat[0], max[0]);
        }
        //per channel
        else if (per == "channel") {
            auto step = size / co;
            auto weight_tensor = icraft::xrt::Tensor(weight.cast<Params>());
            std::vector<int> perm(dims_size);
            std::iota(perm.begin(), perm.end(), 0);
            perm[0] = axis;
            perm[axis] = 0;

            //调整对应axis的维度到第一维
            icraft::xrt::Tensor o_tensor;
            if (dims_size == 1) {
                o_tensor = weight_tensor;
            }
            else {
                auto transpose = icraft::xir::Transpose(weight.tensorType(), perm, icraft::xir::Layout::Default(dims_size));
                transpose.inferResults();
                auto backend = HostBackend::Init();
                backend.setDevice(HostDevice::Default());
                auto output_tensors = backend.forwardOp(transpose, { weight_tensor });
                o_tensor = output_tensors[0];
            }
            auto oihw_data = (float*)o_tensor.data().cptr();
            for (int i = 0; i < co; i++) {
                auto channel = new float[step];
                for (int j = 0; j < step; j++) {
                    channel[j] = oihw_data[i * step + j];
                }
                data_stat = observe(step, channel, options);
                delete[] channel;
                sat.push_back(data_stat.first);
                max.push_back(data_stat.second);
                logger.info("\tMeasuring Weight: channel: {}, sat: {}, max: {}", i + 1, sat[i], max[i]);
            }
        }
        else {
            ICRAFT_LOG(EXCEPT, 21003).append("per = {} is not supported", per);
        }
        logger.logRawDims(raw_id, dims);
        logger.logRawMax(raw_id, max);
        logger.logRawSat(raw_id, sat);
        auto sat_max = std::pair<std::vector<float>, std::vector<float>>(sat, max);
        return sat_max;
    }
}

inline static void* QuantizeData(float* data_ptr, size_t size, int bits, int co, std::vector<float> scale) {
    auto bound = pow(2, bits - 1);
    auto top = bound - 1;
    auto bottom = -top;
    auto step = size / co;
    if (bits <= 8) {
        auto qt_data = new int8_t[size];
        for (int i = 0; i < co; i++) {
            std::transform(data_ptr + i * step, data_ptr + (i + 1) * step, qt_data + i * step, [&](auto f) {
                auto qd = round(f / scale[i]);
                if (qd > top) qd = top;
                if (qd < bottom) qd = bottom;
                int8_t qt = static_cast<int8_t>(qd);
                return qt;
                });

        }
        return qt_data;
    }
    else if (bits <= 16) {
        auto qt_data = new int16_t[size];
        for (int i = 0; i < co; i++) {
            std::transform(data_ptr + i * step, data_ptr + (i + 1) * step, qt_data + i * step, [&](auto f) {
                auto qd = round(f / scale[i]);
                if (qd > top) qd = top;
                if (qd < bottom) qd = bottom;
                int16_t qt = static_cast<int16_t>(qd);
                return qt;
                });
        }
        return qt_data;
    }
    else if (bits <= 32) {
        auto qt_data = new int32_t[size];
        for (int i = 0; i < co; i++) {
            std::transform(data_ptr + i * step, data_ptr + (i + 1) * step, qt_data + i * step, [&](auto f) {
                double qd = round(f / scale[i]);
                if (qd > top) qd = top;
                if (qd < bottom) qd = bottom;
                int32_t qt = static_cast<int32_t>(qd);
                return qt;
                });
        }
        return qt_data;
    }
    else {
        ICRAFT_LOG(EXCEPT, 21003).append("bits = {} are not supported!", bits);
        return data_ptr;                        // 防止编译器报没有返回值
    }
}

inline static void QuantizeParams(
    icraft::xir::Value& weight,
    icraft::xir::Value& bias,
    int bits,
    const std::vector<std::pair<int, int>>& h_w_scale,
    const std::vector<std::pair<int, int>>& h_b_scale,
    const std::vector<float>& w_scale,
    const std::vector<float>& b_scale
) {
    auto co = bias.tensorType()->shape[-1];
    //构造bias的dtype并量化bias
    auto b_shape = bias.tensorType()->shape;
    auto b_layout = bias.tensorType()->layout;
    auto b_dtype = MakeQDtype(b_shape, b_layout, 2 * bits, h_b_scale, b_scale);
    bias.setDType(b_dtype);
    if (bias.tensorType().numElements() != 0) {
        auto bias_data = bias.cast<Params>().data<float>().get();
        auto qt_data = QuantizeData(bias_data, bias.tensorType().numElements(), 2 * bits, co, b_scale);
        if (bits <= 8) {
            auto qt_data_ptr = std::shared_ptr<int16_t[]>((int16_t*)qt_data);
            bias.cast<Params>().setData(qt_data_ptr);

        }
        else if (bits <= 16) {
            auto qt_data_ptr = std::shared_ptr<int32_t[]>((int32_t*)qt_data);
            bias.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 32) {
            auto qt_data_ptr = std::shared_ptr<int32_t[]>((int32_t*)qt_data);
            bias.cast<Params>().setData(qt_data_ptr);
        }

    }
    //构造weight的dtype并量化weight
    auto w_shape = weight.tensorType()->shape;
    auto w_layout = weight.tensorType()->layout;
    auto w_dtype = MakeQDtype(w_shape, w_layout, bits, h_w_scale, w_scale);
    weight.setDType(w_dtype);
    //常规卷积
    if (w_shape.size() == 4 && w_layout == Layout::HWIO()) {
        auto oihw_data = new float[weight.tensorType().numElements()];
        transposeHwio2oihw((float*)weight.cast<Params>().data<float>().get(), oihw_data, w_shape);
        auto qt_data = QuantizeData(oihw_data, weight.tensorType().numElements(), bits, co, w_scale);
        delete[] oihw_data;
        std::vector<int64_t> dim_oihw = { w_shape[3], w_shape[2], w_shape[0], w_shape[1] };
        if (bits <= 8) {
            auto hwio_data = new int8_t[weight.tensorType().numElements()];
            transposeOihw2hwio((int8_t*)qt_data, hwio_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int8_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 16) {
            auto hwio_data = new int16_t[weight.tensorType().numElements()];
            transposeOihw2hwio((int16_t*)qt_data, hwio_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int16_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 32) {
            auto hwio_data = new int32_t[weight.tensorType().numElements()];
            transposeOihw2hwio((int32_t*)qt_data, hwio_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int32_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        delete static_cast<char*>(qt_data);
    }
    //反卷积
    else if (w_layout == Layout::Init().H().W().O().I()) {
        auto oihw_data = new float[weight.tensorType().numElements()];
        transposeHwoi2oihw((float*)weight.cast<Params>().data<float>().get(), oihw_data, w_shape);
        auto qt_data = QuantizeData(oihw_data, weight.tensorType().numElements(), bits, co, w_scale);
        delete[] oihw_data;
        std::vector<int64_t> dim_oihw = { w_shape[2], w_shape[3], w_shape[0], w_shape[1] };
        if (bits <= 8) {
            auto hwoi_data = new int8_t[weight.tensorType().numElements()];
            transposeOihw2hwoi((int8_t*)qt_data, hwoi_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int8_t[]>(hwoi_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 16) {
            auto hwoi_data = new int16_t[weight.tensorType().numElements()];
            transposeOihw2hwoi((int16_t*)qt_data, hwoi_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int16_t[]>(hwoi_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 32) {
            auto hwoi_data = new int32_t[weight.tensorType().numElements()];
            transposeOihw2hwoi((int32_t*)qt_data, hwoi_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int32_t[]>(hwoi_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        delete static_cast<char*>(qt_data);
    }
    else if (w_shape.size() == 3) {
        auto oihw_data = new float[weight.tensorType().numElements()];
        transposenio2oin((float*)weight.cast<Params>().data<float>().get(), oihw_data, w_shape);
        auto qt_data = QuantizeData(oihw_data, weight.tensorType().numElements(), bits, w_scale.size(), w_scale);
        delete[] oihw_data;
        std::vector<int64_t> dim_oin = { w_shape[2], w_shape[1], w_shape[0] };
        if (bits <= 8) {
            auto hwio_data = new int8_t[weight.tensorType().numElements()];
            transposeoin2nio((int8_t*)qt_data, hwio_data, dim_oin);
            auto qt_data_ptr = std::shared_ptr<int8_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 16) {
            auto hwio_data = new int16_t[weight.tensorType().numElements()];
            transposeoin2nio((int16_t*)qt_data, hwio_data, dim_oin);
            auto qt_data_ptr = std::shared_ptr<int16_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 32) {
            auto hwio_data = new int32_t[weight.tensorType().numElements()];
            transposeoin2nio((int32_t*)qt_data, hwio_data, dim_oin);
            auto qt_data_ptr = std::shared_ptr<int32_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        delete static_cast<char*>(qt_data);
    }
    //BatchNorm2d类算子
    else {
        auto qt_data = QuantizeData((float*)weight.cast<Params>().data<float>().get(), weight.tensorType().numElements(), bits, w_scale.size(), w_scale);
        if (bits <= 8) {
            auto qt_data_ptr = std::shared_ptr<int8_t[]>((int8_t*)qt_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 16) {
            auto qt_data_ptr = std::shared_ptr<int16_t[]>((int16_t*)qt_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 32) {
            auto qt_data_ptr = std::shared_ptr<int32_t[]>((int32_t*)qt_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
    }
}

inline static void QuantizeParams(
    icraft::xir::Value& weight,
    int bits,
    std::vector<std::pair<int, int>> h_w_scale,
    std::vector<float> w_scale
) {
    auto co = weight.tensorType()->shape[-1];
    //构造weight的dtype并量化weight
    auto w_shape = weight.tensorType()->shape;
    auto w_layout = weight.tensorType()->layout;
    auto w_dtype = MakeQDtype(w_shape, w_layout, bits, h_w_scale, w_scale);
    weight.setDType(w_dtype);
    //常规卷积
    if (w_shape.size() == 4 && w_layout == Layout::HWIO()) {
        auto oihw_data = new float[weight.tensorType().numElements()];
        transposeHwio2oihw((float*)weight.cast<Params>().data<float>().get(), oihw_data, w_shape);
        auto qt_data = QuantizeData(oihw_data, weight.tensorType().numElements(), bits, co, w_scale);
        delete[] oihw_data;
        std::vector<int64_t> dim_oihw = { w_shape[3], w_shape[2], w_shape[0], w_shape[1] };
        if (bits <= 8) {
            auto hwio_data = new int8_t[weight.tensorType().numElements()];
            transposeOihw2hwio((int8_t*)qt_data, hwio_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int8_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 16) {
            auto hwio_data = new int16_t[weight.tensorType().numElements()];
            transposeOihw2hwio((int16_t*)qt_data, hwio_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int16_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 32) {
            auto hwio_data = new int32_t[weight.tensorType().numElements()];
            transposeOihw2hwio((int32_t*)qt_data, hwio_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int32_t[]>(hwio_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        delete static_cast<char*>(qt_data);
    }
    //反卷积
    else if (w_layout == Layout::Init().H().W().O().I()) {
        auto oihw_data = new float[weight.tensorType().numElements()];
        transposeHwoi2oihw((float*)weight.cast<Params>().data<float>().get(), oihw_data, w_shape);
        auto qt_data = QuantizeData(oihw_data, weight.tensorType().numElements(), bits, co, w_scale);
        delete[] oihw_data;
        std::vector<int64_t> dim_oihw = { w_shape[2], w_shape[3], w_shape[0], w_shape[1] };
        if (bits <= 8) {
            auto hwoi_data = new int8_t[weight.tensorType().numElements()];
            transposeOihw2hwoi((int8_t*)qt_data, hwoi_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int8_t[]>(hwoi_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 16) {
            auto hwoi_data = new int16_t[weight.tensorType().numElements()];
            transposeOihw2hwoi((int16_t*)qt_data, hwoi_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int16_t[]>(hwoi_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 32) {
            auto hwoi_data = new int32_t[weight.tensorType().numElements()];
            transposeOihw2hwoi((int32_t*)qt_data, hwoi_data, dim_oihw);
            auto qt_data_ptr = std::shared_ptr<int32_t[]>(hwoi_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        delete static_cast<char*>(qt_data);
    }
    //BatchNorm2d类算子
    else {
        auto qt_data = QuantizeData((float*)weight.cast<Params>().data<float>().get(), weight.tensorType().numElements(), bits, 1, w_scale);
        if (bits <= 8) {
            auto qt_data_ptr = std::shared_ptr<int8_t[]>((int8_t*)qt_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 16) {
            auto qt_data_ptr = std::shared_ptr<int16_t[]>((int16_t*)qt_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
        else if (bits <= 32) {
            auto qt_data_ptr = std::shared_ptr<int32_t[]>((int32_t*)qt_data);
            weight.cast<Params>().setData(qt_data_ptr);
        }
    }
}

inline static std::vector<float> GetBiasSat(
    const Operation& operation,
    QuantizerLogger& logger
) {
    auto oftmp_id = operation->outputs[0]->v_id;
    auto f_max = logger.getFtmpMax(oftmp_id);
    auto norm = logger.getFtmpNormratio(oftmp_id);
    auto getBiasSat = [](std::vector<float> max, std::vector<float> norm) {
        if (max.size() != norm.size()) ICRAFT_LOG(EXCEPT, 21011).append("f_max size != f_norm size");
        std::vector<float> b_sat;
        for (int i = 0; i < max.size(); i++) {
            b_sat.push_back(max[i] / norm[i]);
        }
        return b_sat;
    };
    return getBiasSat(f_max, norm);
}

inline static std::tuple<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>, std::vector<int>, int>
adaptDepthScale(std::vector<float> w_scale, std::vector<float> b_scale, int bits, std::string per, QuantizerLogger& logger) {
    std::vector<float> h_w_scale_f;
    std::vector<float> h_b_scale_f;
    std::vector<std::pair<int, int>> h_w_scale;
    std::vector<std::pair<int, int>> h_b_scale;
    std::vector<int> exp_c;
    int exp_max = INT_MIN;
    auto zero_bound = pow(2, -(2 * bits)) / 2;
    for (int i = 0; i < w_scale.size(); i++) {
        if (w_scale[i] > zero_bound) {
            auto h_w_scale_iter = AdjustScale(w_scale[i], bits, bits, 2 * bits);
            h_w_scale_f.push_back(h_w_scale_iter.first * pow(2, -(h_w_scale_iter.second)));
            h_w_scale.push_back(h_w_scale_iter);
            //b_scale
            auto h_b_scale_iter = h_w_scale_iter;
            h_b_scale_f.push_back(h_b_scale_iter.first * pow(2, -(h_b_scale_iter.second)));
            h_b_scale.push_back(h_b_scale_iter);
        }
        else if (b_scale[i] > zero_bound) {
            auto h_b_scale_iter = AdjustScale(b_scale[i], bits, bits, 2 * bits);
            h_b_scale_f.push_back(h_b_scale_iter.first * pow(2, -(h_b_scale_iter.second)));
            h_b_scale.push_back(h_b_scale_iter);
            auto [a, b] = h_b_scale_iter;
            //w_scale
            auto h_w_scale_iter = h_b_scale_iter;
            h_w_scale_f.push_back(h_w_scale_iter.first * pow(2, -(h_w_scale_iter.second)));
            h_w_scale.push_back(h_w_scale_iter);
        }
        else {
            //w_scale和b_scale全赋1
            h_b_scale_f.push_back(1);
            h_b_scale.push_back({ (int)(pow(2, bits) - 1),bits });
            h_w_scale_f.push_back(1);
            h_w_scale.push_back({ (int)(pow(2, bits) - 1),bits });
        }
        if (per == "channel") {
            logger.info("\tQuantizing Weight: channel: {}, raw scale_w = {}, adjust scale_w = {}, m = {}, n = {}",
                i, w_scale[i], h_w_scale_f[i], h_w_scale[i].first, h_w_scale[i].second);
            logger.info("\tQuantizing Bias: channel: {}, raw scale_b = {}, adjust scale_b = {}, a = {}, b = {}",
                i, b_scale[i], h_b_scale_f[i], h_b_scale[i].first, h_b_scale[i].second);
        }
        auto exp = h_w_scale[i].second - h_b_scale[i].second;
        exp_c.push_back(exp);
        if (exp > exp_max) exp_max = exp;
    }
    return std::tuple(h_w_scale, h_b_scale, exp_c, exp_max);
}

inline static std::tuple<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>, std::vector<int>, int>
adaptScale(std::vector<float> w_scale, std::vector<float> b_scale, int bits, std::string per, QuantizerLogger& logger) {
    std::vector<float> h_w_scale_f;
    std::vector<float> h_b_scale_f;
    std::vector<std::pair<int, int>> h_w_scale;
    std::vector<std::pair<int, int>> h_b_scale;
    std::vector<int> exp_c;
    int exp_max = INT_MIN;
    auto zero_bound = pow(2, -(2 * bits + 5)) / 2;
    for (int i = 0; i < w_scale.size(); i++) {
        if (w_scale[i] > zero_bound) {
            auto h_w_scale_iter = AdjustScale(w_scale[i], bits, bits, 2 * bits + 5);
            h_w_scale_f.push_back(h_w_scale_iter.first * pow(2, -(h_w_scale_iter.second)));
            h_w_scale.push_back(h_w_scale_iter);
            //b_scale
            auto [m, n] = h_w_scale_iter;
            int b_min, b_max;
            n - 5 > bits ? b_min = n - 5 : b_min = bits;
            n < 2 * bits ? b_max = n : b_max = 2 * bits;
            auto h_b_scale_iter = AdjustScaleC(b_scale[i], m, b_min, b_max);
            h_b_scale_f.push_back(h_b_scale_iter.first * pow(2, -(h_b_scale_iter.second)));
            h_b_scale.push_back(h_b_scale_iter);
        }
        else if (b_scale[i] > zero_bound) {
            auto h_b_scale_iter = AdjustScale(b_scale[i], bits, bits, 2 * bits);
            h_b_scale_f.push_back(h_b_scale_iter.first * pow(2, -(h_b_scale_iter.second)));
            h_b_scale.push_back(h_b_scale_iter);
            auto [a, b] = h_b_scale_iter;
            //w_scale
            auto h_w_scale_iter = std::make_pair(a, b + 5);
            h_w_scale_f.push_back(h_w_scale_iter.first * pow(2, -(h_w_scale_iter.second)));
            h_w_scale.push_back(h_w_scale_iter);
        }
        else {
            //w_scale和b_scale全赋1
            h_b_scale_f.push_back(1);
            h_b_scale.push_back({ (int)(pow(2, bits) - 1),bits });
            h_w_scale_f.push_back(1);
            h_w_scale.push_back({ (int)(pow(2, bits) - 1),bits });
        }
        if (per == "channel") {
            logger.info("\tQuantizing Weight: channel: {}, raw scale_w = {}, adjust scale_w = {}, m = {}, n = {}",
                i, w_scale[i], h_w_scale_f[i], h_w_scale[i].first, h_w_scale[i].second);
            logger.info("\tQuantizing Bias: channel: {}, raw scale_b = {}, adjust scale_b = {}, a = {}, b = {}",
                i, b_scale[i], h_b_scale_f[i], h_b_scale[i].first, h_b_scale[i].second);
        }
        auto exp = h_w_scale[i].second - h_b_scale[i].second;
        exp_c.push_back(exp);
        if (exp > exp_max) exp_max = exp;
    }
    return std::tuple(h_w_scale, h_b_scale, exp_c, exp_max);
}

inline static void adaptChannelScale(std::vector<std::pair<int, int>>& h_w_scale, std::vector<std::pair<int, int>>& h_b_scale,
    std::vector<int> exp_c, int exp_max, int bits, QuantizerLogger& logger) {
    for (int i = 0; i < h_w_scale.size(); i++) {
        h_b_scale[i].second = h_b_scale[i].second - (exp_max - exp_c[i]);
        if (h_b_scale[i].second < bits) {
            h_w_scale[i].second = h_w_scale[i].second + (bits - h_b_scale[i].second);
            h_b_scale[i].second = bits;
        }
        logger.info("\tadjust cut2n in channel: {}, scale_w_m: {}, scale_w_n: {}, scale_c_a: {}, scale_c_b: {}",
            i, h_w_scale[i].first, h_w_scale[i].second, h_b_scale[i].first, h_b_scale[i].second);
    }
}
```