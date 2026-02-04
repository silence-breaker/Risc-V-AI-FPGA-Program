# Program Listing for File parser\_api.h

# Program Listing for File parser\_api.h

↰ [Return to documentation for file](file_icraft-parserapi_parser_api.h.md#file-icraft-parserapi-parser-api-h) (`icraft-parserapi\parser_api.h`)

```
#pragma once
#include <icraft-parserapi/dllexport.h>
#include <icraft-parserapi/netparams.h>

namespace icraft {
    namespace parser {
        PARSER_API int parse(const NetParams& net_params);
        PARSER_API int parseNetwork(const NetParam& net_param);
    }
}
```