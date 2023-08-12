#ifndef STR_STRING_BUILDER_H
#define STR_STRING_BUILDER_H

#include <stddef.h>

#define STRING_BUILDER_INITIAL_CAPACITY 16

typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} StringBuilder;

StringBuilder string_builder();
void string_builder_append(StringBuilder* sb, const char* str);
void string_builder_dispose(StringBuilder* sb);
char* string_builder_to_string(StringBuilder sb);

#endif // STR_STRING_BUILDER_H
