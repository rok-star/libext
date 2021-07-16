#include "status.test.cpp"
#include "unicode.test.cpp"
#include "string.test.cpp"
#include "number.test.cpp"
#include "array.test.cpp"
#include "map.test.cpp"
#include "value.test.cpp"
#include "path.test.cpp"

#include "../src/status.cpp"
#include "../src/unicode.cpp"
#include "../src/string.cpp"
#include "../src/number.cpp"
#include "../src/value.cpp"
#include "../src/date.cpp"
#include "../src/json.cpp"
#include "../src/POSIX/path.cpp"

int main(int argc, char const *argv[]) {

	unicode_test();
	array_test();
	map_test();
	string_test();
	value_test();
	number_test();
	status_test();
	path_test();

	ext::output("Nothing failed!\n");

	return 0;
}