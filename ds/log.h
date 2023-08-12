#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdbool.h>
#include "dt.h"

typedef enum LogLevel {
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR,
} LogLevel;

typedef struct Logger {
	LogLevel level;
	const char* category;

	bool show_timestamp;
	TimeZone timestamp_timezone;

	bool show_level;
	bool show_category;
	bool show_file;
} Logger;

void log_level_set(LogLevel level);
LogLevel log_level_get();

Logger logger(LogLevel level, const char* category);
void logger_log(Logger log, LogLevel level, const char* file, int line, const char* format, ...);

#define LOGGER_DEBUG(log, format, ...) logger_log(log, LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOGGER_INFO(log, format, ...) logger_log(log, LOG_LEVEL_INFO, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOGGER_WARNING(log, format, ...) logger_log(log, LOG_LEVEL_WARNING, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOGGER_ERROR(log, format, ...) logger_log(log, LOG_LEVEL_ERROR, __FILE__, __LINE__, format, __VA_ARGS__)

#endif // LOG_H
