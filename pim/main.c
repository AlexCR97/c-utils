#include "pim/errors.h"
#include "pim/hashmap.h"
#include "pim/log.h"
#include "pim/strings.h"
#include "pim/test.h"
#include "test_arrays.h"
#include "test_list.h"
#include "test_maybe.h"
#include "test_strings.h"

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

void test_hashmap() {
	size_t customSize = 20; // Custom hashmap size
	Hashmap* map = createHashmap(customSize);

	map->keyDataType = STRING_KEY; // Set the key data type

	char key1[] = "key1";
	int value1 = 100;
	insert(&map, key1, &value1);

	char key2[] = "key2";
	double value2 = 3.14;
	insert(&map, key2, &value2);

	int* result1 = (int*)get(&map, key1);
	if (result1) {
		printf("Value for key1: %d\n", *result1);
	}
	else {
		printf("Key1 not found\n");
	}

	double* result2 = (double*)get(&map, key2);
	if (result2) {
		printf("Value for key2: %lf\n", *result2);
	}
	else {
		printf("Key2 not found\n");
	}

	cleanup(&map);
}

int main() {
	//test_arrays();
	test_hashmap();
	//test_list();
	//test_maybe();
	//test_strings();

	//test_err();
	//test_logger();

	return 0;
}
