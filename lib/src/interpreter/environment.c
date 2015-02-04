#include "tila.h"

struct Environment *Environment_new(char *src) {
    struct Environment *env = malloc(sizeof(struct Environment));
    env->src = src;
    return env;
}

void Environment_delete(struct Environment *env) {
    free(env);
}
