#pragma once

#include <libext/core/value.hpp>
#include <libext/core/status.hpp>

namespace ext {
namespace json {

ext::value parse(ext::string const& string, ext::status& status);
ext::string stringify(ext::value const& value);

} /* namespace json */
} /* namespace ext */