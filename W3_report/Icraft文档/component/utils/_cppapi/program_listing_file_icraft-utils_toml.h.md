# Program Listing for File toml.h

↰ [Return to documentation for file](file_icraft-utils_toml.h.md#file-icraft-utils-toml-h) (`icraft-utils\toml.h`)

#pragma once
#include &quot;icraft-utils/dllexport.h&quot;
#include &lt;map&gt;
#include &lt;string&gt;

namespace icraft {

    UTILS_DLL std::map&lt;std::string, std::string&gt; getKVfromTomlFile(const std::string&amp; filename, const std::string&amp; command);
}
</pre>

                