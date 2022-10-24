#include "header/lexer.h"
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* fp)
{
    char* buffer = 0;
    long length;
    FILE* f = fopen(fp, "rb");

    if(f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = malloc(length);

        if (buffer)
            fread(buffer, 1, length, f);

        fclose(f);
        return buffer;
    }
    printf("Error reading file");
    return buffer;
}

int main(int argc, char** argv){
    if(argc>=2){
        lexer_state* lexer=init(read_file(argv[1]));
        token* token;
        while ((token=get_next_token(lexer))!=NULL){
            printf("(%d,%s)\n", token->type, token->value);
        }
    }
    return 0;
}