#include "test_maybe.h"

#include <stddef.h>
#include "pim/maybe.h"
#include "pim/test.h"

typedef struct _DivisionByZeroErrData {
	int divisor;
	int dividend;
} _DivisionByZeroErrData;

PmMaybeInt _divide(int a, int b) {
	if (b == 0) {
		_DivisionByZeroErrData err_data;
		err_data.dividend = a;
		err_data.divisor = b;
		PmError err = pm_error(PM_ERR_DIVISION_BY_ZERO, "Cannot divide by zero", &err_data);
		return pm_maybe_raise_int(err);
	}

	return pm_maybe_int(a / b);
}

void _test_pm_maybe_int_succeeded() {
	PmMaybeInt maybe_division = _divide(100, 10);
	PM_ASSERT_EQ(maybe_division.data, 100 / 10);
	PM_ASSERT_EQ(maybe_division.error.code, NULL);
	PM_ASSERT_EQ(maybe_division.error.message, NULL);
	PM_ASSERT_EQ(maybe_division.error.data, NULL);
	PM_ASSERT_EQ(maybe_division.raised_error, false);
};

void _test_pm_maybe_int_raised() {
	PmMaybeInt maybe_division = _divide(100, 0);
	PM_ASSERT_EQ(maybe_division.data, 0);
	PM_ASSERT_EQ(maybe_division.raised_error, true);
	PM_ASSERT(maybe_division.error.code != NULL);
	PM_ASSERT(maybe_division.error.message != NULL);

	_DivisionByZeroErrData* err_data = (_DivisionByZeroErrData*)maybe_division.error.data;
	PM_ASSERT_EQ(err_data->dividend, 100);
	PM_ASSERT_EQ(err_data->divisor, 0);
};

void test_maybe() {
	Test tests[] = {
		test(PM_NAMEOF(pm_maybe_int), _test_pm_maybe_int_succeeded),
		test(PM_NAMEOF(pm_maybe_int), _test_pm_maybe_int_raised),
	};

	TestSuite suite = test_suite("pim/maybe", tests);

	test_suite_run(suite, sizeof(tests) / sizeof(tests[0]));
}
