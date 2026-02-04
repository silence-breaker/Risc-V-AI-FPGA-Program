# Program Listing for File thread.hpp

↰ [Return to documentation for file](file_icraft-utils_midware_thread.hpp.md#file-icraft-utils-midware-thread-hpp) (`icraft-utils\midware\thread.hpp`)

#pragma once
#include &lt;cstddef&gt;

#ifndef _BAREME
#include &lt;omp.h&gt;
#include &lt;thread&gt;
#else
#include &lt;fmsh_common.h&gt;
#endif

namespace icraft::midware {

    inline void set_num_threads(int n) noexcept {
    #ifdef _BAREME
        (void)n;
    #else
        if (n &gt; 0) omp_set_num_threads(n);
    #endif
    }

    template &lt;class Fn&gt;
    inline void parallel_for(std::size_t begin, std::size_t end, Fn&amp;&amp; fn) {
    #ifdef _BAREME
        for (std::size_t i = begin; i &lt; end; ++i) fn(i);
    #else
        #pragma omp parallel for
        for (long long i = static_cast&lt;long long&gt;(begin); i &lt; static_cast&lt;long long&gt;(end); ++i) {
            fn(static_cast&lt;std::size_t&gt;(i));
        }
    #endif
    }

    #ifdef _BAREME
        template&lt;class _Rep, class _Period&gt;
        void sleep_for(const std::chrono::duration&lt;_Rep, _Period&gt;&amp; duration){
            auto us=std::chrono::duration_cast&lt;std::chrono::microseconds&gt;(duration);
            delay_us(us.count());
        }
    #else
        using std::this_thread::sleep_for;
    #endif

} // namespace icraft::midware
</pre>

                