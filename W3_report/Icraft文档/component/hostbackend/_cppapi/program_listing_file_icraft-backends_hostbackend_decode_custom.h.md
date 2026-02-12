# Program Listing for File decode\_custom.h[#](#program-listing-for-file-decode-custom-h "此标题的永久链接")

↰ [Return to documentation for file](file_icraft-backends_hostbackend_decode_custom.h.md#file-icraft-backends-hostbackend-decode-custom-h) (`icraft-backends\hostbackend\decode_custom.h`)

```
#pragma once
#ifndef HOSTBKND_DECODE_CUSTOM_PCH_GUARD
#define HOSTBKND_DECODE_CUSTOM_PCH_GUARD
#ifdef _WIN32
#define CUSTOM_API _declspec(dllexport)
#else
#define CUSTOM_API __attribute__ ((used))
#endif

#include "icraft-xrt/core/tensor.h"

using namespace icraft;

class CustomDecoder {
public:
    virtual std::vector<xrt::Tensor> decode(const std::string& file_path, const std::vector<xrt::TensorType>& data_type) = 0;
};

extern "C" CUSTOM_API CustomDecoder * GetCustomDecoder();

#ifdef _WIN32
    #define REGISTER_CUSTOM_DECODER(CLASS_NAME)     \
    extern "C" __declspec(dllexport) CustomDecoder* GetCustomDecoder(){ return new CLASS_NAME();}
#else
    #define REGISTER_CUSTOM_DECODER(CLASS_NAME)     \
    extern "C" CustomDecoder* GetCustomDecoder(){ return new CLASS_NAME();}
#endif

#endif //HOSTBKND_DECODE_CUSTOM_PCH_GUARD
```
