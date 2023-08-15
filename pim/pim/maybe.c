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

PmMaybeInt pm_maybe_raise_int(PmError error) {
	return _maybe_int(0, error, true);
}

////////// PmMaybeStr

PmMaybeStr _maybe_str(char* data, PmError error, bool raised_error) {
	PmMaybeStr maybe;
	maybe.data = data;
	maybe.error = error;
	maybe.raised_error = raised_error;
	return maybe;
}

PmMaybeStr pm_maybe_str(char* data) {
	PmError empty_error = pm_error(NULL, NULL, NULL);
	return _maybe_str(data, empty_error, false);
}

PmMaybeStr pm_maybe_raise_str(PmError error) {
	return _maybe_str(NULL, error, true);
}

////////// PmMaybeArrInt

PmMaybeArrInt _maybe_arrint(int data[], PmError error, bool raised_error) {
	PmMaybeArrInt maybe;
	maybe.data = data;
	maybe.error = error;
	maybe.raised_error = raised_error;
	return maybe;
}

PmMaybeArrInt pm_maybe_arrint(int data[]) {
	PmError empty_error = pm_error(NULL, NULL, NULL);
	return _maybe_arrint(data, empty_error, false);
}

PmMaybeArrInt pm_maybe_raise_arrint(PmError error) {
	return _maybe_arrint(NULL, error, true);
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
