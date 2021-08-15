#include <libext/core/status.hpp>

namespace ext {

status::status()
    : _type(ext::status_type::success)
    , _message() {}

ext::status_type const& status::type() const {
    return _type;
}

ext::string const& status::message() const {
    return _message;
}

void status::add_failure(ext::string const& message) {
    _type = ext::status_type::failure;
    _message = (_message.empty() == false)
                ? (message + ": " + _message)
                : message;
}

void status::set_success() {
    _type = ext::status_type::success;
    _message = {};
}

} /* namespace ext */