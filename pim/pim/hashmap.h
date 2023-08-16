#ifndef PM_HASHMAP_H
#define PM_HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INT_KEY,
    STRING_KEY,
    // Add more key data types as needed
} KeyDataType;

typedef struct KeyValuePair {
    void* key;
    void* value;
    struct KeyValuePair* next;
} KeyValuePair;

typedef struct Hashmap {
    /// <summary>
    /// An array of pointers to KeyValuePairs
    /// </summary>
    KeyValuePair** buckets;

    KeyDataType keyDataType;

    size_t size;
} Hashmap;

unsigned int hash(const Hashmap* map, const void* key);

KeyValuePair* createKeyValuePair(const void* key, const void* value);

Hashmap* createHashmap(size_t size);

void insert(Hashmap* map, const void* key, const void* value);

void* get(Hashmap* map, const void* key);

void cleanup(Hashmap* map);

#endif // PM_HASHMAP_H
