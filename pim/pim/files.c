#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

#define _PM_FILE_BUFFER_SIZE 1024

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
