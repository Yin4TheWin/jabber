all:
	gcc -c -g lexer.c -o lexer.o
	gcc -c -g token.c -o token.o
	gcc -c -g main.c -o main.o
	gcc lexer.o token.o main.o -g -o jabber
