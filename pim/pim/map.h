#ifndef PM_MAP_H
#define PM_MAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum PmDataType {
	PM_DATA_TYPE_BOOL,
	PM_DATA_TYPE_CHAR,
	PM_DATA_TYPE_DOUBLE,
	PM_DATA_TYPE_FLOAT,
	PM_DATA_TYPE_INT,
	PM_DATA_TYPE_STRING,

	PM_DATA_TYPE_BOOL_PTR,
	PM_DATA_TYPE_CHAR_PTR,
	PM_DATA_TYPE_DOUBLE_PTR,
	PM_DATA_TYPE_FLOAT_PTR,
	PM_DATA_TYPE_INT_PTR,
	PM_DATA_TYPE_STRING_PTR,

	PM_DATA_TYPE_ARR_BOOL,
	PM_DATA_TYPE_ARR_CHAR,
	PM_DATA_TYPE_ARR_DOUBLE,
	PM_DATA_TYPE_ARR_FLOAT,
	PM_DATA_TYPE_ARR_INT,
	PM_DATA_TYPE_ARR_STRING,

	// Add more data types as needed
} PmDataType;

typedef struct PmPair {
	PmDataType key_type;
	void* key;

	PmDataType value_type;
	void* value;

	struct PmPair* next;
} PmPair;

typedef struct PmMap {
	PmDataType key_type;
	PmDataType value_type;
	size_t length;

	/// <summary>
	/// An array of pointers to PmPair
	/// </summary>
	PmPair** buckets;
} PmMap;

/// <summary>
/// Creates a map.
/// </summary>
/// <param name="key_type">The data type of the map's keys</param>
/// <param name="value_type">The data type of the key's values</param>
/// <param name="length">The amount of pairs supported by the map</param>
PmMap pm_map(PmDataType key_type, PmDataType value_type, size_t length);

/// <summary>
/// Checks if the map contains the specified key.
/// </summary>
/// <returns>true if the key is found, false otherwise.</returns>
bool pm_map_contains_key(PmMap map, const void* key);

/// <summary>
/// Checks if the map contains the specified value.
/// </summary>
/// <returns>true if the value is found, false otherwise.</returns>
bool pm_map_contains_value(PmMap map, const void* value);

void pm_map_dispose(PmMap* map);

void* pm_map_get(PmMap map, const void* key);

/// <summary>
/// Collects the keys of the map.
/// </summary>
/// <returns>An array that contains the keys of the map.</returns>
void** pm_map_keys(PmMap map);

/// <summary>
/// Removes a key from the map.
/// </summary>
void pm_map_remove(PmMap* map, const void* key);

void pm_map_set(PmMap* map, const void* key, const void* value);

void** pm_map_values(PmMap map, const void* key);

#endif // PM_MAP_H
