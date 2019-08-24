all: main.c scanner/ex1.l
	./myscanner < teste.txt
myscanner: main.c ex1.l
	lex ex1.l
	gcc main.c lex.yy.c -o myscanner 
