# Program Listing for File version.h

# Program Listing for File version.h

↰ [Return to documentation for file](file_icraft-parserapi_version.h.md#file-icraft-parserapi-version-h) (`icraft-parserapi\version.h`)

```
#pragma once
#include <string>
#include "dllexport.h"

namespace icraft::parser {

    PARSER_API std::string_view MainVersion();

    PARSER_API std::string_view FullVersion();

    PARSER_API uint64_t MajorVersionNum();

    PARSER_API uint64_t MinorVersionNum();

    PARSER_API uint64_t PatchVersionNum();

    PARSER_API uint64_t CommitSinceTag();

    PARSER_API std::string_view CommitID();

    PARSER_API bool IsModified();

    PARSER_API std::string_view BuildTime();
}
```