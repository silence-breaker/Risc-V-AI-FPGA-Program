# Program Listing for File path.hpp

↰ [Return to documentation for file](file_icraft-utils_midware_path.hpp.md#file-icraft-utils-midware-path-hpp) (`icraft-utils\midware\path.hpp`)

#pragma once
#include &lt;string&gt;
#include &lt;string_view&gt;

#include &quot;icraft-utils/logging.h&quot;

#ifdef _BAREME
// define fake filesystem path
#include &quot;platform/baremetal/filesystem.hpp&quot;

#else
#include &lt;filesystem&gt;
#endif  //_BAREME

namespace icraft::midware {

#if !defined(_BAREME)
    class path {
        public:
        using native_t = std::filesystem::path;

        path() = default;

        explicit path(const char* s) : p_(s) {}
        explicit path(std::string s) : p_(std::move(s)) {}
        explicit path(std::string_view s) : p_(std::string(s)) {}
        explicit path(const std::filesystem::path&amp; p) : p_(p) {}
        explicit path(std::filesystem::path&amp;&amp; p) : p_(std::move(p)) {}

        template &lt;size_t N&gt;
        explicit path(const char(&amp;s)[N]) : p_(std::string(s)) {}

        path&amp; operator/=(const path&amp; other) { p_ /= other.p_; return *this; }
        friend path operator/(path lhs, const path&amp; rhs) { lhs /= rhs; return lhs; }

        path&amp; operator=(const std::filesystem::path&amp; p) { p_ = p; return *this; }
        path&amp; operator=(std::filesystem::path&amp;&amp; p) { p_ = std::move(p); return *this; }

        path parent_path() const { return path{ p_.parent_path() }; }
        path filename() const { return path{ p_.filename() }; }
        path stem() const { return path{ p_.stem() }; }
        path extension() const { return path{ p_.extension() }; }

        path&amp; replace_extension(const path&amp; ext) { p_.replace_extension(ext.p_); return *this; }

        std::string string() const { return p_.string(); }
        bool empty() const { return p_.empty(); }

        friend bool operator==(const path&amp; a, const path&amp; b) { return a.p_ == b.p_; }
        friend bool operator!=(const path&amp; a, const path&amp; b) { return !(a==b); }

        const native_t&amp; native() const { return p_; }

        private:
        native_t p_;
    };

#else // 裸机实现
    class path {
        public:
        using native_t = std::string;

        path() = default;
        explicit path(const char* s) : p_(s) {}
        explicit path(std::string s) : p_(std::move(s)) {}
        explicit path(std::string_view s) : p_(std::string(s)) {}

        template &lt;size_t N&gt;
        explicit path(const char(&amp;s)[N]) : p_(std::string(s)) {}

        path&amp; operator/=(const path&amp; other) {
            if (p_.empty()) { p_ = other.p_; return *this; }
            if (p_.back() != &#39;/&#39;) p_.push_back(&#39;/&#39;);
            if (!other.p_.empty() &amp;&amp; other.p_.front() == &#39;/&#39;) p_ += other.p_.substr(1);
            else p_ += other.p_;
            return *this;
        }
        friend path operator/(path lhs, const path&amp; rhs) { lhs /= rhs; return lhs; }

        path parent_path() const {
            if (p_.empty()) return {};
            auto pos = p_.find_last_of(&#39;/&#39;);
            if (pos == std::string::npos) return {};
            if (pos == 0) return path(&quot;/&quot;);
            return path(p_.substr(0, pos));
        }
        path filename() const {
            if (p_.empty()) return {};
            auto pos = p_.find_last_of(&#39;/&#39;);
            return (pos == std::string::npos) ? path(p_) : path(p_.substr(pos+1));
        }
        path extension() const {
            auto fn = filename().p_;
            auto pos = fn.find_last_of(&#39;.&#39;);
            if (pos == std::string::npos || pos == 0) return path{};
            return path(fn.substr(pos));
        }
        path stem() const {
            auto fn = filename().p_;
            auto pos = fn.find_last_of(&#39;.&#39;);
            if (pos == std::string::npos || pos == 0) return path(fn);
            return path(fn.substr(0, pos));
        }
        path&amp; replace_extension(const path&amp; ext) {
            auto base = parent_path() / stem();
            p_ = base.p_ + ext.p_;
            return *this;
        }

        std::string string() const { return p_; }
        bool empty() const { return p_.empty(); }

        friend bool operator==(const path&amp; a, const path&amp; b) { return a.p_ == b.p_; }
        friend bool operator!=(const path&amp; a, const path&amp; b) { return !(a==b); }

        const native_t&amp; native() const { return p_; }

        private:
        native_t p_;
    };

#endif // _BAREME

} // namespace icraft::midware
extern &quot;C&quot; {
    UTILS_DLL bool exists(const icraft::midware::path&amp; path);

    UTILS_DLL bool create_directory(const icraft::midware::path&amp; path);

    UTILS_DLL size_t file_size(const icraft::midware::path&amp; path);

    UTILS_DLL bool is_directory(const icraft::midware::path&amp; path);
}
</pre>

                