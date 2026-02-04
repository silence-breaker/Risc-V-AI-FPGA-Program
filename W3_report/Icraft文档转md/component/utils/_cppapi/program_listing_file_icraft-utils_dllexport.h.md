# Program Listing for File dllexport.h

↰ [Return to documentation for file](file_icraft-utils_dllexport.h.md#file-icraft-utils-dllexport-h) (`icraft-utils\dllexport.h`)

#pragma once

#ifdef _WIN32
#ifdef UTILS_DLL_EXPORTS
#define UTILS_DLL _declspec(dllexport)
#else
#define UTILS_DLL _declspec(dllimport)
#endif
#else
#define UTILS_DLL
#endif
</pre>

                