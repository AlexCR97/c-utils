#ifndef MAYBE_H
#define MAYBE_H

#include <stdbool.h>
#include "err.h"

// Maybe for int

typedef struct MaybeInt {
	int data;
	Error error;
	bool raised_error;
} MaybeInt;

MaybeInt pm_maybe_int(int data);
MaybeInt pm_maybe_int_raise(Error error);

// Maybe for generics

typedef struct {
	Error* error;
	void* data;
} Maybe;

Maybe maybe_error(Error* error);
Maybe maybe_success(void* data);
bool maybe_failed(Maybe maybe);
void maybe_dispose(Maybe* maybe);

#endif // MAYBE_H
