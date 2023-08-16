#include "test_list.h"

#include <stddef.h>
#include "pim/list.h"
#include "pim/test.h"

void _test_pm_list() {
	PmListInt list = pm_list();
	pm_list_push(&list, 1);
	pm_list_push(&list, 2);
	pm_list_push(&list, 3);

	PM_ASSERT_EQ(list.head->data, 1);
	PM_ASSERT_EQ(list.head->next->data, 2);
	PM_ASSERT_EQ(list.head->next->next->data, 3);

	pm_list_dispose(&list);
	PM_ASSERT(list.head == NULL);
}

void test_list() {
	Test tests[] = {
		test(PM_NAMEOF(pm_list), _test_pm_list),
	};

	TestSuite suite = test_suite("pim/list", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
