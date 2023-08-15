#include "maybe.h"

#include <stddef.h>

// Maybe for int

PmMaybeInt _maybe_int(int data, PmError error, bool raised_error) {
	PmMaybeInt maybe;
	maybe.data = data;
	maybe.error = error;
	maybe.raised_error = raised_error;
	return maybe;
}

PmMaybeInt pm_maybe_int(int data) {
	PmError empty_error = pm_error(NULL, NULL, NULL);
	return _maybe_int(data, empty_error, false);
}

PmMaybeInt pm_maybe_int_raise(PmError error) {
	return _maybe_int(0, error, true);
}

// Maybe for generics

Maybe _maybe(PmError* error, void* data) {
	Maybe maybe;
	maybe.error = error;
	maybe.data = data;
	return maybe;
}

Maybe maybe_error(PmError* error) {
	return _maybe(error, NULL);
}

Maybe maybe_success(void* data) {
	return _maybe(NULL, data);
}

bool maybe_failed(Maybe maybe) {
	return maybe.error != NULL;
}

void maybe_dispose(Maybe* maybe) {
	free(maybe->data);
	pm_error_dispose(*maybe->error);
}
