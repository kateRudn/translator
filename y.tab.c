/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.yacc" /* yacc.c:339  */

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


#line 324 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    CONST = 259,
    AND = 260,
    OR = 261,
    XOR = 262,
    MUL = 263,
    DIV = 264,
    ADD = 265,
    SUB = 266,
    MOD = 267,
    INC = 268,
    DEC = 269,
    AND_OP = 270,
    OR_OP = 271,
    LE_OP = 272,
    GE_OP = 273,
    LE_OP_ = 274,
    GE_OP_ = 275,
    EQ_OP = 276,
    NE_OP = 277,
    SHR = 278,
    SHL = 279,
    ASSIGN = 280,
    SUB_ASSIGN = 281,
    AND_ASSIGN = 282,
    MUL_ASSIGN = 283,
    DIV_ASSIGN = 284,
    MOD_ASSIGN = 285,
    ADD_ASSIGN = 286,
    XOR_ASSIGN = 287,
    OR_ASSIGN = 288,
    RIGHT_ASSIGN = 289,
    LEFT_ASSIGN = 290,
    IF = 291,
    ELSE = 292,
    WHILE = 293,
    RETURN = 294,
    PRINT = 295,
    R_SK = 296,
    L_SK = 297,
    UMINUS = 298,
    NOT = 299,
    LOWER_THAN_ELSE = 300
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CONST 259
#define AND 260
#define OR 261
#define XOR 262
#define MUL 263
#define DIV 264
#define ADD 265
#define SUB 266
#define MOD 267
#define INC 268
#define DEC 269
#define AND_OP 270
#define OR_OP 271
#define LE_OP 272
#define GE_OP 273
#define LE_OP_ 274
#define GE_OP_ 275
#define EQ_OP 276
#define NE_OP 277
#define SHR 278
#define SHL 279
#define ASSIGN 280
#define SUB_ASSIGN 281
#define AND_ASSIGN 282
#define MUL_ASSIGN 283
#define DIV_ASSIGN 284
#define MOD_ASSIGN 285
#define ADD_ASSIGN 286
#define XOR_ASSIGN 287
#define OR_ASSIGN 288
#define RIGHT_ASSIGN 289
#define LEFT_ASSIGN 290
#define IF 291
#define ELSE 292
#define WHILE 293
#define RETURN 294
#define PRINT 295
#define R_SK 296
#define L_SK 297
#define UMINUS 298
#define NOT 299
#define LOWER_THAN_ELSE 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 259 "parser.yacc" /* yacc.c:355  */

 int value;
 char *name;

#line 459 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 476 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   376

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  113

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   293,   293,   295,   299,   307,   315,   323,   324,   325,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   350,   351,   352,   356,   362,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   419,   420,   421,   427,
     436,   453,   457,   458,   459,   463,   463,   479,   480,   480,
     484,   487,   487,   484,   502,   529,   530,   534,   535,   539,
     553
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONST", "AND", "OR",
  "XOR", "MUL", "DIV", "ADD", "SUB", "MOD", "INC", "DEC", "AND_OP",
  "OR_OP", "LE_OP", "GE_OP", "LE_OP_", "GE_OP_", "EQ_OP", "NE_OP", "SHR",
  "SHL", "ASSIGN", "SUB_ASSIGN", "AND_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "RIGHT_ASSIGN",
  "LEFT_ASSIGN", "IF", "ELSE", "WHILE", "RETURN", "PRINT", "R_SK", "L_SK",
  "UMINUS", "NOT", "LOWER_THAN_ELSE", "';'", "','", "'{'", "'}'",
  "$accept", "statements", "statement", "assignment_operator",
  "unary_expression", "assignment_expression", "expr", "expression",
  "expression_statement", "selection_statement", "$@1", "slc_stmnt", "$@2",
  "iteration_statement", "$@3", "$@4", "$@5", "print_statement",
  "compound_statement", "statement_list", "return_statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    59,    44,   123,   125
};
# endif

#define YYPACT_NINF -28

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-28)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -28,    74,   -28,    16,   -28,   198,     1,     7,   -27,   181,
     198,   198,   198,   -28,   120,   -28,   341,   -28,   263,   -11,
     -28,   -28,   -28,     6,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   198,   -28,   -21,   -15,   238,   -28,   -28,
     -28,   134,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   -28,   186,   -28,    -4,   -28,   -28,   -28,   -28,   -28,
     -28,   263,   196,   303,   323,   -28,   -28,    15,    15,   -28,
     283,    10,    10,    10,    10,   340,   340,    71,    71,   -28,
       4,   -28,   198,     3,   -28,    11,   -28,    -3,   -28,     3,
       3,   -28,   -28
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    60,     1,    21,    47,     0,     0,     0,     0,     0,
       0,     0,     0,    52,    60,     3,    46,    51,    50,     0,
       4,     5,     6,     0,     9,     7,     8,    48,    49,    46,
      32,    22,    23,     0,    69,     0,     0,     0,    38,    65,
      67,    60,    10,    15,    16,    11,    12,    13,    14,    17,
      18,    19,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    53,     0,    61,     0,    70,    64,    26,    66,    68,
      24,    25,    35,    34,    33,    29,    30,    27,    28,    31,
      39,    40,    41,    42,    43,    44,    45,    37,    36,    54,
       0,    55,     0,    60,    62,    57,    56,     0,    58,    60,
      60,    63,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -28,   -28,   -13,   -28,    -1,   -12,     0,    -7,   -22,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    15,    53,    29,    17,    18,    19,    20,    21,
     103,   106,   110,    22,    23,   100,   107,    24,    25,    41,
      26
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      16,    40,    35,    36,    31,    30,     3,     4,    16,    16,
      32,    37,    38,    16,     5,    33,     6,     7,    57,    58,
      59,    60,    61,    57,    58,    75,    74,    61,    79,    27,
      28,    76,    16,    69,    70,    71,    72,   101,   109,     8,
      16,    80,     9,    10,    73,    11,   102,    12,   108,    13,
      99,    14,    16,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    16,     0,     0,     2,     0,     0,     3,     4,    57,
      58,    59,    60,    61,     0,     5,     0,     6,     7,     0,
     105,     0,     0,     0,     0,   104,   111,   112,     0,     0,
       0,    16,    16,     0,     0,     0,     0,     0,    16,    16,
       8,     0,     0,     9,    10,     0,    11,     0,    12,     0,
      13,     0,    14,     3,     4,     0,     0,     0,     0,     0,
       0,     5,     0,     6,     7,     0,     0,     3,     4,     0,
       0,     0,     0,     0,     0,     5,     0,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     9,
      10,     0,    11,     0,    12,     0,    13,     0,    14,    39,
       8,     0,     0,     9,    10,     0,    11,     0,    12,     0,
      13,     0,    14,    78,     3,     4,     0,     0,     0,     3,
       4,     0,     5,     0,     6,     7,     0,     5,     0,     6,
       7,     3,     4,     0,    57,    58,    59,    60,    61,     5,
       0,     6,     7,    63,    64,    65,    66,    67,    68,    69,
      70,     0,     0,    11,     0,    12,     0,    34,    11,     0,
      12,     0,    13,     0,     0,     0,     0,     0,     0,     0,
      11,     0,    12,    54,    55,    56,    57,    58,    59,    60,
      61,     0,     0,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,     0,     0,     0,     0,     0,    54,    55,
      56,    57,    58,    59,    60,    61,     0,     0,    62,    77,
      63,    64,    65,    66,    67,    68,    69,    70,    54,    55,
      56,    57,    58,    59,    60,    61,     0,     0,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    54,     0,
      56,    57,    58,    59,    60,    61,     0,     0,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    54,     0,
       0,    57,    58,    59,    60,    61,     0,     0,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    57,    58,
      59,    60,    61,     0,     0,     0,     0,    63,    64,    65,
      66,     0,     0,    69,    70,     0,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52
};

static const yytype_int8 yycheck[] =
{
       1,    14,     9,    10,     3,     5,     3,     4,     9,    10,
       3,    11,    12,    14,    11,    42,    13,    14,     8,     9,
      10,    11,    12,     8,     9,    46,    33,    12,    41,    13,
      14,    46,    33,    23,    24,    46,    47,    41,    41,    36,
      41,    53,    39,    40,    38,    42,    42,    44,    37,    46,
      72,    48,    53,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    72,    -1,    -1,     0,    -1,    -1,     3,     4,     8,
       9,    10,    11,    12,    -1,    11,    -1,    13,    14,    -1,
     103,    -1,    -1,    -1,    -1,   102,   109,   110,    -1,    -1,
      -1,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,   110,
      36,    -1,    -1,    39,    40,    -1,    42,    -1,    44,    -1,
      46,    -1,    48,     3,     4,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    -1,    13,    14,    -1,    -1,     3,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    11,    -1,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    39,
      40,    -1,    42,    -1,    44,    -1,    46,    -1,    48,    49,
      36,    -1,    -1,    39,    40,    -1,    42,    -1,    44,    -1,
      46,    -1,    48,    49,     3,     4,    -1,    -1,    -1,     3,
       4,    -1,    11,    -1,    13,    14,    -1,    11,    -1,    13,
      14,     3,     4,    -1,     8,     9,    10,    11,    12,    11,
      -1,    13,    14,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    42,    -1,    44,    -1,    46,    42,    -1,
      44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    44,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,    15,    41,
      17,    18,    19,    20,    21,    22,    23,    24,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,     5,    -1,
       7,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,     5,    -1,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,     8,     9,
      10,    11,    12,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    -1,    -1,    23,    24,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,     0,     3,     4,    11,    13,    14,    36,    39,
      40,    42,    44,    46,    48,    52,    54,    55,    56,    57,
      58,    59,    63,    64,    67,    68,    70,    13,    14,    54,
      56,     3,     3,    42,    46,    57,    57,    56,    56,    49,
      52,    69,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    53,     5,     6,     7,     8,     9,    10,
      11,    12,    15,    17,    18,    19,    20,    21,    22,    23,
      24,    46,    47,    38,    57,    46,    46,    41,    49,    52,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    58,
      65,    41,    42,    60,    57,    52,    61,    66,    37,    41,
      62,    52,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    52,    52,    52,    52,    52,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    58,    58,    58,    60,    59,    61,    62,    61,
      64,    65,    66,    63,    67,    68,    68,    69,    69,    70,
      70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     2,     2,
       1,     1,     1,     2,     3,     0,     6,     1,     0,     4,
       0,     0,     0,     8,     3,     2,     3,     1,     2,     2,
       3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 300 "parser.yacc" /* yacc.c:1646  */
    { if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
	}
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 308 "parser.yacc" /* yacc.c:1646  */
    { if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
	}
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 316 "parser.yacc" /* yacc.c:1646  */
    { if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
	}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 326 "parser.yacc" /* yacc.c:1646  */
    { if (g_hstack_comm)
			{ 
				fprintf (out, "%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]);
				printf ("%s%s\n", stack_command[g_hstack_comm-1], stack[g_hstack-1]); 
				pop_command(); 
			}
	}
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 337 "parser.yacc" /* yacc.c:1646  */
    { op_assign("MUL"); }
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 338 "parser.yacc" /* yacc.c:1646  */
    { op_assign("DIV"); }
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 339 "parser.yacc" /* yacc.c:1646  */
    { op_assign("MOD"); }
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 340 "parser.yacc" /* yacc.c:1646  */
    { op_assign("ADD"); }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 341 "parser.yacc" /* yacc.c:1646  */
    { op_assign("SUB"); }
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 342 "parser.yacc" /* yacc.c:1646  */
    { op_assign("AND"); }
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 343 "parser.yacc" /* yacc.c:1646  */
    { op_assign("XOR"); }
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 344 "parser.yacc" /* yacc.c:1646  */
    { op_assign("OR"); }
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 345 "parser.yacc" /* yacc.c:1646  */
    { op_assign("SHR"); }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 346 "parser.yacc" /* yacc.c:1646  */
    { op_assign("SHL"); }
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 350 "parser.yacc" /* yacc.c:1646  */
    { int i=search_identifier((yyvsp[0].name)); push(g_reg[i]); strcpy(last, g_reg[i]); }
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 351 "parser.yacc" /* yacc.c:1646  */
    { int i=search_identifier((yyvsp[0].name)); fprintf(out, "INC %s\n",g_reg[i]); printf("INC %s\n",g_reg[i]); push(g_reg[i]); strcpy(last, g_reg[i]); }
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 352 "parser.yacc" /* yacc.c:1646  */
    { int i=search_identifier((yyvsp[0].name)); fprintf(out, "DEC %s\n",g_reg[i]); printf("DEC %s\n",g_reg[i]); push(g_reg[i]); strcpy(last, g_reg[i]); }
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 357 "parser.yacc" /* yacc.c:1646  */
    {	
			fprintf (out, "LOAD %s, %s\n", stack[g_hstack-1], stack[g_hstack]);
			printf ("LOAD %s, %s\n", stack[g_hstack-1], stack[g_hstack]);
			pop();
		}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 363 "parser.yacc" /* yacc.c:1646  */
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
#line 1857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 396 "parser.yacc" /* yacc.c:1646  */
    { }
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 397 "parser.yacc" /* yacc.c:1646  */
    { check_command("ADD"); }
#line 1869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 398 "parser.yacc" /* yacc.c:1646  */
    { check_command("SUB"); }
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 399 "parser.yacc" /* yacc.c:1646  */
    { check_command("MUL"); }
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 400 "parser.yacc" /* yacc.c:1646  */
    { check_command("DIV"); }
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 401 "parser.yacc" /* yacc.c:1646  */
    { check_command("MOD"); }
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 402 "parser.yacc" /* yacc.c:1646  */
    { new_register(); fprintf (out, "MUL %s, -1\n", stack[g_hstack-1]); printf ("MUL %s, -1\n", stack[g_hstack-1]); strcpy(last, stack[g_hstack-1]); }
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 403 "parser.yacc" /* yacc.c:1646  */
    { check_command("XOR"); }
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 404 "parser.yacc" /* yacc.c:1646  */
    { check_command("OR"); }
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 405 "parser.yacc" /* yacc.c:1646  */
    { check_command("AND"); }
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 406 "parser.yacc" /* yacc.c:1646  */
    { check_command("SHL"); }
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 407 "parser.yacc" /* yacc.c:1646  */
    { check_command("SHR"); }
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 408 "parser.yacc" /* yacc.c:1646  */
    { new_register(); fprintf (out, "NOT %s\n", stack[g_hstack-1]); printf ("NOT %s\n", stack[g_hstack-1]); }
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 409 "parser.yacc" /* yacc.c:1646  */
    { }
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 410 "parser.yacc" /* yacc.c:1646  */
    { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JGE", loop); printf ("%s loop_%d\n", "JGE", loop); } else { push_label("JGE"); } }
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 411 "parser.yacc" /* yacc.c:1646  */
    { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JLE", loop); printf ("%s loop_%d\n", "JLE", loop); } else { push_label("JLE"); } }
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 412 "parser.yacc" /* yacc.c:1646  */
    { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JG", loop); printf ("%s loop_%d\n", "JG", loop); } else { push_label("JG"); } }
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 413 "parser.yacc" /* yacc.c:1646  */
    { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JL", loop); printf ("%s loop_%d\n", "JL", loop); } else { push_label("JL"); } }
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 414 "parser.yacc" /* yacc.c:1646  */
    { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JNE", loop); printf ("%s loop_%d\n", "JNE", loop); } else { push_label("JNE"); } }
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 415 "parser.yacc" /* yacc.c:1646  */
    { cmp(); if (b_loop) { fprintf (out, "%s loop_%d\n", "JE", loop); printf ("%s loop_%d\n", "JE", loop); } else { push_label("JE"); } }
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 419 "parser.yacc" /* yacc.c:1646  */
    { }
#line 1983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 420 "parser.yacc" /* yacc.c:1646  */
    { char tmp[16]; sprintf(tmp,"%i",(yyvsp[0].value)); push(tmp); strcpy(last, tmp); }
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 422 "parser.yacc" /* yacc.c:1646  */
    { 
			char tmp[300], tmp_2[256]; int i=search_identifier((yyvsp[-1].name)); 
			strcpy(tmp, "INC "); sprintf(tmp_2,"%s", g_reg[i]); strcat(tmp, tmp_2); push(g_reg[i]); push_command(tmp);
			strcpy(last, g_reg[i]);
			}
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 428 "parser.yacc" /* yacc.c:1646  */
    { 
			char tmp[300], tmp_2[256]; int i=search_identifier((yyvsp[-1].name)); 
			strcpy(tmp, "DEC "); sprintf(tmp_2,"%s", g_reg[i]); strcat(tmp, tmp_2); push(g_reg[i]); push_command(tmp); 
			strcpy(last, g_reg[i]);
			}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 437 "parser.yacc" /* yacc.c:1646  */
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
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 463 "parser.yacc" /* yacc.c:1646  */
    { 
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
	}
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 479 "parser.yacc" /* yacc.c:1646  */
    { pop_label(); }
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 480 "parser.yacc" /* yacc.c:1646  */
    { pop_label(); }
#line 2060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 484 "parser.yacc" /* yacc.c:1646  */
    { if (loop!=g_loop) { loop=g_loop; }
		fprintf (out, "loop_%d:\n", loop);
		printf ("loop_%d:\n", loop++); g_loop++; b_loop=1; }
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 487 "parser.yacc" /* yacc.c:1646  */
    { b_loop=1; }
#line 2074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 487 "parser.yacc" /* yacc.c:1646  */
    { loop++; g_loop++; b_loop=0; 		
			if (!b_cmp) 
			{ 
				last_value();
				fprintf (out, "CMP %s, 0\n", last);
				printf ("CMP %s, 0\n", last);
				fprintf (out, "JE loop_%d\n", loop-1);
				printf ("JE loop_%d\n", loop-1);
			} 
		else { b_cmp=0; }  
	}
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 498 "parser.yacc" /* yacc.c:1646  */
    { loop--; fprintf (out, "JMP loop_%d\n", loop-1); printf ("JMP loop_%d\n", loop-1); fprintf (out, "loop_%d:\n", loop); printf ("loop_%d:\n", loop--); }
#line 2096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 503 "parser.yacc" /* yacc.c:1646  */
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
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 540 "parser.yacc" /* yacc.c:1646  */
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
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 554 "parser.yacc" /* yacc.c:1646  */
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
#line 2179 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2183 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 588 "parser.yacc" /* yacc.c:1906  */

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

