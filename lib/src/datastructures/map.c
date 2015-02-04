#include "tila.h"

struct Map *Map_new() {
    struct Map *map = (struct Map *) malloc(sizeof(struct Map));
    map->size = 0;
    map->allocated_size = 2<<6;
    map->data = calloc(2<<6, sizeof(struct MapEntry *));
    map->copy_value = true;
    map->hash_function = &generic_hash;
    map->equals_function = &generic_equals;
    return map;
}

void Map_set_operations(struct Map *map,
                        unsigned long (*hash_function)(void *, size_t),
                        bool (*equals_function)(void *, size_t, void *, size_t)) {
    map->hash_function = hash_function;
    map->equals_function = equals_function;
}

unsigned int Map_hash(struct Map *map, void *key, size_t key_length) {
    return map->hash_function(key, key_length) % map->allocated_size;
}

bool Map_contains(struct Map *map, void *key, size_t key_length) {
    return Map_get(map, key, key_length) != NULL;
}

void *Map_get(struct Map *map, void *key, size_t key_length) {
    unsigned int hash = Map_hash(map, key, key_length);
    struct MapEntry *node = map->data[hash];
    while(node != NULL) {
        if(map->equals_function(key, key_length, node->key, node->key_length)) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void Map_remove(struct Map *map, void *key, size_t key_length) {
    unsigned long hash = map->hash_function(key, key_length);
    unsigned int local = hash % map->allocated_size;
    struct MapEntry *node = map->data[local];
    while(node != NULL) {
        if(node->hash == hash) {
            if(node->prev == NULL
               && map->equals_function(key, key_length,
                                       node->key, node->key_length)) {
                map->data[local] = node->next;
            } else if(node->prev != NULL) {
                node->prev->next = node->next;
            }
            map->size--;
            MapEntry_delete(node);
            return;
        }
        node = node->next;
    }
}

void Map_put_raw(struct Map *map, void *key, size_t key_length,
                 unsigned long hash, void *value, size_t value_length) {
    unsigned int local = hash % map->allocated_size;
    struct MapEntry *old = map->data[local];
    if(old == NULL) {
        map->data[local] = MapEntry_new(key, key_length, hash,
                                        value, value_length, map->copy_value);
    } else {
        if(old->hash == hash) {
            MapEntry_set(old, value, value_length);
            return;
        }
        while(old->next != NULL) {
            if(old->hash == hash
               && map->equals_function(key, key_length,
                                       old->key, old->key_length)) {
                MapEntry_set(old, value, value_length);
                return;
            }
            old = old->next;
        }
        old->next = MapEntry_new(key, key_length, hash, value, value_length,
                                 map->copy_value);
        old->next->prev = old;
    }
    map->size++;
    if((double)map->size/map->allocated_size > 0.75) {
        Map_resize(map, map->allocated_size * 2);
    }
    return;
}

void Map_put(struct Map *map, void *key, size_t key_length,
             void *value, size_t value_length) {
    Map_put_raw(map, key, key_length, map->hash_function(key, key_length),
                value, value_length);
}

struct MapEntry** Map_entrys(struct Map *map) {
    struct MapEntry** entrys = malloc(map->size * sizeof(struct MapEntry *));
    struct MapEntry* entry;
    unsigned int pos = 0;
    for(unsigned int i = 0; i < map->allocated_size; i++) {
        entry = map->data[i];
        while(entry != NULL) {
            entrys[pos++] = entry;
            entry = entry->next;
        }
    }
    return entrys;
}

void Map_resize(struct Map *map, unsigned int new_size) {
    struct MapEntry** entrys = Map_entrys(map);
    free(map->data);
    map->allocated_size = new_size;
    map->data = calloc(new_size, sizeof(struct MapEntry *));
    unsigned int current_size = map->size;
    map->size = 0;
    for(unsigned int i = 0; i < current_size; i++) {
        Map_put_raw(map, entrys[i]->key, entrys[i]->key_length, entrys[i]->hash,
                    entrys[i]->value, entrys[i]->value_length);
        MapEntry_delete(entrys[i]);
    }
    free(entrys);
}

void Map_delete(struct Map *map) {
    struct MapEntry** entrys = Map_entrys(map);
    unsigned int size = map->size;
    for(unsigned int i = 0; i < size; i++) {
        MapEntry_delete(entrys[i]);
    }
    free(entrys);
    free(map->data);
    free(map);
}
