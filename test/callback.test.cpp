void callback_test() {
	{
        auto val1 = 0;
        auto val2 = 0;
        auto val3 = 0;

        auto callback = ext::callback<int const&>();
        
        auto const s1 = callback([&](int const& val) {
            val1 = val;
        });

        auto const s2 = callback([&](int const& val) {
            val2 = val;
        });

        auto const s3 = callback([&](int const& val) {
            val3 = val;
        });

        callback.trigger(123);

        assert(val1 == 123);
        assert(val2 == 123);
        assert(val3 == 123);

        callback.trigger(333);

        assert(val1 == 333);
        assert(val2 == 333);
        assert(val3 == 333);

        callback.remove(s1);
        callback.remove(s3);

        callback.trigger(777);

        assert(val1 == 333);
        assert(val2 == 777);
        assert(val3 == 333);
	}
}