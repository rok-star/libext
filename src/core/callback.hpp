#pragma once

#include <functional>
#include <libext/core/map.hpp>

namespace ext {

template<typename... A>
class callback final {
private:
    int _seq;
    ext::map<int, std::function<void(A...)>> _map;
public:
    callback();
    void trigger(A...) const;
    bool remove(int);
    int add(std::function<void(A...)> const&);
    int operator()(std::function<void(A...)> const&);
};

template<typename... A>
inline callback<A...>::callback()
    : _seq(0)
    , _map() {}

template<typename... A>
inline void callback<A...>::trigger(A... args) const {
    for (auto const& item : _map.data()) {
        item.value()(args...);
    }
}

template<typename... A>
inline bool callback<A...>::remove(int id) {
    return _map.remove(id);
}

template<typename... A>
inline int callback<A...>::add(std::function<void(A...)> const& fn) {
    _map.set(++_seq, fn);
    return _seq;
}

template<typename... A>
inline int callback<A...>::operator()(std::function<void(A...)> const& fn) {
    return add(fn);
}

} /* namespace ext */