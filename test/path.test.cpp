void path_test() {
    auto cwd = ext::path::cwd();
    auto stat = ext::path::stat(cwd);
    auto copy = stat;

    ASSERT(stat.exists() == true);
    ASSERT(stat.directory() == true);
    ASSERT(stat.file() == false);
    ASSERT(stat.path() == cwd);
    ASSERT(copy.path() == stat.path());
    ASSERT(copy.exists() == stat.exists());
    ASSERT(copy.directory() == stat.directory());
    ASSERT(copy.file() == stat.file());
    ASSERT(copy.modified() == stat.modified());
    ASSERT(copy.size() == stat.size());
}
