#include "test_map.h"

#include "pim/map.h"
#include "pim/strings.h"
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

void _test_pm_map_contains_value() {
	PmMap map = pm_map(PM_DATA_TYPE_STRING, PM_DATA_TYPE_INT, 10);
	pm_map_set(&map, "foo", 1);
	PM_ASSERT_EQ(pm_map_contains_value(map, 1), true);
	PM_ASSERT_EQ(pm_map_contains_value(map, 2), false);
	pm_map_dispose(&map);
}

void _test_pm_map_keys() {
	PmMap map = pm_map(PM_DATA_TYPE_STRING, PM_DATA_TYPE_INT, 10);
	pm_map_set(&map, "key1", 1);
	pm_map_set(&map, "key2", 2);
	pm_map_set(&map, "key3", 3);
	pm_map_set(&map, "key4", 4);
	pm_map_set(&map, "key5", 5);

	char** keys = pm_map_keys(map);
	char* key_at_0 = keys[0];
	char* key_at_1 = keys[1];
	char* key_at_2 = keys[2];
	char* key_at_3 = keys[3];
	char* key_at_4 = keys[4];

	PM_ASSERT(pm_str_equals(key_at_0, "key1") || pm_str_equals(key_at_0, "key2") || pm_str_equals(key_at_0, "key3") || pm_str_equals(key_at_0, "key4") || pm_str_equals(key_at_0, "key5"));
	PM_ASSERT(pm_str_equals(key_at_1, "key1") || pm_str_equals(key_at_1, "key2") || pm_str_equals(key_at_1, "key3") || pm_str_equals(key_at_1, "key4") || pm_str_equals(key_at_1, "key5"));
	PM_ASSERT(pm_str_equals(key_at_2, "key1") || pm_str_equals(key_at_2, "key2") || pm_str_equals(key_at_2, "key3") || pm_str_equals(key_at_2, "key4") || pm_str_equals(key_at_2, "key5"));
	PM_ASSERT(pm_str_equals(key_at_3, "key1") || pm_str_equals(key_at_3, "key2") || pm_str_equals(key_at_3, "key3") || pm_str_equals(key_at_3, "key4") || pm_str_equals(key_at_3, "key5"));
	PM_ASSERT(pm_str_equals(key_at_4, "key1") || pm_str_equals(key_at_4, "key2") || pm_str_equals(key_at_4, "key3") || pm_str_equals(key_at_4, "key4") || pm_str_equals(key_at_4, "key5"));

	pm_map_dispose(&map);
}

void _test_pm_map_remove() {
	PmMap map = pm_map(PM_DATA_TYPE_STRING, PM_DATA_TYPE_INT, 10);

	pm_map_set(&map, "foo", 1);
	PM_ASSERT_EQ(pm_map_contains_key(map, "foo"), true);

	pm_map_remove(&map, "foo");
	PM_ASSERT_EQ(pm_map_contains_key(map, "foo"), false);

	pm_map_dispose(&map);

}
void test_map() {
	Test tests[] = {
		test(PM_NAMEOF(pm_map), _test_pm_map),
		test("pm_map_getset", _test_pm_map_getset),
		test(PM_NAMEOF(pm_map_contains_key), _test_pm_map_contains_key),
		test(PM_NAMEOF(pm_map_contains_value), _test_pm_map_contains_value),
		test(PM_NAMEOF(pm_map_keys), _test_pm_map_keys),
		test(PM_NAMEOF(pm_map_remove), _test_pm_map_remove),
	};

	TestSuite suite = test_suite("pim/map", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
