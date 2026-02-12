# Program Listing for File dllexport.h



↰ [Return to documentation for file](file_icraft-backends_hostbackend_dllexport.h.md#file-icraft-backends-hostbackend-dllexport-h) (`icraft-backends\hostbackend\dllexport.h`)


```cpp
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
</pre>
```
