# Program Listing for File mutex.hpp

↰ [Return to documentation for file](file_icraft-utils_midware_mutex.hpp.md#file-icraft-utils-midware-mutex-hpp) (`icraft-utils\midware\mutex.hpp`)

#pragma once

#ifndef _BAREME
#include &lt;mutex&gt;
#else
#include &lt;fmsh_common_lock.h&gt;
#endif

namespace icraft::midware
{
    namespace impl
    {
        /*
         * @brief 无效mutex，用于裸机单线程环境
         */
        class DummyMutex
        {
        public:
            void lock() noexcept
            {
            }
            void unlock() noexcept
            {
            }
            void try_lock() noexcept
            {
            }
        };

        template &lt;class _Mutex&gt;
        class lock_guard { // class with destructor that unlocks a mutex
        public:
            using mutex_type = _Mutex;

            explicit lock_guard(_Mutex&amp; _Mtx) : _MyMutex(_Mtx) { // construct and lock
                _MyMutex.lock();
            }

            ~lock_guard() noexcept {
                _MyMutex.unlock();
            }

            lock_guard(const lock_guard&amp;)            = delete;
            lock_guard&amp; operator=(const lock_guard&amp;) = delete;

        private:
            _Mutex&amp; _MyMutex;
        };
    }
#ifndef _BAREME
    using Mutex = std::mutex;
    template&lt;class _Mutex&gt;
    using LockGuard=std::lock_guard&lt;_Mutex&gt;;
#else

    // using Mutex = impl::DummyMutex;
    using Mutex = Spinlock;
    template&lt;class _Mutex&gt;
    using LockGuard=impl::lock_guard&lt;_Mutex&gt;;
#endif
}
</pre>

                