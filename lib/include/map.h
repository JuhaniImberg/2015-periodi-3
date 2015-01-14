#ifndef MAP_H
#define MAP_H

#include "tila.h"

struct Map {
    unsigned int size;
    unsigned int allocated_size;
    struct MapEntry** data;
};

struct Map *Map_new();
bool Map_contains(struct Map *map, const char *key);
void *Map_get(struct Map *map, const char *key);
void Map_put(struct Map *map, const char *key, void *value);
void Map_remove(struct Map *map, const char *key);
void Map_delete(struct Map *map);
void Map_resize(struct Map *map, unsigned int new_size);
struct MapEntry** Map_entrys(struct Map *map);
//const char** Map_keys(struct Map *map);

#endif
