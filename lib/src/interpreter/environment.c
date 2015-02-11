#include "tila.h"

struct Environment *Environment_new(struct GC *gc, char *src) {
    struct Environment *env = malloc(sizeof(struct Environment));
    env->src = src;
    env->symbols = Map_new();
    env->parent = NULL;
    env->gc = gc;
    return env;
}

struct Environment *Environment_new_sub(struct Environment *env) {
    struct Environment *new = Environment_new(env->gc, env->src);
    new->parent = env;
    env->gc->env = new;
    return new;
}

void Environment_mark(struct Environment *env) {
    struct MapEntry** entrys = Map_entrys(env->symbols);
    for(size_t i = 0; i < env->symbols->size; i++) {
        struct MapEntry *entry = entrys[i];
        Node_mark(entry->value);
    }
    free(entrys);
    if(env->parent != NULL) {
        Environment_mark(env->parent);
    }
}

struct Node *Environment_get(struct Environment *env,
                             char *key) {
    void *value = Map_get(env->symbols, key, strlen(key) + 1);
    if(value == NULL) {
        ASSERT(env->parent == NULL, "Unknown symbol access");
        return Environment_get(env->parent, key);
    }
    return value;
}

void Environment_put(struct Environment *env,
                     char *key,
                     struct Node *value) {
    Map_put(env->symbols, key, strlen(key) + 1, value, sizeof(struct Node));
}

bool Environment_contains(struct Environment *env,
                          char *key) {
    return Map_contains(env->symbols, key, strlen(key) + 1);
}

void Environment_delete(struct Environment *env) {
    if(env->parent != NULL && env->gc->env == env) {
        env->gc->env = env->parent;
    }
    Map_delete(env->symbols);
    free(env);
}
