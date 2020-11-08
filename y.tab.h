/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 259 "parser.yacc" /* yacc.c:1909  */

 int value;
 char *name;

#line 149 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
