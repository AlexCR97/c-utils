#include "map.h"

#include <stdbool.h>

PmMap pm_map(PmDataType key_type, PmDataType value_type, size_t length) {
	PmMap map;
	map.key_type = key_type;
	map.value_type = value_type;
	map.length = length;
	map.buckets = (PmPair**)calloc(length, sizeof(PmPair*));
	return map;
}

void pm_map_dispose(PmMap* map) {
	for (size_t i = 0; i < map->length; i++) {
		PmPair* pair = map->buckets[i];

		while (pair != NULL) {
			PmPair* next = pair->next;

			// TODO Make if check if key type is a pointer
			if (false) {
				free(pair->key);
			}
			
			// TODO Make if check if value type is a pointer
			if (false) {
				free(pair->value);
			}

			free(pair);

			pair = next;
		}
	}

	free(map->buckets);
}

unsigned int _pm_map_hash(PmMap map, const void* key) {
	unsigned int hashValue = 0;

	switch (map.key_type) {
	case PM_DATA_TYPE_INT:
		hashValue = *((int*)key);
		break;

	case PM_DATA_TYPE_STRING:
		for (size_t i = 0; ((char*)key)[i]; i++) {
			hashValue = (hashValue * 31) + ((char*)key)[i];
		}
		break;

		// Add more cases for other key data types

	default:
		// Handle unsupported data types
		break;
	}

	return hashValue % map.length;
}

void* pm_map_get(PmMap map, const void* key) {
	const int index = _pm_map_hash(map, key);

	PmPair* pair = map.buckets[index];

	while (pair != NULL) {
		if (pair->key == key) {
			return pair->value;
		}

		pair = pair->next;
	}

	return NULL;
}

PmPair* _pm_pair(PmDataType key_type, void* key, PmDataType value_type, void* value) {
	PmPair* pair = (PmPair*)malloc(sizeof(PmPair));

	if (pair == NULL) {
		return NULL; // TODO Return a Maybe?
	}

	pair->key = key;
	pair->key_type = key_type;
	pair->value = value;
	pair->value_type = value_type;
	pair->next = NULL;
	return pair;
}

void pm_map_set(PmMap* map, const void* key, const void* value) {
	const int index = _pm_map_hash(*map, key);

	PmPair* pair = _pm_pair(
		map->key_type, key,
		map->value_type, value);

	pair->next = map->buckets[index];
	map->buckets[index] = pair;
}
