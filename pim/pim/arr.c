#include "arr.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "str_string.h"
#include "str_string_builder.h"

const int _ARR_DEFAULT_INT = 0;

int* arr_alloc_int(size_t length) {
    int* arr = (int*)malloc(sizeof(int) * length);

    if (arr == NULL) {
        // TODO How to handle NULL?
        return NULL;
    }

    arr[0] = _ARR_DEFAULT_INT;

    return arr;
}

bool arr_any_int(int arr[], size_t arr_length, AnyFunctionInt predicate) {
    // TODO Is there a way to improve performance?

    for (size_t i = 0; i < arr_length; i++) {
        bool result = predicate(i, arr[i]);

        if (result) {
            return true;
        }
    }

    return false;
}

int* arr_concat_int(int arr_a[], size_t arr_a_length, int arr_b[], size_t arr_b_length) {
    size_t arr_c_length = arr_a_length + arr_b_length;
    int* arr_c = arr_alloc_int(arr_c_length);

    for (size_t i = 0; i < arr_a_length; i++) {
        arr_c[i] = arr_a[i];
    }

    for (size_t i = 0; i < arr_b_length; i++) {
        size_t index = arr_a_length + i;
        arr_c[index] = arr_b[i];
    }

    return arr_c;
}

bool arr_contains_int(int arr[], size_t arr_length, int item) {
    // TODO Is there a way to improve performance?

    for (size_t i = 0; i < arr_length; i++) {
        if (arr[i] == item) {
            return true;
        }
    }

    return false;
}

void arr_foreach(int* arr, size_t size, IntFunction func) {
    for (size_t i = 0; i < size; i++) {
        func(arr[i]);
    }
}

void* arr_map(void* arr, size_t item_size, size_t arr_length, MapFunction func) {
    void* mapped_arr = malloc(item_size * arr_length);  // Allocate memory for the result array

    if (mapped_arr == NULL) {
        // TODO How to handle error?
        return NULL;
    }

    for (size_t i = 0; i < arr_length; i++) {
        void* current_item = (char*)arr + i * item_size;
        void* mapped_item = func(i, current_item);
        memcpy((char*)mapped_arr + i * item_size, mapped_item, item_size); // Copy the modified item to the result array
        free(mapped_item);  // Free the memory allocated for the modified item
    }

    return mapped_arr;
}

int* arr_map_int(int arr[], size_t arr_length, MapFunctionInt func) {
    int* mapped_arr = (int*)malloc(sizeof(int) * arr_length);

    if (mapped_arr == NULL) {
        // TODO How to handle error?
        return NULL;
    }

    for (size_t i = 0; i < arr_length; i++) {
        int current_item = arr[i];
        int mapped_item = func(i, current_item);
        mapped_arr[i] = mapped_item;
    }

    return mapped_arr;
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

char* arr_to_string(int* arr, size_t size) {
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