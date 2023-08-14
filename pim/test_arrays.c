#include "test_arrays.h"

#include "pim/arr.h"
#include "pim/test.h"

void _test_ARR_LENGTH() {
	int arr[] = { 1, 2, 3, 4, 5 };
	int length = ARR_LENGTH(arr);
	PM_ASSERT_EQ(length, 5);
}

void _test_arr_alloc_int() {
	int* arr = arr_alloc_int(5);
	PM_ASSERT_EQ(arr[0], 0);
}

int _increment_by_index(int index, int item) {
	return item + index;
}

void _test_arr_map_int() {
	int arr[] = { 1, 2, 3, 4, 5 };
	int* mapped_arr = arr_map_int(arr, ARR_LENGTH(arr), _increment_by_index);
	PM_ASSERT_EQ(mapped_arr[0], arr[0] + 0);
	PM_ASSERT_EQ(mapped_arr[1], arr[1] + 1);
	PM_ASSERT_EQ(mapped_arr[2], arr[2] + 2);
	PM_ASSERT_EQ(mapped_arr[3], arr[3] + 3);
	PM_ASSERT_EQ(mapped_arr[4], arr[4] + 4);
}

void _test_arr_to_string() {
	int arr[] = { 1, 2, 3, 4, 5 };
	char* arr_str = arr_to_string(arr, ARR_LENGTH(arr));
	PM_ASSERT_EQ_STR(arr_str, "{ 1, 2, 3, 4, 5 }");
}

void test_arrays() {
	Test tests[] = {
		test(PM_NAMEOF(ARR_LENGTH), _test_ARR_LENGTH),
		test(PM_NAMEOF(arr_alloc_int), _test_arr_alloc_int),
		test(PM_NAMEOF(arr_map_int), _test_arr_map_int),
		test(PM_NAMEOF(arr_to_string), _test_arr_to_string),
	};

	TestSuite suite = test_suite("Arrays", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
