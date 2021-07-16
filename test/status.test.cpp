#include <libext/libext.hpp>

void status_test() {
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
}