#ifndef STR_STRING_H
#define STR_STRING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_NULL_TERMINATOR_OFFSET 1

bool str_equals(const char* a, const char* b);
char** str_split(const char* str, char split_by);
char* str_to_lower(const char* str);
char* str_to_string(int num);
char* str_trim_trailing(const char* str, char trim);

#endif // STR_STRING_H
