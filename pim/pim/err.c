#include <stddef.h>
#include "err.h"
#include "str_string_builder.h"

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
	StringBuilder sb = string_builder();
	string_builder_append(&sb, _error_code_get(error));
	string_builder_append(&sb, ": ");
	string_builder_append(&sb, _error_message_get(error));
	return string_builder_to_string(sb);
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
