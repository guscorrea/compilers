etapa3: y.tab.o lex.yy.o main.o hash.o astree.o
	gcc -o etapa3 y.tab.o lex.yy.o main.o hash.o astree.o
y.tab.o: y.tab.c
	gcc -c y.tab.c
lex.yy.o: lex.yy.c y.tab.c
	gcc -c lex.yy.c
hash.o: hash.c
	gcc -c hash.c
main.o: main.c
	gcc -c main.c
astree.o: astree.c
	gcc -c astree.c
lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l
y.tab.c: parser.y
	yacc -d parser.y
clean:
	rm lex.yy.c lex.yy.h etapa3 y.tab.c y.tab.h *.o
