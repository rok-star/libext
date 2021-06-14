#include <libext/map.hpp>

void map_test() {
	{
        auto map = ext::map<ext::string, double>();
        map.set("prop1", 123);
        ASSERT(map.has("prop1") == true);
        ASSERT(map.get("prop1") == 123);
	} {
        auto map = ext::map<ext::string, double>({
            { "prop1", 123 }
        });
        ASSERT(map.has("prop1") == true);
        ASSERT(map.get("prop1") == 123);
    }
}