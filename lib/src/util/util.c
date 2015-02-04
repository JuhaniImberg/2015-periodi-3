#include "tila.h"

unsigned long generic_hash(void *key, size_t key_length) {
    char *rkey = key;
    unsigned long h, g;
    h = 0;
    for(unsigned int i = 0; i < key_length; i++) {
        h = (h << 4) + rkey[i];
        g = h & 0xf0000000l;
        if(g != 0) {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h;
}

bool generic_equals(void *a, size_t a_length, void *b, size_t b_length) {
    if(a_length != b_length) {
        return false;
    }
    return memcmp(a, b, a_length) == 0;
}

bool t_is_digit(char c) {
    return ('0' <= c && c <= '9');
}

bool t_is_alpha(char c) {
    return (('A' <= c && c <= 'Z') ||
            ('a' <= c && c <= 'z') ||
            c == '_');
}
