#pragma once

#include <libext/core/base.hpp>
#include <libext/core/array.hpp>

namespace ext {

template<typename K, typename V>
class pair {
private:
    K _key;
    V _value;
public:
    using key_type = K;
    using value_type = V;
    pair();
    pair(K const& key, V const& value);
    pair(K const& key, V && value);
    pair(K && key, V const& value);
    pair(K && key, V && value);
    pair(ext::pair<K, V> const& pair);
    pair(ext::pair<K, V> && pair);
    ext::pair<K, V>& operator=(ext::pair<K, V> const& pair);
    ext::pair<K, V>& operator=(ext::pair<K, V> && pair);
    bool operator==(ext::pair<K, V> const& pair) const;
    bool operator!=(ext::pair<K, V> const& pair) const;
    K const& key() const;
    V const& value() const;
    K& key();
    V& value();
};

template<typename K, typename V>
class map {
private:
    ext::array<ext::pair<K, V>> _data;
    int64_t _find_index(K const& key) const;
public:
    using key_type = K;
    using value_type = V;
    map();
    map(ext::map<K, V> const& map);
    map(ext::map<K, V> && map);
    map(std::initializer_list<ext::pair<K, V>> const& pairs);
    ext::map<K, V>& operator=(ext::map<K, V> const& map);
    ext::map<K, V>& operator=(ext::map<K, V> && map);
    V const& operator[](K const& key) const;
    V& operator[](K const& key);
    bool operator==(ext::map<K, V> const& map) const;
    bool operator!=(ext::map<K, V> const& map) const;
    ext::array<ext::pair<K, V>> const& data() const;
    ext::array<ext::pair<K, V>>& data();
    bool has(K const& key) const;
    V const& get(K const& key) const;
    V& get(K const& key);
    ext::map<K, V>& set(K const& key, V const& value);
    ext::map<K, V>& set(K const& key, V && value);
};

template<typename K, typename V>
inline pair<K, V>::pair()
    : _key()
    , _value() {}

template<typename K, typename V>
inline pair<K, V>::pair(K const& key, V const& value)
    : _key(key)
    , _value(value) {}

template<typename K, typename V>
inline pair<K, V>::pair(K const& key, V && value)
    : _key(key)
    , _value(std::move(value)) {}

template<typename K, typename V>
inline pair<K, V>::pair(K && key, V const& value)
    : _key(std::move(key))
    , _value(value) {}

template<typename K, typename V>
inline pair<K, V>::pair(K && key, V && value)
    : _key(std::move(key))
    , _value(std::move(value)) {}

template<typename K, typename V>
inline pair<K, V>::pair(ext::pair<K, V> const& pair)
    : _key(pair._key)
    , _value(pair._value) {}

template<typename K, typename V>
inline pair<K, V>::pair(ext::pair<K, V> && pair)
    : _key(std::move(pair._key))
    , _value(std::move(pair._value)) {}

template<typename K, typename V>
inline ext::pair<K, V>& pair<K, V>::operator=(ext::pair<K, V> const& pair) {
    _key = pair._key;
    _value = pair._value;
    return *this;
}

template<typename K, typename V>
inline ext::pair<K, V>& pair<K, V>::operator=(ext::pair<K, V> && pair) {
    _key = std::move(pair._key);
    _value = std::move(pair._value);
    return *this;
}

template<typename K, typename V>
inline bool pair<K, V>::operator==(ext::pair<K, V> const& pair) const {
    return (_key == pair._key)
        && (_value == pair._value);
}

template<typename K, typename V>
inline bool pair<K, V>::operator!=(ext::pair<K, V> const& pair) const {
    return !operator==(pair);
}

template<typename K, typename V>
inline K const& pair<K, V>::key() const {
    return _key;
}

template<typename K, typename V>
inline V const& pair<K, V>::value() const {
    return _value;
}

template<typename K, typename V>
inline K& pair<K, V>::key() {
    return _key;
}

template<typename K, typename V>
inline V& pair<K, V>::value() {
    return _value;
}

template<typename K, typename V>
inline int64_t map<K, V>::_find_index(K const& key) const {
    for (int64_t i = 0; i < _data.size(); i++)
        if (_data[i].key() == key)
            return i;
    return -1;
}

template<typename K, typename V>
inline map<K, V>::map()
    : _data() {}

template<typename K, typename V>
inline map<K, V>::map(std::initializer_list<ext::pair<K, V>> const& pairs)
    : _data(pairs) {}

template<typename K, typename V>
inline map<K, V>::map(ext::map<K, V> const& map)
    : _data(map._data) {}

template<typename K, typename V>
inline map<K, V>::map(ext::map<K, V> && map)
    : _data(std::move(map._data)) {}

template<typename K, typename V>
inline ext::map<K, V>& map<K, V>::operator=(ext::map<K, V> const& map) {
    if (this != &map)
        _data = map._data;
    return *this;
}

template<typename K, typename V>
inline ext::map<K, V>& map<K, V>::operator=(ext::map<K, V> && map) {
    if (this != &map)
        _data = std::move(map._data);
    return *this;
}

template<typename K, typename V>
inline V const& map<K, V>::operator[](K const& key) const {
    return get(key);
}

template<typename K, typename V>
inline V& map<K, V>::operator[](K const& key) {
    return get(key);
}

template<typename K, typename V>
inline bool map<K, V>::operator==(ext::map<K, V> const& map) const {
    return (_data == map._data);
}

template<typename K, typename V>
inline bool map<K, V>::operator!=(ext::map<K, V> const& map) const {
    return !operator==(map);
}

template<typename K, typename V>
inline ext::array<ext::pair<K, V>> const& map<K, V>::data() const {
    return _data;
}

template<typename K, typename V>
inline ext::array<ext::pair<K, V>>& map<K, V>::data() {
    return _data;
}

template<typename K, typename V>
inline bool map<K, V>::has(K const& key) const {
    for (ext::pair<K, V> const& pair : _data) {
        if (pair.key() == key) {
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
inline V const& map<K, V>::get(K const& key) const {
    int64_t index = _find_index(key);
    assert(index > -1);
    return _data[index].value();
}

template<typename K, typename V>
inline V& map<K, V>::get(K const& key) {
    int64_t index = _find_index(key);
    assert(index > -1);
    return _data[index].value();
}

template<typename K, typename V>
inline ext::map<K, V>& map<K, V>::set(K const& key, V const& value) {
    int64_t index = _find_index(key);
    if (index > -1) {
        _data[index].value() = value;
    } else {
        _data.push({ key, value });
    }
    return *this;
}

template<typename K, typename V>
inline ext::map<K, V>& map<K, V>::set(K const& key, V && value) {
    int64_t index = _find_index(key);
    if (index > -1) {
        _data[index].value() = std::move(value);
    } else {
        _data.push({ key, std::move(value) });
    }
    return *this;
}

} /* namespace ext */