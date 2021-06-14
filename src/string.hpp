#pragma once

#include <libext/base.hpp>
#include <libext/array.hpp>

namespace ext {

class string final {
private:
    ext::array<char> _data;
public:
    string();
    string(ext::string const& string);
    string(ext::string && string);
    string(ext::array<char> const& array);
    string(ext::array<char> && array);
    string(char const* pchar);
    string(char const* pchar, int64_t len);
    ext::string& operator=(ext::string const& string);
    ext::string& operator=(ext::string && string);
    ext::string& operator+=(ext::string const& string);
    ext::string& operator+=(char const* pchar);
    ext::string operator+(ext::string const& string) const;
    ext::string operator+(char const* pchar) const;
    bool operator==(ext::string const& string) const;
    bool operator==(char const* pchar) const;
    bool operator!=(ext::string const& string) const;
    bool operator!=(char const* pchar) const;
    ext::array<char> const& data() const;
    ext::array<char>& data();
    int64_t size() const;
    ext::string substr(int64_t index, int64_t size) const;
    ext::string slice(int64_t start, int64_t end) const;
    ext::string first() const;
    ext::string last() const;
    ext::string first_or(ext::string const& string) const;
    ext::string last_or(ext::string const& string) const;
    ext::string& clear();
    ext::string& push(char char_);
    ext::string& push(ext::string const& string);
    ext::string& unshift(char char_);
    ext::string& unshift(ext::string const& string);
    bool empty() const;
    bool digital() const;
    bool whitespace() const;
    ext::string upper() const;
    ext::string lower() const;
    ext::array<ext::string> split() const;
    ext::array<ext::string> split(char const* sep) const;
    ext::array<ext::string> split(ext::string const& sep) const;
    char const* c_string() const;
    ext::array<uint32_t> codepoints() const;
    static ext::string from_codepoints(ext::array<uint32_t> const& codepoints);
    static ext::string with_pchar(char* pchar, int64_t size);
    static ext::string with_pchar(char* pchar, int64_t size, int64_t capacity);
    static ext::string with_capacity(int64_t capacity);
    template<typename... A>
    static ext::string format(A const&... args);
};

template<typename... A>
inline ext::string ext::string::format(A const&... args) {
    int64_t len = snprintf(nullptr, 0, args...);
    char* pchar = ext::alloc<char>(len + 1);
    sprintf(pchar, args...);
    return ext::string::with_pchar(pchar, len, (len + 1));
}

template<typename T>
inline ext::string ext::array<T>::join(char const* sep) const {
    return {};
}

template<typename T>
inline ext::string ext::array<T>::join(ext::string const& sep) const {
    return {};
}

} /* namespace ext */