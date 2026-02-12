# Program Listing for File dll.h

↰ [Return to documentation for file](file_icraft-utils_dll.h.md#file-icraft-utils-dll-h) (`icraft-utils\dll.h`)

#pragma once
#include &lt;optional&gt;
#include &quot;icraft-utils/midware/path.hpp&quot;
#include &quot;icraft-utils/midware/thread.hpp&quot;
#include &quot;icraft-utils/dllexport.h&quot;

namespace icraft {

    UTILS_DLL void* LoadDLLByPath(const icraft::midware::path&amp; dll_file);
    #ifndef _BAREME
    UTILS_DLL void* LoadDLLByPath(const std::filesystem::path&amp; p);
    #endif
    UTILS_DLL void* LoadDLLInBinDir(const std::string&amp; target_name);

    UTILS_DLL std::optional&lt;std::string&gt; SearchDLLByEnvVar(const std::string&amp; target_name, const std::string&amp; env_var);

    UTILS_DLL int SearchAndLoadDlls(const std::string&amp; type_key);

    UTILS_DLL std::string GetDLLDir();

    UTILS_DLL std::string GetDLLFileName(const std::string&amp; target_name);
}
</pre>

                