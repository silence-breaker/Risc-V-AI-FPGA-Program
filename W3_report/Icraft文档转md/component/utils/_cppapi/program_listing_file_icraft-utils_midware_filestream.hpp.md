# Program Listing for File filestream.hpp

↰ [Return to documentation for file](file_icraft-utils_midware_filestream.hpp.md#file-icraft-utils-midware-filestream-hpp) (`icraft-utils\midware\filestream.hpp`)

#pragma once
#include &lt;memory&gt;
#include &lt;string&gt;
#include &lt;string_view&gt;
#include &lt;cstdint&gt;
#include &lt;istream&gt;
#include &lt;ostream&gt;
#include &quot;icraft-utils/dllexport.h&quot;
#include &quot;icraft-utils/midware/path.hpp&quot;

namespace icraft::midware {

class UTILS_DLL ifstream : public std::istream {
public:
    ifstream();                                      // 构造时先用空 rdbuf
    explicit ifstream(std::string_view path, bool binary = true);

    explicit inline ifstream(const icraft::midware::path&amp; p, bool binary = true)
        : ifstream(p.string(), binary) {
    };
    ~ifstream();

    ifstream(const ifstream&amp;) = delete;
    ifstream&amp; operator=(const ifstream&amp;) = delete;
    ifstream(ifstream&amp;&amp;) noexcept;
    ifstream&amp; operator=(ifstream&amp;&amp;) noexcept;

    bool   open(std::string_view path, bool binary = true);
    void   close();

    std::size_t read(void* dst, std::size_t bytes);
    std::size_t gcount_ex() const noexcept { return last_read_; }

    bool   seek(int64_t offset, int origin);
    int64_t tell() const;
    int64_t size() const;

    bool   is_open() const noexcept;
    bool   good()   const noexcept;
    bool   eof()    const noexcept;

private:
    struct impl;
    std::unique_ptr&lt;impl&gt; p_;
    std::size_t last_read_ = 0;
};

class UTILS_DLL ofstream : public std::ostream {
public:
    ofstream();
    explicit ofstream(std::string_view path, bool binary = true, bool append = false);
    explicit inline ofstream(const icraft::midware::path&amp; p, bool binary = true, bool append = false)
        : ofstream(p.string(), binary, append) {
    }
    ~ofstream();

    ofstream(const ofstream&amp;) = delete;
    ofstream&amp; operator=(const ofstream&amp;) = delete;
    ofstream(ofstream&amp;&amp;) noexcept;
    ofstream&amp; operator=(ofstream&amp;&amp;) noexcept;

    bool   open(std::string_view path, bool binary = true, bool append = false);
    void   close();

    //
    std::size_t write(const void* src, std::size_t bytes);
    void   flush();

    bool   seek(int64_t offset, int origin);
    int64_t tell() const;

    bool   is_open() const noexcept;
    bool   good()   const noexcept;

private:
    struct impl;
    std::unique_ptr&lt;impl&gt; p_;
};

} // namespace icraft::midware
</pre>

                