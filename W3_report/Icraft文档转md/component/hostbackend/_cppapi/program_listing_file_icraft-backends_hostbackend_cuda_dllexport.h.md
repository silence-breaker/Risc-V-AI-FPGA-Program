# Program Listing for File dllexport.h[#](#program-listing-for-file-dllexport-h "此标题的永久链接")

↰ [Return to documentation for file](file_icraft-backends_hostbackend_cuda_dllexport.h.md#file-icraft-backends-hostbackend-cuda-dllexport-h) (`icraft-backends\hostbackend\cuda\dllexport.h`)

```
#pragma once

#ifdef _WIN32
#ifdef  CUDADEV_DLL_EXPORTS
#define CUDADEV_DLL _declspec(dllexport)
#else
#define CUDADEV_DLL _declspec(dllimport)
#endif
#else
#define CUDADEV_DLL
#endif
```
