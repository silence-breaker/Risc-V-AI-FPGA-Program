# Program Listing for File utils.h[#](#program-listing-for-file-utils-h "此标题的永久链接")

↰ [Return to documentation for file](file_icraft-backends_hostbackend_utils.h.md#file-icraft-backends-hostbackend-utils-h) (`icraft-backends\hostbackend\utils.h`)

```
#pragma once
#ifndef HOSTBKND_UTILS_PCH_GUARD
#define HOSTBKND_UTILS_PCH_GUARD
#include "icraft-backends/hostbackend/backend.h"
#include "icraft-backends/hostbackend/dllexport.h"
#include "icraft-backends/hostbackend/decode_custom.h"
#include "icraft-xrt/core/tensor.h"

namespace icraft::hostbackend::utils {

    HOSTBKND_DLL xrt::Tensor Image2Tensor(const std::string& img_path, int height = -1, int width = -1);

    HOSTBKND_DLL xrt::Tensor Image2Tensor(const std::string& img_path, const xir::Value& value, bool bgr_order = true);

    HOSTBKND_DLL xrt::Tensor Ftmp2Tensor(const std::string& ftmp_path, const xir::Value& value);

    HOSTBKND_DLL std::vector<xrt::Tensor> DecodeWithDecoder(const std::string& dll_path, const std::string& file_path, const std::vector<xir::TensorType>& data_type);

    HOSTBKND_DLL xrt::Tensor Cast(const xrt::Tensor& input, const xrt::TensorType& input_type, const xrt::TensorType& output_type, xrt::HostBackend& backend);
}

#endif //HOSTBKND_UTILS_PCH_GUARD
```
