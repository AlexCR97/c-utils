#ifndef ERR_H
#define ERR_H

#define ERR_ALLOCATION_FAILED "allocation_failed"
#define ERR_DIVISION_BY_ZERO "division_by_zero"
#define ERR_INDEX_OUT_OF_BOUNDS "index_out_of_bounds"
#define ERR_INVALID_ARGUMENT "invalid_argument"
#define ERR_NULL_ARGUMENT "null_argument"
#define ERR_UNKNOWN "unknown"

typedef struct PmError {
	char* code;
	char* message;
	void* data;
} PmError;

PmError pm_error(char* code, char* message, void* data);
void pm_error_dispose(PmError error);
char* pm_error_to_string(PmError error);

#endif // ERR_H
