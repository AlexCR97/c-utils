#ifndef PM_MAP_H
#define PM_MAP_H

#include <stdlib.h>
#include <string.h>

typedef enum PmDataType {
	PM_DATA_TYPE_INT,
	PM_DATA_TYPE_STRING,
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

PmMap pm_map(PmDataType key_type, PmDataType value_type, size_t length);

void pm_map_dispose(PmMap* map);

void* pm_map_get(PmMap map, const void* key);

void pm_map_set(PmMap* map, const void* key, const void* value);

#endif // PM_MAP_H
