#include "maybe.h"

#include <stddef.h>

////////// MaybeInt

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

////////// Maybe (generic)

PmMaybe _maybe(void* data, PmError error, bool raised_error) {
	PmMaybe maybe;
	maybe.data = data;
	maybe.error = error;
	maybe.raised_error = raised_error;
	return maybe;
}

PmMaybe pm_maybe(void* data) {
	PmError empty_error = pm_error(NULL, NULL, NULL);
	return _maybe(data, empty_error, false);
}

PmMaybe pm_maybe_raise(PmError error) {
	return _maybe(0, error, true);
}
