# Program Listing for File file.h

↰ [Return to documentation for file](file_icraft-utils_file.h.md#file-icraft-utils-file-h) (`icraft-utils\file.h`)

#include &lt;fstream&gt;
#include &lt;vector&gt;
#include &quot;icraft-utils/midware/path.hpp&quot;
#include &quot;icraft-utils/midware/filestream.hpp&quot;
#include &quot;icraft-utils/dllexport.h&quot;

namespace icraft {

#ifndef _BAREME
    UTILS_DLL icraft::midware::ifstream safeLoadFileMidware(const std::filesystem::path&amp; filename, std::ios_base::openmode mode = std::ios_base::in);

    // 原始接口，保证编译器其他组件不修改
    UTILS_DLL std::ifstream safeLoadFile(const std::filesystem::path&amp; filename, std::ios_base::openmode mode = std::ios_base::in);

#endif
    UTILS_DLL icraft::midware::ifstream safeLoadFileMidware(const icraft::midware::path&amp; filename, std::ios_base::openmode mode = std::ios_base::in);

    UTILS_DLL void safeCreateDirectory(const icraft::midware::path&amp; dirname);

#ifndef _BAREME
    UTILS_DLL void safeCreateDirectory(const std::filesystem::path&amp; dirname);
#endif // !_BAREME

    UTILS_DLL std::string getSuffix(const std::string&amp; file_name);

    UTILS_DLL bool isPicture(const std::string&amp; file_name);

    UTILS_DLL bool isFtmp(const std::string&amp; file_name);

    UTILS_DLL std::vector&lt;std::string&gt; getFiles(std::string input_str);
}
</pre>

                