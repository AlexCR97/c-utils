#ifndef MAYBE_H
#define MAYBE_H

#include <stdbool.h>
#include "err.h"

// Maybe for int

typedef struct MaybeInt {
	int data;
	PmError error;
	bool raised_error;
} PmMaybeInt;

PmMaybeInt pm_maybe_int(int data);
PmMaybeInt pm_maybe_int_raise(PmError error);

// Maybe for generics

typedef struct {
	PmError* error;
	void* data;
} Maybe;

Maybe maybe_error(PmError* error);
Maybe maybe_success(void* data);
bool maybe_failed(Maybe maybe);
void maybe_dispose(Maybe* maybe);

#endif // MAYBE_H
