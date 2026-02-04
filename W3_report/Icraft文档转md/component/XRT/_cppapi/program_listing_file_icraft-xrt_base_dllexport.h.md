# Program Listing for File dllexport.h

```cpp
#pragma once

#ifdef _WIN32
#ifdef XRT_DLL_EXPORTS
#define XRT_DLL _declspec(dllexport)
#else
#define XRT_DLL _declspec(dllimport)
#endif
#else
#define XRT_DLL
#endif
```

[Return to documentation for file](file_icraft-xrt_base_dllexport.h.md#file-icraft-xrt-base-dllexport-h)
