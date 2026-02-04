# Program Listing for File test.hpp

↰ [Return to documentation for file](file_icraft-utils_test.hpp.md#file-icraft-utils-test-hpp) (`icraft-utils\test.hpp`)

#ifdef _BAREME

#include &lt;cassert&gt;
using namespace icraft::xir;

#define TEST_CASE(caseName, tags) void test_case()
#define REQUIRE(...) assert(##__VA_ARGS__)

#else // no bareme

#include &lt;catch2/catch.hpp&gt;

#define TEST_CASE(caseName, tags) TEST_CASE( #caseName, tags)

#endif  // #ifndef _BAREME
</pre>

                