#ifndef PM_STRINGS_H
#define PM_STRINGS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // TODO Is this needed?
#include "maybe.h"

/// <summary>
/// Allocates a string.
/// </summary>
/// <param name="length">The length of the string.</param>
/// <returns>A null terminated string</returns>
PmMaybeStr pm_str_alloc(size_t length);

/// <summary>
/// Checks if a substring is contained within the string.
/// </summary>
bool pm_str_contains(const char* str, const char* substring);

/// <summary>
/// Compares 2 strings.
/// </summary>
/// <param name="a">The string to compare to.</param>
/// <param name="b">The string to compare against.</param>
/// <returns>true if both strings match, false otherwise.</returns>
bool pm_str_equals(const char* a, const char* b);

/// <summary>
/// Splits a string by a given character.
/// </summary>
/// <param name="str">The string to split.</param>
/// <param name="split_by">The character to split by.</param>
/// <returns>An array of strings.</returns>
PmMaybeArrStr pm_str_split(const char* str, char split_by);

/// <summary>
/// Converts a string to lowercase.
/// </summary>
/// <returns>A lowercase string.</returns>
PmMaybeStr pm_str_to_lower(const char* str);

/// <summary>
/// Converts a string to uppercase.
/// </summary>
/// <returns>An uppercase string.</returns>
PmMaybeStr pm_str_to_upper(const char* str);

/// <summary>
/// Converts an int to it's string representation.
/// </summary>
PmMaybeStr pm_str_to_string_int(int num);

/// <summary>
/// Removes the specified trailing characters from the string.
/// </summary>
/// <returns>A string without the trailing characters.</returns>
PmMaybeStr pm_str_trim_trailing(const char* str, char trim);

#endif // PM_STRINGS_H
