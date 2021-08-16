void status_test() {
    auto status = ext::status();
	assert(status.type() == ext::status_type::success);
	assert(status.message() == "");

	status.add_failure("abc");
	assert(status.type() == ext::status_type::failure);
	assert(status.message() == "abc");

	status.set_success();
	assert(status.type() == ext::status_type::success);
	assert(status.message() == "");

	status.add_failure("abc%s", "123");
	assert(status.type() == ext::status_type::failure);
	assert(status.message() == "abc123");
}