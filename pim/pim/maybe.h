#ifndef PM_MAYBE_H
#define PM_MAYBE_H

#include <stdbool.h>
#include "errors.h"

////////// PmMaybeInt

typedef struct PmMaybeInt {
	int data;
	PmError error;
	bool raised_error;
} PmMaybeInt;

PmMaybeInt pm_maybe_int(int data);
PmMaybeInt pm_maybe_raise_int(PmError error);

////////// PmMaybeArrInt

typedef struct PmMaybeArrInt {
	int* data;
	PmError error;
	bool raised_error;
} PmMaybeArrInt;

PmMaybeArrInt pm_maybe_arrint(int data[]);
PmMaybeArrInt pm_maybe_raise_arrint(PmError error);

////////// PmMaybe (generic)

typedef struct PmMaybe {
	void* data;
	PmError error;
	bool raised_error;
} PmMaybe;

PmMaybe pm_maybe(void* data);
PmMaybe pm_maybe_raise(PmError error);

#endif // PM_MAYBE_H
