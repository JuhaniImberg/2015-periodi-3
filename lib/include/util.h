#ifndef UTIL_H
#define UTIL_H

#include "tila.h"

/**
 * @brief UNIX ELF object hash for a char *
 * @param key This will be casted to a char *
 * @returns The hash of the key
*/
unsigned long string_hash(void *key);

/**
 * @brief Compares two strings
 * @param a The first string, will be casted to char *
 * @param b The second string, will be casted to char *
 * @returns True if the strings are equal
 */
bool string_equals(void *a, void *b);

/**
 * @brief Hashes a number
 * @param key This will be casted to a unsigned long
 * @returns The hash of the key
 */
unsigned long number_hash(void *key);

/**
 * @brief Compares two numbers
 * @param a The first number, will be casted to a unsigned long
 * @param b The second number, will be casted to a unsigned long
 * @returns True if the numbers are equal
 */
bool number_equals(void *a, void *b);

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
