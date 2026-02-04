# Program Listing for File dllexport.h[#](#program-listing-for-file-dllexport-h "此标题的永久链接")

↰ [Return to documentation for file](file_icraft-backends_hostbackend_dllexport.h.md#file-icraft-backends-hostbackend-dllexport-h) (`icraft-backends\hostbackend\dllexport.h`)

```
#pragma once

#ifdef _WIN32
#ifdef  HOSTBKND_DLL_EXPORTS
#define HOSTBKND_DLL _declspec(dllexport)
#else
#define HOSTBKND_DLL _declspec(dllimport)
#endif
#else
#define HOSTBKND_DLL
#endif
```
