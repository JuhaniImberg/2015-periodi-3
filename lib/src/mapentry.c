#include "tila.h"

struct MapEntry *MapEntry_new(const char *key, unsigned long hash, void *value) {
    struct MapEntry *entry = (struct MapEntry *) malloc(sizeof(struct MapEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    entry->prev = NULL;
    entry->hash = hash;
    return entry;
}

void MapEntry_set(struct MapEntry *entry, void *value) {
    entry->value = value;
}

void MapEntry_delete(struct MapEntry *entry) {
    free(entry);
}
