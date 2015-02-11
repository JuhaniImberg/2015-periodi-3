#include "tila.h"

struct Environment *Environment_new(char *src) {
    struct Environment *env = malloc(sizeof(struct Environment));
    env->src = src;
    env->symbols = Map_new();
    env->parent = NULL;
    return env;
}

struct Environment *Environment_new_sub(struct Environment *env) {
    struct Environment *new = Environment_new(env->src);
    new->parent = env;
    return new;
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
    Map_delete(env->symbols);
    free(env);
}
