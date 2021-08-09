#include <libext/core.hpp>

#include "status.test.cpp"
#include "unicode.test.cpp"
#include "string.test.cpp"
#include "number.test.cpp"
#include "array.test.cpp"
#include "map.test.cpp"
#include "value.test.cpp"
#include "path.test.cpp"

#include "../src/core/status.cpp"
#include "../src/core/unicode.cpp"
#include "../src/core/string.cpp"
#include "../src/core/number.cpp"
#include "../src/core/value.cpp"
#include "../src/core/date.cpp"
#include "../src/core/json.cpp"
#include "../src/core/POSIX/path.cpp"

int main(int argc, char const *argv[]) {

	unicode_test();
	array_test();
	map_test();
	string_test();
	value_test();
	number_test();
	status_test();
	path_test();

	ext::output("%s\n", "Nothing failed!");

	return 0;
}