#ifndef MAPENTRY_H
#define MAPENTRY_H

/**
 * @brief Internal datastructure of the @link //ref/c/tag/Map @/link
 */
struct MapEntry {
    unsigned long hash;
    void *key;
    void *value;
    struct MapEntry *next;
    struct MapEntry *prev;
};

/**
 * @brief Creates a new MapEntry
 * @param key The key that's associated with the value in the map
 * @param hash The hash value of the key
 * @param value Pointer to the data
 */
struct MapEntry *MapEntry_new(void *key, unsigned long hash, void *value);

/**
 * @brief Sets the value of the given MapEntry
 * @param entry The entry to modify
 * @param value The new value of the entry
 */
void MapEntry_set(struct MapEntry *entry, void *value);

/**
 * @brief Frees the allocated memory for the given entry
 * @param entry The entry to delete
 */
void MapEntry_delete(struct MapEntry *entry);

#endif
