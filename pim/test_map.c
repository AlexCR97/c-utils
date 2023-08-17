#include "test_map.h"

#include "pim/map.h"
#include "pim/test.h"

void _test_pm_map() {
	PmMap map = pm_map(PM_DATA_TYPE_STRING, PM_DATA_TYPE_INT, 10);
	PM_ASSERT_EQ(map.key_type, PM_DATA_TYPE_STRING);
	PM_ASSERT_EQ(map.value_type, PM_DATA_TYPE_INT);
	PM_ASSERT_EQ(map.length, 10);
	pm_map_dispose(&map);
}

void _test_pm_map_getset() {
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

void _test_pm_map_contains_key() {
	PmMap map = pm_map(PM_DATA_TYPE_STRING, PM_DATA_TYPE_INT, 10);
	pm_map_set(&map, "foo", 1);
	PM_ASSERT_EQ(pm_map_contains_key(map, "foo"), true);
	PM_ASSERT_EQ(pm_map_contains_key(map, "bar"), false);
	pm_map_dispose(&map);
}

void test_map() {
	Test tests[] = {
		test(PM_NAMEOF(pm_map), _test_pm_map),
		test("pm_map_getset", _test_pm_map_getset),
		test(PM_NAMEOF(pm_map_contains_key), _test_pm_map_contains_key),
	};

	TestSuite suite = test_suite("pim/map", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
