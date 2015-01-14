#include "tila.h"

unsigned long elf_hash(const char *key) {
    unsigned long h, g;
    size_t len = strlen(key);
    h = 0;
    for(unsigned int i = 0; i < len; i++) {
        h = (h << 4) + key[i];
        g = h & 0xf0000000l;
        if(g != 0) {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h;
}
