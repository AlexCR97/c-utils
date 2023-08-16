#include <stddef.h>
#include "errors.h"
#include "strings.h"

char* _error_code_get(PmError error);
char* _error_message_get(PmError error);

PmError pm_error(char* code, char* message, void* data) {
	PmError error;
	error.code = code;
	error.message = message;
	error.data = data;
	return error;
}

void pm_error_dispose(PmError error) {
	free(error.code);
	free(error.data);
	free(error.message);
}

char* pm_error_to_string(PmError error) {
	PmStringBuilder sb = pm_str_builder();
	pm_str_builder_append(&sb, _error_code_get(error));
	pm_str_builder_append(&sb, ": ");
	pm_str_builder_append(&sb, _error_message_get(error));
	return pm_str_builder_to_string(sb);
}

char* _error_code_get(PmError error) {
	return error.code != NULL
		? error.code
		: "unknown";
}

char* _error_message_get(PmError error) {
	return error.message != NULL
		? error.message
		: "An unexpected error occurred.";
}
