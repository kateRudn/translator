D			[0-9]+
L			[a-zA-Z_][a-zA-Z0-9_]*

%{
#include <stdio.h>
#include "y.tab.h"
int yylex();
int c;
void count();
%}

%%

"else"			{ count(); return ELSE; }
"if"			{ count(); return IF; }
"return"		{ count(); return RETURN; }
"while"			{ count(); return WHILE; }
"print"			{ count(); return PRINT; }

{D}			{ count(); yylval.value = atoi(yytext); return CONST; }
{L}			{ count(); yylval.name = strdup(yytext); return IDENTIFIER; }

"="			{ count(); return ASSIGN; }
"+="			{ count(); return ADD_ASSIGN; }
"-="			{ count(); return SUB_ASSIGN; }
"*="			{ count(); return MUL_ASSIGN; }
"/="			{ count(); return DIV_ASSIGN; }
"%="			{ count(); return MOD_ASSIGN; }
"&="			{ count(); return AND_ASSIGN; }
"^="			{ count(); return XOR_ASSIGN; }
"|="			{ count(); return OR_ASSIGN; }

">>="			{ count(); return RIGHT_ASSIGN; }
"<<="			{ count(); return LEFT_ASSIGN; }

">>"			{ count(); return SHR; }
"<<"			{ count(); return SHL; }

"++"			{ count(); return INC; }
"--"			{ count(); return DEC; }

"&&"			{ count(); return AND_OP; }
"||"			{ count(); return OR_OP; }
"<"			{ count(); return LE_OP; }
">"			{ count(); return GE_OP; }
"<="			{ count(); return LE_OP_; }
">="			{ count(); return GE_OP_; }
"=="			{ count(); return EQ_OP; }
"!="			{ count(); return NE_OP; }
"!"			{ count(); return NOT; }

";"			{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","			{ count(); return(','); }
"("			{ count(); return L_SK; }
")"			{ count(); return R_SK; }

"-"			{ count(); return SUB; }
"+"			{ count(); return ADD; }
"*"			{ count(); return MUL; }
"&"			{ count(); return AND; }
"/"			{ count(); return DIV; }
"%"			{ count(); return MOD; }
"^"			{ count(); return XOR; }
"|"			{ count(); return OR; }


[ \t\v\n\f]		{ count(); }
.			{}

%%

int yywrap()
{
	return(1);
}


int column = 0;
int string=1;

void count()
{

	for (int i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			{column = 0; string++;}
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	//ECHO;
}
