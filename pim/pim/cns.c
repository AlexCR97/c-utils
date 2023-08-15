#include "cns.h"

#include "strings.h"

PmMaybe cns_prompt(const char* message, size_t capacity) {
    if (message == NULL) {
        PmError err = pm_error(PM_ERR_NULL_ARGUMENT, "The argument \"message\" is null", NULL);
        return pm_maybe_raise(err);
    }

    printf("%s", message);

    char* input = (char*)malloc(capacity * sizeof(char));

    if (input == NULL) {
        PmError err = pm_error(PM_ERR_ALLOCATION_FAILED, "Could not allocate buffer for input", NULL);
        return pm_maybe_raise(err);
    }

    if (fgets(input, capacity, stdin) == NULL) {
        free(input);
        PmError err = pm_error("invalid_input", NULL, NULL);
        return pm_maybe_raise(err);
    }

    // TODO handle error
    input = pm_str_trim_trailing(input, '\n').data;

    return pm_maybe(input);
}
