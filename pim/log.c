#include "log.h"

// Resources:
// https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix

#include <stdio.h>
#include "arr.h"
#include "str_string.h"

#define LOG_COLOR_DEFAULT "\x1B[0m"
#define LOG_COLOR_RED     "\x1B[31m"
#define LOG_COLOR_GREEN   "\x1B[32m"
#define LOG_COLOR_YELLOW  "\x1B[33m"
#define LOG_COLOR_CYAN    "\x1B[36m"
#define LOG_COLOR_MAGENTA "\x1B[35m"

LogLevel GLOBAL_LEVEL = LOG_LEVEL_DEBUG;

void log_level_set(LogLevel level) {
	GLOBAL_LEVEL = level;
}

LogLevel log_level_get() {
	return GLOBAL_LEVEL;
}

Logger logger(LogLevel level, const char* category) {
	Logger log;
	log.level = level;
	log.category = category;
	log.show_timestamp = true;
	log.show_level = true;
	log.show_category = true;
	log.show_file = true;
	return log;
}

bool _can_log(LogLevel level) {
	return level >= GLOBAL_LEVEL;
}

DateTime _get_now(Logger log) {
	if (log.timestamp_timezone == DT_TIME_ZONE_LOCAL) {
		return dt_now();
	}

	if (log.timestamp_timezone == DT_TIME_ZONE_UTC) {
		return dt_now_utc();
	}

	return dt_now();
}

const char* _log_level_to_color(LogLevel level) {
	if (level == LOG_LEVEL_DEBUG) {
		return LOG_COLOR_GREEN;
	}

	if (level == LOG_LEVEL_INFO) {
		return LOG_COLOR_CYAN;
	}

	if (level == LOG_LEVEL_WARNING) {
		return LOG_COLOR_YELLOW;
	}

	if (level == LOG_LEVEL_ERROR) {
		return LOG_COLOR_RED;
	}

	return LOG_COLOR_DEFAULT;
}

const char* _log_level_to_string(LogLevel level) {
	if (level == LOG_LEVEL_DEBUG) {
		return "DEBUG";
	}

	if (level == LOG_LEVEL_INFO) {
		return "INFO";
	}

	if (level == LOG_LEVEL_WARNING) {
		return "WARNING";
	}

	if (level == LOG_LEVEL_ERROR) {
		return "ERROR";
	}

	return NULL;
}

void logger_log(Logger log, LogLevel level, const char* file, int line, const char* format, ...) {
	if (!_can_log(level)) {
		return;
	}

	if (log.show_timestamp) {
		DateTime now = _get_now(log);
		char* timestamp = dt_to_string(now);
		printf(timestamp);
		printf(" ");
	}

	if (log.show_level) {
		printf(_log_level_to_color(level));
		printf(_log_level_to_string(level));
		printf(LOG_COLOR_DEFAULT);
		printf(" ");
	}

	if (log.show_category && log.category != NULL) {
		printf(LOG_COLOR_MAGENTA);
		printf(log.category);
		printf(LOG_COLOR_DEFAULT);
	}

	if (log.show_file) {
		const char* file_absolute_path = file;
		const char** file_absolute_path_parts = str_split(file_absolute_path, '\\');
		const char* file_name = arr_tail_str(file_absolute_path_parts);

		printf("(");
		printf(LOG_COLOR_MAGENTA);
		printf(file_name);
		printf("@");
		printf(str_to_string(line));
		printf(LOG_COLOR_DEFAULT);
		printf(") ");
	}

	va_list args; // Declare a va_list to hold the variadic arguments
	va_start(args, format); // Initialize va_list with the last named argument

	if (level == LOG_LEVEL_WARNING || level == LOG_LEVEL_ERROR) {
		printf(_log_level_to_color(level));
	}

	vprintf(format, args);  // Use vprintf to print with the va_list
	va_end(args);  // Clean up the va_list
	printf(LOG_COLOR_DEFAULT);
	printf("\n");
}
