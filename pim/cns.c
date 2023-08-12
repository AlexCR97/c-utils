#include "cns.h"

#include "str_string.h"

Maybe cns_prompt(const char* message, size_t capacity) {
    if (message == NULL) {
        const Error err = error(ERR_NULL_ARGUMENT, "The argument \"message\" is null", NULL);
        return maybe_error(&err);
    }

    printf("%s", message);

    char* input = (char*)malloc(capacity * sizeof(char));

    if (input == NULL) {
        const Error err = error(ERR_ALLOCATION_FAILED, "Could not allocate buffer for input", NULL);
        return maybe_error(&err);
    }

    if (fgets(input, capacity, stdin) == NULL) {
        free(input);
        const Error err = error("invalid_input", NULL, NULL);
        return maybe_error(&err);
    }

    input = str_trim_trailing(input, '\n');

    return maybe_success(input);
}
