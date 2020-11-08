SOURCE_LEX=parser.lex
SOURSE_YACC=parser.yacc
LEX_YY_C=lex.yy.c
Y_TAB_C=y.tab.c
Y_TAB_H=y.tab.h
BINNAME=parser

all: lex yacc cc
lex:
	lex $(SOURCE_LEX)
yacc:
	yacc -v -d $(SOURSE_YACC)
cc:
	cc $(Y_TAB_C) $(LEX_YY_C) -o $(BINNAME)
clean:
	rm -f $(BINNAME) $(SOURCE)
	rm -f $(LEX_YY_C)
	rm -f $(Y_TAB_C)
	rm -f $(Y_TAB_H)
rebuild: clean all
