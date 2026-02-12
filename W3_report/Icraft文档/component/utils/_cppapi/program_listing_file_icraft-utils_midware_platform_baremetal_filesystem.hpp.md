# Program Listing for File filesystem.hpp

↰ [Return to documentation for file](file_icraft-utils_midware_platform_baremetal_filesystem.hpp.md#file-icraft-utils-midware-platform-baremetal-filesystem-hpp) (`icraft-utils\midware\platform\baremetal\filesystem.hpp`)

#pragma once
#include &quot;ff.h&quot;
#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;stdexcept&gt;
#include &lt;streambuf&gt;
#include &lt;iostream&gt;

// FileSystem 类的声明
class FileSystem {
    public:
        static FileSystem&amp; instance() {
        std::cout &lt;&lt; &quot;FileSystem instance &quot; &lt;&lt; std::endl;

        static FileSystem fs;
        return fs;
    }
        FileSystem();
        FileSystem(const FileSystem&amp;) = delete;
        FileSystem(FileSystem&amp;&amp;) = delete;
        FileSystem &amp;operator=(const FileSystem &amp;) = delete;
        FileSystem &amp;operator=(FileSystem &amp;&amp;) = delete;
        ~FileSystem();
        bool exists(const std::string&amp; path);
        void create_directory(const std::string&amp; path);
        void remove(const std::string&amp; path);
        std::vector&lt;std::string&gt; list_directory(const std::string&amp; path);

    private:
        FATFS* fs;
    };

    // File 类的声明
class File {
    public:
        File(const std::string&amp; path, BYTE mode);
        void write(const std::string&amp; data);
        void close();
        std::string read(UINT size);
        void read(char* to, UINT size);
        void write(const std::vector&lt;BYTE&gt;&amp; data);
        void write(const char* data, uint64_t size);
        std::vector&lt;BYTE&gt; readBinary(UINT size);
        FSIZE_t size() const;
        void seek(FSIZE_t offset);
        FSIZE_t tell() const;
        void flush();
        ~File();

    private:
        FIL file;
    };

    // FileStreamBuf 类的声明
    class FileStreamBuf : public std::streambuf {
    public:
        FileStreamBuf(File&amp; file);
    protected:
        int_type underflow() override;
        int_type overflow(int_type ch) override;
        int sync() override;
        pos_type seekoff(off_type off, std::ios_base::seekdir way, std::ios_base::openmode which) override;
        pos_type seekpos(pos_type pos, std::ios_base::openmode which) override;

    private:
        int_type flushBuffer();
        File&amp; file;
        std::vector&lt;uint8_t&gt; buffer{ std::vector&lt;uint8_t&gt;(1024) };
    };

    // FileIStream 类的声明
    class FileIStream : public std::istream {
    public:
        FileIStream(File&amp; file);
    private:
        FileStreamBuf buf;
};

    // FileOStream 类的声明
    class FileOStream : public std::ostream {
    public:
        FileOStream(File&amp; file);
    private:
        FileStreamBuf buf;
};
</pre>

                