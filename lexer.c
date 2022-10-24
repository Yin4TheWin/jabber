#include "header/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum{
    Single, Double
};

char* to_string(lexer_state* lexer){
    char* str=malloc(2*sizeof(char));
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
    return lexer->index<strlen(lexer->input)&&lexer->current!='\0';
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
    token* token=init_token(token_type, to_string(lexer));
    advance_state(lexer);
    return token;
}

token* collect_string(lexer_state* lexer, int type_of_quote){
    advance_state(lexer);

    char curr=lexer->current;

    char* value=calloc(1,sizeof(char));
    value[0]='\0';

    while((curr!='"'&&type_of_quote==Double) || (curr!='\''&&type_of_quote==Single)){
        char* str=to_string(lexer);
        value=realloc(value, (strlen(value)+strlen(str)+1)*sizeof(char));
        strcat(value, str);
        advance_state(lexer);
    }

    advance_state(lexer);

    return init_token(Str, value);
}

token* collect_Id(lexer_state* lexer){
    char* value=calloc(1,sizeof(char));
    value[0]='\0';

    while(isalnum(lexer->current) || lexer->current=='_'){
        char* str=to_string(lexer);
        value=realloc(value, (strlen(value)+strlen(str)+1));
        strcat(value, str);
        advance_state(lexer);
    }
    int type=0;

    //Sorry this is about to get a bit ugly...
    if(strcmp(value,"int")==0 || strcmp(value,"float")==0 || strcmp(value,"string")==0 || strcmp(value,"list")==0 || strcmp(value,"language")==0)
        type=Id;
    else if(strcmp(value,"forall")==0 || strcmp(value,"exists")==0 || strcmp(value,"unique")==0)
        type=Quantifier;
    else if(strcmp(value,"accepts")==0 || strcmp(value,"rejects")==0)
        type=Condition;
    else if(strcmp(value,"in")==0 || strcmp(value,"rejected")==0 || strcmp(value,"loner")==0)
        type=Containment;
    else if(strcmp(value,"union")==0 || strcmp(value,"concat")==0 || strcmp(value,"star")==0)
        type=Connective;
    else if(strcmp(value,"st")==0)
        type=SuchThat;
    else if(strcmp(value,"iterate")==0)
        type=Iter;
    else if(strcmp(value,"as")==0)
        type=As;
    else
        type=Name;
    return init_token(type, value);
}

token* get_next_token(lexer_state* lexer){
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
            case ',':
                return advance_with_token(lexer, Comma);
                break;
            case '.':
                return advance_with_token(lexer, Point);
                break;
            case '"':
                return collect_string(lexer, Double);
                break;
            case '\'':
                return collect_string(lexer, Single);
                break;
        }
    }
    return NULL;
}