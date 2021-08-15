#pragma once

namespace ext {

template<typename T>
struct point {
    T x;
    T y;
    ext::point<T> operator+(ext::point<T> const&) const;
    ext::point<T>& operator+=(ext::point<T> const&) const;
};

template<typename T>
struct size {
    T width;
    T height;
    ext::size<T> operator+(ext::size<T> const&) const;
    ext::size<T>& operator+=(ext::size<T> const&) const;
};

template<typename T>
struct rect {
    ext::point<T> origin;
    ext::size<T> size;
    ext::point<T> top_left() const;
    ext::point<T> top_right() const;
    ext::point<T> bottom_left() const;
    ext::point<T> bottom_right() const;
};

template<typename T>
inline ext::point<T> point<T>::operator+(ext::point<T> const& point) const {
    return { x + point.x, y + point.y };
}

template<typename T>
inline ext::point<T>& point<T>::operator+=(ext::point<T> const& point) const {
    x += point.x;
    y += point.y;
    return *this;
}

template<typename T>
inline ext::size<T> size<T>::operator+(ext::size<T> const& size) const {
    return { width + size.width, height + size.height };
}

template<typename T>
inline ext::size<T>& size<T>::operator+=(ext::size<T> const& size) const {
    width += size.width;
    height += size.height;
    return *this;
}

template<typename T>
inline ext::point<T> rect<T>::top_left() const {
    return origin;
}

template<typename T>
inline ext::point<T> rect<T>::top_right() const {
    return origin + ext::point<T>({ size.width, 0 });
}

template<typename T>
inline ext::point<T> rect<T>::bottom_left() const {
    return origin + ext::point<T>({ 0, size.height });
}

template<typename T>
inline ext::point<T> rect<T>::bottom_right() const {
    return origin + ext::point<T>({ size.width, size.height });
}

} /* namespace ext */