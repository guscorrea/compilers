etapa2: lex.yy.c
	gcc -o etapa2 lex.yy.c
lex.yy.c: scanner.l
	lex scanner.l
scanner.l: parser.y
	yacc parser.y -d
clean:
	rm lex.yy.c etapa2
