#ifndef ARR_ARR_H
#define ARR_ARR_H

#include <stdio.h>

#define ARR_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARR_DELIMETER_HEAD "{"
#define ARR_DELIMETER_TAIL "}"

typedef void (*IntFunction)(int); // Function that takes an integer as an argument

void arr_foreach(int* arr, size_t size, IntFunction func);
char* arr_tail_str(char** arr);
char* arr_to_string(int* arr, size_t size);

#endif // ARR_ARR_H
