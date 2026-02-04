# Program Listing for File string.h

↰ [Return to documentation for file](file_icraft-utils_string.h.md#file-icraft-utils-string-h) (`icraft-utils\string.h`)

#pragma once
#include &lt;vector&gt;
#include &lt;string&gt;

#include &quot;icraft-utils/dllexport.h&quot;

namespace icraft {

    UTILS_DLL std::vector&lt;std::string&gt; split(const std::string&amp; seq, const std::string&amp; delim);

    template &lt;typename T&gt;
    std::vector&lt;std::pair&lt;int64_t, T&gt;&gt; rleCompress(const std::vector&lt;T&gt;&amp; input) {

        if (input.empty()) {
            return {};
        }

        std::vector&lt;std::pair&lt;int64_t, T&gt;&gt; ans;

        std::string compressed;
        T currentChar = input[0];
        int count = 1;

        for (size_t i = 1; i &lt; input.size(); ++i) {
            if (input[i] == currentChar) {
                ++count;
            }
            else {
                ans.push_back({ count, currentChar });
                currentChar = input[i];
                count = 1;
            }
        }

        ans.push_back({ count, currentChar });

        return ans;
    }

    UTILS_DLL void replace_substring_in_place(std::string&amp; str, const std::string&amp; from, const std::string&amp; to);

    UTILS_DLL std::string DecoTypeKey(std::string_view type_key);

    UTILS_DLL std::string UnDecoTypeKey(const std::string&amp; type_name);

    UTILS_DLL std::string getC(int size);
}
</pre>

                