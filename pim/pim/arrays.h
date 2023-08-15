#ifndef ARR_ARR_H
#define ARR_ARR_H

#include <stdbool.h>
#include <stdio.h>

#define ARR_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARR_DELIMETER_HEAD "{"
#define ARR_DELIMETER_TAIL "}"

// Allocates an array of int of the specified length
int* arr_alloc_int(size_t length);

// A function that receives the current index and item, and returns a bool
typedef bool (*AnyFunctionInt)(size_t index, int item);

// Returns true if any of the items in the array satisfies the predicate
bool arr_any_int(int arr[], size_t arr_length, AnyFunctionInt predicate);

// Returns an array which is the concatenation of array A and array B
int* arr_concat_int(int arr_a[], size_t arr_a_length, int arr_b[], size_t arr_b_length);

// Returns true if the array contains the specified item, false otherwise
bool arr_contains_int(int arr[], size_t arr_length, int item);

// A function that receives the current index and item, and returns a bool
typedef bool (*CountFunctionInt)(size_t index, int item);

// Returns the amount of items that satisfy the predicate
size_t arr_count_int(int arr[], size_t arr_length, CountFunctionInt predicate);

// A function that receives the current index and item, and returns a bool
typedef bool (*EveryFunctionInt)(size_t index, int item);

// Returns true if all of the items satisfy the predicate, false otherwise
bool arr_every_int(int arr[], size_t arr_length, EveryFunctionInt predicate);

// A function that receives the current index and item, and returns a bool
typedef bool (*FilterFunctionInt)(size_t index, int item);

// Returns an array which is a subset of the specified array, where all of the items satisfy the predicate
int* arr_filter_int(int arr[], size_t arr_length, FilterFunctionInt predicate);

// A function that receives the current index and item, and returns a bool
typedef bool (*FindFunctionInt)(size_t index, int item);

// Returns the first item that satisfies the predicate
int arr_find_int(int arr[], size_t arr_length, FindFunctionInt predicate); // TODO Return a Maybe?

// Returns the first item that satisfies the predicate
int arr_find_index_int(int arr[], size_t arr_length, FindFunctionInt predicate); // TODO Return a Maybe?

// A function that receives the current index and item, and returns a new value
typedef void* (*MapFunction)(size_t index, void* item);

// Applies a map function to every element and returns them in a new array
void* arr_map(void* arr, size_t item_size, size_t arr_length, MapFunction func);

// A function that receives the current index and item, and returns a new value
typedef void* (*MapFunctionInt)(size_t index, int item); // TODO Change void* to int?

// Applies a map function to every element and returns them in a new array
int* arr_map_int(int arr[], size_t arr_length, MapFunctionInt func);

// Reverses the position of each item and returns them in a new array
int* arr_reverse_int(int arr[], size_t arr_length);

// Returns a sorted array
int* arr_sort_int(int arr[], size_t arr_length);

// Skips the specified offset of items and returns the rest in a new array
int* arr_skip_int(int arr[], size_t arr_length, size_t offset);

// Takes the specified count of items and returns them in a new array
int* arr_take_int(int arr[], size_t arr_length, size_t count);

char* arr_tail_str(char** arr);

char* arr_to_string(int* arr, size_t size);

#endif // ARR_ARR_H
