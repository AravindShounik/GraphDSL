all: 
	bison -d -t parser.y
	flex lexer.l
	g++ lex.yy.c parser.tab.c funcs.c -lm

clean:
	rm -f parser \
	parser.tab.c parser.tab.h parser.lex.c lex.yy.c \
	parser.output a.out
