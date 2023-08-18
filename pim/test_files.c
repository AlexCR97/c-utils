#include "test_files.h"

#include <stddef.h>
#include "pim/files.h"
#include "pim/test.h"

void _test_pm_fs_read_lines() {
	const char* file = "C:\\Projects\\Visual Studio C\\vxlibs\\pim\\_test_pm_fs_read_lines.txt";
	char** lines = pm_fs_read_lines(file);
	PM_ASSERT(lines != NULL);
	PM_ASSERT_EQ_STR(lines[0], "This is line 1");
	PM_ASSERT_EQ_STR(lines[1], "This is line 2");
	PM_ASSERT_EQ_STR(lines[2], "This is line 3");
	free(lines[0]);
	free(lines[1]);
	free(lines[2]);
	free(lines);
}

void _test_pm_fs_read_text() {
	const char* file = "C:\\Projects\\Visual Studio C\\vxlibs\\pim\\_test_pm_fs_read_text.txt";
	char* text = pm_fs_read_text(file);
	PM_ASSERT(text != NULL);
	PM_ASSERT_EQ_STR(text, "Hello, World!");
	free(text);
}

void test_files() {
	Test tests[] = {
		test(PM_NAMEOF(pm_fs_read_lines), _test_pm_fs_read_lines),
		test(PM_NAMEOF(pm_fs_read_text), _test_pm_fs_read_text),
	};

	TestSuite suite = test_suite("pim/maybe", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
