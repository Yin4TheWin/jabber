#include "header/token.h"
#include <stdlib.h>

token* init_token(int type, char* value){
    token* token = calloc(1, sizeof(struct TOKEN));
    token->type=type;
    token->value=value;
}