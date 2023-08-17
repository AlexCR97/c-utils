#include "test_map.h"

#include "pim/map.h"
#include "pim/test.h"

void _test_pm_map() {
	PmMap map = pm_map(PM_DATA_TYPE_STRING, PM_DATA_TYPE_INT, 10);
	pm_map_set(&map, "key1", 1);
	pm_map_set(&map, "key2", 2);
	pm_map_set(&map, "key3", 3);
	PM_ASSERT_EQ(pm_map_get(map, "key1"), 1);
	PM_ASSERT_EQ(pm_map_get(map, "key2"), 2);
	PM_ASSERT_EQ(pm_map_get(map, "key3"), 3);
	PM_ASSERT(pm_map_get(map, "key4") == NULL);
	pm_map_dispose(&map);
}

void test_map() {
	Test tests[] = {
		test(PM_NAMEOF(pm_map), _test_pm_map),
	};

	TestSuite suite = test_suite("pim/map", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
