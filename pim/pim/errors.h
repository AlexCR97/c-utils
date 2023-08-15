#ifndef PM_ERRORS_H
#define PM_ERRORS_H

#define PM_ERR_ALLOCATION_FAILED "pim:allocation_failed"
#define PM_ERR_DIVISION_BY_ZERO "pim:division_by_zero"
#define PM_ERR_INDEX_OUT_OF_BOUNDS "pim:index_out_of_bounds"
#define PM_ERR_INVALID_ARGUMENT "pim:invalid_argument"
#define PM_ERR_NULL_ARGUMENT "pim:null_argument"
#define PM_ERR_UNKNOWN "pim:unknown"

typedef struct PmError {
	char* code;
	char* message;
	void* data;
} PmError;

PmError pm_error(char* code, char* message, void* data);
void pm_error_dispose(PmError error);
char* pm_error_to_string(PmError error);

#endif // PM_ERRORS_H
