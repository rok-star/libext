void map_test() {
	{
        auto map = ext::map<ext::string, double>();
        map.set("prop1", 123);
        assert(map.has("prop1") == true);
        assert(map.get("prop1") == 123);
	} {
        auto map = ext::map<ext::string, double>({
            { "prop1", 123 }
        });
        assert(map.has("prop1") == true);
        assert(map.get("prop1") == 123);
    }
}