void value_test() {
    {
        auto val = ext::value();
        assert(val.type() == ext::value_type::null);
    } {
        auto val = ext::value::null();
        assert(val.type() == ext::value_type::null);
    } {
        auto val = ext::value::string();
        assert(val.type() == ext::value_type::string);
    } {
        auto val = ext::value::number();
        assert(val.type() == ext::value_type::number);
    } {
        auto val = ext::value::array();
        assert(val.type() == ext::value_type::array);
    } {
        auto val = ext::value::object();
        assert(val.type() == ext::value_type::object);
    } {
        auto val = ext::value::string("privet_rulet");
        assert(val.type() == ext::value_type::string);
        assert(val.string_value() == "privet_rulet");
    } {
        auto val = ext::value::number(12345.12345);
        assert(val.type() == ext::value_type::number);
        assert(val.number_value() == 12345.12345);
    } {
        auto item_0 = ext::value::string("London");
        auto item_1 = ext::value::string("is the");
        auto item_2 = ext::value::string("capital");
        auto item_3 = ext::value::number(777.777);
        auto item_4 = ext::value::null();

        auto val = ext::value::array({ item_0, item_1, item_2, item_3, item_4 });
        assert(val.type() == ext::value_type::array);
        assert(val[0].type() == ext::value_type::string);
        assert(val[1].type() == ext::value_type::string);
        assert(val[2].type() == ext::value_type::string);
        assert(val[3].type() == ext::value_type::number);
        assert(val[4].type() == ext::value_type::null);
        assert(val[0].type() == item_0.type());
        assert(val[1].type() == item_1.type());
        assert(val[2].type() == item_2.type());
        assert(val[3].type() == item_3.type());
        assert(val[4].type() == item_4.type());
        assert(val[0].string_value() == "London");
        assert(val[1].string_value() == "is the");
        assert(val[2].string_value() == "capital");
        assert(val[3].number_value() == 777.777);
        assert(val[0] == item_0);
        assert(val[1] == item_1);
        assert(val[2] == item_2);
        assert(val[3] == item_3);
        assert(val[4] == item_4);
    } {
        auto val = ext::value::object({
            { "prop1", 1 },
            { "prop2", "prop2" },
            { "prop3", ext::value::object({{ "subprop1", ext::value() }}) }
        });
        assert(val.type() == ext::value_type::object);
        assert(val.has("prop1") == true);
        assert(val.has("prop2") == true);
        assert(val.has("prop3") == true);
        assert(val["prop1"].type() == ext::value_type::number);
        assert(val["prop2"].type() == ext::value_type::string);
        assert(val["prop3"].type() == ext::value_type::object);
    }
}