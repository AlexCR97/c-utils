#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_string_builder.h"

StringBuilder string_builder() {
    StringBuilder sb;
    sb.data = (char*)malloc(STRING_BUILDER_INITIAL_CAPACITY * sizeof(char));
    sb.data[0] = '\0';
    sb.length = 0;
    sb.capacity = STRING_BUILDER_INITIAL_CAPACITY;
    return sb;
}

void string_builder_append(StringBuilder* sb, const char* str) {
    size_t str_length = strlen(str);

    if (sb->length + str_length + 1 > sb->capacity) {
        sb->capacity = sb->length + str_length + 1; // +1 for null terminator
        sb->data = (char*)realloc(sb->data, sb->capacity * sizeof(char));
    }

    strcpy_s(sb->data + sb->length, sb->capacity - sb->length, str);
    sb->length += str_length;
}

void string_builder_dispose(StringBuilder* sb) {
    free(sb->data);
}

char* string_builder_to_string(StringBuilder sb) {
    return sb.data;
}
