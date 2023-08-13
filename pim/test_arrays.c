#include "test_arrays.h"

#include "pim/arr.h"
#include "pim/test.h"

void _test_ARR_LENGTH() {
	int arr[] = { 1, 2, 3, 4, 5 };
	int length = ARR_LENGTH(arr);
	PM_ASSERT_EQ(length, 5);
}

void test_arrays() {
	Test tests[] = {
		test("ARR_LENGTH", _test_ARR_LENGTH),
	};

	TestSuite suite = test_suite("Arrays", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
