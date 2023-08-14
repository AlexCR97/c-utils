# Coding Guidelines

- [Naming conventions](#naming-conventions)
  - [Variables](#variables)
  - [Functions](#functions)
  - [Enums](#enums)
  - [Structs](#structs)
  - [Macros](#macros)
  - [Private members](#private-members)
- [File placement and structure](#file-placement-and-structure)

## Naming conventions

### Variables

Variables should use the `snake_case` convention.

#### Examples

```c
int[] arr;
char* first_name;
Logger logger;
```

### Functions

Functions should use the `snake_case` convention.

A valid function name looks like this:

`pm_receiver_operation_datatype`

Where:

- `pm` is the lib prefix. This is mandatory to prevent name collisions.
- `receiver` is the data type of the receiver of the function. This is typically an array, enum, struct or some sort of "instance" of a specific type. In order to mimic object orientation, where you would use `obj.do_something`, you should use instead `obj_do_something(receiver)`. This is optional, and should only be used for "instance" specific operations.
- `operation` is the actual function name. This is typically a verb, but is not restricted to it. It can be a descriptive as necessary and there is no length restriction. E.g.: `find_index`, `sort`, `to_string`, etc.
- `datatype` is the data type of the function. In order to support polymorphism and generics, it is preferred to implement the code for the needed data type instead of using `void*`, since things can quickly become unnecessarily complicated with `void*`. This is optional, and should only be used in the case where the function can apply to multiple data types.

If the function has a receiver, it should be the first parameter.

#### Examples

```c
int pm_arr_find_index_int(int arr[], size_t arr_length);

DateTime pm_dt_now();

List pm_list_push_string(List list, char* item);

void pm_logger_log(Logger logger);
```

### Enums

Enums should be typedef'ed.

The name of the enum should use the `PascalCase` convention, prefixed with `Pm`.

The members of the enum should use the uppercase `SNAKE_CASE` convention, prefixed with `PM` and the enum's name in uppercase `SNAKE_CASE`.

#### Examples:

```c
typedef enum PmLogLevel {
	PM_LOG_LEVEL_DEBUG,
	PM_LOG_LEVEL_INFO,
	PM_LOG_LEVEL_WARNING,
	PM_LOG_LEVEL_ERROR,
} PmLogLevel;
```

### Structs

Structs should be typedef'ed.

The name of the struct should use the `PascalCase` convention, prefixed with `Pm`.

The members of the struct should use the guidelines established in the [Variables](#variables) section.

#### Examples:

```c
typedef struct PmLogger {
	PmLogLevel level;
	const char* category;

	bool show_timestamp;
	PmTimeZone timestamp_timezone;

	bool show_level;
	bool show_category;
	bool show_file;
} PmLogger;
```

### Macros

Macros should use the uppercase `SNAKE_CASE` convention, prefixed with `PM`.

#### Examples:

```c
#define PM_ARR_LENGTH_INT(arr) (sizeof(arr) / sizeof(int))

#define PM_ERR_ALLOCATION_FAILED "allocation_failed"

#define PM_NAMEOF(x) #x
```

### Private members

Private members are typically global constants, functions, enums, structs, typedefs, macros, etc. that are declared in a source file rather than a header file, whose purpose is to be used exclusively in that source file and should not be used by the caller via the public interface, even if available.

This also applies to members of a struct that should not be used directly by the caller.

Private members should be prefixed with an `underscore`.

There aren't hard constraints in naming private members since they won't be exposed by the public api, but you should try to stick with the guidelines as much as possible.

#### Examples:

```c
int _some_global_constant;

void _do_something();

typedef enum _MyPrivateEnum {
  // members
} _MyPrivateEnum

typedef struct _MyPrivateStruct {
  // members
} _MyPrivateStruct

#define _SOME_USEFUL_MACRO_
```

## File placement and structure

TODO
