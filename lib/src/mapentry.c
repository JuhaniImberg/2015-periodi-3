#include "tila.h"

struct MapEntry *MapEntry_new(void *key, size_t key_length, unsigned long hash,
                              void *value, size_t value_length) {
    struct MapEntry *entry = malloc(sizeof(struct MapEntry));
    entry->key = malloc(key_length);
    memcpy(entry->key, key, key_length);
    entry->value = malloc(value_length);
    memcpy(entry->value, value, value_length);

    entry->key_length = key_length;
    entry->value_length = value_length;

    entry->next = NULL;
    entry->prev = NULL;
    entry->hash = hash;
    return entry;
}

void MapEntry_set(struct MapEntry *entry, void *value, size_t value_length) {
    free(entry->value);
    entry->value = malloc(value_length);
    entry->value_length = value_length;
    memcpy(entry->value, value, value_length);
}

void MapEntry_delete(struct MapEntry *entry) {
    free(entry->key);
    free(entry->value);
    free(entry);
}
