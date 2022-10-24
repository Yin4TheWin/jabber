all:
	gcc -c -g src/lexer.c -o lexer.o
	gcc -c -g src/token.c -o token.o
	gcc -c -g src/main.c -o main.o
	gcc lexer.o token.o main.o -g -o jabber
