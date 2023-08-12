#ifndef DT_H
#define DT_H

typedef struct {
    int year;
    int month;
    int date;

    // TODO Not supported for now
    //int day_of_week;

    // TODO Not supported for now
    //int day_of_year;

    int hour;
    int minute;
    int second;
} DateTime;

DateTime dt(int year, int month, int date, int hour, int minute, int second);
DateTime dt_now();
DateTime dt_now_utc();
char* dt_to_string(DateTime dt);

typedef enum {
    DT_TIME_ZONE_LOCAL,
    DT_TIME_ZONE_UTC,
} TimeZone;

#endif // DT_H
