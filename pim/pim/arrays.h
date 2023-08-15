#ifndef PM_ARRAYS_H
#define PM_ARRAYS_H

#include <stdbool.h>
#include <stdio.h>

#define PM_ARR_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define PM_ARR_DELIMETER_HEAD "{"
#define PM_ARR_DELIMETER_TAIL "}"

// Allocates an array of int of the specified length
int* pm_arr_alloc_int(size_t length);

// A function that receives the current index and item, and returns a bool
typedef bool (*PmAnyFunctionInt)(size_t index, int item);

// Returns true if any of the items in the array satisfies the predicate
bool pm_arr_any_int(int arr[], size_t arr_length, PmAnyFunctionInt predicate);

// Returns an array which is the concatenation of array A and array B
int* pm_arr_concat_int(int arr_a[], size_t arr_a_length, int arr_b[], size_t arr_b_length);

// Returns true if the array contains the specified item, false otherwise
bool pm_arr_contains_int(int arr[], size_t arr_length, int item);

// A function that receives the current index and item, and returns a bool
typedef bool (*PmCountFunctionInt)(size_t index, int item);

// Returns the amount of items that satisfy the predicate
size_t pm_arr_count_int(int arr[], size_t arr_length, PmCountFunctionInt predicate);

// A function that receives the current index and item, and returns a bool
typedef bool (*PmEveryFunctionInt)(size_t index, int item);

// Returns true if all of the items satisfy the predicate, false otherwise
bool pm_arr_every_int(int arr[], size_t arr_length, PmEveryFunctionInt predicate);

// A function that receives the current index and item, and returns a bool
typedef bool (*PmFilterFunctionInt)(size_t index, int item);

// Returns an array which is a subset of the specified array, where all of the items satisfy the predicate
int* pm_arr_filter_int(int arr[], size_t arr_length, PmFilterFunctionInt predicate);

// A function that receives the current index and item, and returns a bool
typedef bool (*PmFindFunctionInt)(size_t index, int item);

// Returns the first item that satisfies the predicate
int pm_arr_find_int(int arr[], size_t arr_length, PmFindFunctionInt predicate); // TODO Return a Maybe?

// Returns the first item that satisfies the predicate
int pm_arr_find_index_int(int arr[], size_t arr_length, PmFindFunctionInt predicate); // TODO Return a Maybe?

// A function that receives the current index and item, and returns a new value
typedef void* (*PmMapFunction)(size_t index, void* item);

// Applies a map function to every element and returns them in a new array
void* pm_arr_map(void* arr, size_t item_size, size_t arr_length, PmMapFunction func);

// A function that receives the current index and item, and returns a new value
typedef void* (*PmMapFunctionInt)(size_t index, int item); // TODO Change void* to int?

// Applies a map function to every element and returns them in a new array
int* pm_arr_map_int(int arr[], size_t arr_length, PmMapFunctionInt func);

// Reverses the position of each item and returns them in a new array
int* pm_arr_reverse_int(int arr[], size_t arr_length);

// Returns a sorted array
int* pm_arr_sort_int(int arr[], size_t arr_length);

// Skips the specified offset of items and returns the rest in a new array
int* pm_arr_skip_int(int arr[], size_t arr_length, size_t offset);

// Takes the specified count of items and returns them in a new array
int* pm_arr_take_int(int arr[], size_t arr_length, size_t count);

char* pm_arr_tail_str(char** arr);

char* pm_arr_to_string(int* arr, size_t size);

#endif // PM_ARRAYS_H
