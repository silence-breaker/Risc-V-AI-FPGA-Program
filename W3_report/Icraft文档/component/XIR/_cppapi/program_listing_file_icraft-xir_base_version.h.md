# Program Listing for File version.h



↰ [Return to documentation for file](file_icraft-xir_base_version.h.md#file-icraft-xir-base-version-h) (`icraft-xir\base\version.h`)


```cpp
#pragma once
#include <string_view>
#include <icraft-xir/base/dllexport.h>

namespace icraft::xir {

    XIR_DLL std::string_view MainVersion();

    XIR_DLL std::string_view FullVersion();

    XIR_DLL uint64_t MajorVersionNum();

    XIR_DLL uint64_t MinorVersionNum();

    XIR_DLL uint64_t PatchVersionNum();

    XIR_DLL std::string_view IcraftVersion();

    XIR_DLL uint64_t CommitSinceTag();

    XIR_DLL std::string_view CommitID();

    XIR_DLL bool IsModified();

    XIR_DLL std::string_view BuildTime();
}
</pre>
```
