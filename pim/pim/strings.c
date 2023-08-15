#include "strings.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool str_equals(char* a, char* b) {
    const int difference = strcmp(a, b);
    return difference == 0;
}

char** str_split(const char* str, char split_by) {
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
    char** result = (char**)malloc((count + 2) * sizeof(char*));  // +2 to account for the strings and a NULL terminator
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
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
        result[index] = (char*)malloc((length + 1) * sizeof(char));
        if (result[index] == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        //strncpy(result[index], start, length);
        strncpy_s(result[index], length + 1, start, length);
        result[index][length] = '\0';
        index++;

        if (*ptr == '\0') {
            break;
        }
        ptr++;  // Skip the split character
    }

    result[index] = NULL;  // Null-terminate the array

    return result;
}

char* str_to_lower(const char* str) {
    if (str == NULL) {
        return NULL; // Handle NULL input gracefully
    }

    size_t len = strlen(str);
    char* lower_str = (char*)malloc(len + 1); // +1 for null terminator

    if (lower_str != NULL) {
        for (size_t i = 0; i < len; i++) {
            lower_str[i] = tolower(str[i]);
        }
        lower_str[len] = '\0'; // Null-terminate the new string
    }

    return lower_str;
}

char* str_to_string(int num) {
    int length = snprintf(NULL, 0, "%d", num);
    char* str = (char*)malloc((length + 1) * sizeof(char)); // +1 for null terminator
    snprintf(str, length + 1, "%d", num);
    return str;
}

char* str_trim_trailing(const char* str, char trim) {
    if (str == NULL) {
        return NULL; // Handle NULL input gracefully
    }

    size_t len = strlen(str);
    size_t end = len;

    while (end > 0 && str[end - 1] == trim) {
        end--;
    }

    char* trimmed = (char*)malloc(end + 1); // +1 for null terminator

    if (trimmed != NULL) {
        strncpy_s(trimmed, end + 1, str, end);
        trimmed[end] = '\0'; // Null-terminate the trimmed string
    }

    return trimmed;
}
