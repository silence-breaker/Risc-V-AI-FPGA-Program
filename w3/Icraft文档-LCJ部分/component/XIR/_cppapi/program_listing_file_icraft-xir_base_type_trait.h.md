# Program Listing for File type_trait.h



↰ [Return to documentation for file](file_icraft-xir_base_type_trait.h.md#file-icraft-xir-base-type-trait-h) (`icraft-xir\base\type_trait.h`)


```cpp
#pragma once
#include <icraft-xir/base/array.h>

template<typename E>
constexpr auto IcraftGetSignature() noexcept {

    #if defined(__GNUC__) || defined(__clang__) || defined(__IAR_SYSTEMS_ICC__)
        return __PRETTY_FUNCTION__;
    #elif defined(_MSC_VER)
        return __FUNCSIG__;
    //#else // baremetal
        //return __PRETTY_FUNCTION__;
    #endif
}

namespace icraft::xir {

    namespace detail {
        // 获取类型字符串的辅助函数
        constexpr auto is_pretty(char ch) noexcept {
            return (ch >= 'a' && ch <= 'z')
                || (ch >= 'A' && ch <= 'Z')
                || (ch >= '0' && ch <= '9')
                || (ch == '<') || (ch == '>')
                || (ch == ':');
        }

        constexpr auto pretty_name(std::string_view sv, int num) noexcept {

            sv.remove_suffix(num);

            for (std::size_t n = sv.size() - 1; n > 0; --n) {
                if (!is_pretty(sv[n])) {
                    sv.remove_prefix(n + 1);
                    break;
                }
            }
            return sv;
        }

        template<typename E>
        constexpr auto n() noexcept {
            #if defined(__GNUC__) || defined(__clang__) || defined(__IAR_SYSTEMS_ICC__)
                return pretty_name(IcraftGetSignature<E>(), 1);
            #elif defined(_MSC_VER)
                return pretty_name(IcraftGetSignature<E>(), 16);
            //#elif // baremetal
            //  return pretty_name(IcraftGetSignature<E>(), 0);
            #endif
        }
    }

    template<typename E>
    std::string TypeName() {

        std::string str = IcraftGetSignature<E>();

        #if defined(__GNUC__) || defined(__clang__)

            str.erase(0, 46);

            std::string::size_type pos = str.find_first_of("]");
            str = str.substr(0, pos);

            pos = 0;
            int i = 0;
            while ((pos = str.find_first_of(" ", pos)) != std::string::npos) {
                str.erase(pos, 1); // " " 的长度是 1
            }

            return str;

        #elif defined(__IAR_SYSTEMS_ICC__)
            str.erase(0, 46);

            std::string::size_type pos = str.find_first_of("]");
            str = str.substr(0, pos);

            pos = 0;
            int i = 0;
            // 取第一个空格后的所有，然后删除空格
            while ((pos = str.find_first_of(" ", pos)) != std::string::npos) {
                if (i++ == 0) str = str.substr(pos + 1, str.size()); // " " 的长度是 1
                else str.erase(pos, 1); // " " 的长度是 1

            }

            return str;

        #elif defined(_MSC_VER)

            str.erase(0, 31);

            size_t size = str.length();
            size_t l = size;
            size_t r = 0;

            for (size_t i = 0; i < size; i++) {
                if (str[i] == '<') {
                    l = std::min(l, i);
                }

                if (str[i] == '>') {
                    r = std::max(r, i);
                }
            }

            str = str.substr(l + 1, r - l - 1);

            std::string::size_type pos = 0;

            while ((pos = str.find("class ", pos)) != std::string::npos) {
                str.erase(pos, 6); // "class " 的长度是 6
            }

            pos = 0;
            while ((pos = str.find(",void", pos)) != std::string::npos) {
                str.erase(pos, 5); // ",void" 的长度是 5
            }

            pos = 0;
            while ((pos = str.find("enum ", pos)) != std::string::npos) {
                str.erase(pos, 5); // "enum " 的长度是 5
            }

            pos = 0;
            while ((pos = str.find(" ", pos)) != std::string::npos) {
                str.erase(pos, 1); // " " 的长度是 1
            }

            return str;
    #endif
    }

    template<>
    XIR_DLL std::string TypeName<int64_t>();

    template<>
    XIR_DLL std::string TypeName<uint64_t>();

    template<>
    XIR_DLL std::string TypeName<std::string>();

    template<>
    XIR_DLL std::string TypeName<Array<int64_t>>();

    template<>
    XIR_DLL std::string TypeName<Array<uint64_t>>();

    template<>
    XIR_DLL std::string TypeName<Array<std::string>>();
}
</pre>
```
