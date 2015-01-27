#ifndef TOKEN_H
#define TOKEN_H

#include "tila.h"

/**
 * @brief Holds information about a token
 * @field start Starting position of the token
 * @field end Ending position of the token
 * @field line Line number of the start of the token
 * @field column Column number of the start of the token
 */
struct Token {
    unsigned int start, end, line, column;
    char *content;
    struct TokenType *type;
};

/**
 * @brief Creates a new token
 * @field start Starting position of the token
 * @field end Ending position of the token
 * @field line Line number of the start of the token
 * @field column Column number of the start of the token
 */
struct Token *Token_new(unsigned int start, unsigned int end,
                        unsigned int line, unsigned int column);

/**
 * @brief How long is the token (endposition - startposition)
 * @returns The length of the token
 */
unsigned int Token_length(struct Token *token);

/**
 * @brief If the token is an indentation, the length of it
 * @returns The length of the token if it is an indentation, -1 else
 */
int Token_indent_length(struct Token *token);

/**
 * @brief Prints the token to stdout for debug purposes
 * @param src The source code that holds the characters for printing
 */
void Token_print(struct Token *token, const char *src);

/**
 * @brief Returns a string of the content of the token. Don't free this
 *        as it will be freed automatically at Token_delete.
 * @param src The source code tha tholds the characters for copying
 * @returns An allocated string of the content
 */
char *Token_content(struct Token *token, const char *src);

/**
 * @brief Deletes the token
 */
void Token_delete(struct Token *token);


#endif
