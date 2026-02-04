# Program Listing for File semaphore.hpp

↰ [Return to documentation for file](file_icraft-utils_midware_semaphore.hpp.md#file-icraft-utils-midware-semaphore-hpp) (`icraft-utils\midware\semaphore.hpp`)

#pragma once

#ifdef _BAREME
#include &lt;cstddef&gt;
#include &lt;chrono&gt;
#include &lt;atomic&gt;

namespace icraft::midware
{
    class Semaphore
    {
    public:
        explicit Semaphore(std::ptrdiff_t desired);
        Semaphore(const Semaphore &amp;) = delete;
        void release(std::ptrdiff_t update = 1);
        void acquire();
        bool try_acquire() noexcept;
        template &lt;class Rep, class Period&gt;
        bool try_acquire_for(const std::chrono::duration&lt;Rep, Period&gt; &amp;rel_time)
        {
            auto begin = std::chrono::high_resolution_clock::now();
            while (!try_acquire())
            {
                auto now = std::chrono::high_resolution_clock::now();
                if (now - begin &gt; rel_time)
                {
                    return false;
                }
            }
            return true;
        }
        template &lt;class Clock, class Duration&gt;
        bool try_acquire_until(const std::chrono::time_point&lt;Clock, Duration&gt; &amp;abs_time)
        {
            while (!try_acquire())
            {
                auto now = std::chrono::high_resolution_clock::now();
                if (now &gt; abs_time)
                {
                    return false;
                }
            }
            return true;
        }

    private:
        std::atomic_uint32_t count;
    };
}
#endif
</pre>

                