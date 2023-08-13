#include "test_arrays.h"

#include "pim/arr.h"
#include "pim/test.h"

void _print_square(int num) {
	printf("%d^2 = %d\n", num, num * num);
}

void _test_arr_foreach() {
	int arr[] = { 1, 2, 3, 4, 5 };
	size_t arr_length = ARR_LENGTH(arr);

	printf("Original array:\n");
	printf("%s\n\n", arr_to_string(arr, arr_length));

	printf("Squared array:\n");
	arr_foreach(arr, arr_length, _print_square);
}

void test_arrays() {
	Test tests[] = {
		test("Map", _test_arr_foreach),
	};

	TestSuite suite = test_suite("Arrays", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
