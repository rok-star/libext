#pragma once

#include <libext/core/base.hpp>

namespace ext {

class string;

template<typename T>
class array final {
private:
    int64_t _capacity;
    int64_t _size;
    T* _data;
public:
    using item_type = T;
    ~array();
    array();
    array(ext::array<T> const& array);
    array(ext::array<T> && array);
    array(std::initializer_list<T> const& list);
    array(T const* data, int64_t size);
    ext::array<T>& operator=(ext::array<T> const& array);
    ext::array<T>& operator=(ext::array<T> && array);
    ext::array<T>& operator+=(T const& item);
    ext::array<T>& operator+=(ext::array<T> const& array);
    ext::array<T> operator+(T const& item) const;
    ext::array<T> operator+(ext::array<T> const& item) const;
    bool operator==(ext::array<T> const& array) const;
    bool operator!=(ext::array<T> const& array) const;
    T const& operator[](int64_t index) const;
    T& operator[](int64_t index);
    int64_t size() const;
    int64_t capacity() const;
    T const* begin() const;
    T* begin();
    T const* end() const;
    T* end();
    T const* data() const;
    T* data();
    T const& first() const;
    T& first();
    T const& last() const;
    T& last();
    T const& first_or(T const& item) const;
    T const& last_or(T const& item) const;
    ext::array<T> subarr(int64_t index, int64_t size) const;
    ext::array<T> slice(int64_t start, int64_t end) const;
    int64_t index_of(T const& item, int64_t start = 0) const;
    int64_t index_of(ext::array<T> const& array, int64_t start = 0) const;
    bool empty() const;
    bool starts_with(T const& item, int64_t start = 0) const;
    bool starts_with(ext::array<T> const& array, int64_t start = 0) const;
    bool ends_with(T const& item, int64_t end = 0) const;
    bool ends_with(ext::array<T> const& item, int64_t end = 0) const;
    bool includes(T const& item) const;
    bool includes(ext::array<T> const& array) const;
    void attach(T* data, int64_t size, int64_t capacity);
    void detach();
    ext::array<T>& clear();
    ext::array<T>& splice(int64_t index, int64_t remove, ext::array<T> const& array);
    ext::array<T>& splice(int64_t index, int64_t remove, T const& item);
    ext::array<T>& splice(int64_t index, int64_t remove);
    ext::array<T>& push(T const& item);
    ext::array<T>& push(ext::array<T> const& array);
    ext::array<T>& unshift(T const& item);
    ext::array<T>& unshift(ext::array<T> const& array);
    T pop();
    T shift();
    template<typename... A>
    ext::array<T>& push_new(A &&... a);
    template<typename... A>
    ext::array<T>& unshift_new(A &&... a);
    ext::array<T>& reserve(int64_t capacity);
    ext::string join(char const* sep) const;
    ext::string join(ext::string const& sep) const;
    static ext::array<T> with_data(T* data, int64_t size);
    static ext::array<T> with_data(T* data, int64_t size, int64_t capacity);
    static ext::array<T> with_capacity(int64_t capacity);
};

template<typename T>
inline array<T>::~array() {
    for (int64_t i = 0; i < _size; i++)
        _data[i].~T();
    SAFE_FREE(_data);
}

template<typename T>
inline array<T>::array()
    : _capacity(0)
    , _size(0)
    , _data(nullptr) {}

template<typename T>
inline array<T>::array(ext::array<T> const& array)
    : _capacity(array._capacity)
    , _size(array._size)
    , _data(ext::alloc<T>(array._capacity)) {
    for (int64_t i = 0; i < array._size; i++)
        new (_data + i) T(array._data[i]);
}

template<typename T>
inline array<T>::array(ext::array<T> && array)
    : _capacity(array._capacity)
    , _size(array._size)
    , _data(array._data) {
    array._capacity = 0;
    array._size = 0;
    array._data = nullptr;
}

template<typename T>
inline array<T>::array(std::initializer_list<T> const& list)
    : _capacity(list.size())
    , _size(list.size())
    , _data(ext::alloc<T>(list.size())) {
    T* dst = _data;
    for (T const& item : list)
        new (dst++) T(item);
}

template<typename T>
inline array<T>::array(T const* data, int64_t size)
    : _capacity(size)
    , _size(size)
    , _data(ext::alloc<T>(size)) {
    ASSERT(data != nullptr);
    for (int64_t i = 0; i < size; i++)
        new (_data + i) T(data[i]);
}

template<typename T>
inline ext::array<T>& array<T>::operator=(ext::array<T> const& array) {
    if (this != &array) {
        clear();
        reserve(array._size);
        _size = array._size;
        for (int64_t i = 0; i < array._size; i++)
            new (_data + i) T(array._data[i]);
    }
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::operator=(ext::array<T> && array) {
    if (this != &array) {
        T* td = _data;
        int64_t ts = _size;
        int64_t tc = _capacity;
        _data = array._data;
        _size = array._size;
        _capacity = array._capacity;
        array._data = td;
        array._size = ts;
        array._capacity = tc;
    }
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::operator+=(T const& item) {
    push(item);
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::operator+=(ext::array<T> const& array) {
    push(array);
    return *this;
}

template<typename T>
inline ext::array<T> array<T>::operator+(T const& item) const {
    ext::array<T> ret;
    ret.push(item);
    return ret;
}

template<typename T>
inline ext::array<T> array<T>::operator+(ext::array<T> const& item) const {
    ext::array<T> ret;
    ret.push(item);
    return ret;
}

template<typename T>
inline bool array<T>::operator==(ext::array<T> const& array) const {
    if (_size == array._size) {
        for (int64_t i = 0; i < _size; i++) {
            if (_data[i] != array._data[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template<typename T>
inline bool array<T>::operator!=(ext::array<T> const& array) const {
    return !operator==(array);
}

template<typename T>
inline T const& array<T>::operator[](int64_t index) const {
    ASSERT((index >= 0) && (index < _size));
    return _data[index];
}

template<typename T>
inline T& array<T>::operator[](int64_t index) {
    ASSERT((index >= 0) && (index < _size));
    return _data[index];
}

template<typename T>
inline int64_t array<T>::size() const {
    return _size;
}

template<typename T>
inline int64_t array<T>::capacity() const {
    return _capacity;
}

template<typename T>
inline T const* array<T>::begin() const {
    return _data;
}

template<typename T>
inline T* array<T>::begin() {
    return _data;
}

template<typename T>
inline T const* array<T>::end() const {
    return (_data + _size);
}

template<typename T>
inline T* array<T>::end() {
    return (_data + _size);
}

template<typename T>
inline T const* array<T>::data() const {
    return _data;
}

template<typename T>
inline T* array<T>::data() {
    return _data;
}

template<typename T>
inline T const& array<T>::first() const {
    ASSERT(_size > 0);
    return _data[0];
}

template<typename T>
inline T& array<T>::first() {
    ASSERT(_size > 0);
    return _data[0];
}

template<typename T>
inline T const& array<T>::last() const {
    ASSERT(_size > 0);
    return _data[_size - 1];
}

template<typename T>
inline T& array<T>::last() {
    ASSERT(_size > 0);
    return _data[_size - 1];
}

template<typename T>
inline T const& array<T>::first_or(T const& item) const {
    return (_size > 0) ? _data[0] : item;
}

template<typename T>
inline T const& array<T>::last_or(T const& item) const {
    return (_size > 0) ? _data[_size - 1] : item;
}

template<typename T>
inline ext::array<T> array<T>::subarr(int64_t index, int64_t size) const {
    index = (index < 0) ? 0 : ((index > _size) ? _size : index);
    size = (size < 0) ? 0 : ((size > (_size - index)) ? (_size - index) : size);
    return ext::array(_data + index, size);
}

template<typename T>
inline ext::array<T> array<T>::slice(int64_t start, int64_t end) const {
    ext::abort("not implemented");
    return ext::array<T>();
}

template<typename T>
inline int64_t array<T>::index_of(T const& item, int64_t start) const {
    start = (start < 0) ? 0 : start;
    for (int64_t i = start; i < _size; i++)
        if (_data[i] == item)
            return i;
    return -1;
}

template<typename T>
inline int64_t array<T>::index_of(ext::array<T> const& array, int64_t start) const {
    if (array._size > 0) {
        for (int64_t i = start; i < _size; i++) {
            if ((_size - i) >= array._size) {
                for (int64_t j = 0; j < array._size; j++)
                    if (_data[i + j] != array[j])
                        goto __continue;
                return i;
            } else return -1;
            __continue: ;
        }
        return -1;
    } else return -1;
}

template<typename T>
inline bool array<T>::includes(T const& item) const {
    return (index_of(item) > -1);
}

template<typename T>
inline bool array<T>::includes(ext::array<T> const& array) const {
    return (index_of(array) > -1);
}

template<typename T>
inline bool array<T>::empty() const {
    return (_size == 0);
}

template<typename T>
inline void array<T>::detach() {
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

template<typename T>
inline ext::array<T>& array<T>::clear() {
    for (int64_t i = 0; i < _size; i++)
        _data[i].~T();
    _size = 0;
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::splice(int64_t index, int64_t remove, ext::array<T> const& array) {
    index = (index < 0) ? 0 : ((index > _size) ? _size : index);
    remove = (remove < 0) ? 0 : ((remove > (_size - index)) ? (_size - index) : remove);
    ext::array<T> copy(array);
    ;
    _size -= (remove + copy._size);
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::splice(int64_t index, int64_t remove, T const& item) {
    index = (index < 0) ? 0 : ((index > _size) ? _size : index);
    remove = (remove < 0) ? 0 : ((remove > (_size - index)) ? (_size - index) : remove);
    T copy(item);
    ;
    _size -= (remove + 1);
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::splice(int64_t index, int64_t remove) {
    index = (index < 0) ? 0 : ((index > _size) ? _size : index);
    remove = (remove < 0) ? 0 : ((remove > (_size - index)) ? (_size - index) : remove);
    for (int64_t i = index; i < (index + remove); i++)
        _data[i].~T();
    for (int64_t i = (index + remove); i < _size; i++)
        new (_data + (i - remove)) T(std::move(_data[i]));
    _size -= remove;
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::push(T const& item) {
    if (_capacity == _size) {
        T copy(item);
        reserve((_size + 1) * 2);
        new (_data + _size) T(std::move(copy));
    } else {
        new (_data + _size) T(item);
    }
    _size += 1;
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::push(ext::array<T> const& array) {
    if (_capacity < (_size + array._size)) {
        ext::array<T> copy(array);
        reserve((_size + copy._size) * 2);
        for (int64_t i = 0; i < copy._size; i++)
            new (_data + _size + i) T(std::move(copy._data[i]));
    } else {
        for (int64_t i = 0; i < array._size; i++)
            new (_data + _size + i) T(array._data[i]);
    }
    _size += array._size;
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::unshift(T const& item) {
    T copy(item);
    if (_capacity == _size)
        reserve(_size * 2);
    for (int64_t i = (_size - 1); i >= 0; i--)
        new (_data + i + 1) T(std::move(_data[i]));
    new (_data) T(std::move(copy));
    _size += 1;
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::unshift(ext::array<T> const& array) {
    ext::array<T> copy(array);
    if (_capacity < (_size + copy._size))
        reserve((_size + copy._size) * 2);
    for (int64_t i = (_size - 1); i >= 0; i--)
        new (_data + i + copy._size) T(std::move(_data[i]));
    for (int64_t i = 0; i < copy._size; i++)
        new (_data + i) T(std::move(copy._data[i]));
    _size += array._size;
    return *this;
}

template<typename T>
inline T array<T>::pop() {
    ASSERT(_size > 0);
    T ret(std::move(_data[_size - 1]));
    _data[_size - 1].~T();
    _size -= 1;
    return ret;
}

template<typename T>
inline T array<T>::shift() {
    ASSERT(_size > 0);
    T ret(std::move(_data[0]));
    _data[0].~T();
    _size -= 1;
    for (int64_t i = 0; i < _size; i++)
        new (_data + i) T(std::move(_data[i + 1]));
    return ret;
}

template<typename T>
template<typename... A>
inline ext::array<T>& array<T>::push_new(A &&... a) {
    if (_capacity == _size) {
        reserve(_size * 2);
    }
    new (_data + _size) T(std::forward<A>(a)...);
    _size += 1;
    return *this;
}

template<typename T>
template<typename... A>
inline ext::array<T>& array<T>::unshift_new(A &&... a) {
    if (_capacity == _size)
        reserve(_size * 2);
    for (int64_t i = (_size - 1); i >= 0; i--)
        new (_data + i + 1) T(std::move(_data[i]));
    new (_data) T(std::forward<A>(a)...);
    _size += 1;
    return *this;
}

template<typename T>
inline ext::array<T>& array<T>::reserve(int64_t capacity) {
    if (capacity > _capacity) {
        T* data = ext::alloc<T>(capacity);
        for (int64_t i = 0; i < _size; i++)
            new (data + i) T(std::move(_data[i]));
        SAFE_FREE(_data);
        _data = data;
        _capacity = capacity;
    }
    return *this;
}

template<typename T>
inline ext::array<T> array<T>::with_data(T* data, int64_t size) {
    ext::array<T> ret;
    ret._data = data;
    ret._size =
    ret._capacity = size;
    return ret;
}

template<typename T>
inline ext::array<T> array<T>::with_data(T* data, int64_t size, int64_t capacity) {
    ext::array<T> ret;
    ret._data = data;
    ret._size = size;
    ret._capacity = capacity;
    return ret;
}

template<typename T>
inline ext::array<T> array<T>::with_capacity(int64_t capacity) {
    ext::array<T> ret;
    ret.reserve(capacity);
    return ret;
}

} /* namespace ext */