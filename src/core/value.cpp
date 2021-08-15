#include <libext/core/value.hpp>

namespace ext {

value::~value() {
    set_null();
}

value::value()
    : _type(ext::value_type::null)
    , _data(nullptr) {}

value::value(ext::value const& value)
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

value::value(ext::value && value)
    : _type(value._type)
    , _data(value._data) {
    value._type = ext::value_type::null;
    value._data = nullptr;
}

value::value(char const* pchar)
    : _type(ext::value_type::string)
    , _data(new ext::string(pchar)) {}

value::value(double const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

value::value(int64_t const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

value::value(int32_t const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

value::value(int16_t const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

value::value(int8_t const& number)
    : _type(ext::value_type::number)
    , _data(new double(number)) {}

value::value(ext::string const& string)
    : _type(ext::value_type::string)
    , _data(new ext::string(string)) {}

value::value(ext::string && string)
    : _type(ext::value_type::string)
    , _data(new ext::string(std::move(string))) {}

ext::value& value::operator=(ext::value const& value) {
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

ext::value& value::operator=(ext::value && value) {
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

ext::value const& value::operator[](key_type const& key) const {
    ASSERT(_type == ext::value_type::object);
    return object_value()[key];
}

ext::value const& value::operator[](index_type const& index) const {
    ASSERT(_type == ext::value_type::array);
    return array_value()[index];
}

ext::value& value::operator[](key_type const& key) {
    ASSERT(_type == ext::value_type::object);
    return object_value()[key];
}

ext::value& value::operator[](index_type const& index) {
    ASSERT(_type == ext::value_type::array);
    return array_value()[index];
}

bool value::operator==(ext::value const& value) const {
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

bool value::operator!=(ext::value const& value) const {
    return !operator==(value);
}

ext::value_type const& value::type() const {
    return _type;
}

value::boolean_type const& value::boolean_value() const {
    ASSERT(_type == ext::value_type::boolean);
    return *(static_cast<value::boolean_type*>(_data));
}

value::number_type const& value::number_value() const {
    ASSERT(_type == ext::value_type::number);
    return *(static_cast<value::number_type*>(_data));
}

value::string_type const& value::string_value() const {
    ASSERT(_type == ext::value_type::string);
    return *(static_cast<value::string_type*>(_data));
}

value::object_type const& value::object_value() const {
    ASSERT(_type == ext::value_type::object);
    return *(static_cast<value::object_type*>(_data));
}

value::array_type const& value::array_value() const {
    ASSERT(_type == ext::value_type::array);
    return *(static_cast<value::array_type*>(_data));
}

value::datetime_type const& value::datetime_value() const {
    ASSERT(_type == ext::value_type::datetime);
    return *(static_cast<value::datetime_type*>(_data));
}

value::number_type& value::number_value() {
    ASSERT(_type == ext::value_type::number);
    return *(static_cast<value::number_type*>(_data));
}

value::string_type& value::string_value() {
    ASSERT(_type == ext::value_type::string);
    return *(static_cast<value::string_type*>(_data));
}

value::object_type& value::object_value() {
    ASSERT(_type == ext::value_type::object);
    return *(static_cast<value::object_type*>(_data));
}

value::array_type& value::array_value() {
    ASSERT(_type == ext::value_type::array);
    return *(static_cast<value::array_type*>(_data));
}

value::datetime_type& value::datetime_value() {
    ASSERT(_type == ext::value_type::datetime);
    return *(static_cast<value::datetime_type*>(_data));
}

bool value::has(char const* key) const {
    ASSERT(_type == ext::value_type::object);
    return object_value().has(key);
}

bool value::has(key_type const& key) const {
    ASSERT(_type == ext::value_type::object);
    return object_value().has(key);
}

void value::set_null() {
    if (_type == ext::value_type::boolean) {
        delete static_cast<value::boolean_type*>(_data);
    } else if (_type == ext::value_type::number) {
        delete static_cast<value::number_type*>(_data);
    } else if (_type == ext::value_type::string) {
        delete static_cast<value::string_type*>(_data);
    } else if (_type == ext::value_type::object) {
        delete static_cast<value::object_type*>(_data);
    } else if (_type == ext::value_type::array) {
        delete static_cast<value::array_type*>(_data);
    } else if (_type == ext::value_type::datetime) {
        delete static_cast<value::datetime_type*>(_data);
    }

    _type = ext::value_type::null;
    _data = nullptr;
}

void value::set_boolean(boolean_type const& boolean) {
    set_null();
    _type = ext::value_type::boolean;
    _data = new boolean_type(boolean);
}

void value::set_number(number_type const& number) {
    set_null();
    _type = ext::value_type::number;
    _data = new number_type(number);
}

void value::set_string(string_type const& string) {
    set_null();
    _type = ext::value_type::string;
    _data = new string_type(string);
}

void value::set_string(string_type && string) {
    set_null();
    _type = ext::value_type::string;
    _data = new string_type(std::move(string));
}

void value::set_object(object_type const& object) {
    set_null();
    _type = ext::value_type::object;
    _data = new object_type(object);
}

void value::set_object(object_type && object) {
    set_null();
    _type = ext::value_type::object;
    _data = new object_type(std::move(object));
}

void value::set_array(array_type const& array) {
    set_null();
    _type = ext::value_type::array;
    _data = new array_type(array);
}

void value::set_array(array_type && array) {
    set_null();
    _type = ext::value_type::array;
    _data = new array_type(std::move(array));
}

void value::set_datetime(datetime_type const& datetime) {
    set_null();
    _type = ext::value_type::datetime;
    _data = new datetime_type(datetime);
}

int64_t value::int64_value() const {
    ASSERT(_type == ext::value_type::number);
    return number_value();
}

int32_t value::int32_value() const {
    ASSERT(_type == ext::value_type::number);
    return number_value();
}

int16_t value::int16_value() const {
    ASSERT(_type == ext::value_type::number);
    return number_value();
}

int8_t value::int8_value() const {
    ASSERT(_type == ext::value_type::number);
    return number_value();
}

ext::value value::null() {
    return ext::value();
}

ext::value value::number() {
    auto value = ext::value();
    value.set_number(0);
    return value;
}

ext::value value::boolean() {
    auto value = ext::value();
    value.set_boolean(false);
    return value;
}

ext::value value::string() {
    auto value = ext::value();
    value.set_string({});
    return value;
}

ext::value value::object() {
    auto value = ext::value();
    value.set_object({});
    return value;
}

ext::value value::array() {
    auto value = ext::value();
    value.set_array({});
    return value;
}

ext::value value::datetime() {
    auto value = ext::value();
    value.set_datetime({});
    return value;
}


ext::value value::number(value::number_type const& number) {
    auto value = ext::value();
    value.set_number(number);
    return value;
}

ext::value value::boolean(value::boolean_type const& boolean) {
    auto value = ext::value();
    value.set_boolean(boolean);
    return value;
}

ext::value value::string(value::string_type const& string) {
    auto value = ext::value();
    value.set_string(string);
    return value;
}

ext::value value::object(value::object_type const& object) {
    auto value = ext::value();
    value.set_object(object);
    return value;
}

ext::value value::array(value::array_type const& array) {
    auto value = ext::value();
    value.set_array(array);
    return value;
}

ext::value value::datetime(value::datetime_type const& datetime) {
    auto value = ext::value();
    value.set_datetime(datetime);
    return value;
}

} /* namespace ext */