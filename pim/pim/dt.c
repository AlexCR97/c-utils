#include "dt.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int DT_YEAR_OFFSET  = 1900; // In the tm struct, the tm_year field represents the number of years since 1900. For example, if tm_year is 121, it refers to the year 2021 (1900 + 121). This was a design choice made to save space in the struct back when memory usage was a more critical concern.
const int DT_MONTH_OFFSET = 1;    // In the tm struct, the tm_mon field represents the month as an integer value from 0 to 11, where 0 corresponds to January and 11 corresponds to December.

DateTime dt(int year, int month, int date, int hour, int minute, int second) {
    DateTime dt;
    dt.year = year;
    dt.month = month;
    dt.date = date;
    dt.hour = hour;
    dt.minute = minute;
    dt.second = second;
    return dt;
}

DateTime dt_now() {
    time_t current_time = time(NULL);
    struct tm local_time;

    if (localtime_s(&local_time, &current_time) != 0) {
        // TODO Handle error here
    }

    int year = local_time.tm_year + DT_YEAR_OFFSET;
    int month = local_time.tm_mon + DT_MONTH_OFFSET;
    int date = local_time.tm_mday;
    int hour = local_time.tm_hour;
    int minute = local_time.tm_min;
    int second = local_time.tm_sec;

    return dt(year, month, date, hour, minute, second);
}

DateTime dt_now_utc() {
    time_t current_time = time(NULL);
    struct tm utc_time;

    if (gmtime_s(&utc_time, &current_time) != 0) {
        // TODO Handle error here
    }

    int year = utc_time.tm_year + DT_YEAR_OFFSET;
    int month = utc_time.tm_mon + DT_MONTH_OFFSET;
    int date = utc_time.tm_mday;
    int hour = utc_time.tm_hour;
    int minute = utc_time.tm_min;
    int second = utc_time.tm_sec;

    return dt(year, month, date, hour, minute, second);
}

char* dt_to_string(DateTime datetime) {
    // TODO What format should be used?
    // For now, the format is: YYYY-MM-DD@HH:MM:SS

    const int capacity = 20;
    char* str = (char*)malloc(capacity * sizeof(char));

    snprintf(
        str,
        capacity,
        "%04d-%02d-%02d@%02d:%02d:%02d",
        datetime.year, datetime.month, datetime.date,
        datetime.hour, datetime.minute, datetime.second);

    return str;
}
