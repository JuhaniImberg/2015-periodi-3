#include "tila.h"

const char *src = "HELLO WORLD ";

int main() {
    printf("%s %lu", src, elf_hash(src));
    return 0;
}
