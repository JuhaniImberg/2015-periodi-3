#ifndef MAP_H
#define MAP_H

#include "tila.h"

/**
 * @brief Holds information about a mapping between keys and values
 * @field size How many elements are in the map
 * @field allocated_size How much memory is allocated for the map
 * @field data The allocated memory
 * @field hash_function The function that is used for hashing the keys
 * @field equals_function The function that is used for checking if two keys are
 *        the same
 */
struct Map {
    unsigned int size;
    unsigned int allocated_size;
    struct MapEntry** data;
    unsigned long (*hash_function)(void *);
    bool (*equals_function)(void *, void *);
};

/**
 * @brief Creates a new map
 */
struct Map *Map_new();

/**
 * @brief Sets the maps key hashing and equals functions
 * @param hash_function The function that will be used for hashing the keys
 * @param equals_function The function that will be used for determining if two
 *        keys are equal
 */
void Map_set_operations(struct Map *map,
                        unsigned long (*hash_function)(void *),
                        bool (*equals_function)(void *, void *));

/**
 * @brief Does the map contain the key
 * @param key The key that gets checked
 * @returns True if the map contains the key
 */
bool Map_contains(struct Map *map, void *key);

/**
 * @brief Gets a value from the map
 * @param key The key that is associated with the wanted value
 * @returns Pointer to the value if found, NULL otherwise
 */
void *Map_get(struct Map *map, void *key);

/**
 * @brief Associates the key with the value in the map
 * @param key The key that is to be associated with the value
 * @param value Pointer to the value
 */
void Map_put(struct Map *map, void *key, void *value);

/**
 * @brief Removes the value from the map that's associated with the key
 * @param key The key that is associated with the wanted value
 */
void Map_remove(struct Map *map, void *key);

/**
 * @brief Deletes the map
 * @param map The map that is to be deleted
 */
void Map_delete(struct Map *map);

/**
 * @brief Resizes the maps allocated space
 * @param new_size The new size for the map
 */
void Map_resize(struct Map *map, unsigned int new_size);

/**
 * @brief Gets all of the internal MapEntry structs
 * @returns All of the internal MapEntry structs
 * @see MapEntry MapEntry
 */
struct MapEntry** Map_entrys(struct Map *map);

#endif
