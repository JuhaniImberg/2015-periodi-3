#ifndef MAPENTRY_H
#define MAPENTRY_H

struct MapEntry {
    unsigned long hash;
    const char *key;
    void *value;
    struct MapEntry *next;
    struct MapEntry *prev;
};

struct MapEntry *MapEntry_new(const char *key, unsigned long hash, void *value);
void MapEntry_set(struct MapEntry *entry, void *value);
void MapEntry_delete(struct MapEntry *entry);

#endif
