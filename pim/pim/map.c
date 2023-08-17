#include "map.h"

#include <stdbool.h>
#include "arrays.h"
#include "strings.h"

PmMap pm_map(PmDataType key_type, PmDataType value_type, size_t length) {
	PmMap map;
	map.key_type = key_type;
	map.value_type = value_type;
	map.length = length;
	map.buckets = (PmPair**)calloc(length, sizeof(PmPair*));
	return map;
}

// TODO Move this to another header?
bool _pm_equals(void* a, void* b, PmDataType type) {
	if (type == PM_DATA_TYPE_INT) {
		int a_int = (int)a;
		int b_int = (int)b;
		return a_int == b_int;
	}

	if (type == PM_DATA_TYPE_STRING) {
		char* a_str = a;
		char* b_str = b;
		return pm_str_equals(a_str, b_str);
	}

	fprintf(stderr, "_pm_equals is not implemented for PmDataType %d\n", type);
	exit(EXIT_FAILURE);
}

bool pm_map_contains_key(PmMap map, const void* key) {
	for (size_t i = 0; i < map.length; i++) {
		PmPair* pair = map.buckets[i];

		while (pair != NULL) {
			PmPair* next = pair->next;

			if (_pm_equals(pair->key, key, map.key_type)) {
				return true;
			}

			pair = next;
		}
	}

	return false;
}

bool pm_map_contains_value(PmMap map, const void* value) {
	for (size_t i = 0; i < map.length; i++) {
		PmPair* pair = map.buckets[i];

		while (pair != NULL) {
			PmPair* next = pair->next;

			if (_pm_equals(pair->value, value, map.value_type)) {
				return true;
			}

			pair = next;
		}
	}

	return false;
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

void** _pm_alloc_typed_array(PmDataType type, size_t length) {
	if (type == PM_DATA_TYPE_INT) {
		PmMaybeArrInt maybe_arrint = pm_arr_alloc_int(length);
		// TODO Handle error
		return maybe_arrint.data;
	}

	if (type == PM_DATA_TYPE_STRING) {
		PmMaybeArrStr maybe_arrstr = pm_arr_alloc_str(length);
		// TODO Handle error
		return maybe_arrstr.data;
	}

	fprintf(stderr, "_pm_alloc_keys_array is not implemented for PmDataType %d\n", type);
	exit(EXIT_FAILURE);
}

void** pm_map_keys(PmMap map) {
	void** keys = _pm_alloc_typed_array(map.key_type, map.length);
	int keys_index = 0;

	for (size_t i = 0; i < map.length; i++) {
		PmPair* pair = map.buckets[i];

		while (pair != NULL) {
			PmPair* next = pair->next;
			keys[keys_index] = pair->key;
			keys_index++;
			pair = next;
		}
	}

	return keys;
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

void pm_map_remove(PmMap* map, const void* key) {
	for (size_t i = 0; i < map->length; i++) {
		PmPair* pair = map->buckets[i];

		while (pair != NULL) {
			PmPair* next = pair->next;

			if (_pm_equals(pair->key, key, map->key_type)) {
				// TODO Check if key type is a pointer
				if (false) {
					free(pair->key);
				}

				// TODO Check if value type is a pointer
				if (false) {
					free(pair->value);
				}

				free(pair);
				map->buckets[i] = NULL;
				return;
			}

			pair = next;
		}
	}
}

void pm_map_set(PmMap* map, const void* key, const void* value) {
	const int index = _pm_map_hash(*map, key);

	PmPair* pair = _pm_pair(
		map->key_type, key,
		map->value_type, value);

	pair->next = map->buckets[index];
	map->buckets[index] = pair;
}

void** pm_map_values(PmMap map) {
	void** values = _pm_alloc_typed_array(map.key_type, map.length);
	int values_index = 0;

	for (size_t i = 0; i < map.length; i++) {
		PmPair* pair = map.buckets[i];

		while (pair != NULL) {
			PmPair* next = pair->next;
			values[values_index] = pair->value;
			values_index++;
			pair = next;
		}
	}

	return values;
}
