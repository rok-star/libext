#include <libext/status.hpp>

namespace ext {

ext::status::status()
    : _type(ext::status_type::success)
    , _message() {}

ext::status_type const& ext::status::type() const {
    return _type;
}

ext::string const& ext::status::message() const {
    return _message;
}

void ext::status::add_failure(ext::string const& message) {
    _type = ext::status_type::failure;
    _message = (_message.empty() == false)
                ? (message + ": " + _message)
                : message;
}

void ext::status::set_success() {
    _type = ext::status_type::success;
    _message = {};
}

} /* namespace ext */