#include "pim/errors.h"
#include "pim/list.h"
#include "pim/log.h"
#include "pim/strings.h"
#include "pim/test.h"
#include "test_arrays.h"
#include "test_maybe.h"
#include "test_strings.h"

void test_ds_list() {
	PmListInt my_list = pm_list();
	pm_list_push(&my_list, 1);
	pm_list_push(&my_list, 2);
	pm_list_push(&my_list, 3);
	printf("list: %s\n", pm_list_to_string(my_list));
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
	LOGGER_DEBUG(simple_logger, "%d %c %d %c %s", 1, '+', 2, '=', pm_str_to_string_int(3).data);
}

int main() {
	test_arrays();
	test_maybe();
	test_strings();

	//test_ds_list();
	//test_err();
	//test_logger();

	return 0;
}
