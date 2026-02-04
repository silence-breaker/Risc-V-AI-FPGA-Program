# Program Listing for File with.h



↰ [Return to documentation for file](file_icraft-xir_base_with.h.md#file-icraft-xir-base-with-h) (`icraft-xir\base\with.h`)


```cpp
#pragma once

namespace icraft::xir {

    template <typename ContextType>
    class With {
    public:

        template <typename... Args>
        explicit With(Args&&... args) : ctx_(std::forward<Args>(args)...) {
            ctx_._enterWithScope();
        }

        ~With() { ctx_._exitWithScope(); }

        // 删除复制和移动构造函数
        With(const With& other) = delete;
        With& operator=(const With& other) = delete;
        With(With&& other) = delete;
        With& operator=(With&& other) = delete;

        ContextType* get() { return &ctx_; }
        const ContextType* get() const { return &ctx_; }

        ContextType* operator->() { return get(); }
        const ContextType* operator->() const { return get(); }
        ContextType& operator*() { return *get(); }
        const ContextType* operator*() const { return *get(); }

        ContextType operator()() { return ctx_; }

    private:
        ContextType ctx_;
    };
}
</pre>
```
