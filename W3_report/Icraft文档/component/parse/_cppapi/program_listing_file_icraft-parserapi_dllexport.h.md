# Program Listing for File dllexport.h

# Program Listing for File dllexport.h

↰ [Return to documentation for file](file_icraft-parserapi_dllexport.h.md#file-icraft-parserapi-dllexport-h) (`icraft-parserapi\dllexport.h`)

```
#pragma once

#ifdef _WIN32
#ifdef PARSER_DLL_EXPORTS
#define PARSER_API _declspec(dllexport)
#else
#define PARSER_API _declspec(dllimport)
#endif
#else
#define PARSER_API
#endif
```