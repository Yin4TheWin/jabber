#include "header/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum{
    Single, Double
};

char* to_string(lexer_state* lexer){
    char str[2];
    str[0]=lexer->current;
    str[1]='\0';
    return str;
}

lexer_state* init(char* input)
{
    lexer_state* lexer = calloc(1, sizeof(struct LEXER_STATE));
    lexer->input=input;
    lexer->index=0;
    lexer->current=input[lexer->index];
    return lexer;
}

int valid(lexer_state* lexer){
    return lexer->index<strlen(lexer->input);
}

void advance_state(lexer_state* lexer){
    if(valid(lexer)){
        lexer->index+=1;
        lexer->current=lexer->input[lexer->index];
    }
}

void ignore_whitespace(lexer_state* lexer){
    while(lexer->current==' '||lexer->current=='\n'){
        advance_state(lexer);
    }
}

token* advance_with_token(lexer_state* lexer, int token_type){
    advance_state(lexer);
    return init_token(token_type, to_string(lexer));
}

token* collect_string(lexer_state* lexer, int type_of_quote){
    advance_state(lexer);
    char curr=lexer->current;
    char* value=calloc(1,sizeof(char));

    while((curr!='"'&&type_of_quote==Double) || (curr!='\''&&type_of_quote==Single)){
        char* str=to_string(lexer);
        value=realloc(value, (strlen(value)+strlen(str)+1));
        strcat(value, str);
        advance_state(lexer);
    }

    return init_token(Str, value);
}

token* collect_Id(lexer_state* lexer){
    char curr=lexer->current;
    char* value=calloc(1,sizeof(char));

    while(isalnum(lexer->current)){
        char* str=to_string(lexer);
        value=realloc(value, (strlen(value)+strlen(str)+1));
        strcat(value, str);
        advance_state(lexer);
    }
    return init_token(Id, value);
}

token* lexer_get_next_token(lexer_state* lexer){
    while(valid(lexer)){
        ignore_whitespace(lexer);
        if(isalnum(lexer->current))
            return collect_Id(lexer);
        switch(lexer->current){
            case '*':
                return advance_with_token(lexer, Mult);
                break;
            case '/':
                return advance_with_token(lexer, Div);
                break;
            case '%':
                return advance_with_token(lexer, Mod);
                break;
            case '+':
                return advance_with_token(lexer, Add);
                break;
            case '-':
                return advance_with_token(lexer, Sub);
                break;
            case '=':
                return advance_with_token(lexer, Assign);
                break;
            case '(':
                return advance_with_token(lexer, Lparen);
                break;
            case ')':
                return advance_with_token(lexer, Rparen);
                break;
            case '"':
                return collect_string(lexer, Double);
                break;
            case '\'':
                return collect_string(lexer, Single);
                break;
        }
    }
    return init_token(EOF, "\0");
}