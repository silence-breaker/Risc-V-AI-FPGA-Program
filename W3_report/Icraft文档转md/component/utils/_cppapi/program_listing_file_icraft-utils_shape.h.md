# Program Listing for File shape.h

↰ [Return to documentation for file](file_icraft-utils_shape.h.md#file-icraft-utils-shape-h) (`icraft-utils\shape.h`)

#pragma once
#include &lt;cstdint&gt;
#include &lt;vector&gt;

#include &quot;icraft-utils/dllexport.h&quot;

namespace icraft {

    UTILS_DLL bool isBroadcastable(const std::vector&lt;int64_t&gt; left, std::vector&lt;int64_t&gt; right);

    UTILS_DLL std::vector&lt;int64_t&gt; getBroadcastShape(std::vector&lt;int64_t&gt; left, std::vector&lt;int64_t&gt; right);

    UTILS_DLL std::vector&lt;int64_t&gt; range(int64_t stop);
}
</pre>

                