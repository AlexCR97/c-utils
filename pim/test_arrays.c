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

bool _is_even(size_t index, int item) {
	return item % 2 == 0;
}

void _test_arr_any_int() {
	int nums[] = { 1, 2, 3, 4, 5 };
	bool nums_any_even = arr_any_int(nums, ARR_LENGTH(nums), _is_even);
	PM_ASSERT(nums_any_even == true);

	int odd_nums[] = { 1, 3, 5, 7, 9 };
	bool odd_nums_any_even = arr_any_int(odd_nums, ARR_LENGTH(odd_nums), _is_even);
	PM_ASSERT(odd_nums_any_even == false);
}

int _increment_by_index(int index, int item) {
	return item + index;
}

void _test_arr_concat_int() {
	int arr_a[] = { 1, 2, 3, 4 };
	int arr_b[] = { 5, 6, 7, 8 };
	int* arr_c = arr_concat_int(arr_a, ARR_LENGTH(arr_a), arr_b, ARR_LENGTH(arr_b));
	PM_ASSERT_EQ(arr_c[0], 1);
	PM_ASSERT_EQ(arr_c[1], 2);
	PM_ASSERT_EQ(arr_c[2], 3);
	PM_ASSERT_EQ(arr_c[3], 4);
	PM_ASSERT_EQ(arr_c[4], 5);
	PM_ASSERT_EQ(arr_c[5], 6);
	PM_ASSERT_EQ(arr_c[6], 7);
	PM_ASSERT_EQ(arr_c[7], 8);
}

void _test_arr_contains_int() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	bool contains_7 = arr_contains_int(arr, ARR_LENGTH(arr), 7);
	PM_ASSERT(contains_7 == true);

	bool contains_11 = arr_contains_int(arr, ARR_LENGTH(arr), 11);
	PM_ASSERT(contains_11 == false);
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
		test(PM_NAMEOF(arr_any_int), _test_arr_any_int),
		test(PM_NAMEOF(arr_concat_int), _test_arr_concat_int),
		test(PM_NAMEOF(arr_contains_int), _test_arr_contains_int),
		test(PM_NAMEOF(arr_map_int), _test_arr_map_int),
		test(PM_NAMEOF(arr_to_string), _test_arr_to_string),
	};

	TestSuite suite = test_suite("Arrays", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
