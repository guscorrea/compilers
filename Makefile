etapa5: y.tab.o lex.yy.o main.o hash.o astree.o semantic.o tacs.o
	gcc -o etapa5 y.tab.o lex.yy.o main.o hash.o astree.o semantic.o tacs.o
y.tab.o: y.tab.c
	gcc -c y.tab.c
lex.yy.o: lex.yy.c y.tab.c
	gcc -c lex.yy.c
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
astree.o: astree.c
	gcc -c astree.c
semantic.o: semantic.c
	gcc -c semantic.c
tacs.o: tacs.c
	gcc -c tacs.c
lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l
y.tab.c: parser.y lex.yy.c
	yacc parser.y -d
clean:
	rm lex.yy.c lex.yy.h etapa4 y.tab.c y.tab.h *.o
