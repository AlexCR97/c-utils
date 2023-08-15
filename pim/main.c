#include "pim/arrays.h"
#include "pim/cns.h"
#include "pim/ds_list.h"
#include "pim/errors.h"
#include "pim/log.h"
#include "pim/maybe.h"
#include "pim/strings.h"
#include "pim/str_string_builder.h"
#include "pim/test.h"
#include "test_arrays.h"

//int* _increment_by_index(size_t index, int* item) {
//	int* result = malloc(sizeof(int));
//	*result = *item + index;
//	return result;
//}
//
//void test_arr_map() {
//	Logger log = logger(LOG_LEVEL_DEBUG, "test_arr_map");
//
//	int nums[] = { 1, 2, 3, 4, 5 };
//	const int nums_length = PM_ARR_LENGTH(nums);
//
//	LOGGER_DEBUG(log, "Nums:");
//	LOGGER_DEBUG(log, pm_arr_to_string(nums, nums_length));
//
//	int* mapped_nums = pm_arr_map(nums, sizeof(int), nums_length, _increment_by_index);
//	LOGGER_DEBUG(log, "Mapped nums:");
//	LOGGER_DEBUG(log, pm_arr_to_string(mapped_nums, nums_length));
//}

void test_ds_list() {
	List my_list = list();
	list_push(&my_list, 1);
	list_push(&my_list, 2);
	list_push(&my_list, 3);
	printf("list: %s\n", list_to_string(my_list));
}

void test_err() {
	Logger log = logger(LOG_LEVEL_DEBUG, "test_err");
	PmError err = pm_error(NULL, NULL, NULL);
	LOGGER_WARNING(log, pm_error_to_string(err));
	LOGGER_ERROR(log, pm_error_to_string(err));
}

void test_logger() {
	//log_level_set(LOG_LEVEL_DEBUG);
	//log_level_set(LOG_LEVEL_INFO);
	//log_level_set(LOG_LEVEL_WARNING);
	//log_level_set(LOG_LEVEL_ERROR);

	printf("Logs with local time:\n");
	Logger local_time_logger = logger(LOG_LEVEL_DEBUG, "Local");
	LOGGER_DEBUG(local_time_logger, "This is a debug message");
	LOGGER_INFO(local_time_logger, "This is an info message");
	LOGGER_WARNING(local_time_logger, "This is a warning message");
	LOGGER_ERROR(local_time_logger, "This is an error message");

	printf("\n");

	printf("Logs with utc time:\n");
	Logger utc_time_logger = logger(LOG_LEVEL_DEBUG, "UTC");
	utc_time_logger.timestamp_timezone = DT_TIME_ZONE_UTC;
	LOGGER_DEBUG(utc_time_logger, "This is a debug message");
	LOGGER_INFO(utc_time_logger, "This is an info message");
	LOGGER_WARNING(utc_time_logger, "This is a warning message");
	LOGGER_ERROR(utc_time_logger, "This is an error message");

	printf("\n");

	printf("Simple logs:\n");
	Logger simple_logger = logger(LOG_LEVEL_DEBUG, NULL);
	simple_logger.show_category = false;
	simple_logger.show_file = false;
	simple_logger.show_level = false;
	simple_logger.show_timestamp = false;
	LOGGER_DEBUG(simple_logger, "Hello, %s", "World!");
	LOGGER_DEBUG(simple_logger, "%d %c %d %c %s", 1, '+', 2, '=', pm_str_to_string_int(3));
}

void test_str_to_string() {
	int number = 12345;
	char* string = pm_str_to_string_int(number);
	printf("number: %i\n", number);
	printf("string: %s\n", string);
}

void test_string_builder() {
	StringBuilder sb = string_builder();
	string_builder_append(&sb, "Hello, ");
	string_builder_append(&sb, "world!");
	string_builder_append(&sb, "\n");
	string_builder_append(&sb, "This is a new line.");
	printf("%s\n", string_builder_to_string(sb));
	string_builder_dispose(&sb);

	sb = string_builder();
	string_builder_append(&sb, "After dispose: ");
	string_builder_append(&sb, "New content!");
	printf("%s\n", string_builder_to_string(sb));
}

int main() {
	test_arrays();
	test_maybe();

	/*Test tests[] = {
		test("Test 1", _test_1),
		test("Test 2", _test_2),
	};
	TestSuite suite = test_suite("My Test Suite", tests);
	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));

	Test tests2[] = {
		test("Test 3", _test_3),
		test("Test 4", _test_4),
	};
	TestSuite suite2 = test_suite("My Test Suite 2", tests2);
	test_suite_run(suite2, sizeof(tests2) / sizeof(tests2[0]));*/

	//test_arr_map();
	//test_ds_list();
	//test_err();
	//test_logger();
	//test_maybe_2();
	//test_str_to_string();
	//test_string_builder();

	return 0;
}
