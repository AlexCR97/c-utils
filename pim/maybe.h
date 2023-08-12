#ifndef MAYBE_H
#define MAYBE_H

#include <stdbool.h>
#include "err.h"

// Maybe for int

typedef struct {
	Error* error;
	int data;
} MaybeI;

MaybeI maybe_i_error(Error* error);
MaybeI maybe_i_success(int data);
bool maybe_i_failed(MaybeI maybe);
void maybe_i_dispose(MaybeI* maybe);

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
