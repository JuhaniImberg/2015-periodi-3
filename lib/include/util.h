#ifndef UTIL_H
#define UTIL_H

#include "tila.h"

/**
 * @brief UNIX ELF object hash for a char *
 * @param key This will be casted to a char *
 * @returns The hash of the key
*/
unsigned long generic_hash(void *key, size_t key_length);

/**
 * @brief Compares two strings
 * @param a The first string, will be casted to char *
 * @param b The second string, will be casted to char *
 * @returns True if the strings are equal
 */
bool generic_equals(void *a, size_t a_length, void *b, size_t b_length);

/**
 * @brief Is char a digit
 * @param c The character to check
 * @returns True if it's a digit
 */
bool t_is_digit(char c);

/**
 * @brief Is char a valid character for an identifier
 * @param c The character to check
 * @returns True if the character is a valid part of an identifier
 */
bool t_is_alpha(char c);

#endif
