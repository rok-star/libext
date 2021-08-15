#pragma once

#include <cassert>

namespace ext {

struct nullopt_t {
    int dummy = 0;
};

inline const ext::nullopt_t nullopt = {0};

template<typename T>
class optional {
private:
    T* _data;
public:
    optional();
    optional(T const&);
    optional(T &&);
    optional(ext::nullopt_t const&);
    optional(ext::optional<T> const&);
    optional(ext::optional<T> &&);
    ext::optional<T>& operator=(ext::nullopt_t const&);
    ext::optional<T>& operator=(ext::optional<T> const&);
    ext::optional<T>& operator=(ext::optional<T> &&);
    bool has_value() const;
    T const& value() const;
    T const& value_or(T const&) const;
};

template<typename T>
inline optional<T>::optional()
    : _data(nullptr) {}

template<typename T>
inline optional<T>::optional(T const& value)
    : _data(new T(value)) {}

template<typename T>
inline optional<T>::optional(T && value)
    : _data(new T(std::move(value))) {}

template<typename T>
inline optional<T>::optional(ext::nullopt_t const& nullopt)
    : _data(nullptr) {}

template<typename T>
inline optional<T>::optional(ext::optional<T> const& optional)
    : _data(nullptr) {
    if (optional._data != nullptr) {
        _data = new T(*optional._data);
    }
}

template<typename T>
inline optional<T>::optional(ext::optional<T> && optional)
    : _data(optional._data) {
    optional._data = nullptr;
}

template<typename T>
inline ext::optional<T>& optional<T>::operator=(ext::nullopt_t const& nullopt) {
    if (_data != nullptr) {
        delete _data;
        _data = nullptr;
    }
    return *this;
}

template<typename T>
inline ext::optional<T>& optional<T>::operator=(ext::optional<T> const& optional) {
    if (_data != nullptr) {
        delete _data;
        _data = nullptr;
    }
    if (optional._data != nullptr) {
        _data = new T(*optional._data);
    }
    return *this;
}

template<typename T>
inline ext::optional<T>& optional<T>::operator=(ext::optional<T> && optional) {
    if (_data != nullptr) {
        delete _data;
        _data = nullptr;
    }
    if (optional._data != nullptr) {
        _data = optional._data;
        optional._data = nullptr;
    }
    return *this;
}

template<typename T>
inline bool optional<T>::has_value() const {
    return (_data != nullptr);
}

template<typename T>
inline T const& optional<T>::value() const {
    assert(_data != nullptr);
    return *_data;
}

template<typename T>
inline T const& optional<T>::value_or(T const& value) const {
    return ((_data != nullptr) ? *_data : value);
}

} /* namespace ext */