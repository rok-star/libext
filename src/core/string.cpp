#include <libext/core/string.hpp>

namespace ext {

string::string()
    : _data() {}

string::string(ext::string const& string)
    : _data(string._data) {}

string::string(ext::string && string)
    : _data(std::move(string._data)) {}

string::string(ext::array<char> const& array)
    : _data(array) {}

string::string(ext::array<char> && array)
    : _data(std::move(array)) {}

string::string(char const* pchar)
    : _data(pchar, strlen(pchar)) {}

string::string(char const* pchar, int64_t len)
    : _data(pchar, len) {}

ext::string& string::operator=(ext::string const& string) {
    _data = string._data;
    return *this;
}

ext::string& string::operator=(ext::string && string) {
    _data = std::move(string._data);
    return *this;
}

ext::string& string::operator+=(ext::string const& string) {
    _data.push(string._data);
    return *this;
}

ext::string& string::operator+=(char const* pchar) {
    _data.push(ext::string(pchar)._data);
    return *this;
}

ext::string& string::operator+=(char const char_) {
    _data.push(char_);
    return *this;
}

ext::string string::operator+(ext::string const& string) const {
    ext::string ret;
    ret.data().reserve(_data.size() + string._data.size());
    ret.data().push(_data);
    ret.data().push(string._data);
    return ret;
}

ext::string string::operator+(char const* pchar) const {
    ext::string ret;
    ext::string string(pchar);
    ret.data().reserve(_data.size() + string._data.size());
    ret.data().push(_data);
    ret.data().push(string._data);
    return ret;
}

ext::string string::operator+(char const char_) const {
    ext::string ret;
    ret.data().reserve(_data.size() + 2);
    ret.data().push(_data);
    ret.data().push(char_);
    return ret;
}

bool string::operator==(ext::string const& string) const {
    return (_data == string._data);
}

bool string::operator==(char const* pchar) const {
    int64_t size = strlen(pchar);
    if (_data.size() == size) {
        for (int64_t i = 0; i < _data.size(); i++) {
            if (_data[i] != pchar[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool string::operator!=(ext::string const& string) const {
    return !operator==(string);
}

bool string::operator!=(char const* pchar) const {
    return !operator==(pchar);
}

ext::array<char> const& string::data() const {
    return _data;
}

ext::array<char>& string::data() {
    return _data;
}

int64_t string::size() const {
    int64_t ret = 0;
    for (int64_t i = 0; i < _data.size(); i++) {
        if ((_data[i] & 0xc0) != 0x80) {
            ret += 1;
        }
    }
    return ret;
}

int64_t string::index_of(ext::string const& string, int64_t start) const {
    return -1;
}

int64_t string::index_of(char const* pchar, int64_t start) const {
    return -1;
}

int64_t string::index_of(char const char_, int64_t start) const {
    return -1;
}

int64_t string::index_of_last(ext::string const& string, int64_t start) const {
    return -1;
}

int64_t string::index_of_last(char const* pchar, int64_t start) const {
    return -1;
}

int64_t string::index_of_last(char const char_, int64_t start) const {
    return -1;
}

bool string::contains(ext::string const& string) const {
    return false;
}

bool string::contains(char const* pchar) const {
    return false;
}

bool string::contains(char const char_) const {
    return false;
}

bool string::starts_with(ext::string const& string) const {
    return false;
}

bool string::starts_with(char const* pchar) const {
    return false;
}

bool string::starts_with(char const char_) const {
    return false;
}

bool string::ends_with(ext::string const& string) const {
    return false;
}

bool string::ends_with(char const* pchar) const {
    return false;
}

bool string::ends_with(char const char_) const {
    return false;
}

ext::string string::substr(int64_t index, int64_t size) const {
    index = (index < 0) ? 0 : index;
    size = (size < 0) ? 0 : size;
    int64_t index_ = -1;
    int64_t size_ = -1;
    int64_t from_ = 0;
    int64_t to_ = 0;
    for (int64_t i = 0; i < _data.size(); i++) {
        if ((_data[i] & 0xc0) != 0x80)
            index_ += 1;
        if (index_ == index) {
            from_ = i;
            for (; i <= _data.size(); i++) {
                if (i == _data.size()) {
                    to_ = i;
                    break;
                } else if ((_data[i] & 0xc0) != 0x80) {
                    size_ += 1;
                    if (size_ == size) {
                        to_ = i;
                        break;
                    }
                }
            }
            break;
        }
    }
    return ((to_ - from_) > 0)
        ? ext::string(_data.data() + from_, (to_ - from_))
        : ext::string();
}

ext::string string::slice(int64_t start, int64_t end) const {
	return ext::string();
}

ext::string string::first() const {
    assert(size() > 0);
    return substr(0, 1);
}

ext::string string::last() const {
    assert(size() > 0);
    return substr(size() - 1, 1);
}

ext::string string::first_or(ext::string const& string) const {
    return (size() > 0) ? substr(0, 1) : string;
}

ext::string string::last_or(ext::string const& string) const {
    int64_t size_ = size();
    return (size_ > 0) ? substr(size_ - 1, 1) : string;
}

ext::string& string::clear() {
    _data.clear();
    return *this;
}

ext::string& string::push(char char_) {
    _data.push(char_);
    return *this;
}

ext::string& string::push(ext::string const& string) {
    _data.push(string._data);
    return *this;
}

ext::string& string::unshift(char char_) {
    _data.unshift(char_);
    return *this;
}

ext::string& string::unshift(ext::string const& string) {
    _data.unshift(string._data);
    return *this;
}

bool string::empty() const {
    return _data.empty();
}

bool string::whitespace() const {
    return false;
    // if (_data.size() > 0) {
    //     int64_t read = 0;
    //     int64_t index = 0;
    //     uint32_t codepoint = 0;
    //     while ((read = ext::utf8_read_codepoint(_data.data(), (_data.size() - index), codepoint)) > 0) {
    //         if (ext::codepoint_whitespace(codepoint) == false)
    //             return false;
    //         index += read;
    //     }
    //     return true;
    // } else {
    //     return false;
    // }
}

bool string::digital()  const{
    return false;
    // if (_data.size() > 0) {
    //     int64_t read = 0;
    //     int64_t index = 0;
    //     uint32_t codepoint = 0;
    //     while ((read = ext::utf8_read_codepoint(_data.data(), (_data.size() - index), codepoint)) > 0) {
    //         if (ext::codepoint_digital(codepoint) == false)
    //             return false;
    //         index += read;
    //     }
    //     return true;
    // } else {
    //     return false;
    // }
}

ext::string string::upper() const {
    return ext::string();
}

ext::string string::lower() const {
    return ext::string();
}

ext::array<ext::string> string::split() const {
    return {};
}

ext::array<ext::string> string::split(char const* sep) const {
    return {};
}

ext::array<ext::string> string::split(ext::string const& sep) const {
    return {};
}

char const* string::c_string() const {
    static char const* _empty = "";
    if (_data.empty()) {
        return _empty;
    } else {
        const_cast<ext::string*>(this)->_data.push(0x0);
        const_cast<ext::string*>(this)->_data.pop();
        return _data.data();
    }
}

ext::array<uint32_t> string::codepoints() const {
    return {};
    // ext::array<uint32_t> ret;
    // ret.reserve(size());
    // int64_t read = 0;
    // int64_t index = 0;
    // uint32_t codepoint = 0;
    // while ((read = ext::utf8_read_codepoint(_data.data(), (_data.size() - index), codepoint)) > 0) {
    //     ret.push(codepoint);
    // }
    // return ret;
}

ext::string string::from_codepoints(ext::array<uint32_t> const& codepoints) {
    return {};
    // int64_t pos = 0;
    // int64_t len = 0;
    // for (uint32_t const& codepoint : codepoints)
    //     len += ext::codepoint_write_utf8(codepoint, NULL, 0);
    // char* ret = ext::alloc<char>(len + 1);
    // for (uint32_t const& codepoint : codepoints)
    //     pos += ext::codepoint_write_utf8(codepoint, (ret + pos), (len - pos));
    // return string::with_pchar(ret, len, (len + 1));
}

ext::string string::with_pchar(char* pchar, int64_t size) {
    return ext::string(ext::array<char>::with_data(pchar, size, size));
}

ext::string string::with_pchar(char* pchar, int64_t size, int64_t capacity) {
    return ext::string(ext::array<char>::with_data(pchar, size, capacity));
}

ext::string string::with_capacity(int64_t capacity) {
    ext::string ret;
    ret.data().reserve(capacity);
    return ret;
}

} /* namespace ext */