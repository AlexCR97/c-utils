#include <stddef.h>
#include "err.h"
#include "str_string_builder.h"

char* _error_code_get(Error error);
char* _error_message_get(Error error);

Error error(char* code, char* message, void* data) {
	Error error;
	error.code = code;
	error.message = message;
	error.data = data;
	return error;
}

void error_dispose(Error* error) {
	if (error->code != NULL) {
		free(error->code);
	}

	if (error->data != NULL) {
		free(error->data);
	}

	if (error->message != NULL) {
		free(error->message);
	}
}

char* error_to_string(Error error) {
	StringBuilder sb = string_builder();
	string_builder_append(&sb, _error_code_get(error));
	string_builder_append(&sb, ": ");
	string_builder_append(&sb, _error_message_get(error));
	return string_builder_to_string(sb);
}

char* _error_code_get(Error error) {
	return error.code != NULL
		? error.code
		: "unknown";
}

char* _error_message_get(Error error) {
	return error.message != NULL
		? error.message
		: "An unexpected error occurred.";
}
