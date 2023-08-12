#include <stdio.h>
#include "arr.h"
#include "str_string.h"
#include "str_string_builder.h"

void arr_foreach(int* arr, size_t size, IntFunction func) {
    for (size_t i = 0; i < size; i++) {
        func(arr[i]);
    }
}

char* arr_tail_str(char** arr) {
    if (arr == NULL || *arr == NULL) {
        return NULL;  // Return NULL if the input is invalid or the array is empty
    }

    // Traverse the array to find the last non-null element
    char** current = arr;
    while (*current != NULL) {
        current++;
    }

    // The pointer at 'current' points to the first NULL element, so we decrement it to get the last non-null element
    current--;

    return *current;
}

char* arr_to_string(int* arr, size_t size)
{
    StringBuilder sb = string_builder();
    string_builder_append(&sb, ARR_DELIMETER_HEAD);
    string_builder_append(&sb, " ");

    for (size_t i = 0; i < size; i++) {
        string_builder_append(&sb, str_to_string(arr[i]));

        if (i != size - 1) {
            string_builder_append(&sb, ", ");
        } else {
            string_builder_append(&sb, " ");
        }
    }

    string_builder_append(&sb, ARR_DELIMETER_TAIL);

    return string_builder_to_string(sb);
}
