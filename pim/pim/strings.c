#include "strings.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrays.h"

/// <summary>
/// A character that represents the end of a string.
/// Strings should always end with this character. The purpose is to distinguish the
/// end of a string and to allow string manipulation functions to work properly.
/// </summary>
const char _PM_STR_NULL_TERMINATOR = '\0';
const int _PM_STR_NULL_TERMINATOR_OFFSET = 1;

PmMaybeStr pm_str_alloc(size_t length) {
    char* str = (char*)malloc((length + _PM_STR_NULL_TERMINATOR_OFFSET) * sizeof(char));

    if (str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_ALLOCATION_FAILED, NULL, NULL));
    }

    return pm_maybe_str(str);
}

bool pm_str_contains(const char* str, const char* substring) {
    if (str == NULL || substring == NULL) {
        return false; // TODO How to handle NULL args?
    }

    size_t str_len = strlen(str);
    size_t substr_len = strlen(substring);

    if (substr_len > str_len) {
        return false; // TODO How to handle substring greater than string?
    }

    for (size_t i = 0; i <= str_len - substr_len; i++) {
        bool found = true;

        for (size_t j = 0; j < substr_len; j++) {
            if (str[i + j] != substring[j]) {
                found = false;
                break;
            }
        }

        if (found) {
            return true;
        }
    }

    return false;
}

bool pm_str_equals(char* a, char* b) {
    const int difference = strcmp(a, b);
    return difference == 0;
}

PmMaybeStr pm_str_pad_start(const char* str, char pad, int amount) {
    if (str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_NULL_ARGUMENT, NULL, NULL));
    }

    if (amount <= 0) {
        return pm_maybe_raise_str(pm_error(PM_ERR_INVALID_ARGUMENT, "The amount must be greater than 0", NULL));
    }

    int str_len = strlen(str);
    int new_str_len = str_len + amount;
    
    PmMaybeStr maybe_str = pm_str_alloc(new_str_len);

    if (maybe_str.raised_error) {
        return maybe_str;
    }

    char* new_str = maybe_str.data;

    for (int i = 0; i < amount; i++) {
        new_str[i] = pad;
    }

    strcpy_s(new_str + amount, new_str_len - amount + _PM_STR_NULL_TERMINATOR_OFFSET, str);

    new_str[new_str_len] = _PM_STR_NULL_TERMINATOR;

    return pm_maybe_str(new_str);
}

PmMaybeStr pm_str_pad_end(const char* str, char pad, int amount) {
    if (str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_NULL_ARGUMENT, NULL, NULL));
    }

    if (amount <= 0) {
        return pm_maybe_raise_str(pm_error(PM_ERR_INVALID_ARGUMENT, "The amount must be greater than 0", NULL));
    }

    int str_len = strlen(str);
    int new_str_len = str_len + amount;

    PmMaybeStr maybe_str = pm_str_alloc(new_str_len);

    if (maybe_str.raised_error) {
        return maybe_str;
    }

    char* new_str = maybe_str.data;

    strcpy_s(new_str, new_str_len + _PM_STR_NULL_TERMINATOR_OFFSET, str);

    for (int i = str_len; i < new_str_len; i++) {
        new_str[i] = pad;
    }

    new_str[new_str_len] = _PM_STR_NULL_TERMINATOR;

    return pm_maybe_str(new_str);
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
    PmMaybeArrStr maybe_result = pm_arr_alloc_str(count);

    if (maybe_result.raised_error) {
        return maybe_result;
    }

    // TODO allocate with pm_arr_alloc_str
    char** result = maybe_result.data;

    // Split the input string
    int index = 0;
    ptr = str;
    while (*ptr != '\0') {
        const char* start = ptr;
        while (*ptr != split_by && *ptr != '\0') {
            ptr++;
        }

        int length = ptr - start;

        PmMaybeStr maybe_str = pm_str_alloc(length);

        if (maybe_str.raised_error) {
            return pm_maybe_raise_arrstr(maybe_str.error);
        }

        result[index] = maybe_str.data;

        strncpy_s(result[index], length + 1, start, length);
        result[index][length] = '\0';
        index++;

        if (*ptr == '\0') {
            break;
        }

        ptr++; // Skip the split character
    }

    result[index] = _PM_STR_NULL_TERMINATOR;

    return pm_maybe_arrstr(result);
}

PmMaybeStr pm_str_to_lower(const char* str) {
    if (str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_NULL_ARGUMENT, NULL, NULL));
    }

    size_t len = strlen(str);
    PmMaybeStr maybe_lower_str = pm_str_alloc(len);

    if (maybe_lower_str.raised_error) {
        return maybe_lower_str;
    }

    char* lower_str = maybe_lower_str.data;

    if (lower_str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_ALLOCATION_FAILED, NULL, NULL));
    }

    for (size_t i = 0; i < len; i++) {
        lower_str[i] = tolower(str[i]);
    }

    lower_str[len] = _PM_STR_NULL_TERMINATOR;

    return pm_maybe_str(lower_str);
}

PmMaybeStr pm_str_to_upper(const char* str) {
    if (str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_NULL_ARGUMENT, NULL, NULL));
    }

    size_t len = strlen(str);
    PmMaybeStr maybe_str = pm_str_alloc(len);

    if (maybe_str.raised_error) {
        return maybe_str;
    }

    char* upper_str = maybe_str.data;

    if (upper_str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_ALLOCATION_FAILED, NULL, NULL));
    }

    for (size_t i = 0; i < len; i++) {
        upper_str[i] = toupper(str[i]);
    }

    upper_str[len] = _PM_STR_NULL_TERMINATOR;

    return pm_maybe_str(upper_str);
}

PmMaybeStr pm_str_to_string_int(int num) {
    int length = snprintf(NULL, 0, "%d", num);
    
    PmMaybeStr maybe_str = pm_str_alloc(length);

    if (maybe_str.raised_error) {
        return maybe_str;
    }

    char* str = maybe_str.data;

    snprintf(str, length + _PM_STR_NULL_TERMINATOR_OFFSET, "%d", num);

    return pm_maybe_str(str);
}

PmMaybeStr pm_str_trim_leading(const char* str, char trim) {
    if (str == NULL) {
        return pm_maybe_raise_str(pm_error(PM_ERR_NULL_ARGUMENT, NULL, NULL));
    }

    size_t len = strlen(str);
    size_t start = 0;

    while (start < len && str[start] == trim) {
        start++;
    }

    size_t trimmed_len = len - start;
    PmMaybeStr maybe_trimmed = pm_str_alloc(trimmed_len);

    if (maybe_trimmed.raised_error) {
        return maybe_trimmed;
    }

    char* trimmed = maybe_trimmed.data;

    strncpy_s(trimmed, trimmed_len + _PM_STR_NULL_TERMINATOR_OFFSET, str + start, trimmed_len);
    trimmed[trimmed_len] = _PM_STR_NULL_TERMINATOR;

    return pm_maybe_str(trimmed);
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

    PmMaybeStr maybe_trimmed = pm_str_alloc(end);

    if (maybe_trimmed.raised_error) {
        return maybe_trimmed;
    }

    char* trimmed = maybe_trimmed.data;

    strncpy_s(trimmed, end + _PM_STR_NULL_TERMINATOR_OFFSET, str, end);
    trimmed[end] = _PM_STR_NULL_TERMINATOR;

    return pm_maybe_str(trimmed);
}
