#ifndef MAPENTRY_H
#define MAPENTRY_H

#include "tila.h"

/**
 * @brief Internal datastructure of the @link //ref/c/tag/Map @/link
 * @field hash The hash code of the key
 * @field key A pointer to the key
 * @field value A pointer to the value
 */
struct MapEntry {
    unsigned long hash;
    void *key;
    void *value;
    size_t key_length;
    size_t value_length;
    struct MapEntry *next;
    struct MapEntry *prev;
};

/**
 * @brief Creates a new MapEntry
 * @param key The key that's associated with the value in the map
 * @param hash The hash value of the key
 * @param value Pointer to the data
 */
struct MapEntry *MapEntry_new(void *key, size_t key_length, unsigned long hash,
                              void *value, size_t value_length);

void MapEntry_set(struct MapEntry *entry, void *value, size_t value_length);

/**
 * @brief Frees the allocated memory for the given entry
 * @param entry The entry to delete
 */
void MapEntry_delete(struct MapEntry *entry);

#endif
