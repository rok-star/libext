#include <libext/unicode.hpp>

struct unicode_expected {
    uint32_t codepoint;
    uint32_t lower;
    uint32_t upper;
    bool whitespace;
    bool digital;
    struct {
        int64_t position;
        int64_t size;
    } encoding[3];
};

unicode_expected const STRING_EXPECTED[] = {
    { .codepoint = U'П', .lower = U'п', .upper = U'П', .whitespace = false, .digital = false, .encoding = { { 0, 2 }, { 0, 1 }, { 0, 1 } } },
    { .codepoint = U'р', .lower = U'р', .upper = U'Р', .whitespace = false, .digital = false, .encoding = { { 2, 2 }, { 1, 1 }, { 1, 1 } } },
    { .codepoint = U'и', .lower = U'и', .upper = U'И', .whitespace = false, .digital = false, .encoding = { { 4, 2 }, { 2, 1 }, { 2, 1 } } },
    { .codepoint = U'в', .lower = U'в', .upper = U'В', .whitespace = false, .digital = false, .encoding = { { 6, 2 }, { 3, 1 }, { 3, 1 } } },
    { .codepoint = U'е', .lower = U'е', .upper = U'Е', .whitespace = false, .digital = false, .encoding = { { 8, 2 }, { 4, 1 }, { 4, 1 } } },
    { .codepoint = U'т', .lower = U'т', .upper = U'Т', .whitespace = false, .digital = false, .encoding = { { 10, 2 }, { 5, 1 }, { 5, 1 } } },
    { .codepoint = U',', .lower = U',', .upper = U',', .whitespace = false, .digital = false, .encoding = { { 12, 1 }, { 6, 1 }, { 6, 1 } } },
    { .codepoint = U' ', .lower = U' ', .upper = U' ', .whitespace = true, .digital = false, .encoding = { { 13, 1 }, { 7, 1 }, { 7, 1 } } },
    { .codepoint = U'h', .lower = U'h', .upper = U'H', .whitespace = false, .digital = false, .encoding = { { 14, 1 }, { 8, 1 }, { 8, 1 } } },
    { .codepoint = U'o', .lower = U'o', .upper = U'O', .whitespace = false, .digital = false, .encoding = { { 15, 1 }, { 9, 1 }, { 9, 1 } } },
    { .codepoint = U'w', .lower = U'w', .upper = U'W', .whitespace = false, .digital = false, .encoding = { { 16, 1 }, { 10, 1 }, { 10, 1 } } },
    { .codepoint = U' ', .lower = U' ', .upper = U' ', .whitespace = true, .digital = false, .encoding = { { 17, 1 }, { 11, 1 }, { 11, 1 } } },
    { .codepoint = U'a', .lower = U'a', .upper = U'A', .whitespace = false, .digital = false, .encoding = { { 18, 1 }, { 12, 1 }, { 12, 1 } } },
    { .codepoint = U'r', .lower = U'r', .upper = U'R', .whitespace = false, .digital = false, .encoding = { { 19, 1 }, { 13, 1 }, { 13, 1 } } },
    { .codepoint = U'e', .lower = U'e', .upper = U'E', .whitespace = false, .digital = false, .encoding = { { 20, 1 }, { 14, 1 }, { 14, 1 } } },
    { .codepoint = U' ', .lower = U' ', .upper = U' ', .whitespace = true, .digital = false, .encoding = { { 21, 1 }, { 15, 1 }, { 15, 1 } } },
    { .codepoint = U'y', .lower = U'y', .upper = U'Y', .whitespace = false, .digital = false, .encoding = { { 22, 1 }, { 16, 1 }, { 16, 1 } } },
    { .codepoint = U'o', .lower = U'o', .upper = U'O', .whitespace = false, .digital = false, .encoding = { { 23, 1 }, { 17, 1 }, { 17, 1 } } },
    { .codepoint = U'u', .lower = U'u', .upper = U'U', .whitespace = false, .digital = false, .encoding = { { 24, 1 }, { 18, 1 }, { 18, 1 } } },
    { .codepoint = U'?', .lower = U'?', .upper = U'?', .whitespace = false, .digital = false, .encoding = { { 25, 1 }, { 19, 1 }, { 19, 1 } } }
};
int64_t constexpr STRING_LEN = 20;
char const* STRING_UTF8 = "Привет, how are you?";
wchar_t const* STRING_USC2 = L"Привет, how are you?";
char16_t const* STRING_UTF16 = u"Привет, how are you?";
char32_t const* STRING_UTF32 = U"Привет, how are you?";

template<typename T>
int64_t len(T const* string) {
    int64_t ret = 0;
    while (*(string++) != 0x0)
        ret += 1;
    return ret;
}

template<typename T>
void unicode_test_reader(T const* string, int enc) {
    auto const data = ext::array<T>(string, len<T>(string));
    auto reader = ext::unicode::reader<T>(data);
    ASSERT(reader.codepoint() == 0);
    ASSERT(reader.position() == -1);
    ASSERT(reader.index() == -1);
    ASSERT(reader.size() == 0);
    for (int64_t i = 0; i < STRING_LEN; i++) {
        ASSERT(reader.next() == true);
        ASSERT(reader.index() == i);
        ASSERT(reader.codepoint() == STRING_EXPECTED[i].codepoint);
        ASSERT(reader.position() == STRING_EXPECTED[i].encoding[enc].position);
        ASSERT(reader.size() == STRING_EXPECTED[i].encoding[enc].size);
    }
    ASSERT(reader.next() == false);
    ASSERT(reader.next() == false);
}

template<typename T>
void unicode_test_writer(T const* string, int enc) {
    auto codepoints = ext::array<uint32_t>::with_capacity(STRING_LEN);
    for (int64_t i = 0; i < STRING_LEN; i++) {
        codepoints.push(STRING_EXPECTED[i].codepoint);
    }

    auto data = ext::array<T>::with_capacity(codepoints.size() * 4);
    auto writer = ext::unicode::writer<T>(codepoints);
    for (int64_t i = 0; i < STRING_LEN; i++) {
        ASSERT(writer.next() == true);
        ASSERT(writer.index() == i);
        ASSERT(writer.codepoint() == STRING_EXPECTED[i].codepoint);
        data.push(writer.data());
    }

    ASSERT(writer.next() == false);
    ASSERT(writer.next() == false);
    ASSERT(data.size() == len<T>(string));
    ASSERT(data == ext::array<T>(string, len<T>(string)));
}

void unicode_test_codepoints() {
    for (int64_t i = 0; i < STRING_LEN; i++) {
        ASSERT(ext::unicode::upper(STRING_EXPECTED[i].codepoint) == STRING_EXPECTED[i].upper);
        ASSERT(ext::unicode::lower(STRING_EXPECTED[i].codepoint) == STRING_EXPECTED[i].lower);
        ASSERT(ext::unicode::whitespace(STRING_EXPECTED[i].codepoint) == STRING_EXPECTED[i].whitespace);
        ASSERT(ext::unicode::digital(STRING_EXPECTED[i].codepoint) == STRING_EXPECTED[i].digital);
    }
}

void unicode_test() {
    unicode_test_reader<char>(STRING_UTF8, 0);
    unicode_test_reader<wchar_t>(STRING_USC2, 1);
    unicode_test_reader<char16_t>(STRING_UTF16, 1);
    unicode_test_reader<char32_t>(STRING_UTF32, 2);

    unicode_test_writer<char>(STRING_UTF8, 0);
    unicode_test_writer<wchar_t>(STRING_USC2, 1);
    unicode_test_writer<char16_t>(STRING_UTF16, 1);
    unicode_test_writer<char32_t>(STRING_UTF32, 2);

    unicode_test_codepoints();
}