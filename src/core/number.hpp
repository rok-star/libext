#pragma once

#include <libext/core/base.hpp>
#include <libext/core/string.hpp>
#include <libext/core/status.hpp>

namespace ext {
namespace number {

double parse(ext::string const& string, ext::status& status);
int8_t parse_int8(ext::string const& string, ext::status& status);
int16_t parse_int16(ext::string const& string, ext::status& status);
int32_t parse_int32(ext::string const& string, ext::status& status);
int64_t parse_int64(ext::string const& string, ext::status& status);
uint8_t parse_uint8(ext::string const& string, ext::status& status);
uint16_t parse_uint16(ext::string const& string, ext::status& status);
uint32_t parse_uint32(ext::string const& string, ext::status& status);
uint64_t parse_uint64(ext::string const& string, ext::status& status);

} /* namespace number */
} /* namespace ext */