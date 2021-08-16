void string_test() {
    {
        auto str1 = ext::string("hello");
        auto str2 = ext::string("hello");
        assert(str1 == str2);
        assert(str1 == "hello");
    }
}