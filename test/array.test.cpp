#include <libext/array.hpp>

void array_test() {
	{
		auto arr1 = ext::array<int>();
		ASSERT(arr1.data() == nullptr);
		ASSERT(arr1.size() == 0);
		ASSERT(arr1.capacity() == 0);

		arr1.push(123);
		ASSERT(arr1.data() != nullptr);
		ASSERT(arr1.size() == 1);
		ASSERT(arr1.capacity() >= arr1.size());
		ASSERT(arr1[0] == 123);

		arr1.push(321);
		ASSERT(arr1.size() == 2);
		ASSERT(arr1.capacity() >= arr1.size());
		ASSERT(arr1[0] == 123);
		ASSERT(arr1[1] == 321);

		arr1.push(arr1);
		ASSERT(arr1.size() == 4);
		ASSERT(arr1[0] == 123);
		ASSERT(arr1[1] == 321);
		ASSERT(arr1[2] == 123);
		ASSERT(arr1[3] == 321);

		auto arr2 = arr1;
		ASSERT(arr2.size() == 4);
		ASSERT(arr2[0] == 123);
		ASSERT(arr2[1] == 321);
		ASSERT(arr2[2] == 123);
		ASSERT(arr2[3] == 321);

		arr2.push(arr1);
		ASSERT(arr2.size() == 8);
		ASSERT(arr2[0] == 123);
		ASSERT(arr2[1] == 321);
		ASSERT(arr2[2] == 123);
		ASSERT(arr2[3] == 321);
		ASSERT(arr2[4] == 123);
		ASSERT(arr2[5] == 321);
		ASSERT(arr2[6] == 123);
		ASSERT(arr2[7] == 321);
		ASSERT(arr1.size() == 4);
		ASSERT(arr1[0] == 123);
		ASSERT(arr1[1] == 321);
		ASSERT(arr1[2] == 123);
		ASSERT(arr1[3] == 321);
	} {
		auto arr1 = ext::array<char>({ 'h', 'e', 'l', 'l', 'o' });
		auto arr2 = ext::array<char>({ 'h', 'e', 'l', 'l', 'o' });
		ASSERT(arr1 == arr2);
	}
}