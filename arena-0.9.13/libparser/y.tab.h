/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CONST_BOOL = 258,
     CONST_INT = 259,
     CONST_FLOAT = 260,
     CONST_STRING = 261,
     KW_INC = 262,
     KW_IF = 263,
     KW_ELSE = 264,
     KW_WHILE = 265,
     KW_DO = 266,
     KW_RETURN = 267,
     KW_FOR = 268,
     KW_CONTINUE = 269,
     KW_BREAK = 270,
     KW_SWITCH = 271,
     KW_CASE = 272,
     KW_DEFAULT = 273,
     KW_FORCE = 274,
     KW_TRY = 275,
     KW_THROW = 276,
     KW_CATCH = 277,
     KW_TMPL = 278,
     KW_EXTENDS = 279,
     KW_NEW = 280,
     KW_STATIC = 281,
     KW_FILE = 282,
     KW_LINE = 283,
     TYPE_VOID = 284,
     TYPE_BOOL = 285,
     TYPE_INT = 286,
     TYPE_FLOAT = 287,
     TYPE_STRING = 288,
     TYPE_ARRAY = 289,
     TYPE_STRUCT = 290,
     TYPE_FN = 291,
     TYPE_RES = 292,
     TYPE_MIXED = 293,
     OP_ARSHIFT = 294,
     OP_ALSHIFT = 295,
     OP_AXOR = 296,
     OP_AOR = 297,
     OP_AAND = 298,
     OP_ADIV = 299,
     OP_AMUL = 300,
     OP_AMINUS = 301,
     OP_APLUS = 302,
     OP_ASSIGN = 303,
     OP_BOOL_OR = 304,
     OP_BOOL_AND = 305,
     OP_NOT = 306,
     OP_LARGER = 307,
     OP_SMALLER = 308,
     OP_LEQ = 309,
     OP_SEQ = 310,
     OP_NOT_EQUAL = 311,
     OP_EQUAL = 312,
     OP_XOR = 313,
     OP_OR = 314,
     OP_AND = 315,
     OP_MINUS = 316,
     OP_PLUS = 317,
     OP_MOD = 318,
     OP_DIV = 319,
     OP_MUL = 320,
     OP_POW = 321,
     OP_RSHIFT = 322,
     OP_LSHIFT = 323,
     OP_NEG = 324,
     UNARY_MINUS = 325,
     OP_MINUSMINUS = 326,
     OP_PLUSPLUS = 327,
     CAST_STRUCT = 328,
     CAST_ARRAY = 329,
     CAST_STRING = 330,
     CAST_FLOAT = 331,
     CAST_UINT = 332,
     CAST_INT = 333,
     CAST_BOOL = 334,
     CAST_VOID = 335,
     ID = 336
   };
#endif
/* Tokens.  */
#define CONST_BOOL 258
#define CONST_INT 259
#define CONST_FLOAT 260
#define CONST_STRING 261
#define KW_INC 262
#define KW_IF 263
#define KW_ELSE 264
#define KW_WHILE 265
#define KW_DO 266
#define KW_RETURN 267
#define KW_FOR 268
#define KW_CONTINUE 269
#define KW_BREAK 270
#define KW_SWITCH 271
#define KW_CASE 272
#define KW_DEFAULT 273
#define KW_FORCE 274
#define KW_TRY 275
#define KW_THROW 276
#define KW_CATCH 277
#define KW_TMPL 278
#define KW_EXTENDS 279
#define KW_NEW 280
#define KW_STATIC 281
#define KW_FILE 282
#define KW_LINE 283
#define TYPE_VOID 284
#define TYPE_BOOL 285
#define TYPE_INT 286
#define TYPE_FLOAT 287
#define TYPE_STRING 288
#define TYPE_ARRAY 289
#define TYPE_STRUCT 290
#define TYPE_FN 291
#define TYPE_RES 292
#define TYPE_MIXED 293
#define OP_ARSHIFT 294
#define OP_ALSHIFT 295
#define OP_AXOR 296
#define OP_AOR 297
#define OP_AAND 298
#define OP_ADIV 299
#define OP_AMUL 300
#define OP_AMINUS 301
#define OP_APLUS 302
#define OP_ASSIGN 303
#define OP_BOOL_OR 304
#define OP_BOOL_AND 305
#define OP_NOT 306
#define OP_LARGER 307
#define OP_SMALLER 308
#define OP_LEQ 309
#define OP_SEQ 310
#define OP_NOT_EQUAL 311
#define OP_EQUAL 312
#define OP_XOR 313
#define OP_OR 314
#define OP_AND 315
#define OP_MINUS 316
#define OP_PLUS 317
#define OP_MOD 318
#define OP_DIV 319
#define OP_MUL 320
#define OP_POW 321
#define OP_RSHIFT 322
#define OP_LSHIFT 323
#define OP_NEG 324
#define UNARY_MINUS 325
#define OP_MINUSMINUS 326
#define OP_PLUSPLUS 327
#define CAST_STRUCT 328
#define CAST_ARRAY 329
#define CAST_STRING 330
#define CAST_FLOAT 331
#define CAST_UINT 332
#define CAST_INT 333
#define CAST_BOOL 334
#define CAST_VOID 335
#define ID 336




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "grammar.y"
{
	char *string;
	int unused;
}
/* Line 1489 of yacc.c.  */
#line 216 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

