/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "grammar.y"

/*
 * Grammar definitions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int yylex(void);
extern FILE *yyin;

/*
 * Parser error count
 */
int parser_error = 0;

#define YYERROR_VERBOSE

/*
 * Print parser error message
 */
void yyerror(char *msg)
{
  fatal(parser_state, msg);
  parser_error = 1;
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "grammar.y"
{
	char *string;
	int unused;
}
/* Line 187 of yacc.c.  */
#line 297 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 310 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1498

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  211
/* YYNRULES -- Number of states.  */
#define YYNSTATES  379

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   336

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      87,    88,     2,     2,    93,     2,    91,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    50,    84,
       2,     2,     2,    49,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    89,    92,    90,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,     2,    86,     2,     2,     2,     2,
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
      45,    46,    47,    48,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    13,    15,    17,
      19,    22,    25,    29,    31,    32,    37,    40,    42,    43,
      51,    52,    59,    60,    68,    69,    80,    81,    90,    91,
     100,   101,   104,   105,   108,   109,   113,   118,   122,   129,
     133,   136,   138,   139,   141,   143,   145,   147,   150,   153,
     155,   157,   160,   162,   164,   166,   168,   170,   172,   174,
     180,   182,   184,   188,   190,   192,   194,   196,   198,   201,
     205,   208,   213,   219,   220,   229,   233,   238,   243,   249,
     255,   262,   269,   270,   279,   285,   286,   294,   296,   299,
     303,   307,   310,   315,   319,   323,   327,   331,   335,   339,
     343,   347,   351,   355,   359,   364,   369,   374,   379,   384,
     389,   394,   399,   404,   409,   412,   415,   418,   421,   424,
     428,   432,   436,   440,   444,   448,   452,   456,   460,   464,
     468,   472,   476,   480,   484,   488,   492,   496,   500,   503,
     506,   508,   512,   515,   517,   519,   521,   523,   525,   528,
     531,   534,   537,   540,   543,   546,   549,   552,   553,   561,
     563,   565,   567,   569,   571,   573,   575,   577,   579,   581,
     584,   587,   590,   593,   596,   599,   602,   605,   608,   611,
     613,   617,   618,   621,   624,   627,   630,   633,   636,   639,
     642,   645,   648,   652,   656,   660,   664,   668,   672,   676,
     680,   684,   688,   690,   691,   699,   702,   703,   705,   708,
     710,   713
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,    -1,    96,    -1,    97,    -1,    96,    97,
      -1,   137,    -1,   142,    -1,    99,    -1,    99,    -1,    98,
      99,    -1,   114,    84,    -1,     7,     6,    84,    -1,   101,
      -1,    -1,    85,   100,    98,    86,    -1,    85,    86,    -1,
      84,    -1,    -1,     8,   102,    87,   115,    88,    99,   108,
      -1,    -1,    10,   103,    87,   115,    88,    99,    -1,    -1,
      11,   104,    99,    10,    87,   115,    88,    -1,    -1,    13,
     105,    87,   113,    84,   113,    84,   113,    88,    99,    -1,
      -1,    16,   106,    87,   115,    88,    85,   109,    86,    -1,
      -1,    20,   107,    99,    22,    87,    83,    88,    99,    -1,
      -1,     9,    99,    -1,    -1,   110,   112,    -1,    -1,   109,
     111,   112,    -1,    17,   115,    50,    98,    -1,    17,   115,
      50,    -1,    17,   115,    50,    98,    15,    84,    -1,    18,
      50,    98,    -1,    18,    50,    -1,   115,    -1,    -1,   115,
      -1,    14,    -1,    15,    -1,    12,    -1,    12,   115,    -1,
      21,   115,    -1,   127,    -1,   116,    -1,   116,   117,    -1,
     136,    -1,   135,    -1,   131,    -1,   132,    -1,   130,    -1,
     129,    -1,   119,    -1,   115,    49,   115,    50,   115,    -1,
      27,    -1,    28,    -1,    87,   115,    88,    -1,   121,    -1,
     122,    -1,   123,    -1,   124,    -1,   118,    -1,   117,   118,
      -1,    89,   115,    90,    -1,    91,    83,    -1,    91,    83,
      87,    88,    -1,    91,    83,    87,   133,    88,    -1,    -1,
      92,   120,    87,   140,    88,    85,    98,    86,    -1,    83,
      87,    88,    -1,    83,    87,   133,    88,    -1,    25,    83,
      87,    88,    -1,    25,    83,    87,   133,    88,    -1,    83,
      26,    83,    87,    88,    -1,    83,    26,    83,    87,   133,
      88,    -1,    83,   128,    91,    83,    87,    88,    -1,    -1,
      83,   128,    91,    83,    87,   125,   133,    88,    -1,    83,
      91,    83,    87,    88,    -1,    -1,    83,    91,    83,    87,
     126,   133,    88,    -1,    83,    -1,    83,   128,    -1,    83,
      26,    83,    -1,    89,   115,    90,    -1,    91,    83,    -1,
     128,    89,   115,    90,    -1,   128,    91,    83,    -1,    83,
      48,   115,    -1,    83,    47,   115,    -1,    83,    46,   115,
      -1,    83,    45,   115,    -1,    83,    44,   115,    -1,    83,
      43,   115,    -1,    83,    42,   115,    -1,    83,    41,   115,
      -1,    83,    40,   115,    -1,    83,    39,   115,    -1,    83,
     128,    48,   115,    -1,    83,   128,    47,   115,    -1,    83,
     128,    46,   115,    -1,    83,   128,    45,   115,    -1,    83,
     128,    44,   115,    -1,    83,   128,    43,   115,    -1,    83,
     128,    42,   115,    -1,    83,   128,    41,   115,    -1,    83,
     128,    40,   115,    -1,    83,   128,    39,   115,    -1,    53,
     115,    -1,    63,   115,    -1,    74,   115,    -1,    73,   115,
      -1,    71,   115,    -1,   115,    64,   115,    -1,   115,    63,
     115,    -1,   115,    67,   115,    -1,   115,    66,   115,    -1,
     115,    65,   115,    -1,   115,    68,   115,    -1,   115,    52,
     115,    -1,   115,    51,   115,    -1,   115,    62,   115,    -1,
     115,    61,   115,    -1,   115,    60,   115,    -1,   115,    70,
     115,    -1,   115,    69,   115,    -1,   115,    59,   115,    -1,
     115,    58,   115,    -1,   115,    57,   115,    -1,   115,    56,
     115,    -1,   115,    55,   115,    -1,   115,    54,   115,    -1,
     115,    74,    -1,   115,    73,    -1,   134,    -1,   133,    93,
     134,    -1,    62,   115,    -1,   115,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,    87,    88,    -1,    82,   115,
      -1,    81,   115,    -1,    80,   115,    -1,    79,   115,    -1,
      78,   115,    -1,    77,   115,    -1,    76,   115,    -1,    75,
     115,    -1,    -1,   138,   139,    83,    87,   140,    88,    99,
      -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,
      -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,
      -1,    19,    29,    -1,    19,    30,    -1,    19,    31,    -1,
      19,    32,    -1,    19,    33,    -1,    19,    34,    -1,    19,
      35,    -1,    19,    36,    -1,    19,    37,    -1,    19,    38,
      -1,   141,    -1,   140,    93,   141,    -1,    -1,    29,    83,
      -1,    30,    83,    -1,    31,    83,    -1,    32,    83,    -1,
      33,    83,    -1,    34,    83,    -1,    35,    83,    -1,    36,
      83,    -1,    37,    83,    -1,    38,    83,    -1,    19,    29,
      83,    -1,    19,    30,    83,    -1,    19,    31,    83,    -1,
      19,    32,    83,    -1,    19,    33,    83,    -1,    19,    34,
      83,    -1,    19,    35,    83,    -1,    19,    36,    83,    -1,
      19,    37,    83,    -1,    19,    38,    83,    -1,    83,    -1,
      -1,    23,   143,    83,   144,    85,   145,    86,    -1,    24,
      83,    -1,    -1,   146,    -1,   145,   146,    -1,   137,    -1,
      83,    84,    -1,    83,    48,   115,    84,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,   100,   103,   104,   107,   108,   109,   112,
     113,   116,   117,   118,   119,   119,   120,   121,   124,   124,
     125,   125,   126,   126,   127,   127,   128,   128,   129,   129,
     132,   133,   136,   136,   137,   137,   140,   141,   142,   143,
     144,   147,   148,   151,   152,   153,   154,   155,   156,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   174,   175,   176,   177,   178,   181,   182,   185,
     186,   187,   188,   191,   191,   194,   195,   198,   199,   202,
     203,   206,   207,   207,   208,   209,   209,   212,   213,   214,
     217,   218,   219,   220,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   245,   246,   247,   248,   249,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   273,   274,
     277,   278,   281,   282,   285,   286,   287,   288,   289,   292,
     293,   294,   295,   296,   297,   298,   299,   302,   302,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   327,
     328,   329,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   355,   355,   358,   359,   362,   363,   366,
     367,   368
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONST_BOOL", "CONST_INT", "CONST_FLOAT",
  "CONST_STRING", "KW_INC", "KW_IF", "KW_ELSE", "KW_WHILE", "KW_DO",
  "KW_RETURN", "KW_FOR", "KW_CONTINUE", "KW_BREAK", "KW_SWITCH", "KW_CASE",
  "KW_DEFAULT", "KW_FORCE", "KW_TRY", "KW_THROW", "KW_CATCH", "KW_TMPL",
  "KW_EXTENDS", "KW_NEW", "KW_STATIC", "KW_FILE", "KW_LINE", "TYPE_VOID",
  "TYPE_BOOL", "TYPE_INT", "TYPE_FLOAT", "TYPE_STRING", "TYPE_ARRAY",
  "TYPE_STRUCT", "TYPE_FN", "TYPE_RES", "TYPE_MIXED", "OP_ARSHIFT",
  "OP_ALSHIFT", "OP_AXOR", "OP_AOR", "OP_AAND", "OP_ADIV", "OP_AMUL",
  "OP_AMINUS", "OP_APLUS", "OP_ASSIGN", "'?'", "':'", "OP_BOOL_OR",
  "OP_BOOL_AND", "OP_NOT", "OP_LARGER", "OP_SMALLER", "OP_LEQ", "OP_SEQ",
  "OP_NOT_EQUAL", "OP_EQUAL", "OP_XOR", "OP_OR", "OP_AND", "OP_MINUS",
  "OP_PLUS", "OP_MOD", "OP_DIV", "OP_MUL", "OP_POW", "OP_RSHIFT",
  "OP_LSHIFT", "OP_NEG", "UNARY_MINUS", "OP_MINUSMINUS", "OP_PLUSPLUS",
  "CAST_STRUCT", "CAST_ARRAY", "CAST_STRING", "CAST_FLOAT", "CAST_UINT",
  "CAST_INT", "CAST_BOOL", "CAST_VOID", "ID", "';'", "'{'", "'}'", "'('",
  "')'", "'['", "']'", "'.'", "'\\\\'", "','", "$accept", "program",
  "fstatements", "fblock", "statements", "block", "@1", "control", "@2",
  "@3", "@4", "@5", "@6", "@7", "else", "cases", "@8", "@9", "case",
  "nullexpr", "statement", "expr", "indexable", "indexes", "index",
  "lambda", "@10", "call", "cons", "static", "method", "@11", "@12", "ref",
  "refexp", "assign", "prefix", "infix", "postfix", "arglist", "argexpr",
  "const", "cast", "fundef", "@13", "rettype", "argdefs", "argdef",
  "tmpldef", "@14", "extends", "tmpldecls", "tmpldecl", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,    63,
      58,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,    59,   123,   125,    40,    41,    91,
      93,    46,    92,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    96,    96,    97,    97,    97,    98,
      98,    99,    99,    99,   100,    99,    99,    99,   102,   101,
     103,   101,   104,   101,   105,   101,   106,   101,   107,   101,
     108,   108,   110,   109,   111,   109,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   116,   116,   116,   116,   116,   117,   117,   118,
     118,   118,   118,   120,   119,   121,   121,   122,   122,   123,
     123,   124,   125,   124,   124,   126,   124,   127,   127,   127,
     128,   128,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   132,   132,
     133,   133,   134,   134,   135,   135,   135,   135,   135,   136,
     136,   136,   136,   136,   136,   136,   136,   138,   137,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   140,
     140,   140,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   143,   142,   144,   144,   145,   145,   146,
     146,   146
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       2,     2,     3,     1,     0,     4,     2,     1,     0,     7,
       0,     6,     0,     7,     0,    10,     0,     8,     0,     8,
       0,     2,     0,     2,     0,     3,     4,     3,     6,     3,
       2,     1,     0,     1,     1,     1,     1,     2,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     1,     3,     1,     1,     1,     1,     1,     2,     3,
       2,     4,     5,     0,     8,     3,     4,     4,     5,     5,
       6,     6,     0,     8,     5,     0,     7,     1,     2,     3,
       3,     2,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     3,     2,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     0,     7,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       3,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     0,     7,     2,     0,     1,     2,     1,
       2,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     157,   144,   145,   146,   147,     0,    18,    20,    22,    46,
      24,    44,    45,    26,    28,     0,   203,     0,    60,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    17,    14,     0,    73,     0,   157,
       4,     8,    13,     0,    43,    50,    58,    63,    64,    65,
      66,    49,    57,    56,    54,    55,    53,    52,     6,     0,
       7,     0,     0,     0,     0,    47,     0,     0,     0,    48,
       0,     0,   114,   115,   118,   117,   116,   156,   155,   154,
     153,   152,   151,   150,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
      16,     0,   148,     0,     0,     1,     5,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   139,   138,
       0,     0,    51,    67,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,    12,     0,     0,     0,
      42,     0,     0,   206,     0,    89,   103,   102,   101,   100,
      99,    98,    97,    96,    95,    94,     0,    75,   143,     0,
     140,     0,    91,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     9,    62,   181,     0,
     126,   125,   137,   136,   135,   134,   133,   132,   129,   128,
     127,   120,   119,   123,   122,   121,   124,   131,   130,     0,
      70,    68,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,     0,     0,     0,     0,     0,    41,     0,     0,
       0,     0,    77,     0,     0,   142,    76,     0,    90,    85,
     113,   112,   111,   110,   109,   108,   107,   106,   105,   104,
       0,    93,    15,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   202,     0,   179,     0,    69,
       0,   181,     0,     0,     0,    42,     0,     0,   205,   157,
      78,    79,     0,   141,    84,     0,    92,    82,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,     0,     0,
      59,    71,     0,     0,    30,    21,     0,     0,    32,     0,
       0,   209,   157,   207,    80,     0,    81,     0,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,     0,   180,
      72,     0,     0,    19,    23,    42,    34,     0,     0,     0,
     210,   204,   208,    86,     0,     0,   158,    31,     0,    27,
       0,     0,     0,    33,    29,     0,    83,    74,     0,    35,
       0,    40,   211,    25,    37,    39,    36,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    38,    39,    40,   185,   186,   101,    42,    62,    63,
      64,    66,    67,    68,   343,   346,   347,   360,   363,   226,
      43,    44,    45,   132,   133,    46,   104,    47,    48,    49,
      50,   327,   285,    51,    99,    52,    53,    54,    55,   169,
     170,    56,    57,    58,    59,   145,   266,   267,    60,    70,
     231,   322,   323
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -334
static const yytype_int16 yypact[] =
{
     231,  -334,  -334,  -334,  -334,     5,  -334,  -334,  -334,  1070,
    -334,  -334,  -334,  -334,  -334,  1070,  -334,   -55,  -334,  -334,
    1070,  1070,  1070,  1070,  1070,  1070,  1070,  1070,  1070,  1070,
    1070,  1070,  1070,     7,  -334,   -50,   978,  -334,    44,   374,
    -334,  -334,  -334,   -15,  1332,     6,  -334,  -334,  -334,  -334,
    -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,   745,
    -334,    -8,    36,    37,   644,  1332,    39,    40,   644,  1332,
      -4,    41,  1403,    26,    26,  -334,  -334,  -334,  -334,  -334,
    -334,  -334,  -334,  -334,  -334,    51,  1070,  1070,  1070,  1070,
    1070,  1070,  1070,  1070,  1070,  1070,   127,  1070,    52,   318,
    -334,   644,  -334,  1051,    49,  -334,  -334,  -334,  1070,  1070,
    1070,  1070,  1070,  1070,  1070,  1070,  1070,  1070,  1070,  1070,
    1070,  1070,  1070,  1070,  1070,  1070,  1070,  1070,  -334,  -334,
    1070,    54,     6,  -334,   835,  -334,  -334,  -334,  -334,  -334,
    -334,  -334,  -334,  -334,  -334,    55,  -334,  1070,  1070,   129,
    1070,  1070,   118,   117,   767,    60,  1332,  1332,  1332,  1332,
    1332,  1332,  1332,  1332,  1332,  1332,  1070,  -334,  1332,   -85,
    -334,   446,    61,  1070,  1070,  1070,  1070,  1070,  1070,  1070,
    1070,  1070,  1070,  1070,    67,   464,  -334,  -334,   300,  1280,
    1382,   356,  1424,  1424,  1424,  1424,  1424,  1424,    -7,    -7,
      -7,   209,   209,     4,     4,     4,     4,    26,    26,   536,
      64,  -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,
    -334,  -334,    66,  1109,  1144,    69,    73,  1332,  1179,    71,
      76,    75,  -334,   -81,   857,  1332,  -334,  1009,  -334,    74,
    1332,  1332,  1332,  1332,  1332,  1332,  1332,  1332,  1332,  1332,
     626,    77,  -334,  -334,   866,    80,    82,    83,    96,    98,
      99,   100,   101,   104,   105,  -334,   -79,  -334,  1070,  -334,
     888,   300,   644,   644,  1070,  1070,   106,   109,  -334,   110,
    -334,  -334,   -59,  -334,  -334,  1009,  -334,    79,   111,   112,
     113,   114,   116,   128,   130,   133,   134,   135,  -334,  -334,
    -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,   136,   300,
    1358,  -334,   -58,   -56,   203,  -334,  1214,   138,  -334,   132,
     -42,  -334,   -43,  -334,  -334,   -23,  -334,  1009,  -334,  -334,
    -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,   644,  -334,
    -334,   644,   644,  -334,  -334,  1070,   137,    84,   644,  1070,
    -334,  -334,  -334,  -334,   -13,   554,  -334,  -334,   139,  -334,
      84,  1070,   174,  -334,  -334,  1249,  -334,  -334,   644,  -334,
    1306,   644,  -334,  -334,   644,   644,   734,   141,  -334
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -334,  -334,  -334,   187,  -333,     0,  -334,  -334,  -334,  -334,
    -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,  -132,  -274,
    -334,    -5,  -334,  -334,   108,  -334,  -334,  -334,  -334,  -334,
    -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,  -334,  -141,
      11,  -334,  -334,  -277,  -334,  -334,   -41,   -76,  -334,  -334,
    -334,  -334,   -73
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const yytype_int16 yytable[] =
{
      41,   317,   321,   236,    65,   355,   349,   280,   237,   308,
      69,    61,   237,   233,   309,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    71,   324,
     340,   103,   341,    85,   237,   237,   100,   309,   375,    41,
     320,   376,   350,   351,   105,   321,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,   120,   121,   122,   123,
     124,   125,   126,   127,   149,   353,   128,   129,   152,   107,
     237,   358,   125,   126,   127,   366,   146,   128,   129,   153,
     237,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   168,   171,   282,    96,   130,    97,   131,    98,   128,
     129,   361,   362,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   147,   148,   209,   150,   151,   154,   312,
       1,     2,     3,     4,   155,   172,   188,   210,   222,   225,
     229,   230,   223,   224,   325,   227,   228,   234,   239,   168,
     251,   270,    17,   271,    18,    19,   274,   275,   277,   278,
     279,   235,   284,   298,   287,   299,   300,   326,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   301,
      20,   302,   303,   304,   305,   253,   354,   306,   307,   166,
      21,   318,   319,   320,   328,   329,   330,   331,    22,   332,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,   333,   342,   334,    36,   167,   335,   336,   337,    37,
     348,   338,   345,   359,   371,   378,   106,   368,   369,   168,
     313,    -2,   168,   339,     1,     2,     3,     4,     5,     6,
     211,     7,     8,     9,    10,    11,    12,    13,   283,   352,
       0,    14,    15,     0,    16,     0,    17,     0,    18,    19,
       0,     0,     0,   310,     0,   168,     0,     0,     0,   316,
     227,     0,   314,   315,   122,   123,   124,   125,   126,   127,
     168,     0,   128,   129,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,     0,     0,
       0,     0,    22,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     0,    36,   254,
       0,     0,   168,    37,     0,     0,     0,     0,     0,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,     0,
     227,   356,   357,     0,   365,     0,     0,     0,   364,     0,
       0,     0,     0,     0,     0,   253,   370,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,   373,     0,
       0,     0,     0,     0,    -3,   253,   253,     1,     2,     3,
       4,     5,     6,   265,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,    14,    15,     0,    16,     0,    17,
       0,    18,    19,     0,     0,     0,     0,   183,   110,   184,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    20,     0,   128,
     129,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,    22,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,     0,     0,     0,    37,     1,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,    14,    15,     0,     0,     0,    17,
       0,    18,    19,     0,     0,   108,     0,   109,   110,     0,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    20,     0,   128,
     129,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,    22,   238,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     252,    36,     0,     0,     0,     0,    37,     1,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,    14,    15,     0,     0,     0,    17,
       0,    18,    19,     0,     0,   108,     0,   109,   110,     0,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    20,     0,   128,
     129,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,    22,   269,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     367,    36,     0,     0,     0,     0,    37,     1,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,    14,    15,     0,     0,     0,    17,
       0,    18,    19,     0,     0,   108,     0,   109,   110,     0,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    20,     0,   128,
     129,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,    22,   286,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,     0,     0,     0,    37,     1,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,   377,
      13,     0,     0,     0,    14,    15,     0,     0,     0,    17,
       0,    18,    19,     0,   134,     0,     0,     0,     0,     0,
       1,     2,     3,     4,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,    20,     0,     0,
       0,     0,    17,     0,    18,    19,     0,    21,     0,     0,
       0,     0,     0,     0,     0,    22,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      20,    36,     0,     0,     0,     0,    37,     0,     0,   166,
      21,     0,     0,     0,     0,     0,     0,     0,    22,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,     0,    36,   232,     0,     0,     0,    37,
       1,     2,     3,     4,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,    18,    19,     0,     0,     0,     0,
       0,     1,     2,     3,     4,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,     0,     0,     0,     0,     0,
      20,     0,     0,    17,     0,    18,    19,     0,     0,   166,
      21,     0,     0,     0,     0,     0,     0,     0,    22,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    20,     0,     0,    36,   281,     0,     0,     0,    37,
     166,    21,     0,     0,     0,     0,     0,     0,     0,    22,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,     0,     0,    36,   311,     0,     0,     0,
      37,     1,     2,     3,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,    18,    19,     0,     0,     0,
       0,     0,     1,     2,     3,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    17,     0,    18,    19,     0,     0,
       0,    21,     0,     0,     0,     0,     0,     0,     0,    22,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    20,     0,     0,    36,   102,     0,     0,     0,
      37,   166,    21,     1,     2,     3,     4,     0,     0,     0,
      22,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,    17,    36,    18,    19,     0,
     108,    37,   109,   110,     0,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,    20,   128,   129,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     0,     0,   187,
       0,    22,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     0,     0,     0,    36,   108,     0,
     109,   110,    37,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   128,   129,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   109,   110,   272,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,     0,   128,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,     0,
     109,   110,   273,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   128,   129,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,   109,   110,   276,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,     0,   128,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,     0,
     109,   110,   344,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   128,   129,     0,     0,     0,     0,     0,   108,
     268,   109,   110,   372,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   128,   129,   108,   374,   109,   110,     0,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,     0,     0,   128,
     129,   108,     0,   109,   110,     0,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,     0,     0,   128,   129,    -4,     0,   109,
     110,     0,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
       0,   128,   129,   109,   110,     0,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,     0,     0,   128,   129,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,     0,   128,   129,    -4,    -4,
      -4,    -4,    -4,    -4,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,     0,   128,   129
};

static const yytype_int16 yycheck[] =
{
       0,   275,   279,    88,     9,   338,    48,    88,    93,    88,
      15,     6,    93,   154,    93,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    83,    88,
      88,    36,    88,    26,    93,    93,    86,    93,   371,    39,
      83,   374,    84,    86,     0,   322,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    63,    64,    65,    66,
      67,    68,    69,    70,    64,    88,    73,    74,    68,    84,
      93,   345,    68,    69,    70,    88,    84,    73,    74,    83,
      93,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   234,    87,    89,    89,    91,    91,    73,
      74,    17,    18,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    87,    87,   130,    87,    87,    87,   270,
       3,     4,     5,     6,    83,    83,    87,    83,    83,    10,
      22,    24,   147,   148,   285,   150,   151,    87,    87,   154,
      83,    87,    25,    87,    27,    28,    87,    84,    87,    83,
      85,   166,    88,    83,    87,    83,    83,    88,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,    83,
      53,    83,    83,    83,    83,   185,   327,    83,    83,    62,
      63,    85,    83,    83,    83,    83,    83,    83,    71,    83,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    83,     9,    83,    87,    88,    83,    83,    83,    92,
      88,    85,    84,    86,    50,    84,    39,    88,   360,   234,
     271,     0,   237,   309,     3,     4,     5,     6,     7,     8,
     132,    10,    11,    12,    13,    14,    15,    16,   237,   322,
      -1,    20,    21,    -1,    23,    -1,    25,    -1,    27,    28,
      -1,    -1,    -1,   268,    -1,   270,    -1,    -1,    -1,   274,
     275,    -1,   272,   273,    65,    66,    67,    68,    69,    70,
     285,    -1,    73,    74,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    -1,    87,    19,
      -1,    -1,   327,    92,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
     345,   341,   342,    -1,   349,    -1,    -1,    -1,   348,    -1,
      -1,    -1,    -1,    -1,    -1,   355,   361,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,   368,    -1,
      -1,    -1,    -1,    -1,     0,   375,   376,     3,     4,     5,
       6,     7,     8,    83,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    -1,    23,    -1,    25,
      -1,    27,    28,    -1,    -1,    -1,    -1,    89,    52,    91,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    53,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      -1,    87,    -1,    -1,    -1,    -1,    92,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    25,
      -1,    27,    28,    -1,    -1,    49,    -1,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    53,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    90,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    -1,    -1,    -1,    -1,    92,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    25,
      -1,    27,    28,    -1,    -1,    49,    -1,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    53,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    90,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    -1,    -1,    -1,    -1,    92,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    25,
      -1,    27,    28,    -1,    -1,    49,    -1,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    53,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    90,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      -1,    87,    -1,    -1,    -1,    -1,    92,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    25,
      -1,    27,    28,    -1,    19,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    25,    -1,    27,    28,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      53,    87,    -1,    -1,    -1,    -1,    92,    -1,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    87,    88,    -1,    -1,    -1,    92,
       3,     4,     5,     6,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    28,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    25,    -1,    27,    28,    -1,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    53,    -1,    -1,    87,    88,    -1,    -1,    -1,    92,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    -1,    87,    88,    -1,    -1,    -1,
      92,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    28,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    25,    -1,    27,    28,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    53,    -1,    -1,    87,    88,    -1,    -1,    -1,
      92,    62,    63,     3,     4,     5,     6,    -1,    -1,    -1,
      71,    -1,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    25,    87,    27,    28,    -1,
      49,    92,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    53,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    71,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    87,    49,    -1,
      51,    52,    92,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    88,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      51,    52,    88,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    88,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      51,    52,    88,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    49,
      50,    51,    52,    84,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    73,    74,    49,    50,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    -1,    73,
      74,    49,    -1,    51,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    73,    74,    49,    -1,    51,
      52,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    73,    74,    51,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    73,    74,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    -1,    73,    74,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    73,    74
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    15,    16,    20,    21,    23,    25,    27,    28,
      53,    63,    71,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    87,    92,    95,    96,
      97,    99,   101,   114,   115,   116,   119,   121,   122,   123,
     124,   127,   129,   130,   131,   132,   135,   136,   137,   138,
     142,     6,   102,   103,   104,   115,   105,   106,   107,   115,
     143,    83,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,    26,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    87,    89,    91,   128,
      86,   100,    88,   115,   120,     0,    97,    84,    49,    51,
      52,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    73,    74,
      89,    91,   117,   118,    19,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,   139,    84,    87,    87,    99,
      87,    87,    99,    83,    87,    83,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,    62,    88,   115,   133,
     134,   115,    83,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    89,    91,    98,    99,    88,    87,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
      83,   118,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    83,   115,   115,    10,   113,   115,   115,    22,
      24,   144,    88,   133,    87,   115,    88,    93,    90,    87,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,    83,    86,    99,    19,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    83,   140,   141,    50,    90,
      87,    87,    88,    88,    87,    84,    88,    87,    83,    85,
      88,    88,   133,   134,    88,   126,    90,    87,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    88,    93,
     115,    88,   133,   140,    99,    99,   115,   113,    85,    83,
      83,   137,   145,   146,    88,   133,    88,   125,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    85,   141,
      88,    88,     9,   108,    88,    84,   109,   110,    88,    48,
      84,    86,   146,    88,   133,    98,    99,    99,   113,    86,
     111,    17,    18,   112,    99,   115,    88,    86,    88,   112,
     115,    50,    84,    99,    50,    98,    98,    15,    84
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 12:
#line 117 "grammar.y"
    { parser_enter_include((yyvsp[(2) - (3)].string)); }
    break;

  case 14:
#line 119 "grammar.y"
    { stmt_begin_block(); }
    break;

  case 15:
#line 119 "grammar.y"
    { stmt_end_block(); }
    break;

  case 16:
#line 120 "grammar.y"
    { stmt_begin_block(); stmt_end_nop(); stmt_end_block(); }
    break;

  case 17:
#line 121 "grammar.y"
    { stmt_end_nop(); }
    break;

  case 18:
#line 124 "grammar.y"
    { stmt_begin_if(); }
    break;

  case 19:
#line 124 "grammar.y"
    { stmt_end_if(); }
    break;

  case 20:
#line 125 "grammar.y"
    { stmt_begin_while(); }
    break;

  case 21:
#line 125 "grammar.y"
    { stmt_end_while(); }
    break;

  case 22:
#line 126 "grammar.y"
    { stmt_begin_do(); }
    break;

  case 23:
#line 126 "grammar.y"
    { stmt_end_do(); }
    break;

  case 24:
#line 127 "grammar.y"
    { stmt_begin_for(); }
    break;

  case 25:
#line 127 "grammar.y"
    { stmt_end_for(); }
    break;

  case 26:
#line 128 "grammar.y"
    { stmt_begin_switch(); }
    break;

  case 27:
#line 128 "grammar.y"
    { stmt_end_switch(); }
    break;

  case 28:
#line 129 "grammar.y"
    { stmt_begin_try(); }
    break;

  case 29:
#line 129 "grammar.y"
    { stmt_end_try((yyvsp[(6) - (8)].string)); }
    break;

  case 31:
#line 133 "grammar.y"
    { /* nop */ }
    break;

  case 32:
#line 136 "grammar.y"
    { stmt_begin_case(); }
    break;

  case 33:
#line 136 "grammar.y"
    { /* nop */ }
    break;

  case 34:
#line 137 "grammar.y"
    { stmt_begin_case(); }
    break;

  case 35:
#line 137 "grammar.y"
    { /* nop */ }
    break;

  case 36:
#line 140 "grammar.y"
    { stmt_end_case(1); }
    break;

  case 37:
#line 141 "grammar.y"
    { stmt_end_nop(); stmt_end_case(1); }
    break;

  case 38:
#line 142 "grammar.y"
    { stmt_end_case(0); }
    break;

  case 39:
#line 143 "grammar.y"
    { stmt_end_default(); }
    break;

  case 40:
#line 144 "grammar.y"
    { stmt_end_nop(); stmt_end_default(); }
    break;

  case 41:
#line 147 "grammar.y"
    { /* nop */ }
    break;

  case 42:
#line 148 "grammar.y"
    { expr_end_true(); }
    break;

  case 43:
#line 151 "grammar.y"
    { stmt_end_expr(); }
    break;

  case 44:
#line 152 "grammar.y"
    { stmt_end_continue(); }
    break;

  case 45:
#line 153 "grammar.y"
    { stmt_end_break(); }
    break;

  case 46:
#line 154 "grammar.y"
    { stmt_end_return(); }
    break;

  case 47:
#line 155 "grammar.y"
    { stmt_end_return_value(); }
    break;

  case 48:
#line 156 "grammar.y"
    { stmt_end_throw(); }
    break;

  case 49:
#line 159 "grammar.y"
    { /* nop */ }
    break;

  case 50:
#line 160 "grammar.y"
    { /* nop */ }
    break;

  case 51:
#line 161 "grammar.y"
    { /* nop */ }
    break;

  case 52:
#line 162 "grammar.y"
    { /* nop */ }
    break;

  case 53:
#line 163 "grammar.y"
    { /* nop */ }
    break;

  case 54:
#line 164 "grammar.y"
    { /* nop */ }
    break;

  case 55:
#line 165 "grammar.y"
    { /* nop */ }
    break;

  case 56:
#line 166 "grammar.y"
    { /* nop */ }
    break;

  case 57:
#line 167 "grammar.y"
    { /* nop */ }
    break;

  case 58:
#line 168 "grammar.y"
    { /* nop */ }
    break;

  case 59:
#line 169 "grammar.y"
    { expr_end_if(); }
    break;

  case 60:
#line 170 "grammar.y"
    { expr_end_file(); }
    break;

  case 61:
#line 171 "grammar.y"
    { expr_end_line(); }
    break;

  case 62:
#line 174 "grammar.y"
    { /* nop */ }
    break;

  case 63:
#line 175 "grammar.y"
    { /* nop */ }
    break;

  case 64:
#line 176 "grammar.y"
    { /* nop */ }
    break;

  case 65:
#line 177 "grammar.y"
    { /* nop */ }
    break;

  case 66:
#line 178 "grammar.y"
    { /* nop */ }
    break;

  case 69:
#line 185 "grammar.y"
    { expr_end_first(); expr_end_index(); }
    break;

  case 70:
#line 186 "grammar.y"
    { expr_end_field((yyvsp[(2) - (2)].string)); expr_end_first(); expr_end_index(); }
    break;

  case 71:
#line 187 "grammar.y"
    { expr_end_method_void((yyvsp[(2) - (4)].string)); }
    break;

  case 72:
#line 188 "grammar.y"
    { expr_end_method((yyvsp[(2) - (5)].string)); }
    break;

  case 73:
#line 191 "grammar.y"
    { expr_begin_lambda(); }
    break;

  case 74:
#line 191 "grammar.y"
    { expr_end_lambda(); }
    break;

  case 75:
#line 194 "grammar.y"
    { expr_end_call_void((yyvsp[(1) - (3)].string), 0); }
    break;

  case 76:
#line 195 "grammar.y"
    { expr_end_call((yyvsp[(1) - (4)].string), 0); }
    break;

  case 77:
#line 198 "grammar.y"
    { expr_end_call_void((yyvsp[(2) - (4)].string), 1); }
    break;

  case 78:
#line 199 "grammar.y"
    { expr_end_call((yyvsp[(2) - (5)].string), 1); }
    break;

  case 79:
#line 202 "grammar.y"
    { expr_end_static_void((yyvsp[(1) - (5)].string), (yyvsp[(3) - (5)].string)); }
    break;

  case 80:
#line 203 "grammar.y"
    { expr_end_static((yyvsp[(1) - (6)].string), (yyvsp[(3) - (6)].string)); }
    break;

  case 81:
#line 206 "grammar.y"
    { expr_end_ref_array((yyvsp[(1) - (6)].string)); expr_end_method_void((yyvsp[(4) - (6)].string)); }
    break;

  case 82:
#line 207 "grammar.y"
    { expr_end_ref_array((yyvsp[(1) - (5)].string)); }
    break;

  case 83:
#line 207 "grammar.y"
    { expr_end_method((yyvsp[(4) - (8)].string)); }
    break;

  case 84:
#line 208 "grammar.y"
    { expr_end_ref((yyvsp[(1) - (5)].string)); expr_end_method_void((yyvsp[(3) - (5)].string)); }
    break;

  case 85:
#line 209 "grammar.y"
    { expr_end_ref((yyvsp[(1) - (4)].string)); }
    break;

  case 86:
#line 209 "grammar.y"
    { expr_end_method((yyvsp[(3) - (7)].string)); }
    break;

  case 87:
#line 212 "grammar.y"
    { expr_end_ref((yyvsp[(1) - (1)].string)); }
    break;

  case 88:
#line 213 "grammar.y"
    { expr_end_ref_array((yyvsp[(1) - (2)].string)); }
    break;

  case 89:
#line 214 "grammar.y"
    { expr_end_static_ref((yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string)); }
    break;

  case 90:
#line 217 "grammar.y"
    { expr_end_first(); }
    break;

  case 91:
#line 218 "grammar.y"
    { expr_end_field((yyvsp[(2) - (2)].string)); expr_end_first(); }
    break;

  case 92:
#line 219 "grammar.y"
    { expr_end_next(); }
    break;

  case 93:
#line 220 "grammar.y"
    { expr_end_field((yyvsp[(3) - (3)].string)); expr_end_next(); }
    break;

  case 94:
#line 223 "grammar.y"
    { expr_end_assign((yyvsp[(1) - (3)].string)); }
    break;

  case 95:
#line 224 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_PLUS); }
    break;

  case 96:
#line 225 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_MINUS); }
    break;

  case 97:
#line 226 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_MUL); }
    break;

  case 98:
#line 227 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_DIV); }
    break;

  case 99:
#line 228 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_AND); }
    break;

  case 100:
#line 229 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_OR); }
    break;

  case 101:
#line 230 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_XOR); }
    break;

  case 102:
#line 231 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_LSHIFT); }
    break;

  case 103:
#line 232 "grammar.y"
    { expr_end_op_assign((yyvsp[(1) - (3)].string), OPTYPE_RSHIFT); }
    break;

  case 104:
#line 233 "grammar.y"
    { expr_end_assign_array((yyvsp[(1) - (4)].string)); }
    break;

  case 105:
#line 234 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_PLUS); }
    break;

  case 106:
#line 235 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_MINUS); }
    break;

  case 107:
#line 236 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_MUL); }
    break;

  case 108:
#line 237 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_DIV); }
    break;

  case 109:
#line 238 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_AND); }
    break;

  case 110:
#line 239 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_OR); }
    break;

  case 111:
#line 240 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_XOR); }
    break;

  case 112:
#line 241 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_LSHIFT); }
    break;

  case 113:
#line 242 "grammar.y"
    { expr_end_op_assign_array((yyvsp[(1) - (4)].string), OPTYPE_RSHIFT); }
    break;

  case 114:
#line 245 "grammar.y"
    { expr_end_prefix(OPTYPE_NOT); }
    break;

  case 115:
#line 246 "grammar.y"
    { expr_end_prefix(OPTYPE_MINUS); }
    break;

  case 116:
#line 247 "grammar.y"
    { expr_end_prefix(OPTYPE_PREINC); }
    break;

  case 117:
#line 248 "grammar.y"
    { expr_end_prefix(OPTYPE_PREDEC); }
    break;

  case 118:
#line 249 "grammar.y"
    { expr_end_prefix(OPTYPE_NEG); }
    break;

  case 119:
#line 252 "grammar.y"
    { expr_end_infix(OPTYPE_PLUS); }
    break;

  case 120:
#line 253 "grammar.y"
    { expr_end_infix(OPTYPE_MINUS); }
    break;

  case 121:
#line 254 "grammar.y"
    { expr_end_infix(OPTYPE_MUL); }
    break;

  case 122:
#line 255 "grammar.y"
    { expr_end_infix(OPTYPE_DIV); }
    break;

  case 123:
#line 256 "grammar.y"
    { expr_end_infix(OPTYPE_MOD); }
    break;

  case 124:
#line 257 "grammar.y"
    { expr_end_infix(OPTYPE_POW); }
    break;

  case 125:
#line 258 "grammar.y"
    { expr_end_infix(OPTYPE_BOOL_AND); }
    break;

  case 126:
#line 259 "grammar.y"
    { expr_end_infix(OPTYPE_BOOL_OR); }
    break;

  case 127:
#line 260 "grammar.y"
    { expr_end_infix(OPTYPE_AND); }
    break;

  case 128:
#line 261 "grammar.y"
    { expr_end_infix(OPTYPE_OR); }
    break;

  case 129:
#line 262 "grammar.y"
    { expr_end_infix(OPTYPE_XOR); }
    break;

  case 130:
#line 263 "grammar.y"
    { expr_end_infix(OPTYPE_LSHIFT); }
    break;

  case 131:
#line 264 "grammar.y"
    { expr_end_infix(OPTYPE_RSHIFT); }
    break;

  case 132:
#line 265 "grammar.y"
    { expr_end_infix(OPTYPE_EQUAL); }
    break;

  case 133:
#line 266 "grammar.y"
    { expr_end_infix(OPTYPE_NOT_EQUAL); }
    break;

  case 134:
#line 267 "grammar.y"
    { expr_end_infix(OPTYPE_SEQ); }
    break;

  case 135:
#line 268 "grammar.y"
    { expr_end_infix(OPTYPE_LEQ); }
    break;

  case 136:
#line 269 "grammar.y"
    { expr_end_infix(OPTYPE_SMALLER); }
    break;

  case 137:
#line 270 "grammar.y"
    { expr_end_infix(OPTYPE_LARGER); }
    break;

  case 138:
#line 273 "grammar.y"
    { expr_end_postfix(OPTYPE_POSTINC); }
    break;

  case 139:
#line 274 "grammar.y"
    { expr_end_postfix(OPTYPE_POSTDEC); }
    break;

  case 140:
#line 277 "grammar.y"
    { expr_end_first(); }
    break;

  case 141:
#line 278 "grammar.y"
    { expr_end_next(); }
    break;

  case 142:
#line 281 "grammar.y"
    { expr_end_pass_ref(); }
    break;

  case 143:
#line 282 "grammar.y"
    { /* nop */ }
    break;

  case 144:
#line 285 "grammar.y"
    { expr_end_const_bool((yyvsp[(1) - (1)].string)); }
    break;

  case 145:
#line 286 "grammar.y"
    { expr_end_const_int((yyvsp[(1) - (1)].string)); }
    break;

  case 146:
#line 287 "grammar.y"
    { expr_end_const_float((yyvsp[(1) - (1)].string)); }
    break;

  case 147:
#line 288 "grammar.y"
    { expr_end_const_string((yyvsp[(1) - (1)].string)); }
    break;

  case 148:
#line 289 "grammar.y"
    { expr_end_const_void(); }
    break;

  case 149:
#line 292 "grammar.y"
    { expr_end_cast("void"); }
    break;

  case 150:
#line 293 "grammar.y"
    { expr_end_cast("bool"); }
    break;

  case 151:
#line 294 "grammar.y"
    { expr_end_cast("int"); }
    break;

  case 152:
#line 295 "grammar.y"
    { expr_end_cast("uint"); }
    break;

  case 153:
#line 296 "grammar.y"
    { expr_end_cast("float"); }
    break;

  case 154:
#line 297 "grammar.y"
    { expr_end_cast("string"); }
    break;

  case 155:
#line 298 "grammar.y"
    { expr_end_cast("array"); }
    break;

  case 156:
#line 299 "grammar.y"
    { expr_end_cast("struct"); }
    break;

  case 157:
#line 302 "grammar.y"
    { stmt_begin_func(); }
    break;

  case 158:
#line 302 "grammar.y"
    { stmt_end_func((yyvsp[(3) - (7)].string)); }
    break;

  case 159:
#line 305 "grammar.y"
    { stmt_end_rettype('v'); }
    break;

  case 160:
#line 306 "grammar.y"
    { stmt_end_rettype('b'); }
    break;

  case 161:
#line 307 "grammar.y"
    { stmt_end_rettype('i'); }
    break;

  case 162:
#line 308 "grammar.y"
    { stmt_end_rettype('f'); }
    break;

  case 163:
#line 309 "grammar.y"
    { stmt_end_rettype('s'); }
    break;

  case 164:
#line 310 "grammar.y"
    { stmt_end_rettype('a'); }
    break;

  case 165:
#line 311 "grammar.y"
    { stmt_end_rettype('c'); }
    break;

  case 166:
#line 312 "grammar.y"
    { stmt_end_rettype('p'); }
    break;

  case 167:
#line 313 "grammar.y"
    { stmt_end_rettype('r'); }
    break;

  case 168:
#line 314 "grammar.y"
    { stmt_end_rettype('?'); }
    break;

  case 169:
#line 315 "grammar.y"
    { stmt_end_rettype('V'); }
    break;

  case 170:
#line 316 "grammar.y"
    { stmt_end_rettype('B'); }
    break;

  case 171:
#line 317 "grammar.y"
    { stmt_end_rettype('I'); }
    break;

  case 172:
#line 318 "grammar.y"
    { stmt_end_rettype('F'); }
    break;

  case 173:
#line 319 "grammar.y"
    { stmt_end_rettype('S'); }
    break;

  case 174:
#line 320 "grammar.y"
    { stmt_end_rettype('A'); }
    break;

  case 175:
#line 321 "grammar.y"
    { stmt_end_rettype('C'); }
    break;

  case 176:
#line 322 "grammar.y"
    { stmt_end_rettype('P'); }
    break;

  case 177:
#line 323 "grammar.y"
    { stmt_end_rettype('R'); }
    break;

  case 178:
#line 324 "grammar.y"
    { stmt_end_rettype('?'); }
    break;

  case 179:
#line 327 "grammar.y"
    { /* nop */ }
    break;

  case 180:
#line 328 "grammar.y"
    { /* nop */ }
    break;

  case 181:
#line 329 "grammar.y"
    { /* nop */ }
    break;

  case 182:
#line 332 "grammar.y"
    { stmt_end_arg('v', (yyvsp[(2) - (2)].string)); }
    break;

  case 183:
#line 333 "grammar.y"
    { stmt_end_arg('b', (yyvsp[(2) - (2)].string)); }
    break;

  case 184:
#line 334 "grammar.y"
    { stmt_end_arg('i', (yyvsp[(2) - (2)].string)); }
    break;

  case 185:
#line 335 "grammar.y"
    { stmt_end_arg('f', (yyvsp[(2) - (2)].string)); }
    break;

  case 186:
#line 336 "grammar.y"
    { stmt_end_arg('s', (yyvsp[(2) - (2)].string)); }
    break;

  case 187:
#line 337 "grammar.y"
    { stmt_end_arg('a', (yyvsp[(2) - (2)].string)); }
    break;

  case 188:
#line 338 "grammar.y"
    { stmt_end_arg('c', (yyvsp[(2) - (2)].string)); }
    break;

  case 189:
#line 339 "grammar.y"
    { stmt_end_arg('p', (yyvsp[(2) - (2)].string)); }
    break;

  case 190:
#line 340 "grammar.y"
    { stmt_end_arg('r', (yyvsp[(2) - (2)].string)); }
    break;

  case 191:
#line 341 "grammar.y"
    { stmt_end_arg('?', (yyvsp[(2) - (2)].string)); }
    break;

  case 192:
#line 342 "grammar.y"
    { stmt_end_arg('V', (yyvsp[(3) - (3)].string)); }
    break;

  case 193:
#line 343 "grammar.y"
    { stmt_end_arg('B', (yyvsp[(3) - (3)].string)); }
    break;

  case 194:
#line 344 "grammar.y"
    { stmt_end_arg('I', (yyvsp[(3) - (3)].string)); }
    break;

  case 195:
#line 345 "grammar.y"
    { stmt_end_arg('F', (yyvsp[(3) - (3)].string)); }
    break;

  case 196:
#line 346 "grammar.y"
    { stmt_end_arg('S', (yyvsp[(3) - (3)].string)); }
    break;

  case 197:
#line 347 "grammar.y"
    { stmt_end_arg('A', (yyvsp[(3) - (3)].string)); }
    break;

  case 198:
#line 348 "grammar.y"
    { stmt_end_arg('C', (yyvsp[(3) - (3)].string)); }
    break;

  case 199:
#line 349 "grammar.y"
    { stmt_end_arg('P', (yyvsp[(3) - (3)].string)); }
    break;

  case 200:
#line 350 "grammar.y"
    { stmt_end_arg('R', (yyvsp[(3) - (3)].string)); }
    break;

  case 201:
#line 351 "grammar.y"
    { stmt_end_arg('?', (yyvsp[(3) - (3)].string)); }
    break;

  case 202:
#line 352 "grammar.y"
    { stmt_end_arg('?', (yyvsp[(1) - (1)].string)); }
    break;

  case 203:
#line 355 "grammar.y"
    { stmt_begin_tmpl(); }
    break;

  case 204:
#line 355 "grammar.y"
    { stmt_end_tmpl((yyvsp[(3) - (7)].string)); }
    break;

  case 205:
#line 358 "grammar.y"
    { stmt_end_extends((yyvsp[(2) - (2)].string)); }
    break;

  case 206:
#line 359 "grammar.y"
    { stmt_end_extends(NULL); }
    break;

  case 209:
#line 366 "grammar.y"
    { /* nop */ }
    break;

  case 210:
#line 367 "grammar.y"
    { expr_end_const_void(); expr_end_assign((yyvsp[(1) - (2)].string)); stmt_end_expr(); }
    break;

  case 211:
#line 368 "grammar.y"
    { expr_end_assign((yyvsp[(1) - (4)].string)); stmt_end_expr(); }
    break;


/* Line 1267 of yacc.c.  */
#line 3071 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 371 "grammar.y"


