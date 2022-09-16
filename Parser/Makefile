all: 
	bison -d -t fb3-2.y
	flex fb3-2.l
	gcc lex.yy.c fb3-2.tab.c fb3-2funcs.c -lm

clean:
	rm -f fb3-2 \
	fb3-2.tab.c fb3-2.tab.h fb3-2.lex.c \
	fb3-2.output a.out
