#ifndef LEXER_H
#define LEXER_H
#include "token.h"
typedef struct LEXER_STATE
{
    char current;
    unsigned int index;
    char* input;
} lexer_state;

lexer_state* init(char* src);

void advance_state(lexer_state* lexer);

void ignore_whitespace(lexer_state* lexer);

token* lexer_get_next_token(lexer_state* lexer);

token* collect_string(lexer_state* lexer, int type_of_quote);

token* collect_Id(lexer_state* lexer);

char* to_string(lexer_state* lexer);
#endif