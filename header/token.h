#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN{
    enum {
    Id, Assign, EOF,
    Lparen, Rparen,
    Int, Float, Str, List, Lang, Fun,
    All, Exist, Unique, 
    SuchThat, In, Accepts, Rejects, Loner, 
    Iter, As, Return, 
    And, Or, Xor, 
    Eq, Neq, Lt, Gt, Leq, Geq, 
    Add, Sub, Mult, Div, Mod
    } type;

    char* value;
} token;

token* init_token(int type, char* value);
#endif