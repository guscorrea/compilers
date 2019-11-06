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
    TK_IDENTIFIER = 258,
    LIT_TRUE = 259,
    LIT_FALSE = 260,
    LIT_FLOAT = 261,
    LIT_INTEGER = 262,
    LIT_CHAR = 263,
    LIT_STRING = 264,
    KW_BYTE = 265,
    KW_INT = 266,
    KW_LONG = 267,
    KW_FLOAT = 268,
    KW_BOOL = 269,
    KW_IF = 270,
    KW_THEN = 271,
    KW_ELSE = 272,
    KW_WHILE = 273,
    KW_FOR = 274,
    KW_READ = 275,
    KW_PRINT = 276,
    KW_RETURN = 277,
    KW_BREAK = 278,
    OPERATOR_LE = 279,
    OPERATOR_GE = 280,
    OPERATOR_EQ = 281,
    OPERATOR_DIF = 282,
    TOKEN_ERROR = 283
  };
#endif
/* Tokens.  */
#define TK_IDENTIFIER 258
#define LIT_TRUE 259
#define LIT_FALSE 260
#define LIT_FLOAT 261
#define LIT_INTEGER 262
#define LIT_CHAR 263
#define LIT_STRING 264
#define KW_BYTE 265
#define KW_INT 266
#define KW_LONG 267
#define KW_FLOAT 268
#define KW_BOOL 269
#define KW_IF 270
#define KW_THEN 271
#define KW_ELSE 272
#define KW_WHILE 273
#define KW_FOR 274
#define KW_READ 275
#define KW_PRINT 276
#define KW_RETURN 277
#define KW_BREAK 278
#define OPERATOR_LE 279
#define OPERATOR_GE 280
#define OPERATOR_EQ 281
#define OPERATOR_DIF 282
#define TOKEN_ERROR 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "parser.y" /* yacc.c:1909  */

    HASH_NODE *symbol;
    AST *ast;

#line 115 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
