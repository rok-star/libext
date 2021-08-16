void array_test() {
	{
		auto arr1 = ext::array<int>();
		assert(arr1.data() == nullptr);
		assert(arr1.size() == 0);
		assert(arr1.capacity() == 0);

		arr1.push(123);
		assert(arr1.data() != nullptr);
		assert(arr1.size() == 1);
		assert(arr1.capacity() >= arr1.size());
		assert(arr1[0] == 123);

		arr1.push(321);
		assert(arr1.size() == 2);
		assert(arr1.capacity() >= arr1.size());
		assert(arr1[0] == 123);
		assert(arr1[1] == 321);

		arr1.push(arr1);
		assert(arr1.size() == 4);
		assert(arr1[0] == 123);
		assert(arr1[1] == 321);
		assert(arr1[2] == 123);
		assert(arr1[3] == 321);

		auto arr2 = arr1;
		assert(arr2.size() == 4);
		assert(arr2[0] == 123);
		assert(arr2[1] == 321);
		assert(arr2[2] == 123);
		assert(arr2[3] == 321);

		arr2.push(arr1);
		assert(arr2.size() == 8);
		assert(arr2[0] == 123);
		assert(arr2[1] == 321);
		assert(arr2[2] == 123);
		assert(arr2[3] == 321);
		assert(arr2[4] == 123);
		assert(arr2[5] == 321);
		assert(arr2[6] == 123);
		assert(arr2[7] == 321);
		assert(arr1.size() == 4);
		assert(arr1[0] == 123);
		assert(arr1[1] == 321);
		assert(arr1[2] == 123);
		assert(arr1[3] == 321);
	} {
		auto arr1 = ext::array<char>({ 'h', 'e', 'l', 'l', 'o' });
		auto arr2 = ext::array<char>({ 'h', 'e', 'l', 'l', 'o' });
		assert(arr1 == arr2);
	}
}