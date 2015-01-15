#include "tila.h"

struct Map *Map_new() {
    struct Map *map = (struct Map *) malloc(sizeof(struct Map));
    map->size = 0;
    map->allocated_size = 2<<6;
    map->data = calloc(2<<6, sizeof(struct MapEntry));
    return map;
}

unsigned int Map_hash(struct Map *map, const char *key) {
    return elf_hash(key) % map->allocated_size;
}

bool Map_contains(struct Map *map, const char *key) {
    return Map_get(map, key) != NULL;
}

void *Map_get(struct Map *map, const char *key) {
    unsigned int hash = Map_hash(map, key);
    struct MapEntry *node = map->data[hash];
    while(node != NULL) {
        if(strcmp(key, node->key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void Map_remove(struct Map *map, const char *key) {
    unsigned long hash = elf_hash(key);
    unsigned int local = hash % map->allocated_size;
    struct MapEntry *node = map->data[local];
    while(node != NULL) {
        if(node->hash == hash) {
            if(node->prev == NULL) {
                map->data[local] = node->next;
            } else {
                node->prev->next = node->next;
            }
            map->size--;
            MapEntry_delete(node);
            return;
        }
        node = node->next;
    }
}

void Map_put_raw(struct Map *map, const char* key, unsigned long hash, void *value) {
    unsigned int local = hash % map->allocated_size;
    struct MapEntry *old = map->data[local];
    if(old == NULL) {
        map->data[local] = MapEntry_new(key, hash, value);
    } else {
        if(old->hash == hash) {
            MapEntry_set(old, value);
            return;
        }
        while(old->next != NULL) {
            if(old->hash == hash) {
                MapEntry_set(old, value);
                return;
            }
            old = old->next;
        }
        old->next = MapEntry_new(key, hash, value);
        old->next->prev = old;
    }
    map->size++;
    if((double)map->size/map->allocated_size > 0.75) {
        Map_resize(map, map->allocated_size * 2);
    }
    return;
}

void Map_put(struct Map *map, const char *key, void *value) {
    Map_put_raw(map, key, elf_hash(key), value);
}

struct MapEntry** Map_entrys(struct Map *map) {
    struct MapEntry** entrys = (struct MapEntry**) malloc(map->size * sizeof(struct MapEntry));
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
    map->data = calloc(new_size, sizeof(struct MapEntry));
    unsigned int current_size = map->size;
    map->size = 0;
    for(unsigned int i = 0; i < current_size; i++) {
        Map_put_raw(map, entrys[i]->key, entrys[i]->hash, entrys[i]->value);
    }
    for(unsigned int i = 0; i < current_size; i++) {
        free(entrys[i]);
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
