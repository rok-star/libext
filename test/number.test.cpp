#include <libext/number.hpp>

void number_test() {
    {
        auto status = ext::status();
        auto val = ext::number::parse("1234567890", status);
        ASSERT(status.type() == ext::status_type::success);
        ASSERT(val == 1234567890);
    }
}
