#include "maybe.h"

#include <stddef.h>

// Maybe for int

MaybeI _maybe_i(Error* error, int data) {
	MaybeI maybe;
	maybe.error = error;
	maybe.data = data;
	return maybe;
}

MaybeI maybe_i_error(Error* error) {
	return _maybe_i(error, 0);
}

MaybeI maybe_i_success(int data) {
	return _maybe_i(NULL, data);
}

bool maybe_i_failed(MaybeI maybe) {
	return maybe.error != NULL;
}

void maybe_i_dispose(MaybeI* maybe) {
	free(maybe->error);
	free(maybe);
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
