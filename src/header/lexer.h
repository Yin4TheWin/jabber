#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct LEXER_STATE
{
    char current;
    unsigned int index;
    char* input;
} lexer_state;

lexer_state* init(char* src);

void advance_state(lexer_state* lexer);

void ignore_whitespace(lexer_state* lexer);

token* get_next_token(lexer_state* lexer);

token* collect_string(lexer_state* lexer, int type_of_quote);

token* collect_Id(lexer_state* lexer);

char* to_string(lexer_state* lexer);
#endif