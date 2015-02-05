#include "tila.h"

struct Tokenizer *Tokenizer_new(char *source) {
    struct Tokenizer *ti = (struct Tokenizer *)malloc(sizeof(struct Tokenizer));
    size_t len = strlen(source);
    ti->matcher = TTMatcher_new();
    ti->source = (char *)malloc((len + 2) * sizeof(char));
    memcpy(ti->source, source, len);
    ti->source[len] = '\n';
    ti->source[len + 1] = '\0';
    ti->tokens = Vector_new();
    ti->pos = 0;
    ti->line = 1;
    ti->column = 1;
    ti->in_string = false;
    ti->in_comment = false;
    return ti;
}

void Tokenizer_add_new(struct Tokenizer *ti) {
    struct Token *token;
    if(!Vector_empty(ti->tokens)) {
        token = Vector_top(ti->tokens);
        if(Token_length(token) == 0) {
            Token_delete(Vector_pop(ti->tokens));
        }
    }
    token = Token_new(ti->pos, ti->pos, ti->line, ti->column);
    Vector_push(ti->tokens, token);
}

void Tokenizer_add_to_last(struct Tokenizer *ti) {
    if(Vector_empty(ti->tokens)) {
        Tokenizer_add_new(ti);
    }
    struct Token *last = Vector_top(ti->tokens);
    last->end++;
}

void Tokenizer_move_last(struct Tokenizer *ti) {
    struct Token *last = Vector_top(ti->tokens);
    last->start++;
    last->end++;
    last->column++;
}

void Tokenizer_tokenize(struct Tokenizer *ti) {
    size_t len = strlen(ti->source);
    while(ti->pos < len) {
        char current = ti->source[ti->pos];
        bool current_digit = t_is_digit(current);
        bool current_alpha = t_is_alpha(current);
        char last_char = ' ';
        unsigned int last_len = 0;
        bool last_digit = false;
        bool last_alpha = false;
        if(!Vector_empty(ti->tokens)) {
            struct Token *last = Vector_top(ti->tokens);
            if(last->end == ti->pos) {
                last_len = Token_length(last);
                if(last_len > 0) {
                    last_char = ti->source[last->end - 1];
                    last_digit = t_is_digit(last_char);
                    last_alpha = t_is_alpha(last_char);
                }
            }
        }
        if(ti->in_comment && current != '\n') {
            ti->column++;
            ti->pos++;
            continue;
        }
        if(ti->in_string && current != '\"') {
            Tokenizer_add_to_last(ti);
            ti->column++;
            ti->pos++;
            continue;
        }
        switch(current) {
        case '#':
            ti->in_comment = true;
            break;
        case '\"':
            if(!ti->in_string) {
                Tokenizer_add_new(ti);
            }
            Tokenizer_add_to_last(ti);
            ti->in_string = !ti->in_string;
            break;
        case '\n':
            Tokenizer_add_new(ti);
            Tokenizer_add_to_last(ti);
            Tokenizer_add_new(ti);
            ti->line++;
            ti->column = 0;
            ti->in_comment = false;
            break;
        case ' ': // count indent plz
            if(last_len > 0 && last_char == ' ') {
                Tokenizer_add_to_last(ti);
            } else if(ti->column == 1) {
                Tokenizer_add_new(ti);
                Tokenizer_add_to_last(ti);
            } else {
                Tokenizer_add_new(ti);
                Tokenizer_move_last(ti);
            }
            break;
        case '?':
            if(last_len == 1 && last_char == '!') {
                Tokenizer_add_to_last(ti);
                break;
            }
            Tokenizer_add_new(ti);
            Tokenizer_add_to_last(ti);
            break;
        case '=':
            if(last_len == 1) {
                if(last_char == '=' || last_char == '!' ||
                   last_char == '<' || last_char == '>') {
                    Tokenizer_add_to_last(ti);
                    break;
                }
            }
            Tokenizer_add_new(ti);
            Tokenizer_add_to_last(ti);
            break;
        case '&':
        case '|':
            if(last_len == 1 && last_char == current) {
                Tokenizer_add_to_last(ti);
                break;
            }
            Tokenizer_add_new(ti);
            Tokenizer_add_to_last(ti);
            break;
        case '>':
            if(last_len == 1 && last_char == '-') {
                Tokenizer_add_to_last(ti);
                break;
            }
        case '<':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '[':
        case ']':
        case '!':
        case ',':
        case '%':
            Tokenizer_add_new(ti);
            Tokenizer_add_to_last(ti);
            break;
        default:
            if((last_alpha && (current_alpha || current_digit)) ||
               (last_digit && current_digit)) {
                Tokenizer_add_to_last(ti);
                break;
            }
            if(current_digit || current_alpha) {
                Tokenizer_add_new(ti);
                Tokenizer_add_to_last(ti);
                break;
            }
            ASSERT(1, "Unknown character met while tokenization %d:%d '%c'",
                  ti->line, ti->column, current);
        }
        ti->column++;
        ti->pos++;
    }
    struct Token *token;
    if(!Vector_empty(ti->tokens)) {
        token = Vector_top(ti->tokens);
        if(Token_length(token) == 0) {
            Token_delete(Vector_pop(ti->tokens));
        }
    }
    unsigned int tlen = Vector_size(ti->tokens);
    for(unsigned int i = 0; i < tlen; i++) {
        token = Vector_get(ti->tokens, i);
        TTMatcher_match(ti->matcher, token, ti->source);
        ASSERT(token->type == NULL, "Unknown token met while tokenization %d:%d",
              token->line, token->column)
    }
}

void Tokenizer_delete(struct Tokenizer *ti) {
    TTMatcher_delete(ti->matcher);
    free(ti->source);
    unsigned int tlen = Vector_size(ti->tokens);
    for(unsigned int i = 0; i < tlen; i++) {
        Token_delete(Vector_pop(ti->tokens));
    }
    Vector_delete(ti->tokens);
    free(ti);
}
