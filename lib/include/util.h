#ifndef UTIL_H
#define UTIL_H

#include "tila.h"

/* UNIX ELF object hash */
unsigned long elf_hash(const char *key);

bool t_is_digit(char c);
bool t_is_alpha(char c);

#endif
