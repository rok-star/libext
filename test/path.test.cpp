void path_test() {
    auto cwd = ext::path::cwd();
    auto stat = ext::path::stat(cwd);
    auto copy = stat;

    assert(stat.exists() == true);
    assert(stat.directory() == true);
    assert(stat.file() == false);
    assert(stat.path() == cwd);
    assert(copy.path() == stat.path());
    assert(copy.exists() == stat.exists());
    assert(copy.directory() == stat.directory());
    assert(copy.file() == stat.file());
    assert(copy.modified() == stat.modified());
    assert(copy.size() == stat.size());
}
