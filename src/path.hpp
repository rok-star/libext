#pragma once

#include <libext/string.hpp>
#include <libext/status.hpp>

namespace ext {
namespace path {

ext::string cwd();
ext::string basename(ext::string const& path);
ext::string extname(ext::string const& path);

class stat {
private:
    ext::string _path;
    bool _exists;
    bool _directory;
    bool _file;
    double _modified;
    int64_t _size;
public:
    stat(ext::string const& path);
    stat(stat const& stat) = default;
    stat(stat && stat) = default;
    stat& operator=(stat const& stat) = default;
    stat& operator=(stat && stat) = default;
    ext::string const& path() const;
    bool exists() const;
    bool directory() const;
    bool file() const;
    double modified() const;
    int64_t size() const;
};

template<typename... A>
inline ext::string resolve(ext::string const& head, A const&... tail);
template<typename... A>
inline ext::string join(ext::string const& head, A const&... tail);

template<typename... A>
inline ext::string resolve(ext::string const& head, A const&... tail) {

}

template<typename... A>
inline ext::string join(ext::string const& head, A const&... tail) {

}

} /* namespace path */
} /* namespace ext */