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
    ext::point<T> corner(int) const;
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
inline ext::point<T> rect<T>::corner(int index) const {
    auto const norm = (index % 4);
    assert(norm >= 0);
    assert(norm <= 3);
    if (norm == 0) return origin;
    else if (norm == 1) return { origin.x + size.width, origin.y };
    else if (norm == 2) return { origin.x + size.width, origin.y + origin.height };
    else if (norm == 3) return { origin.x, origin.y + origin.height };
    else return { 0, 0 };
}

} /* namespace ext */