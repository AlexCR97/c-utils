#include "hashmap.h"

unsigned int hash(const Hashmap* map, const void* key) {
    // Improved hash function using keyDataType
    unsigned int hashValue = 0;

    switch (map->keyDataType) {
    case INT_KEY:
        hashValue = *((int*)key);
        break;

    case STRING_KEY:
        for (size_t i = 0; ((char*)key)[i]; i++) {
            hashValue = (hashValue * 31) + ((char*)key)[i];
        }
        break;

        // Add more cases for other key data types

    default:
        // Handle unsupported data types
        break;
    }

    return hashValue % map->size;
}

KeyValuePair* createKeyValuePair(const void* key, const void* value) {
    KeyValuePair* pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    pair->key = (void*)key;
    pair->value = (void*)value;
    pair->next = NULL;
    return pair;
}

Hashmap* createHashmap(size_t size) {
    Hashmap* map = (Hashmap*)malloc(sizeof(Hashmap));
    if (map == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    map->size = size;
    map->buckets = (KeyValuePair**)calloc(size, sizeof(KeyValuePair*));
    if (map->buckets == NULL) {
        perror("Memory allocation failed");
        free(map);
        exit(EXIT_FAILURE);
    }

    return map;
}

void insert(Hashmap* map, const void* key, const void* value) {
    unsigned int index = hash(map, key);

    KeyValuePair* pair = createKeyValuePair(key, value);
    pair->next = map->buckets[index];
    map->buckets[index] = pair;
}

void* get(Hashmap* map, const void* key) {
    unsigned int index = hash(map, key);

    KeyValuePair* pair = map->buckets[index];
    while (pair) {
        if (pair->key == key) {
            return pair->value;
        }
        pair = pair->next;
    }

    return NULL;
}

void cleanup(Hashmap* map) {
    // TODO How to free map?

    /*free(map->buckets);
    free(map);*/

    /*for (int i = 0; i < map->size; i++) {
        KeyValuePair* pair = map->buckets[i];
        while (pair) {
            KeyValuePair* next = pair->next;
            free(pair);
            pair = next;
        }
    }*/
}
