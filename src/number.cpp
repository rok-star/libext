#include <libext/number.hpp>
#include <libext/parser.hpp>

namespace ext {
namespace number {

template<typename T>
T __parse(ext::string const& string, bool sign, double min, double max, char const* name, ext::status& status) {
    auto number = 0.0;
    auto parser = ext::parser(string);
    if (parser.read_number({ .sign = sign }, number) && parser.end()) {
        if ((number >= min)
        && (number <= max)) {
            status.set_success();
            return static_cast<T>(number);
        } else {
            status.add_failure("failed to parse number from \"%s\": impossible to narrow into %s", string.c_string(), name.c_string());
            return 0;
        }
    } else {
        status.add_failure("failed to parse number from \"%s\": string is not a number", string.c_string());
        return 0;
    }
}

double parse(ext::string const& string, ext::status& status) {
    auto number = 0.0;
    auto parser = ext::parser(string);
    if (parser.read_number({ .sign = true, .precision = true }, number) && parser.end()) {
        status.set_success();
        return number;
    } else {
        status.add_failure("failed to parse number from \"%s\": string is not a number", string.c_string());
        return 0;
    }
}

int8_t parse_int8(ext::string const& string, ext::status& status) {
    return __parse<int8_t>(string, true, INT8_MIN, INT8_MAX, "int8_t", status);
}

int16_t parse_int16(ext::string const& string, ext::status& status) {
    return __parse<int16_t>(string, true, INT16_MIN, INT16_MAX, "int16_t", status);
}

int32_t parse_int32(ext::string const& string, ext::status& status) {
    return __parse<int32_t>(string, true, INT32_MIN, INT32_MAX, "int32_t", status);
}

int64_t parse_int64(ext::string const& string, ext::status& status) {
    return __parse<int64_t>(string, true, INT64_MIN, INT64_MAX, "int64_t", status);
}

uint8_t parse_uint8(ext::string const& string, ext::status& status) {
    return __parse<uint8_t>(string, false, 0, UINT8_MAX, "uint8_t", status);
}

uint16_t parse_uint16(ext::string const& string, ext::status& status) {
    return __parse<uint16_t>(string, false, 0, UINT16_MAX, "uint16_t", status);
}

uint32_t parse_uint32(ext::string const& string, ext::status& status) {
    return __parse<uint32_t>(string, false, 0, UINT32_MAX, "uint32_t", status);
}

uint64_t parse_uint64(ext::string const& string, ext::status& status) {
    return __parse<uint64_t>(string, false, 0, UINT64_MAX, "uint64_t", status);
}

} /* namespace number */
} /* namespace ext */