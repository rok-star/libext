#pragma once

#include <libext/value.hpp>
#include <libext/status.hpp>

namespace ext {
namespace json {

ext::value parse(ext::array<char> const& data, ext::status& status);
ext::value parse(ext::string const& string, ext::status& status);
ext::string stringify(ext::value const& value);

} /* namespace json */
} /* namespace ext */