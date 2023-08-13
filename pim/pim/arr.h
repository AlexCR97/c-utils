#ifndef ARR_ARR_H
#define ARR_ARR_H

#include <stdio.h>

#define ARR_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARR_DELIMETER_HEAD "{"
#define ARR_DELIMETER_TAIL "}"

typedef void (*IntFunction)(int); // Function that takes an integer as an argument

void arr_foreach(int* arr, size_t size, IntFunction func);

// A function that receives the current index and item, and returns a new value
typedef void* (*MapFunction)(size_t index, void* item);

// Applies a map function to every element and returns them in a new array
void* arr_map(void* arr, size_t item_size, size_t arr_length, MapFunction func);

// A function that receives the current index and item, and returns a new value
typedef void* (*MapFunctionInt)(size_t index, int item);

// Applies a map function to every element and returns them in a new array
int* arr_map_int(int arr[], size_t arr_length, MapFunctionInt func);

char* arr_tail_str(char** arr);
char* arr_to_string(int* arr, size_t size);

#endif // ARR_ARR_H
