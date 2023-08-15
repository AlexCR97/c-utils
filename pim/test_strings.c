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
	char** tokens = pm_str_split(str, ' ').data;
	PM_ASSERT_EQ_STR(tokens[0], "this");
	PM_ASSERT_EQ_STR(tokens[1], "is");
	PM_ASSERT_EQ_STR(tokens[2], "a");
	PM_ASSERT_EQ_STR(tokens[3], "string");

	free(tokens[0]);
	free(tokens[1]);
	free(tokens[2]);
	free(tokens[3]);
	free(tokens);
}

void _test_pm_str_to_lower() {
	char* str = "This Is A String Used For Testing\0";
	char* str_lower = pm_str_to_lower(str).data;
	PM_ASSERT_EQ_STR(str_lower, "this is a string used for testing");
	free(str_lower);
}

void _test_pm_str_to_string_int() {
	int num = 1972;
	char* num_str = pm_str_to_string_int(num).data;
	PM_ASSERT_EQ_STR(num_str, "1972");
	free(num_str);
}

void _test_pm_str_trim_trailing() {
	char* str = "string with leading whitespaces    \0";
	char* str_trimmed = pm_str_trim_trailing(str, ' ').data;
	PM_ASSERT_EQ_STR(str_trimmed, "string with leading whitespaces");
	free(str_trimmed);
}

void test_strings() {
	Test tests[] = {
		test(PM_NAMEOF(pm_str_equals), _test_pm_str_equals),
		test(PM_NAMEOF(pm_str_split), _test_pm_str_split),
		test(PM_NAMEOF(pm_str_to_lower), _test_pm_str_to_lower),
		test(PM_NAMEOF(pm_str_to_string_int), _test_pm_str_to_string_int),
		test(PM_NAMEOF(pm_str_trim_trailing), _test_pm_str_trim_trailing),
	};

	TestSuite suite = test_suite("pim/strings", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
