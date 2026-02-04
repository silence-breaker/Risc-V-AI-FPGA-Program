# Program Listing for File logging.h

↰ [Return to documentation for file](file_icraft-utils_logging.h.md#file-icraft-utils-logging-h) (`icraft-utils\logging.h`)

#pragma once
#include &lt;chrono&gt;
#include &lt;string&gt;
#include &lt;cstdlib&gt;
#include &lt;sstream&gt;
#include &lt;fstream&gt;
#include &lt;iostream&gt;
#include &lt;stdexcept&gt;
#include &lt;array&gt;

#define FMT_HEADER_ONLY
#include &lt;fmt/core.h&gt;
#ifndef _BAREME
    #include &lt;spdlog/spdlog.h&gt;
    #include &lt;spdlog/sinks/basic_file_sink.h&gt;
    #include &lt;spdlog/sinks/ansicolor_sink.h&gt;
    #include &lt;filesystem&gt;
#endif  //_BAREME

#include &quot;icraft-utils/dllexport.h&quot;

#if defined(_MSC_VER)
#define ICRAFT_NO_INLINE __declspec(noinline)
#else
#define ICRAFT_NO_INLINE __attribute__((noinline))
#endif

#ifdef _MSC_VER
#define ICRAFT_ALWAYS_INLINE __forceinline
#else
#define ICRAFT_ALWAYS_INLINE inline __attribute__((always_inline))
#endif

#define ICRAFT_THROW_EXCEPTION noexcept(false)

namespace icraft::detail {
    class Console {
    public:
        UTILS_DLL static void SetAnsiMode();

        UTILS_DLL static void SetUTF8Output();

    private:
        static inline bool ansi_mode_ = false;
    };

    struct UFT8ConsoleHelper {
        UTILS_DLL UFT8ConsoleHelper();
    };
}

namespace icraft {

    enum class LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERR,
        FATAL,
        OFF
    };

    enum class ColorName {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    class LogColor {
    public:
        UTILS_DLL static LogColor Foregroud(ColorName name);

        UTILS_DLL static LogColor Background(ColorName name);

        UTILS_DLL LogColor(ColorName fg_color, ColorName bg_color);

    private:
        UTILS_DLL auto get();
        friend class StdoutSink;
        friend class StderrSink;

        UTILS_DLL LogColor(std::string_view color);

        inline static const std::string black = &quot;\033[90m&quot;;
        inline static const std::string red = &quot;\033[91m&quot;;
        inline static const std::string green = &quot;\033[92m&quot;;
        inline static const std::string yellow = &quot;\033[93m&quot;;
        inline static const std::string blue = &quot;\033[94m&quot;;
        inline static const std::string magenta = &quot;\033[95m&quot;;
        inline static const std::string cyan = &quot;\033[96m&quot;;
        inline static const std::string white = &quot;\033[97m&quot;;

        inline static const std::array&lt;std::string, 8&gt; fg_colors {
            black, red, green, yellow, blue, magenta, cyan, white
        };

        inline static const std::string on_black = &quot;\033[100m&quot;;
        inline static const std::string on_red = &quot;\033[101m&quot;;
        inline static const std::string on_green = &quot;\033[102m&quot;;
        inline static const std::string on_yellow = &quot;\033[103m&quot;;
        inline static const std::string on_blue = &quot;\033[104m&quot;;
        inline static const std::string on_magenta = &quot;\033[105m&quot;;
        inline static const std::string on_cyan = &quot;\033[106m&quot;;
        inline static const std::string on_white = &quot;\033[107m&quot;;
        inline static const std::array&lt;std::string, 8&gt; bg_colors{
            on_black, on_red, on_green, on_yellow, on_blue, on_magenta, on_cyan, on_white
        };

        std::string color_;
    };
#ifndef _BAREME
    class BasicSink {
    public:
        UTILS_DLL void setPattern(const char* pattern);

        UTILS_DLL void setLevel(LogLevel level);

        UTILS_DLL LogLevel level() const;

        UTILS_DLL virtual void setColor(LogLevel level, LogColor color);

        UTILS_DLL virtual ~BasicSink();

    protected:
        UTILS_DLL BasicSink(spdlog::sink_ptr sptr);

        UTILS_DLL const spdlog::sink_ptr&amp; get() const;
    private:
        spdlog::sink_ptr sptr_ = nullptr;

        friend class Logger;
    };

    class FileSink : public BasicSink {
    public:
        UTILS_DLL explicit FileSink(const std::filesystem::path&amp; file_path);
    };

    class StdoutSink : public BasicSink {
    public:
        UTILS_DLL StdoutSink();

        UTILS_DLL virtual void setColor(LogLevel level, LogColor color) override;
    };

    class StderrSink : public BasicSink {
    public:
        UTILS_DLL StderrSink();

        UTILS_DLL virtual void setColor(LogLevel level, LogColor color) override;
    };
#endif  //_BAREME

    class Logger {
    public:
#ifndef _BAREME
        template&lt;typename It&gt;
        Logger(const std::string&amp; name, It begin, It end)
            : name_(name) {
            std::vector&lt;spdlog::sink_ptr&gt; sptrs;
            std::transform(
                begin,
                end,
                std::back_inserter(sptrs),
                [](auto&amp; s) { return s.get(); }
            );
            spdlogger_ = std::make_shared&lt;spdlog::logger&gt;(name, sptrs.begin(), sptrs.end());
            icraft::detail::Console::SetAnsiMode();
            this-&gt;setPattern(&quot;%^[%D %T.%e] [%L] %v%$&quot;);
        }

        UTILS_DLL Logger(const std::string&amp; name, const BasicSink&amp; sink);

        UTILS_DLL Logger(const std::string&amp; name, std::initializer_list&lt;BasicSink&gt; sinks);
#endif  //_BAREME

        UTILS_DLL Logger(const std::string&amp; name, LogLevel level);

        UTILS_DLL const std::string&amp; name() const;

        UTILS_DLL void setPattern(const char* pattern);

        UTILS_DLL void setLevel(LogLevel level);

        UTILS_DLL LogLevel level() const;

        UTILS_DLL static Logger&amp; Global();

        UTILS_DLL void log(LogLevel level, std::string_view msg);

        template&lt;typename... Args&gt;
        void debug(std::string fmt, Args&amp;&amp;... args) {
        #ifndef _BAREME
            spdlogger_-&gt;debug((fmt::format_string&lt;Args...&gt;)fmt, std::forward&lt;Args&gt;(args)...);
            spdlogger_-&gt;flush();
        #endif
        }

        template&lt;typename... Args&gt;
        void info(std::string fmt, Args&amp;&amp;... args) {
        #ifndef _BAREME
            spdlogger_-&gt;info((fmt::format_string&lt;Args...&gt;)fmt, std::forward&lt;Args&gt;(args)...);
            spdlogger_-&gt;flush();
        #endif
        }

        template&lt;typename... Args&gt;
        void warn(std::string fmt, Args&amp;&amp;... args) {
        #ifndef _BAREME
            spdlogger_-&gt;warn((fmt::format_string&lt;Args...&gt;)fmt, std::forward&lt;Args&gt;(args)...);
            spdlogger_-&gt;flush();
        #endif
        }

        template&lt;typename... Args&gt;
        void error(std::string fmt, Args&amp;&amp;... args) {
        #ifndef _BAREME
            spdlogger_-&gt;error((fmt::format_string&lt;Args...&gt;)fmt, std::forward&lt;Args&gt;(args)...);
            spdlogger_-&gt;flush();
        #endif
        }

        template&lt;typename... Args&gt;
        void fatal(std::string fmt, Args&amp;&amp;... args) {
        #ifndef _BAREME
            spdlogger_-&gt;critical((fmt::format_string&lt;Args...&gt;)fmt, std::forward&lt;Args&gt;(args)...);
            spdlogger_-&gt;flush();
        #endif
        }

        UTILS_DLL void debug(const std::string_view&amp; msg);

        UTILS_DLL void info(const std::string_view&amp; msg);

        UTILS_DLL void warn(const std::string_view&amp; msg);

        UTILS_DLL void error(const std::string_view&amp; msg);

        UTILS_DLL void fatal(const std::string_view&amp; msg);

    private:
        std::string name_;
        LogLevel level_;
#if _BAREME
        LogColor color_{ ColorName::BLACK, ColorName::WHITE };
#else
        std::shared_ptr&lt;spdlog::logger&gt; spdlogger_ = nullptr;
#endif  //_BAREME
    };

    class BackTrace {
    public:
        UTILS_DLL static std::string Get(int bt_limit = 500);
    };

    class Error : public std::runtime_error {
    public:
        UTILS_DLL explicit Error(const std::string&amp; s);
    };

    using std::chrono::system_clock;

    class InternalError : public Error {
    public:
    #if _BAREME
        UTILS_DLL InternalError(std::string file, int lineno, std::string msg, int err_code);
    #else
        UTILS_DLL InternalError(std::string file, int lineno, std::string msg, int err_code,
            system_clock::time_point time = system_clock::now(), std::string backtrace = BackTrace::Get());
    #endif // _BAREME

        UTILS_DLL const std::string&amp; file() const;

        UTILS_DLL const std::string&amp; msg() const;

        UTILS_DLL const std::string&amp; fullMsg() const;

        UTILS_DLL const std::string&amp; backtrace() const;

        #ifndef _BAREME
        UTILS_DLL const system_clock::time_point&amp; time() const;
        #endif // _BAREME

        UTILS_DLL int lineno() const;

        UTILS_DLL virtual const char* what() const noexcept;

        UTILS_DLL const int errorCode() const;

        UTILS_DLL void rethrow(std::string info, std::string file, int line, int err_code);

    private:
        std::string file_;
        int lineno_;
        std::string msg_;
        #ifndef _BAREME
            system_clock::time_point time_;
        #endif // _BAREME
        std::string backtrace_;
        std::string full_msg_;
        int err_code_;
    };

    namespace detail{

        class StreamBuf {
        public:
            template&lt;typename... Args&gt;
            StreamBuf&amp; append(std::string fmt, Args&amp;&amp;... args) {
                stream_ &lt;&lt; fmt::format((fmt::format_string&lt;Args...&gt;)fmt, std::forward&lt;Args&gt;(args)...);
                return *this;
            }

            template&lt;typename T&gt;
            StreamBuf&amp; append(const T&amp; msg) {
                stream_ &lt;&lt; fmt::format(msg);
                return *this;
            }

            template&lt;typename T&gt;
            StreamBuf&amp; operator&lt;&lt;(const T&amp; args) {
                stream_ &lt;&lt; args;
                return *this;
            }

            UTILS_DLL std::string str() const;

            UTILS_DLL void str(const std::string&amp; s);

        private:
            std::ostringstream stream_;
        };

        class LogExcept {
        public:
            ICRAFT_NO_INLINE LogExcept(const char* file, int lineno, int err_code = 1) { GetEntry().init(file, lineno, err_code); }

            ICRAFT_NO_INLINE LogExcept(InternalError* err, const char* file, int lineno) {
                GetEntry().init(err, file, lineno, err-&gt;errorCode());
            }

            ICRAFT_NO_INLINE LogExcept(InternalError* err, const char* file, int lineno, int err_code) {
                GetEntry().init(err, file, lineno, err_code);
            }
#ifdef _MSC_VER
#pragma warning(disable : 4722)
#endif
            ~LogExcept() ICRAFT_THROW_EXCEPTION { GetEntry().finalize(); }

            StreamBuf&amp; stream() { return GetEntry().streambuf_; }

        private:
            class Entry {
            public:
                UTILS_DLL void init(const char* file, int lineno, int err_code);

                UTILS_DLL void init(InternalError* err, const char* file, int lineno, int err_code);

                UTILS_DLL Error finalize();

                StreamBuf streambuf_;
                std::string file_;
                int lineno_;
                int err_code_;
                InternalError* err_ = nullptr;
            };

            ICRAFT_NO_INLINE static Entry&amp; GetEntry() {
            #if _BAREME
                static LogExcept::Entry result;
            #else
                static thread_local LogExcept::Entry result;
            #endif // _BAREME
                return result;
            }
        };

        template&lt;LogLevel L&gt;
        class LogMsg {
        public:
            LogMsg() {
                #ifndef _BAREME
                fmt::print(&quot;\033[2K\r&quot;);
                #endif
            };

            LogMsg(const std::string&amp; file, int lineno) : LogMsg() {
                streambuf_.append(&quot;{}:{}: &quot;, file, lineno);
            }

            StreamBuf&amp; stream() { return streambuf_; }

            ICRAFT_NO_INLINE ~LogMsg() { Logger::Global().log(L, streambuf_.str()); }

        private:
            StreamBuf streambuf_;
        };
    }
}

#define ICRAFT_CONCAT_IMPL( x, y ) x##y
#define ICRAFT_MACRO_CONCAT( x, y ) ICRAFT_CONCAT_IMPL( x, y )

#define ICRAFT_LOG(level, ...) ICRAFT_LOG_##level(__VA_ARGS__)
#define ICRAFT_LOG_DEBUG() ::icraft::detail::LogMsg&lt;::icraft::LogLevel::DEBUG&gt;().stream()
#define ICRAFT_LOG_INFO() ::icraft::detail::LogMsg&lt;::icraft::LogLevel::INFO&gt;().stream()
#define ICRAFT_LOG_WARNING() ::icraft::detail::LogMsg&lt;::icraft::LogLevel::WARN&gt;().stream()
#define ICRAFT_LOG_ERROR() ::icraft::detail::LogMsg&lt;::icraft::LogLevel::ERR&gt;().stream()
#define ICRAFT_LOG_FATAL() ::icraft::detail::LogMsg&lt;::icraft::LogLevel::FATAL&gt;().stream()
#define ICRAFT_LOG_EXCEPT(...) ::icraft::detail::LogExcept(__FILE__, __LINE__, ##__VA_ARGS__).stream()
#define ICRAFT_RETHROW(err, ...) ::icraft::detail::LogExcept(&amp;err, __FILE__, __LINE__, ##__VA_ARGS__).stream()

#define ICRAFT_SET_LOG_LEVEL(level) ICRAFT_SET_LOG_LEVEL_##level
#define ICRAFT_SET_LOG_LEVEL_OFF ::icraft::Logger::Global().setLevel(::icraft::LogLevel::OFF);
#define ICRAFT_SET_LOG_LEVEL_DEBUG ::icraft::Logger::Global().setLevel(::icraft::LogLevel::DEBUG);
#define ICRAFT_SET_LOG_LEVEL_INFO ::icraft::Logger::Global().setLevel(::icraft::LogLevel::INFO);
#define ICRAFT_SET_LOG_LEVEL_WARNING ::icraft::Logger::Global().setLevel(::icraft::LogLevel::WARN);
#define ICRAFT_SET_LOG_LEVEL_ERROR ::icraft::Logger::Global().setLevel(::icraft::LogLevel::ERR);
#define ICRAFT_SET_LOG_LEVEL_FATAL ::icraft::Logger::Global().setLevel(::icraft::LogLevel::FATAL);
#define ICRAFT_SET_LOG_LEVEL_EXCEPT ::icraft::Logger::Global().setLevel(::icraft::LogLevel::EXCEPT);

#ifndef ICRAFT_NO_EXCEPTIONS

#define ICRAFT_TRY(...)                                 \
try {                                                   \
    __VA_ARGS__                                         \
}catch (const std::exception&amp; e) {                      \
    LOG(FATAL) &lt;&lt; e.what();                             \
    exit(-1);                                           \
}
#endif

#define ICRAFT_CONSOLE_USE_UTF8 icraft::detail::UFT8ConsoleHelper ICRAFT_MACRO_CONCAT(_utf8_console_helper_, __COUNTER__);

#define ICRAFT_CHECK_BINARY_OP(name, op, x, y, ...) if (!(x op y)) (ICRAFT_LOG(EXCEPT, ##__VA_ARGS__) &lt;&lt; &quot;Check failed: &quot; #x &quot; &quot; #op &quot; &quot; #y &lt;&lt; &quot;\n&quot;)

#define ICRAFT_CHECK_LT(x, y, ...) ICRAFT_CHECK_BINARY_OP(_LT, &lt;, x, y, ##__VA_ARGS__)
#define ICRAFT_CHECK_GT(x, y, ...) ICRAFT_CHECK_BINARY_OP(_GT, &gt;, x, y, ##__VA_ARGS__)
#define ICRAFT_CHECK_LE(x, y, ...) ICRAFT_CHECK_BINARY_OP(_LE, &lt;=, x, y, ##__VA_ARGS__)
#define ICRAFT_CHECK_GE(x, y, ...) ICRAFT_CHECK_BINARY_OP(_GE, &gt;=, x, y, ##__VA_ARGS__)
#define ICRAFT_CHECK_EQ(x, y, ...) ICRAFT_CHECK_BINARY_OP(_EQ, ==, x, y, ##__VA_ARGS__)
#define ICRAFT_CHECK_NE(x, y, ...) ICRAFT_CHECK_BINARY_OP(_NE, !=, x, y, ##__VA_ARGS__)

#define ICRAFT_CHECK(x, ...) if (!(x)) (ICRAFT_LOG(EXCEPT, ##__VA_ARGS__) &lt;&lt; &quot;Check failed: (&quot; #x &quot;) is false\n&quot;)
</pre>

                