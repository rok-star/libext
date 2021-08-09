#include <libext/core/value.hpp>

namespace ext {

ext::value::~value() {
    set_null();
}

ext::value::value()
    : _type(ext::value_type::null)
    , _data(nullptr) {}

ext::value::value(ext::value const& value)
    : _type(value._type)
    , _data(nullptr) {

    if (_type == ext::value_type::boolean) {
        _data = new boolean_type(value.boolean_value());
    } else if (_type == ext::value_type::number) {
        _data = new number_type(value.number_value());
    } else if (_type == ext::value_type::string) {
        _data = new string_type(value.string_value());
    } else if (_type == ext::value_type::object) {
        _data = new object_type(value.object_value());
    } else if (_type == ext::value_type::array) {
        _data = new array_type(value.array_value());
    } else if (_type == ext::value_type::datetime) {
        _data = new datetime_type(value.datetime_value());
    }
}

ext::value::value(ext::value && value)
    : _type(value._type)
    , _data(value._data) {
    value._type = ext::value_type::null;
    value._data = nullptr;
}

ext::value::value(char const* pchar)
    : _type(ext::value_type::string)
    , _data(new ext::string(pchar)) {}

ext::value::value(double const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

ext::value::value(int64_t const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

ext::value::value(int32_t const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

ext::value::value(int16_t const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

ext::value::value(int8_t const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

ext::value::value(ext::string const& string)
    : _type(ext::value_type::string)
    , _data(new ext::string(string)) {}

ext::value::value(ext::string && string)
    : _type(ext::value_type::string)
    , _data(new ext::string(std::move(string))) {}

ext::value& ext::value::operator=(ext::value const& value) {
    if (this != &value) {
        if (value._type == ext::value_type::null) {
            set_null();
        } else if (value._type == ext::value_type::boolean) {
            set_boolean(value.boolean_value());
        } else if (value._type == ext::value_type::number) {
            set_number(value.number_value());
        } else if (value._type == ext::value_type::string) {
            set_string(value.string_value());
        } else if (value._type == ext::value_type::object) {
            set_object(value.object_value());
        } else if (value._type == ext::value_type::array) {
            set_array(value.array_value());
        } else if (value._type == ext::value_type::datetime) {
            set_datetime(value.datetime_value());
        }
    }
    return *this;
}

ext::value& ext::value::operator=(ext::value && value) {
    if (this != &value) {
        auto tt = _type;
        auto td = _data;
        _type = value._type;
        _data = value._data;
        value._type = tt;
        value._data = td;
    }
    return *this;
}

ext::value const& ext::value::operator[](key_type const& key) const {
    ASSERT(_type == ext::value_type::object);
    return object_value()[key];
}

ext::value const& ext::value::operator[](index_type const& index) const {
    ASSERT(_type == ext::value_type::array);
    return array_value()[index];
}

ext::value& ext::value::operator[](key_type const& key) {
    ASSERT(_type == ext::value_type::object);
    return object_value()[key];
}

ext::value& ext::value::operator[](index_type const& index) {
    ASSERT(_type == ext::value_type::array);
    return array_value()[index];
}

bool ext::value::operator==(ext::value const& value) const {
    if (_type == value._type) {
        if (_type == ext::value_type::null) {
            return true;
        } else if (_type == ext::value_type::boolean) {
            return boolean_value() == value.boolean_value();
        } else if (_type == ext::value_type::number) {
            return number_value() == value.number_value();
        } else if (_type == ext::value_type::string) {
            return string_value() == value.string_value();
        } else if (_type == ext::value_type::object) {
            return object_value() == value.object_value();
        } else if (_type == ext::value_type::array) {
            return array_value() == value.array_value();
        } else if (_type == ext::value_type::datetime) {
            return datetime_value() == value.datetime_value();
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool ext::value::operator!=(ext::value const& value) const {
    return !operator==(value);
}

ext::value_type const& ext::value::type() const {
    return _type;
}

ext::value::boolean_type const& ext::value::boolean_value() const {
    ASSERT(_type == ext::value_type::boolean);
    return *(static_cast<ext::value::boolean_type*>(_data));
}

ext::value::number_type const& ext::value::number_value() const {
    ASSERT(_type == ext::value_type::number);
    return *(static_cast<ext::value::number_type*>(_data));
}

ext::value::string_type const& ext::value::string_value() const {
    ASSERT(_type == ext::value_type::string);
    return *(static_cast<ext::value::string_type*>(_data));
}

ext::value::object_type const& ext::value::object_value() const {
    ASSERT(_type == ext::value_type::object);
    return *(static_cast<ext::value::object_type*>(_data));
}

ext::value::array_type const& ext::value::array_value() const {
    ASSERT(_type == ext::value_type::array);
    return *(static_cast<ext::value::array_type*>(_data));
}

ext::value::datetime_type const& ext::value::datetime_value() const {
    ASSERT(_type == ext::value_type::datetime);
    return *(static_cast<ext::value::datetime_type*>(_data));
}

ext::value::number_type& ext::value::number_value() {
    ASSERT(_type == ext::value_type::number);
    return *(static_cast<ext::value::number_type*>(_data));
}

ext::value::string_type& ext::value::string_value() {
    ASSERT(_type == ext::value_type::string);
    return *(static_cast<ext::value::string_type*>(_data));
}

ext::value::object_type& ext::value::object_value() {
    ASSERT(_type == ext::value_type::object);
    return *(static_cast<ext::value::object_type*>(_data));
}

ext::value::array_type& ext::value::array_value() {
    ASSERT(_type == ext::value_type::array);
    return *(static_cast<ext::value::array_type*>(_data));
}

ext::value::datetime_type& ext::value::datetime_value() {
    ASSERT(_type == ext::value_type::datetime);
    return *(static_cast<ext::value::datetime_type*>(_data));
}

bool ext::value::has(char const* key) const {
    ASSERT(_type == ext::value_type::object);
    return object_value().has(key);
}

bool ext::value::has(key_type const& key) const {
    ASSERT(_type == ext::value_type::object);
    return object_value().has(key);
}

void ext::value::set_null() {
    if (_type == ext::value_type::boolean) {
        delete static_cast<ext::value::boolean_type*>(_data);
    } else if (_type == ext::value_type::number) {
        delete static_cast<ext::value::number_type*>(_data);
    } else if (_type == ext::value_type::string) {
        delete static_cast<ext::value::string_type*>(_data);
    } else if (_type == ext::value_type::object) {
        delete static_cast<ext::value::object_type*>(_data);
    } else if (_type == ext::value_type::array) {
        delete static_cast<ext::value::array_type*>(_data);
    } else if (_type == ext::value_type::datetime) {
        delete static_cast<ext::value::datetime_type*>(_data);
    }

    _type = ext::value_type::null;
    _data = nullptr;
}

void ext::value::set_boolean(boolean_type const& boolean) {
    set_null();
    _type = ext::value_type::boolean;
    _data = new boolean_type(boolean);
}

void ext::value::set_number(number_type const& number) {
    set_null();
    _type = ext::value_type::number;
    _data = new number_type(number);
}

void ext::value::set_string(string_type const& string) {
    set_null();
    _type = ext::value_type::string;
    _data = new string_type(string);
}

void ext::value::set_string(string_type && string) {
    set_null();
    _type = ext::value_type::string;
    _data = new string_type(std::move(string));
}

void ext::value::set_object(object_type const& object) {
    set_null();
    _type = ext::value_type::object;
    _data = new object_type(object);
}

void ext::value::set_object(object_type && object) {
    set_null();
    _type = ext::value_type::object;
    _data = new object_type(std::move(object));
}

void ext::value::set_array(array_type const& array) {
    set_null();
    _type = ext::value_type::array;
    _data = new array_type(array);
}

void ext::value::set_array(array_type && array) {
    set_null();
    _type = ext::value_type::array;
    _data = new array_type(std::move(array));
}

void ext::value::set_datetime(datetime_type const& datetime) {
    set_null();
    _type = ext::value_type::datetime;
    _data = new datetime_type(datetime);
}

int64_t ext::value::int64_value() const {
    ASSERT(_type == ext::value_type::number);
    return number_value();
}

int32_t ext::value::int32_value() const {
    ASSERT(_type == ext::value_type::number);
    return number_value();
}

int16_t ext::value::int16_value() const {
    ASSERT(_type == ext::value_type::number);
    return number_value();
}

int8_t ext::value::int8_value() const {
    ASSERT(_type == ext::value_type::number);
    return number_value();
}

ext::value ext::value::null() {
    return ext::value();
}

ext::value ext::value::number() {
    auto value = ext::value();
    value.set_number(0);
    return value;
}

ext::value ext::value::boolean() {
    auto value = ext::value();
    value.set_boolean(false);
    return value;
}

ext::value ext::value::string() {
    auto value = ext::value();
    value.set_string({});
    return value;
}

ext::value ext::value::object() {
    auto value = ext::value();
    value.set_object({});
    return value;
}

ext::value ext::value::array() {
    auto value = ext::value();
    value.set_array({});
    return value;
}

ext::value ext::value::datetime() {
    auto value = ext::value();
    value.set_datetime({});
    return value;
}


ext::value ext::value::number(ext::value::number_type const& number) {
    auto value = ext::value();
    value.set_number(number);
    return value;
}

ext::value ext::value::boolean(ext::value::boolean_type const& boolean) {
    auto value = ext::value();
    value.set_boolean(boolean);
    return value;
}

ext::value ext::value::string(ext::value::string_type const& string) {
    auto value = ext::value();
    value.set_string(string);
    return value;
}

ext::value ext::value::object(ext::value::object_type const& object) {
    auto value = ext::value();
    value.set_object(object);
    return value;
}

ext::value ext::value::array(ext::value::array_type const& array) {
    auto value = ext::value();
    value.set_array(array);
    return value;
}

ext::value ext::value::datetime(ext::value::datetime_type const& datetime) {
    auto value = ext::value();
    value.set_datetime(datetime);
    return value;
}

} /* namespace ext */