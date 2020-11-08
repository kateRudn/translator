%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int yyerror(const char *s);
int yylex();
extern int yychar;
FILE *out;

char check_num[10]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char stack[32][256];
char stack_command[5][256];
int g_hstack=0;
int g_hstack_comm=0;

char throw_expr[5];
char last[5];
char g_reg[18][5]={"0","EAX","EBX","ECX", "EDX", "ESI", "EDI", "EBP", "ESP", "EIX", "EIP", "EGX", "EHX", "EKX", "ELX", "EMX", "ENX", "EPX"}; //name of registers
int g_bool_reg[18]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; //bool is free
int g_bool_tmp[18]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //bool is tmp
int g_bool_xor[18]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //bool is used
struct list_identifier
{
char ident[256]; //name identifier
int reg; //number of register
} list[20];

int loop=1;
int g_loop=1;
int b_loop=0;

int label=0; //num of arr
int g_label=1; //metka
int arr_label[20]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int b_cmp=0;

void pop();
void push(char* arg);
void pop_command();
void push_command(char *arg);
void new_register();
int search_register();
int search_identifier (char* id);
int check_number_ident(int f);
void swap(int a, int b);
void check_command();
void cmp();
void push_label(char *command);
void pop_label();
void last_value();

void cmp()
{
	b_cmp=1;
	if (check_number_ident(g_hstack-1)&&check_number_ident(g_hstack-2))
	{
		new_register();
	}
	if (!check_number_ident(g_hstack-1)&&check_number_ident(g_hstack-2))
				{
					swap(g_hstack-1, g_hstack-2);
				} 
	fprintf (out, "CMP %s, %s\n", stack[g_hstack-2], stack[g_hstack-1]);
	printf ("CMP %s, %s\n", stack[g_hstack-2], stack[g_hstack-1]); 
}

void swap(int a, int b)
{
	char tmp[5];
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,stack[a]);
	strcpy(stack[a],stack[b]);
	strcpy(stack[b],tmp);
}

int check_number_ident(int f)
{
for (int i=0; i<10; i++)
	{
		if (stack[f][0]==check_num[i])
		{
			return 1; //if number
		}
	}
return 0; //else
}

void new_register()
{

//if (flag_rez)
	{
		int find=search_register();
		if (!check_number_ident(g_hstack-1)&&check_number_ident(g_hstack-2))
		{
			swap(g_hstack-1, g_hstack-2);
		}
		fprintf(out, "LOAD %s, %s\n", g_reg[find], stack[g_hstack-1]);
		printf("LOAD %s, %s\n", g_reg[find], stack[g_hstack-1]);
		g_bool_tmp[find]=1;
		pop();
		push(g_reg[find]);
	}
}

int search_register_by_name(char *rfind)
{
	for (int i=1; i<18; i++)
	{
		if (!strcmp(g_reg[i], rfind))
		{
			return i;
		}
	}
	return 0;
}

int search_register()
{
	for (int j=1; j<18; j++)
		{
			if (g_bool_reg[j]) //if is free
				{
					g_bool_reg[j]=0; //null
					g_bool_xor[j]=1;
					return j; //number of register
				}
		}
	return 0;

}

int search_identifier (char* id)
{

for (int i=1; i<20; i++)
	{
	   if (!strcmp(id, list[i].ident))
		{
			return list[i].reg; //ret number of register
		}
	}
for (int i=1; i<20; i++)
	{
		if (!list[i].reg) //find
		{
			strcpy(list[i].ident, id); //copy to DB
			int find=search_register();
			if (find)
				{
					list[i].reg=find;
					return list[i].reg;
				}
		}
	}

	return 0;

}

void pop()
{
	strcpy(stack[g_hstack], "0");
	g_hstack--;
}

void push(char *arg)
{
	strcpy(stack[g_hstack], arg);
	g_hstack++;
}

void pop_command()
{
	strcpy(stack_command[g_hstack_comm], "0");
	g_hstack_comm--;
}

void push_command(char *arg)
{
	strcpy(stack_command[g_hstack_comm], arg);
	g_hstack_comm++;
}

void check_command(char *command)
{
	int f_1=search_register_by_name(stack[g_hstack-1]);
	int f_2=search_register_by_name(stack[g_hstack-2]);
	if ((check_number_ident(g_hstack-1)&&check_number_ident(g_hstack-2))||(!g_bool_tmp[f_1]&&f_1)||(!g_bool_tmp[f_2]&&f_2)) 
	{ 
		new_register(); 
	}
	int f=search_register_by_name(stack[g_hstack-1]);
	if (!check_number_ident(g_hstack-1)&&g_bool_tmp[f]&&f) 
	{ 
		swap (g_hstack-1, g_hstack-2); 
	} 
	printf ("%s %s, %s\n", command, stack[g_hstack-2], stack[g_hstack-1]);
	fprintf (out, "%s %s, %s\n", command, stack[g_hstack-2], stack[g_hstack-1]);
	strcpy(last, stack[g_hstack-2]);
	f=search_register_by_name(stack[g_hstack-1]); 
	if (f&&g_bool_tmp[f]) 
	{
		g_bool_reg[f]=1; 
		g_bool_tmp[f]=0; 
	}
	pop(); 
	if (g_hstack_comm)
	{
		printf ("%s\n", stack_command[g_hstack_comm-1]);
		fprintf (out, "%s\n", stack_command[g_hstack_comm-1]);
		pop_command();
	}
}

void op_assign(char *op)
{
	char tmp[300], tmp_2[256];
	strcpy(tmp, op); sprintf(tmp_2," %s, ", stack[g_hstack-1]); 
	strcat(tmp, tmp_2); push_command(tmp); 	
}

void push_label (char *command)
{
	arr_label[label]=g_label;  
	fprintf (out, "%s label_%d\n", command, g_label);
	printf ("%s label_%d\n", command, g_label);
}

void pop_label ()
{
	fprintf (out, "label_%d:\n", arr_label[label-1]);
	printf ("label_%d:\n", arr_label[label-1]);
	arr_label[label-1]=0;
	label--;
}

void last_value()
{
	int find=0;
	for (int i=0; i<10; i++)
		{
			if (last[0]==check_num[i])
				{
					find=search_register();
					g_bool_reg[find]=0;
					g_bool_tmp[find]=1;
					g_bool_xor[find]=1;
					fprintf (out, "LOAD %s, %s\n", g_reg[find], last);
					printf ("LOAD %s, %s\n", g_reg[find], last);
					strcpy(last, g_reg[find]);
				}
		}
}

%}
%union
{
 int value;
 char *name;
}
%token <name> IDENTIFIER
%token <value> CONST
%token AND OR XOR MUL DIV ADD SUB MOD
%token INC DEC AND_OP OR_OP LE_OP GE_OP LE_OP_ GE_OP_ EQ_OP NE_OP SHR SHL
%token ASSIGN SUB_ASSIGN AND_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN XOR_ASSIGN OR_ASSIGN RIGHT_ASSIGN LEFT_ASSIGN

%token IF ELSE WHILE RETURN PRINT R_SK L_SK

%right ASSIGN SUB_ASSIGN AND_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN XOR_ASSIGN OR_ASSIGN RIGHT_ASSIGN LEFT_ASSIGN

%left OR_OP
%left AND_OP
%left OR 
%left XOR
%left AND
%left EQ_OP NE_OP
%left LE_OP GE_OP LE_OP_ GE_OP_
%left SHR SHL
%left ADD SUB
%left MUL DIV MOD
%left INC DEC UMINUS NOT
%left L_SK R_SK

%type <name> expr

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

statements
	: 
        | statements statement
        ;

statement
	: expression_statement 
	{ if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
	}
	| selection_statement
	{ if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
	}
	| iteration_statement
	{ if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
	}
	| compound_statement
	| return_statement
	| print_statement
	{ if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
	}
	;

assignment_operator
	: ASSIGN 
	| MUL_ASSIGN { op_assign("MUL"); }
	| DIV_ASSIGN { op_assign("DIV"); }
	| MOD_ASSIGN { op_assign("MOD"); }
	| ADD_ASSIGN { op_assign("ADD"); }
	| SUB_ASSIGN { op_assign("SUB"); }
	| AND_ASSIGN { op_assign("AND"); }
	| XOR_ASSIGN { op_assign("XOR"); }
	| OR_ASSIGN { op_assign("OR"); }
	| RIGHT_ASSIGN { op_assign("SHR"); }
	| LEFT_ASSIGN { op_assign("SHL"); }
	;

unary_expression
	: IDENTIFIER { int i=search_identifier($1); push(g_reg[i]); strcpy(last, g_reg[i]); }
	| INC IDENTIFIER { int i=search_identifier($2); fprintf(out, "INC %s\n",g_reg[i]); printf("INC %s\n",g_reg[i]); push(g_reg[i]); strcpy(last, g_reg[i]); }
	| DEC IDENTIFIER { int i=search_identifier($2); fprintf(out, "DEC %s\n",g_reg[i]); printf("DEC %s\n",g_reg[i]); push(g_reg[i]); strcpy(last, g_reg[i]); }
	;

assignment_expression
	: unary_expression assignment_operator assignment_expression
		{	
			fprintf (out, "LOAD %s, %s\n", stack[g_hstack-1], stack[g_hstack]);
			printf ("LOAD %s, %s\n", stack[g_hstack-1], stack[g_hstack]);
			pop();
		}
	| unary_expression assignment_operator expr 
		{
			if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
			else 
			{
				fprintf (out, "LOAD %s, %s\n", stack[g_hstack-2], stack[g_hstack-1]);
				printf ("LOAD %s, %s\n", stack[g_hstack-2], stack[g_hstack-1]);
			}
			strcpy(last, stack[g_hstack-2]);
			int f=search_register_by_name(stack[g_hstack-1]);
			if (f&&g_bool_tmp[f]) 
			{ 
				g_bool_reg[f]=1;
				g_bool_tmp[f]=0; 
			} 
			f=search_register_by_name(stack[g_hstack-2]);
			if (f&&g_bool_tmp[f]) 
			{
				g_bool_reg[f]=1; 
				g_bool_tmp[f]=0; 
			}
			pop();
			pop();
			/*if (g_hstack_comm)
			{printf ("%s\n", stack_command[g_hstack_comm-1]); pop_command(); }*/
		}
	;

expr
	: L_SK expr R_SK { }
	| expr ADD expr { check_command("ADD"); }
	| expr SUB expr { check_command("SUB"); }
	| expr MUL expr { check_command("MUL"); }
	| expr DIV expr { check_command("DIV"); }
	| expr MOD expr { check_command("MOD"); }
	| SUB expr %prec UMINUS { new_register(); fprintf (out, "MUL %s, -1\n", stack[g_hstack-1]); printf ("MUL %s, -1\n", stack[g_hstack-1]); strcpy(last, stack[g_hstack-1]); }
	| expr XOR expr { check_command("XOR"); }
	| expr OR expr { check_command("OR"); }
	| expr AND expr { check_command("AND"); }
	| expr SHL expr { check_command("SHL"); }
	| expr SHR expr { check_command("SHR"); }
	| NOT expr { new_register(); fprintf (out, "NOT %s\n", stack[g_hstack-1]); printf ("NOT %s\n", stack[g_hstack-1]); }
	| expr AND_OP expr { }
	| expr LE_OP expr { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JGE", loop); printf ("%s loop_%d\n", "JGE", loop); } else { push_label("JGE"); } }
	| expr GE_OP expr { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JLE", loop); printf ("%s loop_%d\n", "JLE", loop); } else { push_label("JLE"); } }
	| expr LE_OP_ expr { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JG", loop); printf ("%s loop_%d\n", "JG", loop); } else { push_label("JG"); } }
	| expr GE_OP_ expr { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JL", loop); printf ("%s loop_%d\n", "JL", loop); } else { push_label("JL"); } }
	| expr EQ_OP expr { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JNE", loop); printf ("%s loop_%d\n", "JNE", loop); } else { push_label("JNE"); } }
	| expr NE_OP expr { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JE", loop); printf ("%s loop_%d\n", "JE", loop); } else { push_label("JE"); } }
	;

expr
	: unary_expression { }
	| CONST { char tmp[16]; sprintf(tmp,"%i",$1); push(tmp); strcpy(last, tmp); }
	| IDENTIFIER INC 
			{ 
			char tmp[300], tmp_2[256]; int i=search_identifier($1); 
			strcpy(tmp, "INC "); sprintf(tmp_2,"%s", g_reg[i]); strcat(tmp, tmp_2); push(g_reg[i]); push_command(tmp);
			strcpy(last, g_reg[i]);
			}
	| IDENTIFIER DEC 
			{ 
			char tmp[300], tmp_2[256]; int i=search_identifier($1); 
			strcpy(tmp, "DEC "); sprintf(tmp_2,"%s", g_reg[i]); strcat(tmp, tmp_2); push(g_reg[i]); push_command(tmp); 
			strcpy(last, g_reg[i]);
			}
	;

expression
	: expr 
		{
			int f=search_register_by_name(stack[g_hstack-1]);
			if (f&&g_bool_tmp[f]) 
			{ 
				g_bool_reg[f]=1; 
				g_bool_tmp[f]=0; 
			} 
			f=search_register_by_name(stack[g_hstack-2]);
			if (f&&g_bool_tmp[f]) 
			{ 
				g_bool_reg[f]=1; 
				g_bool_tmp[f]=0; 
			}
			pop(); 
			pop();
		}
	| assignment_expression
	;

expression_statement
	: ';'
	| expression ';'
	| expression ',' expression_statement
	;

selection_statement 
	: IF L_SK expression R_SK { 
		label++; g_label++; 
		if (!b_cmp)
			{
				last_value();
				fprintf (out, "CMP %s, 0\n", last);
				printf ("CMP %s, 0\n", last);
				arr_label[label-1]=g_label-1;
				fprintf (out, "JE label_%d\n", g_label-1);
				printf ("JE label_%d\n", g_label-1);
			} 
		else { b_cmp=0; } 
	} slc_stmnt
	;

slc_stmnt
	: statement %prec LOWER_THAN_ELSE { pop_label(); }
	| statement ELSE { pop_label(); } statement
	;

iteration_statement
	: { if (loop!=g_loop) { loop=g_loop; }
		fprintf (out, "loop_%d:\n", loop);
		printf ("loop_%d:\n", loop++); g_loop++; b_loop=1; } 
		WHILE { b_loop=1; } L_SK expression { loop++; g_loop++; b_loop=0; 		
			if (!b_cmp) 
			{ 
				last_value();
				fprintf (out, "CMP %s, 0\n", last);
				printf ("CMP %s, 0\n", last);
				fprintf (out, "JE loop_%d\n", loop-1);
				printf ("JE loop_%d\n", loop-1);
			} 
		else { b_cmp=0; }  
	} R_SK statement 
		{ loop--; fprintf (out, "JMP loop_%d\n", loop-1); printf ("JMP loop_%d\n", loop-1); fprintf (out, "loop_%d:\n", loop); printf ("loop_%d:\n", loop--); }
	;

print_statement
	: PRINT expression ';' 
		{
			int find=0;
			for (int i=0; i<10; i++)
				{
					if (last[0]==check_num[i])
					{
						find=search_register();
						g_bool_reg[find]=0;
						g_bool_tmp[find]=1;
						g_bool_xor[find]=1;
						fprintf (out, "LOAD %s, %s\n", g_reg[find], last);
						printf ("LOAD %s, %s\n", g_reg[find], last);
						strcpy(last, g_reg[find]);
					}
				}
			fprintf(out, "THROW %s\n", last);
			printf("THROW %s\n", last);
			fprintf (out, "CALL print\n");
 			printf ("CALL print\n"); 
			g_bool_reg[find]=1;
			g_bool_tmp[find]=0;
			g_bool_xor[find]=0;
		}
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	;

statement_list
	: statement
	| statement_list statement
	;

return_statement
	: RETURN ';' 
		{ 
			for (int i=1; i<18; i++)
				{
					if (g_bool_xor[i])
					{
						fprintf(out, "XOR %s, %s\n", g_reg[i], g_reg[i]);
						printf("XOR %s, %s\n", g_reg[i], g_reg[i]);
					}
				}

			fprintf (out, "RET\n");
			printf ("RET\n"); 
		}
	| RETURN expression ';'
		{ 
			for (int i=1; i<18; i++)
				{
					if (g_bool_xor[i] && strcmp(g_reg[i],last))
					{
						fprintf(out, "XOR %s, %s\n", g_reg[i], g_reg[i]);
						printf("XOR %s, %s\n", g_reg[i], g_reg[i]);
						/*g_bool_reg[i]=1;
						g_bool_tmp[i]=0;
						g_bool_xor[i]=0;*/
					}
				}
			int find=0;
			for (int i=0; i<10; i++)
				{
					if (last[0]==check_num[i])
					{
						find=search_register();
						g_bool_reg[find]=0;
						g_bool_tmp[find]=1;
						g_bool_xor[find]=1;
						fprintf (out, "LOAD %s, %s\n", g_reg[find], last);
						printf ("LOAD %s, %s\n", g_reg[find], last);
						strcpy(last, g_reg[find]);
					}
				}
			g_bool_reg[find]=1;
			g_bool_tmp[find]=0;
			g_bool_xor[find]=0;
			fprintf (out, "RET\n");
			printf ("RET\n"); 
		}
	;

%%
#include <stdio.h>

extern char yytext[];
extern int column;
extern int string;
FILE *yyin;

int yyerror(const char *s)
{
	printf ("Error on %d string and %d column\n", string, column);
}

void main(int argc, char *argv[]) {
	
	if (argc != 2)
	{
		printf("Error: not enough arguments!\n");
		return;
	}

	if ((yyin = fopen(argv[1], "r")) == NULL)
	{
		printf("Error: cannot open file %s.\n", argv[1]);
		return;
	}
	out=fopen("out.txt", "w");
	yyparse();
	fclose(out);

 }

