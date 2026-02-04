# Program Listing for File numeric.h

↰ [Return to documentation for file](file_icraft-utils_numeric.h.md#file-icraft-utils-numeric-h) (`icraft-utils\numeric.h`)

#pragma once
#include &lt;cstdint&gt;
#include &quot;icraft-utils/dllexport.h&quot;

namespace icraft {

    UTILS_DLL float emxxToFp32(uint16_t em_bits, uint32_t e_bits, uint32_t m_bits);

    UTILS_DLL uint16_t fp32ToEmxx(float value, uint32_t e_bits, uint32_t m_bits);
}
</pre>

                