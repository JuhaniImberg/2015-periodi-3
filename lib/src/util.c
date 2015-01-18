#include "tila.h"

unsigned long string_hash(void *key) {
    char *rkey = (char *)key;
    unsigned long h, g;
    size_t len = strlen(key);
    h = 0;
    for(unsigned int i = 0; i < len; i++) {
        h = (h << 4) + rkey[i];
        g = h & 0xf0000000l;
        if(g != 0) {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h;
}

bool string_equals(void *a, void *b) {
    return strcmp((char *)a, (char *)b) == 0;
}

unsigned long number_hash(void *key) {
    return *(unsigned long *)key;
}

bool number_equals(void *a, void *b) {
    return (*(unsigned long *)a) == (*(unsigned long *)b);
}

bool t_is_digit(char c) {
    return ('0' <= c && c <= '9');
}

bool t_is_alpha(char c) {
    return (('A' <= c && c <= 'Z') ||
            ('a' <= c && c <= 'z') ||
            c == '_');
}
