#ifndef MAYBE_H
#define MAYBE_H

#include <stdbool.h>
#include "errors.h"

////////// MaybeInt

typedef struct MaybeInt {
	int data;
	PmError error;
	bool raised_error;
} PmMaybeInt;

PmMaybeInt pm_maybe_int(int data);
PmMaybeInt pm_maybe_raise_int(PmError error);

////////// Maybe (generic)

typedef struct PmMaybe {
	void* data;
	PmError error;
	bool raised_error;
} PmMaybe;

PmMaybe pm_maybe(void* data);
PmMaybe pm_maybe_raise(PmError error);

#endif // MAYBE_H
