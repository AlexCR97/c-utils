#include "arr.h"
#include "cns.h"
#include "ds_list.h"
#include "err.h"
#include "log.h"
#include "maybe.h"
#include "str_string.h"
#include "str_string_builder.h"

void _print_square(int num) {
	printf("%d^2 = %d\n", num, num * num);
}

void test_arr_foreach() {
	int arr[] = { 1, 2, 3, 4, 5 };
	size_t arr_length = ARR_LENGTH(arr);

	printf("Original array:\n");
	printf("%s\n\n", arr_to_string(arr, arr_length));

	printf("Squared array:\n");
	arr_foreach(arr, arr_length, _print_square);
}

int* _increment_by_index(size_t index, int* item) {
	int* result = malloc(sizeof(int));
	*result = *item + index;
	return result;
}

void test_arr_map() {
	Logger log = logger(LOG_LEVEL_DEBUG, "test_arr_map");

	int nums[] = { 1, 2, 3, 4, 5 };
	const int nums_length = ARR_LENGTH(nums);

	LOGGER_DEBUG(log, "Nums:");
	LOGGER_DEBUG(log, arr_to_string(nums, nums_length));

	int* mapped_nums = arr_map(nums, sizeof(int), nums_length, _increment_by_index);
	LOGGER_DEBUG(log, "Mapped nums:");
	LOGGER_DEBUG(log, arr_to_string(mapped_nums, nums_length));
}

void test_ds_list() {
	List my_list = list();
	list_push(&my_list, 1);
	list_push(&my_list, 2);
	list_push(&my_list, 3);
	printf("list: %s\n", list_to_string(my_list));
}

void test_err() {
	Logger log = logger(LOG_LEVEL_DEBUG, "test_err");
	Error err = error(NULL, NULL, NULL);
	LOGGER_WARNING(log, error_to_string(err));
	LOGGER_ERROR(log, error_to_string(err));
}

MaybeI _divide(int a, int b) {
	if (b == 0) {
		const Error err = error(ERR_DIVISION_BY_ZERO, "Cannot divide by zero", NULL);
		return maybe_i_error(&err);
	}

	return maybe_i_success(a / b);
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
	LOGGER_DEBUG(simple_logger, "%d %c %d %c %s", 1, '+', 2, '=', str_to_string(3));
}

void test_maybe() {
	const int a = 100;
	const int b = 0;
	MaybeI maybe_division = _divide(a, b);

	if (maybe_i_failed(maybe_division)) {
		printf(error_to_string(*maybe_division.error));
	} else {
		printf("%d / %d = %d\n", a, b, maybe_division.data);
	}
}

Maybe _input_favorite_programming_lang() {
	const int input_capacity = 10;
	Maybe maybe_input = cns_prompt("What's your favorite programming language?\n > ", input_capacity);

	if (maybe_failed(maybe_input)) {
		return maybe_error(maybe_input.error);
	}

	char* input = (char*)maybe_input.data;
	input = str_to_lower(input);

	if (!str_equals(input, "c")) {
		const Error err = error("invalid_programming_lang", "Nope! You must answer \"C\"", NULL);
		return maybe_error(&err);
	}
	
	return maybe_success(input);
}

void test_maybe_2() {
	Maybe maybe_answer = _input_favorite_programming_lang();

	if (maybe_failed(maybe_answer)) {
		printf("%s\n", error_to_string(*maybe_answer.error));
	}
	else {
		printf("That's right, that's the only correct answer.\n");
	}
}

void test_str_to_string() {
	int number = 12345;
	char* string = str_to_string(number);
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
	//test_arr_foreach();
	test_arr_map();
	//test_ds_list();
	//test_err();
	//test_logger();
	//test_maybe();
	//test_maybe_2();
	//test_str_to_string();
	//test_string_builder();
	return 0;
}