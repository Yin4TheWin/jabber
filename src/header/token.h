#ifndef TOKEN_H
#define TOKEN_H
#include <stdlib.h>
typedef struct TOKEN{
    enum {
    Id, Quantifier, Condition, Assign, Iter, As, Containment, Connective, Name, EOF,
    Int, Float, Str, List, Lang, Fun,
    All, Exist, Unique, 
    SuchThat, In, Accepts, Rejects, Loner, 
    Return, 
    And, Or, Xor, 
    Eq, Neq, Lt, Gt, Leq, Geq, 
    Add, Sub, Mult, Div, Mod,
    Lparen, Rparen, LBracket, RBracket, Comma, Point
    } type;

    char* value;
} token;

token* init_token(int type, char* value);
#endif