#include <libext/string.hpp>

void string_test() {
    {
        auto str1 = ext::string("hello");
        auto str2 = ext::string("hello");
        ASSERT(str1 == str2);
        ASSERT(str1 == "hello");
    }
}