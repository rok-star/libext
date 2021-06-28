#include <iostream>

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

	auto status = ext::status();
	ASSERT(status.type() == ext::status_type::success);
	ASSERT(status.message() == "");

	status.add_failure("abc");
	ASSERT(status.type() == ext::status_type::failure);
	ASSERT(status.message() == "abc");

	status.set_success();
	ASSERT(status.type() == ext::status_type::success);
	ASSERT(status.message() == "");

	status.add_failure("abc%s", "123");
	ASSERT(status.type() == ext::status_type::failure);
	ASSERT(status.message() == "abc123");

	path_test();

	std::cout << "Nothing failed!" << std::endl;

	return 0;
}