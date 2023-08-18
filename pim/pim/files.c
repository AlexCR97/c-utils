#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrays.h"
#include "strings.h"

#define _PM_FILE_BUFFER_SIZE 1024

char** pm_fs_read_lines(const char* path) {
    FILE* file;

    if (fopen_s(&file, path, "r") != 0) {
        // Handle error gracefully (e.g., log, return error code, etc.)
        return NULL;
    }

    char buffer[_PM_FILE_BUFFER_SIZE];
    size_t line_count = 0;

    // Count the number of lines in the file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_count++;
    }

    // Allocate memory for the array of strings
    //lines = (char**)malloc(line_count * sizeof(char*));
    char** lines = (char**)calloc(line_count, sizeof(char*));

    if (lines == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }

    // Reset file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Read lines and store them in the array
    for (size_t i = 0; i < line_count; i++) {
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            size_t length = strlen(buffer);
            if (buffer[length - 1] == '\n') {
                buffer[length - 1] = '\0'; // Remove newline character
            }
            char* buffer_copy = _strdup(buffer);
            lines[i] = buffer_copy;
        }
    }

    fclose(file);

    return lines;
}

char* pm_fs_read_text(const char* path) {
    FILE* file;

    if (fopen_s(&file, path, "r") != 0) {
        // Handle error gracefully (e.g., log, return error code, etc.)
        return NULL;
    }

    // TODO implement pm_str_builder_with_capacity
    //PmStringBuilder sb = pm_str_builder_with_capacity(_PM_FILE_BUFFER_SIZE);
    PmStringBuilder sb = pm_str_builder();
    char buffer[_PM_FILE_BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // TODO implement pm_str_builder_append_n
        //pm_str_builder_append_n(&sb, line, line_length);
        pm_str_builder_append(&sb, buffer);
    }

    fclose(file);

    return pm_str_builder_to_string(sb);
}
