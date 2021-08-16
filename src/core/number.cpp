#include <math.h>
#include <libext/core/number.hpp>

namespace ext {
namespace number {

struct __parse_options {
    bool E;
    bool sign;
    bool fraction;
    char delimiter;
};

struct __parse_result {
    int8_t sign;
    uint64_t integer;
    uint64_t fraction;
    int64_t integer_read;
    int64_t fraction_read;
    int64_t read;
    double value;
};

__parse_result __parse(ext::string const& string, __parse_options const& options, ext::status& status) {

    #define __EMPTY_STRING() \
        status.add_failure("failed to parse number \"%s\": empty string", string.c_string()); \
        return {};

    #define __UNEXPECTED_TOKEN() \
        status.add_failure("failed to parse number \"%s\": unexpected token found \"%c\"", string.c_string(), chr); \
        return {};

    #define __UNEXPECTED_END() \
        status.add_failure("failed to parse number \"%s\": unexpected end of string", string.c_string()); \
        return {};

    __parse_result res = { .sign = 1 };

    if (string.data().size() == 0) {
        __EMPTY_STRING();
    }

    if (options.sign) {
        if (string.data()[0] == '-')  {
            res.sign = -1;
            res.read += 1;
            if (string.data().size() == 1) {
                __UNEXPECTED_END();
            }
        } else if (string.data()[0] == '+') {
            res.read += 1;
        }
    }

    while (res.read < string.data().size()) {
        auto const chr = string.data()[res.read];
        if (chr >= '0' && chr <= '9') {
            res.integer = (res.integer * 10) + (chr - '0');
            res.integer_read += 1;
            res.read += 1;
        } else if (chr == (options.delimiter ?: '.')) {
            if (options.fraction) {
                res.read += 1;
                break;
            } else {
                __UNEXPECTED_TOKEN();
            }
        } else {
            __UNEXPECTED_TOKEN();
        }
    }

    while (res.read < string.data().size()) {
        auto const chr = string.data()[res.read];
        if (chr >= '0' && chr <= '9') {
            res.fraction = (res.fraction * 10) + (chr - '0');
            res.fraction_read += 1;
            res.read += 1;
        } else {
            __UNEXPECTED_TOKEN();
        }
    }

    assert(res.integer_read <= 19);
    assert(res.fraction_read <= 19);

    if (res.fraction_read > 0) {
        res.value = (static_cast<double>(res.integer)
                    + (static_cast<double>(res.fraction)
                        * pow(10, res.fraction_read * -1))
                            * static_cast<double>(res.sign));
    } else {
        res.value = (static_cast<double>(res.integer)
                    * static_cast<double>(res.sign));
    }

    status.set_success();
    return res;

    #undef __UNEXPECTED_END
    #undef __UNEXPECTED_TOKEN
    #undef __EMPTY_STRING
}

double parse(ext::string const& string, ext::status& status) {
    return __parse(string, { .sign = true, .fraction = true }, status).value;
}

template<typename T>
T __parse_int(ext::string const& string, bool sign, long double min, long double max, char const* name, ext::status& status) {
    auto const res = __parse(string, { .sign = sign }, status);
    if (status.type() == ext::status_type::success) {
        if ((res.value >= min)
        && (res.value <= max)) {
            return static_cast<T>(res.value);
        } else {
            status.add_failure("failed to parse number \"%s\": value is out of range (%s)", string.c_string(), name);
            return 0;
        }
    } else {
        return 0;
    }
}

int8_t parse_int8(ext::string const& string, ext::status& status) {
    return __parse_int<int8_t>(string, true, INT8_MIN, INT8_MAX, "int8_t", status);
}

int16_t parse_int16(ext::string const& string, ext::status& status) {
    return __parse_int<int16_t>(string, true, INT16_MIN, INT16_MAX, "int16_t", status);
}

int32_t parse_int32(ext::string const& string, ext::status& status) {
    return __parse_int<int32_t>(string, true, INT32_MIN, INT32_MAX, "int32_t", status);
}

int64_t parse_int64(ext::string const& string, ext::status& status) {
    return __parse_int<int64_t>(string, true, INT64_MIN, INT64_MAX, "int64_t", status);
}

uint8_t parse_uint8(ext::string const& string, ext::status& status) {
    return __parse_int<uint8_t>(string, false, 0, UINT8_MAX, "uint8_t", status);
}

uint16_t parse_uint16(ext::string const& string, ext::status& status) {
    return __parse_int<uint16_t>(string, false, 0, UINT16_MAX, "uint16_t", status);
}

uint32_t parse_uint32(ext::string const& string, ext::status& status) {
    return __parse_int<uint32_t>(string, false, 0, UINT32_MAX, "uint32_t", status);
}

uint64_t parse_uint64(ext::string const& string, ext::status& status) {
    return __parse_int<uint64_t>(string, false, 0, UINT64_MAX, "uint64_t", status);
}

} /* namespace number */
} /* namespace ext */