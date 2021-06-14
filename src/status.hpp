#pragma once

#include <libext/base.hpp>
#include <libext/string.hpp>

namespace ext {

enum class status_type {
    success,
    failure
};

class status final {
private:
    ext::status_type _type;
    ext::string _message;
public:
    status();
    status(ext::status const& status) = default;
    status(ext::status && status) = default;
    ext::status& operator=(ext::status const& status) = default;
    ext::status& operator=(ext::status && status) = default;
    ext::status_type const& type() const;
    ext::string const& message() const;
    template<typename T, typename... A>
    void add_failure(char const* fmt, T const& head, A const&... tail);
    void add_failure(ext::string const& message);
    void set_success();
};

template<typename T, typename... A>
inline void ext::status::add_failure(char const* fmt, T const& head, A const&... tail) {
    _type = ext::status_type::failure;
    _message = (_message.empty() == false)
                ? (ext::string::format(fmt, head, tail...) + ": " + _message)
                : ext::string::format(fmt, head, tail...);
}

} /* namespace ext */