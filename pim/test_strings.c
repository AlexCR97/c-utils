#include "test_strings.h"

#include <stddef.h>
#include "pim/strings.h"
#include "pim/test.h"

void _test_pm_str_equals() {
	char* a = "Foo bar!";
	char* b = "Foo bar!";
	bool are_equal_ab = pm_str_equals(a, b);
	PM_ASSERT_EQ(are_equal_ab, true);

	char* c = "foo bar!";
	char* d = "Foo Bar!";
	bool are_equal_cd = pm_str_equals(c, d);
	PM_ASSERT_EQ(are_equal_cd, false);
}

void _test_pm_str_split() {
	char* str = "this is a string\0";
	char** tokens = pm_str_split(str, ' ');
	PM_ASSERT_EQ_STR(tokens[0], "this");
	PM_ASSERT_EQ_STR(tokens[1], "is");
	PM_ASSERT_EQ_STR(tokens[2], "a");
	PM_ASSERT_EQ_STR(tokens[3], "string");
	free(tokens);
}

void test_strings() {
	Test tests[] = {
		test(PM_NAMEOF(pm_str_equals), _test_pm_str_equals),
		test(PM_NAMEOF(pm_str_split), _test_pm_str_split),
	};

	TestSuite suite = test_suite("pim/strings", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
