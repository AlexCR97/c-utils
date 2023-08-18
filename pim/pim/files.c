#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

char* pm_fs_read_text(const char* path) {
    FILE* file;

    if (fopen_s(&file, path, "r") != 0) {
        // TODO How to handle error?
        return NULL;
    }

    PmStringBuilder sb = pm_str_builder();
    char buffer[6]; // TODO figure out why 6

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        pm_str_builder_append(&sb, buffer);
    }

    fclose(file);

    return pm_str_builder_to_string(sb);
}
