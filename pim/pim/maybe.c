#include "maybe.h"

#include <stddef.h>

// Maybe for int

MaybeInt _maybe_int(int data, Error error, bool raised_error) {
	MaybeInt maybe;
	maybe.data = data;
	maybe.error = error;
	maybe.raised_error = raised_error;
	return maybe;
}

MaybeInt pm_maybe_int(int data) {
	Error empty_error = error(NULL, NULL, NULL);
	return _maybe_int(data, empty_error, false);
}

MaybeInt pm_maybe_int_raise(Error error) {
	return _maybe_int(0, error, true);
}

// Maybe for generics

Maybe _maybe(Error* error, void* data) {
	Maybe maybe;
	maybe.error = error;
	maybe.data = data;
	return maybe;
}

Maybe maybe_error(Error* error) {
	return _maybe(error, NULL);
}

Maybe maybe_success(void* data) {
	return _maybe(NULL, data);
}

bool maybe_failed(Maybe maybe) {
	return maybe.error != NULL;
}

void maybe_dispose(Maybe* maybe) {
	if (maybe->data != NULL) {
		free(maybe->data);
	}

	if (maybe->error != NULL) {
		error_dispose(maybe->error);
	}
}
