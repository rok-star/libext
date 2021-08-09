#pragma once

#include <libext/core/base.hpp>
#include <libext/core/array.hpp>
#include <libext/core/string.hpp>
#include <libext/core/date.hpp>
#include <libext/core/map.hpp>

namespace ext {

enum class value_type {
    null,
    boolean,
    number,
    string,
    object,
    array,
    datetime,
};

class value final {
private:
    ext::value_type _type;
    void* _data;
public:
    using key_type = ext::string;
    using pair_type = ext::pair<key_type, ext::value>;
    using index_type = int64_t;
    using boolean_type = bool;
    using number_type = double;
    using string_type = ext::string;
    using object_type = ext::map<ext::string, ext::value>;
    using array_type = ext::array<ext::value>;
    using datetime_type = ext::datetime;
    ~value();
    value();
    value(ext::value const& value);
    value(ext::value && value);
    value(char const* pchar);
    value(double const& number);
    value(int64_t const& number);
    value(int32_t const& number);
    value(int16_t const& number);
    value(int8_t const& number);
    value(ext::string const& string);
    value(ext::string && string);
    ext::value& operator=(ext::value const& value);
    ext::value& operator=(ext::value && value);
    ext::value const& operator[](key_type const& key) const;
    ext::value const& operator[](index_type const& index) const;
    ext::value& operator[](key_type const& key);
    ext::value& operator[](index_type const& index);
    bool operator==(ext::value const& value) const;
    bool operator!=(ext::value const& value) const;
    ext::value_type const& type() const;
    boolean_type const& boolean_value() const;
    number_type const& number_value() const;
    string_type const& string_value() const;
    object_type const& object_value() const;
    array_type const& array_value() const;
    datetime_type const& datetime_value() const;
    boolean_type& boolean_value();
    number_type& number_value();
    string_type& string_value();
    object_type& object_value();
    array_type& array_value();
    datetime_type& datetime_value();
    bool has(char const* key) const;
    bool has(key_type const& key) const;
    void set_null();
    void set_boolean(boolean_type const& boolean);
    void set_number(number_type const& number);
    void set_string(string_type const& string);
    void set_string(string_type && string);
    void set_object(object_type const& object);
    void set_object(object_type && object);
    void set_array(array_type const& array);
    void set_array(array_type && array);
    void set_datetime(datetime_type const& datetime);
    int64_t int64_value() const;
    int32_t int32_value() const;
    int16_t int16_value() const;
    int8_t int8_value() const;
    static ext::value null();
    static ext::value boolean();
    static ext::value number();
    static ext::value string();
    static ext::value object();
    static ext::value array();
    static ext::value datetime();
    static ext::value boolean(boolean_type const& boolean);
    static ext::value number(number_type const& number);
    static ext::value string(string_type const& string);
    static ext::value object(object_type const& object);
    static ext::value array(array_type const& array);
    static ext::value datetime(datetime_type const& datetime);
};

} /* namespace ext */