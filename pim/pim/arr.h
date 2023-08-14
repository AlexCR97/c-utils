#ifndef ARR_ARR_H
#define ARR_ARR_H

#include <stdbool.h>
#include <stdio.h>

#define ARR_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARR_DELIMETER_HEAD "{"
#define ARR_DELIMETER_TAIL "}"

typedef void (*IntFunction)(int); // Function that takes an integer as an argument

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

void arr_foreach(int* arr, size_t size, IntFunction func);

// A function that receives the current index and item, and returns a new value
typedef void* (*MapFunction)(size_t index, void* item);

// Applies a map function to every element and returns them in a new array
void* arr_map(void* arr, size_t item_size, size_t arr_length, MapFunction func);

// A function that receives the current index and item, and returns a new value
typedef void* (*MapFunctionInt)(size_t index, int item); // TODO Change void* to int?

// Applies a map function to every element and returns them in a new array
int* arr_map_int(int arr[], size_t arr_length, MapFunctionInt func);

char* arr_tail_str(char** arr);

char* arr_to_string(int* arr, size_t size);

#endif // ARR_ARR_H
