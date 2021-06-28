#include <libext/value.hpp>

void value_test() {
    {
        auto val = ext::value();
        ASSERT(val.type() == ext::value_type::null);
    } {
        auto val = ext::value::null();
        ASSERT(val.type() == ext::value_type::null);
    } {
        auto val = ext::value::string();
        ASSERT(val.type() == ext::value_type::string);
    } {
        auto val = ext::value::number();
        ASSERT(val.type() == ext::value_type::number);
    } {
        auto val = ext::value::array();
        ASSERT(val.type() == ext::value_type::array);
    } {
        auto val = ext::value::object();
        ASSERT(val.type() == ext::value_type::object);
    } {
        auto val = ext::value::string("privet_rulet");
        ASSERT(val.type() == ext::value_type::string);
        ASSERT(val.string_value() == "privet_rulet");
    } {
        auto val = ext::value::number(12345.12345);
        ASSERT(val.type() == ext::value_type::number);
        ASSERT(val.number_value() == 12345.12345);
    } {
        auto item_0 = ext::value::string("London");
        auto item_1 = ext::value::string("is the");
        auto item_2 = ext::value::string("capital");
        auto item_3 = ext::value::number(777.777);
        auto item_4 = ext::value::null();

        auto val = ext::value::array({ item_0, item_1, item_2, item_3, item_4 });
        ASSERT(val.type() == ext::value_type::array);
        ASSERT(val[0].type() == ext::value_type::string);
        ASSERT(val[1].type() == ext::value_type::string);
        ASSERT(val[2].type() == ext::value_type::string);
        ASSERT(val[3].type() == ext::value_type::number);
        ASSERT(val[4].type() == ext::value_type::null);
        ASSERT(val[0].type() == item_0.type());
        ASSERT(val[1].type() == item_1.type());
        ASSERT(val[2].type() == item_2.type());
        ASSERT(val[3].type() == item_3.type());
        ASSERT(val[4].type() == item_4.type());
        ASSERT(val[0].string_value() == "London");
        ASSERT(val[1].string_value() == "is the");
        ASSERT(val[2].string_value() == "capital");
        ASSERT(val[3].number_value() == 777.777);
        ASSERT(val[0] == item_0);
        ASSERT(val[1] == item_1);
        ASSERT(val[2] == item_2);
        ASSERT(val[3] == item_3);
        ASSERT(val[4] == item_4);
    } {
        auto val = ext::value::object({
            { "prop1", 1 },
            { "prop2", "prop2" },
            { "prop3", ext::value::object({{ "subprop1", ext::value() }}) }
        });
        ASSERT(val.type() == ext::value_type::object);
        ASSERT(val.has("prop1") == true);
        ASSERT(val.has("prop2") == true);
        ASSERT(val.has("prop3") == true);
        ASSERT(val["prop1"].type() == ext::value_type::number);
        ASSERT(val["prop2"].type() == ext::value_type::string);
        ASSERT(val["prop3"].type() == ext::value_type::object);
    }
}