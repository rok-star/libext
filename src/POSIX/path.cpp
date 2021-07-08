#ifdef __linux__
    #define _POSIX_C_SOURCE 200809L
#endif

#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libext/path.hpp>

typedef struct stat __stat_t;

namespace ext {
namespace path {

ext::string cwd() {
    int64_t size = (PATH_MAX + 1);
    char* data = ext::alloc<char>(size);
    if (getcwd(data, PATH_MAX) == NULL) {
        ext::abort("getcwd() failed: %s\n", strerror(errno));
    }
    return ext::string::with_pchar(data, size);
}

ext::string basename(ext::string const& path) {
    return {};
}

ext::string extname(ext::string const& path) {
    return {};
}

stat::stat(ext::string const& path)
    : _path(path)
    , _exists(false)
    , _directory(false)
    , _file(false)
    , _modified(0)
    , _size(0) {

    __stat_t st = {};
    if (::stat(path.c_string(), &st) == 0) {
        _exists = true;
        _file = S_ISREG(st.st_mode);
        _directory = S_ISDIR(st.st_mode);
        _size = st.st_size;
#if __linux__
        _modified = ((st.st_mtim.tv_sec * 1000.0)
                    + (st.st_mtim.tv_nsec / 1000000.0));
#else
        _modified = ((st.st_mtimespec.tv_sec * 1000.0)
                    + (st.st_mtimespec.tv_nsec / 1000000.0));
#endif
    }
}

ext::string const& stat::path() const {
    return _path;
}

bool stat::exists() const {
    return _exists;
}

bool stat::directory() const {
    return _directory;
}

bool stat::file() const {
    return _file;
}

double stat::modified() const {
    return _modified;
}

int64_t stat::size() const {
    return _size;
}

} /* namespace path */
} /* namespace ext */