#include "test_arrays.h"

#include <stdlib.h>
#include "pim/arrays.h"
#include "pim/test.h"

void _test_PM_ARR_LENGTH() {
	int arr[] = { 1, 2, 3, 4, 5 };
	int length = PM_ARR_LENGTH(arr);
	PM_ASSERT_EQ(length, 5);
}

void _test_pm_arr_alloc_int() {
	int* arr = pm_arr_alloc_int(5).data;
	PM_ASSERT_EQ(arr[0], 0);
	free(arr);
}

bool _is_even(size_t index, int item) {
	return item % 2 == 0;
}

void _test_pm_arr_any_int() {
	int nums[] = { 1, 2, 3, 4, 5 };
	bool nums_any_even = pm_arr_any_int(nums, PM_ARR_LENGTH(nums), _is_even);
	PM_ASSERT(nums_any_even == true);

	int odd_nums[] = { 1, 3, 5, 7, 9 };
	bool odd_nums_any_even = pm_arr_any_int(odd_nums, PM_ARR_LENGTH(odd_nums), _is_even);
	PM_ASSERT(odd_nums_any_even == false);
}

int _increment_by_index(int index, int item) {
	return item + index;
}

void _test_pm_arr_concat_int() {
	int arr_a[] = { 1, 2, 3, 4 };
	int arr_b[] = { 5, 6, 7, 8 };
	int* arr_c = pm_arr_concat_int(arr_a, PM_ARR_LENGTH(arr_a), arr_b, PM_ARR_LENGTH(arr_b)).data;
	PM_ASSERT_EQ(arr_c[0], 1);
	PM_ASSERT_EQ(arr_c[1], 2);
	PM_ASSERT_EQ(arr_c[2], 3);
	PM_ASSERT_EQ(arr_c[3], 4);
	PM_ASSERT_EQ(arr_c[4], 5);
	PM_ASSERT_EQ(arr_c[5], 6);
	PM_ASSERT_EQ(arr_c[6], 7);
	PM_ASSERT_EQ(arr_c[7], 8);
	free(arr_c);
}

void _test_pm_arr_contains_int() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	bool contains_7 = pm_arr_contains_int(arr, PM_ARR_LENGTH(arr), 7);
	PM_ASSERT(contains_7 == true);

	bool contains_11 = pm_arr_contains_int(arr, PM_ARR_LENGTH(arr), 11);
	PM_ASSERT(contains_11 == false);
}

bool _is_num_even(int index, int item) {
	return item % 2 == 0;
}

bool _is_num_odd(int index, int item) {
	return item % 2 != 0;
}

void _test_pm_arr_count_int() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	int even_count = pm_arr_count_int(arr, PM_ARR_LENGTH(arr), _is_num_even);
	PM_ASSERT_EQ(even_count, 5);

	int odd_count = pm_arr_count_int(arr, PM_ARR_LENGTH(arr), _is_num_odd);
	PM_ASSERT_EQ(odd_count, 6);
}

void _test_pm_arr_every_int() {
	int evens[] = { 2, 4, 6, 8, 10 };
	bool all_even = pm_arr_every_int(evens, PM_ARR_LENGTH(evens), _is_num_even);
	PM_ASSERT(all_even == true);

	int odds[] = { 1, 3, 5, 7, 9 };
	bool all_odd = pm_arr_every_int(odds, PM_ARR_LENGTH(odds), _is_num_odd);
	PM_ASSERT(all_odd == true);

	all_even = pm_arr_every_int(evens, PM_ARR_LENGTH(evens), _is_num_odd);
	PM_ASSERT(all_even == false);

	all_odd = pm_arr_every_int(odds, PM_ARR_LENGTH(odds), _is_num_even);
	PM_ASSERT(all_odd == false);
}

bool _is_divisible_by_5(int index, int item) {
	return item % 5 == 0;
}

void _test_pm_arr_filter_int() {
	int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int* even_nums = pm_arr_filter_int(nums, PM_ARR_LENGTH(nums), _is_num_even).data;
	PM_ASSERT_EQ(even_nums[0], 2);
	PM_ASSERT_EQ(even_nums[1], 4);
	PM_ASSERT_EQ(even_nums[2], 6);
	PM_ASSERT_EQ(even_nums[3], 8);
	PM_ASSERT_EQ(even_nums[4], 10);
	free(even_nums);

	int* odd_nums = pm_arr_filter_int(nums, PM_ARR_LENGTH(nums), _is_num_odd).data;
	PM_ASSERT_EQ(odd_nums[0], 1);
	PM_ASSERT_EQ(odd_nums[1], 3);
	PM_ASSERT_EQ(odd_nums[2], 5);
	PM_ASSERT_EQ(odd_nums[3], 7);
	PM_ASSERT_EQ(odd_nums[4], 9);
	free(odd_nums);
}

void _test_pm_arr_find_int() {
	int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int divisible_by_5 = pm_arr_find_int(nums, PM_ARR_LENGTH(nums), _is_divisible_by_5);
	PM_ASSERT_EQ(divisible_by_5, 5);
}

void _test_pm_arr_find_index_int() {
	int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int divisible_by_5_index = pm_arr_find_index_int(nums, PM_ARR_LENGTH(nums), _is_divisible_by_5);
	PM_ASSERT_EQ(divisible_by_5_index, 4);
	PM_ASSERT_EQ(nums[divisible_by_5_index], 5);
}

void _test_pm_arr_map_int() {
	int arr[] = { 1, 2, 3, 4, 5 };
	int* mapped_arr = pm_arr_map_int(arr, PM_ARR_LENGTH(arr), _increment_by_index).data;
	PM_ASSERT_EQ(mapped_arr[0], arr[0] + 0);
	PM_ASSERT_EQ(mapped_arr[1], arr[1] + 1);
	PM_ASSERT_EQ(mapped_arr[2], arr[2] + 2);
	PM_ASSERT_EQ(mapped_arr[3], arr[3] + 3);
	PM_ASSERT_EQ(mapped_arr[4], arr[4] + 4);
	free(mapped_arr);
}

void _test_pm_arr_reverse_int() {
	int arr[] = { 1, 2, 3, 4, 5 };
	const int arr_length = PM_ARR_LENGTH(arr);
	int* reversed = pm_arr_reverse_int(arr, arr_length).data;
	PM_ASSERT_EQ(reversed[0], arr[arr_length - 1]);
	PM_ASSERT_EQ(reversed[1], arr[arr_length - 2]);
	PM_ASSERT_EQ(reversed[2], arr[arr_length - 3]);
	PM_ASSERT_EQ(reversed[3], arr[arr_length - 4]);
	PM_ASSERT_EQ(reversed[4], arr[arr_length - 5]);
	free(reversed);
}

void _test_pm_arr_sort_int() {
	int arr[] = { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };
	int* sorted = pm_arr_sort_int(arr, PM_ARR_LENGTH(arr)).data;
	PM_ASSERT_EQ(sorted[0], 1);
	PM_ASSERT_EQ(sorted[1], 2);
	PM_ASSERT_EQ(sorted[2], 3);
	PM_ASSERT_EQ(sorted[3], 4);
	PM_ASSERT_EQ(sorted[4], 5);
	PM_ASSERT_EQ(sorted[5], 6);
	PM_ASSERT_EQ(sorted[6], 7);
	PM_ASSERT_EQ(sorted[7], 8);
	PM_ASSERT_EQ(sorted[8], 9);
	PM_ASSERT_EQ(sorted[9], 10);
	free(sorted);
}

void _test_pm_arr_skip_int() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	size_t arr_length = PM_ARR_LENGTH(arr);

	size_t offset = 3;
	int* arr_with_offset = pm_arr_skip_int(arr, arr_length, offset).data;

	PM_ASSERT_EQ(arr_with_offset[0], arr[0 + offset]);
	PM_ASSERT_EQ(arr_with_offset[1], arr[1 + offset]);
	PM_ASSERT_EQ(arr_with_offset[2], arr[2 + offset]);
	PM_ASSERT_EQ(arr_with_offset[3], arr[3 + offset]);
	PM_ASSERT_EQ(arr_with_offset[4], arr[4 + offset]);
	PM_ASSERT_EQ(arr_with_offset[5], arr[5 + offset]);
	PM_ASSERT_EQ(arr_with_offset[6], arr[6 + offset]);

	free(arr_with_offset);
}

void _test_pm_arr_take_int() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	size_t take = 3;
	int* taken = pm_arr_take_int(arr, PM_ARR_LENGTH(arr), take).data;
	PM_ASSERT_EQ(taken[0], arr[0]);
	PM_ASSERT_EQ(taken[1], arr[1]);
	PM_ASSERT_EQ(taken[2], arr[2]);
	PM_ASSERT(taken[3] != arr[3]);
	free(taken);
}

void _test_pm_arr_to_string() {
	int arr[] = { 1, 2, 3, 4, 5 };
	char* arr_str = pm_arr_to_string(arr, PM_ARR_LENGTH(arr));
	PM_ASSERT_EQ_STR(arr_str, "{ 1, 2, 3, 4, 5 }");
	free(arr_str);
}

void test_arrays() {
	Test tests[] = {
		test(PM_NAMEOF(PM_ARR_LENGTH), _test_PM_ARR_LENGTH),
		test(PM_NAMEOF(pm_arr_alloc_int), _test_pm_arr_alloc_int),
		test(PM_NAMEOF(pm_arr_any_int), _test_pm_arr_any_int),
		test(PM_NAMEOF(pm_arr_concat_int), _test_pm_arr_concat_int),
		test(PM_NAMEOF(pm_arr_contains_int), _test_pm_arr_contains_int),
		test(PM_NAMEOF(pm_arr_count_int), _test_pm_arr_count_int),
		test(PM_NAMEOF(pm_arr_every_int), _test_pm_arr_every_int),
		test(PM_NAMEOF(pm_arr_filter_int), _test_pm_arr_filter_int),
		test(PM_NAMEOF(pm_arr_find_int), _test_pm_arr_find_int),
		test(PM_NAMEOF(pm_arr_find_index_int), _test_pm_arr_find_index_int),
		test(PM_NAMEOF(pm_arr_map_int), _test_pm_arr_map_int),
		test(PM_NAMEOF(pm_arr_reverse_int), _test_pm_arr_reverse_int),
		test(PM_NAMEOF(pm_arr_sort_int), _test_pm_arr_sort_int),
		test(PM_NAMEOF(pm_arr_skip_int), _test_pm_arr_skip_int),
		test(PM_NAMEOF(pm_arr_take_int), _test_pm_arr_take_int),
		test(PM_NAMEOF(pm_arr_to_string), _test_pm_arr_to_string),
	};

	TestSuite suite = test_suite("pim/arrays", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
