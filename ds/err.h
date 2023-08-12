#ifndef ERR_H
#define ERR_H

#define ERR_ALLOCATION_FAILED "allocation_failed"
#define ERR_DIVISION_BY_ZERO "division_by_zero"
#define ERR_INVALID_ARGUMENT "invalid_argument"
#define ERR_NULL_ARGUMENT "null_argument"
#define ERR_UNKNOWN "unknown"

typedef struct {
	char* code;
	char* message;
	void* data;
} Error;

Error error(char* code, char* message, void* data);
void error_dispose(Error* error);
char* error_to_string(Error error);

#endif // ERR_H
