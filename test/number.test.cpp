void number_test() {
    // int8_t
    {
        auto status = ext::status();
        auto const val = ext::number::parse_int8("123", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 123);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int8("-123", status);
        assert(status.type() == ext::status_type::success);
        assert(val == -123);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int8("127", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 127);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int8("-128", status);
        assert(status.type() == ext::status_type::success);
        assert(val == -128);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int8("-129", status);
        assert(status.type() == ext::status_type::failure);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int8("128", status);
        assert(status.type() == ext::status_type::failure);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int8("1234", status);
        assert(status.type() == ext::status_type::failure);
    }
    // int16_t
    {
        auto status = ext::status();
        auto const val = ext::number::parse_int16("123", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 123);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int16("-123", status);
        assert(status.type() == ext::status_type::success);
        assert(val == -123);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int16("32767", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 32767);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int16("-32768", status);
        assert(status.type() == ext::status_type::success);
        assert(val == -32768);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int16("-32769", status);
        assert(status.type() == ext::status_type::failure);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int16("32768", status);
        assert(status.type() == ext::status_type::failure);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int16("327691", status);
        assert(status.type() == ext::status_type::failure);
    }
    // int32_t
    {
        auto status = ext::status();
        auto const val = ext::number::parse_int32("123", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 123);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int32("-123", status);
        assert(status.type() == ext::status_type::success);
        assert(val == -123);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int32("2147483647", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 2147483647);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int32("-2147483648", status);
        assert(status.type() == ext::status_type::success);
        assert(val == -2147483648);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int32("-2147483649", status);
        assert(status.type() == ext::status_type::failure);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int32("2147483648", status);
        assert(status.type() == ext::status_type::failure);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int32("214748364711", status);
        assert(status.type() == ext::status_type::failure);
    }




    {
        auto status = ext::status();
        auto const val = ext::number::parse("1234567890.2", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 1234567890.2);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse("1234567890", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 1234567890);
    } {
        auto status = ext::status();
        auto const val = ext::number::parse_int8("123", status);
        assert(status.type() == ext::status_type::success);
        assert(val == 123);
    }
}
