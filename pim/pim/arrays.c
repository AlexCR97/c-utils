#include "arrays.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "str_string.h"
#include "str_string_builder.h"

const char* _PM_ARR_DELIMETER_HEAD = "{";
const char* _PM_ARR_DELIMETER_TAIL = "}";

#pragma region int

const int _ARR_DEFAULT_INT = 0;

PmMaybeArrInt pm_arr_alloc_int(size_t length) {
    int* arr = (int*)malloc(sizeof(int) * length);

    if (arr == NULL) {
        PmError err = pm_error(PM_ERR_ALLOCATION_FAILED, NULL, NULL);
        return pm_maybe_raise_arrint(err);
    }

    arr[0] = _ARR_DEFAULT_INT;

    return pm_maybe_arrint(arr);
}

bool pm_arr_any_int(int arr[], size_t arr_length, PmArrPredicateFunctionInt predicate) {
    // TODO Is there a way to improve performance?

    for (size_t i = 0; i < arr_length; i++) {
        bool result = predicate(i, arr[i]);

        if (result) {
            return true;
        }
    }

    return false;
}

PmMaybeArrInt pm_arr_concat_int(int arr_a[], size_t arr_a_length, int arr_b[], size_t arr_b_length) {
    size_t arr_c_length = arr_a_length + arr_b_length;
    PmMaybeArrInt maybe_arr_c = pm_arr_alloc_int(arr_c_length);

    if (maybe_arr_c.raised_error) {
        return maybe_arr_c;
    }

    int* arr_c = maybe_arr_c.data;

    for (size_t i = 0; i < arr_a_length; i++) {
        arr_c[i] = arr_a[i];
    }

    for (size_t i = 0; i < arr_b_length; i++) {
        size_t index = arr_a_length + i;
        arr_c[index] = arr_b[i];
    }

    return pm_maybe_arrint(arr_c);
}

bool pm_arr_contains_int(int arr[], size_t arr_length, int item) {
    // TODO Is there a way to improve performance?

    for (size_t i = 0; i < arr_length; i++) {
        if (arr[i] == item) {
            return true;
        }
    }

    return false;
}

size_t pm_arr_count_int(int arr[], size_t arr_length, PmArrPredicateFunctionInt predicate) {
    // TODO Is there a way to improve performance?
    size_t count = 0;

    for (size_t i = 0; i < arr_length; i++) {
        bool result = predicate(i, arr[i]);

        if (result) {
            count += 1;
        }
    }

    return count;
}

bool pm_arr_every_int(int arr[], size_t arr_length, PmArrPredicateFunctionInt predicate) {
    // TODO Is there a way to improve performance?

    for (size_t i = 0; i < arr_length; i++) {
        bool result = predicate(i, arr[i]);

        if (result == false) {
            return false;
        }
    }

    return true;
}

PmMaybeArrInt pm_arr_filter_int(int arr[], size_t arr_length, PmArrPredicateFunctionInt predicate) {
    PmMaybeArrInt maybe_filtered_arr = pm_arr_alloc_int(arr_length);

    if (maybe_filtered_arr.raised_error) {
        return maybe_filtered_arr;
    }

    int* filtered_arr = maybe_filtered_arr.data;
    size_t filtered_length = 0;

    for (size_t i = 0; i < arr_length; i++) {
        int current_item = arr[i];
        bool satisfies_predicate = predicate(i, current_item);

        if (satisfies_predicate) {
            filtered_arr[filtered_length] = current_item;
            filtered_length++;
        }
    }

    // Resize the allocated memory to match the actual number of filtered items
    int* filtered_arr_resized = (int*)realloc(filtered_arr, filtered_length * sizeof(int));

    if (filtered_arr_resized == NULL) {
        PmError err = pm_error(PM_ERR_ALLOCATION_FAILED, NULL, NULL);
        return pm_maybe_raise_arrint(err);
    }

    return pm_maybe_arrint(filtered_arr_resized);
}

int _arr_find_index_int(int arr[], size_t arr_length, PmArrPredicateFunctionInt predicate) {
    // TODO Is there a way to improve performance?

    for (size_t i = 0; i < arr_length; i++) {
        int current_item = arr[i];
        bool satisfies_predicate = predicate(i, current_item);

        if (satisfies_predicate) {
            return i;
        }
    }

    return -1; // TODO Return a Maybe?
}

int pm_arr_find_int(int arr[], size_t arr_length, PmArrPredicateFunctionInt predicate) {
    int index = _arr_find_index_int(arr, arr_length, predicate);
    return arr[index];
}

int pm_arr_find_index_int(int arr[], size_t arr_length, PmArrPredicateFunctionInt predicate) {
    return _arr_find_index_int(arr, arr_length, predicate);
}

PmMaybeArrInt pm_arr_map_int(int arr[], size_t arr_length, PmArrMapFunctionInt func) {
    PmMaybeArrInt maybe_mapped_arr = pm_arr_alloc_int(arr_length);

    if (maybe_mapped_arr.raised_error) {
        return maybe_mapped_arr;
    }

    int* mapped_arr = maybe_mapped_arr.data;

    for (size_t i = 0; i < arr_length; i++) {
        int current_item = arr[i];
        int mapped_item = func(i, current_item);
        mapped_arr[i] = mapped_item;
    }

    return pm_maybe_arrint(mapped_arr);
}

PmMaybeArrInt pm_arr_reverse_int(int arr[], size_t arr_length) {
    PmMaybeArrInt maybe_reversed_arr = pm_arr_alloc_int(arr_length);

    if (maybe_reversed_arr.raised_error) {
        return maybe_reversed_arr;
    }

    int* reversed_arr = maybe_reversed_arr.data;

    for (size_t i = 0; i < arr_length; i++) {
        reversed_arr[i] = arr[arr_length - 1 - i];
    }

    return pm_maybe_arrint(reversed_arr);
}

// Quick sort - Swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Quick sort - Partitioning
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}

// Quick sort
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

PmMaybeArrInt pm_arr_sort_int(int arr[], size_t arr_length) {
    PmMaybeArrInt maybe_sorted_arr = pm_arr_alloc_int(arr_length);

    if (maybe_sorted_arr.raised_error) {
        return maybe_sorted_arr;
    }
    
    int* sorted_arr = maybe_sorted_arr.data;

    // Copy the original array into the sorted array
    for (size_t i = 0; i < arr_length; i++) {
        sorted_arr[i] = arr[i];
    }

    // Perform quick sort
    quick_sort(sorted_arr, 0, arr_length - 1);

    return pm_maybe_arrint(sorted_arr);
}

PmMaybeArrInt pm_arr_skip_int(int arr[], size_t arr_length, size_t offset) {
    if (offset >= arr_length) {
        return pm_maybe_raise_arrint(pm_error(PM_ERR_INVALID_ARGUMENT, NULL, NULL));
    }

    size_t offset_arr_length = arr_length - offset;
    PmMaybeArrInt maybe_offset_arr = pm_arr_alloc_int(offset_arr_length);

    if (maybe_offset_arr.raised_error) {
        return maybe_offset_arr;
    }

    int* offset_arr = maybe_offset_arr.data;

    for (size_t i = offset; i < arr_length; i++) {
        offset_arr[i - offset] = arr[i];
    }

    return pm_maybe_arrint(offset_arr);
}

PmMaybeArrInt pm_arr_take_int(int arr[], size_t arr_length, size_t count) {
    if (count > arr_length) {
        return pm_maybe_raise_arrint(pm_error(PM_ERR_INVALID_ARGUMENT, NULL, NULL));
    }

    PmMaybeArrInt maybe_result = pm_arr_alloc_int(count);

    if (maybe_result.raised_error) {
        return maybe_result;
    }

    int* result = maybe_result.data;

    for (size_t i = 0; i < count; i++) {
        result[i] = arr[i];
    }

    return pm_maybe_arrint(result);
}

char* pm_arr_to_string(int* arr, size_t size) {
    StringBuilder sb = string_builder();
    string_builder_append(&sb, _PM_ARR_DELIMETER_HEAD);
    string_builder_append(&sb, " ");

    for (size_t i = 0; i < size; i++) {
        string_builder_append(&sb, str_to_string(arr[i]));

        if (i != size - 1) {
            string_builder_append(&sb, ", ");
        } else {
            string_builder_append(&sb, " ");
        }
    }

    string_builder_append(&sb, _PM_ARR_DELIMETER_TAIL);

    return string_builder_to_string(sb);
}

#pragma endregion

#pragma region char*

char* pm_arr_tail_str(char** arr) {
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

#pragma endregion

#pragma region void*

void* pm_arr_map(void* arr, size_t item_size, size_t arr_length, PmMapFunction func) {
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

#pragma endregion
