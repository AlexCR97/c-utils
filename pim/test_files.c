#include "test_files.h"

#include <stddef.h>
#include "pim/files.h"
#include "pim/test.h"

void _test_pm_fs_read_text() {
	const char* file = "C:\\Projects\\Visual Studio C\\vxlibs\\pim\\_test_pm_fs_read_text.txt";
	char* text = pm_fs_read_text(file);
	PM_ASSERT(text != NULL);
	PM_ASSERT_EQ_STR(text, "Hello, World!");
	free(text);
}

void test_files() {
	Test tests[] = {
		test(PM_NAMEOF(pm_fs_read_text), _test_pm_fs_read_text),
	};

	TestSuite suite = test_suite("pim/maybe", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
