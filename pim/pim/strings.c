#include "strings.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// <summary>
/// A character that represents the end of a string.
/// Strings should always end with this character. The purpose is to distinguish the
/// end of a string and to allow string manipulation functions to work properly.
/// </summary>
const char _PM_STR_NULL_TERMINATOR = '\0';
const int _PM_STR_NULL_TERMINATOR_OFFSET = 1;

bool pm_str_equals(char* a, char* b) {
    const int difference = strcmp(a, b);
    return difference == 0;
}

PmMaybeArrStr pm_str_split(const char* str, char split_by) {
    // Count the number of occurrences of the split character
    int count = 0;
    const char* ptr = str;
    while (*ptr != '\0') {
        if (*ptr == split_by) {
            count++;
        }
        ptr++;
    }

    // Allocate memory for an array of pointers
    // TODO allocate with pm_arr_alloc_str
    char** result = (char**)malloc((count + 2) * sizeof(char*));  // +2 to account for the strings and a NULL terminator

    if (result == NULL) {
        return pm_maybe_raise_arrstr(pm_error(PM_ERR_ALLOCATION_FAILED, NULL, NULL));
    }

    // Split the input string
    int index = 0;
    ptr = str;
    while (*ptr != '\0') {
        const char* start = ptr;
        while (*ptr != split_by && *ptr != '\0') {
            ptr++;
        }

        int length = ptr - start;

        // TODO allocate with pm_str_alloc
        result[index] = (char*)malloc((length + 1) * sizeof(char));

        if (result[index] == NULL) {
            return pm_maybe_raise_arrstr(pm_error(PM_ERR_ALLOCATION_FAILED, NULL, NULL));
        }

        strncpy_s(result[index], length + 1, start, length);
        result[index][length] = '\0';
        index++;

        if (*ptr == '\0') {
            break;
        }

        ptr++;  // Skip the split character
    }

    // TODO use null terminator here?
    result[index] = NULL; // Null-terminate the array

    return pm_maybe_arrstr(result);
}

PmMaybeStr pm_str_to_lower(const char* str) {
    if (str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_NULL_ARGUMENT, NULL, NULL));
    }

    size_t len = strlen(str);

    // TODO allocate with pm_str_alloc
    char* lower_str = (char*)malloc(len + _PM_STR_NULL_TERMINATOR_OFFSET);

    if (lower_str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_ALLOCATION_FAILED, NULL, NULL));
    }

    for (size_t i = 0; i < len; i++) {
        lower_str[i] = tolower(str[i]);
    }

    lower_str[len] = _PM_STR_NULL_TERMINATOR;

    return pm_maybe_str(lower_str);
}

PmMaybeStr pm_str_to_string_int(int num) {
    int length = snprintf(NULL, 0, "%d", num);
    
    // TODO allocate with pm_str_alloc
    char* str = (char*)malloc((length + _PM_STR_NULL_TERMINATOR_OFFSET) * sizeof(char));

    snprintf(str, length + _PM_STR_NULL_TERMINATOR_OFFSET, "%d", num);

    return pm_maybe_str(str);
}

PmMaybeStr pm_str_trim_trailing(const char* str, char trim) {
    if (str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_NULL_ARGUMENT, NULL, NULL));
    }

    size_t len = strlen(str);
    size_t end = len;

    while (end > 0 && str[end - 1] == trim) {
        end--;
    }

    // TODO allocate with pm_str_alloc
    char* trimmed = (char*)malloc(end + _PM_STR_NULL_TERMINATOR_OFFSET);

    if (trimmed != NULL) {
        strncpy_s(trimmed, end + _PM_STR_NULL_TERMINATOR_OFFSET, str, end);
        trimmed[end] = _PM_STR_NULL_TERMINATOR;
    }

    return pm_maybe_str(trimmed);
}
