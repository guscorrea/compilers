etapa1: lex.yy.c
	gcc lex.yy.c -o etapa1
lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm lex.yy.c etapa1