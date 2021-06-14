#include "json.hpp"

namespace ext {
namespace json {

ext::value parse(ext::array<char> const& data, ext::status& status) {
    return {};
}

ext::value parse(ext::string const& string, ext::status& status) {
    return ext::json::parse(string.data(), status);
}

ext::string stringify(ext::value const& value) {
    return {};
}

} /* namespace json */
} /* namespace ext */