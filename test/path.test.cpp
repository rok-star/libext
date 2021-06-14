#include <libext/path.hpp>

void path_test() {
    auto cwd = ext::path::cwd();

    auto stat = ext::path::stat(cwd);
    ASSERT(stat.exists() == true);
    ASSERT(stat.directory() == true);
    ASSERT(stat.file() == false);
    ASSERT(stat.path() == cwd);

    auto copy = stat;
    ASSERT(copy.path() == stat.path());
    ASSERT(copy.exists() == stat.exists());
    ASSERT(copy.directory() == stat.directory());
    ASSERT(copy.file() == stat.file());
    ASSERT(copy.modified() == stat.modified());
    ASSERT(copy.size() == stat.size());

    ext::output("cwd: %s\n", cwd.c_string());
    ext::output("size: %ld\n", stat.size());
}
