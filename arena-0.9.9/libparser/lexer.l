%{
/*
 * lexer definitions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "y.tab.h"

/*
 * Parser data
 */
YYSTYPE yylval;

/*
 * Include file stack
 */
static int include_depth = 0;
static char **include_files = NULL;
static FILE **include_fps = NULL;
static int *include_lines = NULL;
static int *include_cols = NULL;
static YY_BUFFER_STATE *include_state = NULL;

/*
 * Side copy of all allocated filenames
 */
static int include_all = 0;
static char **include_all_files = NULL;

/*
 * Block comment flag
 */
static int in_block = 0;

/*
 * Helper macros for position updates
 */
#define COLS parser_state->source_col += yyleng
#define LINES parser_state->source_line++; parser_state->source_col = 0

/*
 * Helper macro for nested comment block handling
 */
#define BLOCK if (in_block == 0)

/*
 * Dirty hack to keep old flex / new gcc combo from warning
 */
static void yyunput();
void yyunused()
{
  yyunput();
}

/*
 * define default yywrap without -lfl
 */
int yywrap(void)
{
  return 1;
}

/*
 * Adjust line and column for string literals
 */
static void literal(char *text, int len)
{
  int i;
  
  for (i = 0; i < len; ++i) {
    if (text[i] == '\n') {
      ++parser_state->source_line;
      parser_state->source_col = 0;
    } else {
      ++parser_state->source_col;
    }
  }
}

/*
 * Record filename for eventual deallocation
 */
static void record_file(char *path)
{
  char **names;
  int depth = include_all + 1;
  
  names = oom(realloc(include_all_files, depth * sizeof(char *)));
  names[include_all] = path;
  
  include_all_files = names;
  ++include_all;
}

/*
 * Enter new include file
 */
void parser_enter_include(char *path)
{
  char **files;
  FILE **fps;
  int *lines;
  int *cols;
  YY_BUFFER_STATE *state;
  FILE *inc;
  int depth = include_depth + 1;

  inc = fopen(path, "r");
  if (!inc) {
    yyerror("could not open include file");
  }

  record_file(path);
  
  files = oom(realloc(include_files, depth * sizeof(char *)));
  fps   = oom(realloc(include_fps, depth * sizeof(FILE *)));
  lines = oom(realloc(include_lines, depth * sizeof(int)));
  cols  = oom(realloc(include_cols, depth * sizeof(int)));
  state = oom(realloc(include_state, depth * sizeof(YY_BUFFER_STATE)));
  
  files[include_depth] = parser_state->source_file;
  fps[include_depth]   = inc;
  lines[include_depth] = parser_state->source_line;
  cols[include_depth]  = parser_state->source_col;
  state[include_depth] = YY_CURRENT_BUFFER;
  
  include_files = files;
  include_fps   = fps;
  include_lines = lines;
  include_cols  = cols;
  include_state = state;
  include_depth++;
  
  parser_state->source_file = path;
  parser_state->source_line = 1;
  parser_state->source_col = 0;
  
  yy_switch_to_buffer(yy_create_buffer(inc, YY_BUF_SIZE));
}

/*
 * Leave include file
 */
static int leave_include(void)
{
  if (include_depth == 0) {
    free(include_lines);
    free(include_cols);
    free(include_files);
    free(include_fps);
    free(include_state);
    include_lines = include_cols = NULL;
    include_files = NULL;
    include_state = NULL;
    yy_delete_buffer(YY_CURRENT_BUFFER);
    return 0;
  }
  
  include_depth--;
  parser_state->source_line = include_lines[include_depth];
  parser_state->source_col  = include_cols[include_depth];
  parser_state->source_file = include_files[include_depth];
  fclose(include_fps[include_depth]);

  yy_delete_buffer(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(include_state[include_depth]);

  return 1;
}

/*
 * Clean up memory used by include file names
 */
void parser_include_teardown(void)
{
  int i;
  
  for (i = 0; i < include_all; i++) {
    free(include_all_files[i]);
  }
  free(include_all_files);
}

/*
 * Copy arbitrary string to token buffer
 *
 * This function does a string copy of the given token into the
 * parser's semantic union.
 */
static void copy_string(const char *from, int len)
{
  char *copy;
  
  copy = malloc(len + 1);
  if (!copy) {
    parser_error++;
    return;
  }
  memcpy(copy, from, len);
  copy[len] = 0;
  yylval.string = copy;
}

%}

ID [_a-zA-Z][_a-zA-Z0-9]*
INTVAL [1-9][0-9]*
OCTVAL 0[0-7]*
HEXVAL 0x[0-9a-zA-Z]+
FLOATVAL ([0-9]*)?\.[0-9]+([eE][+\-][0-9]*)?
STRINGVAL \"[^"]*\"
STRINGLIT \'[^']*\'
WHITE [ \r\t]

%%

{WHITE}*		{ COLS; /* eat whitespace */ }
"#".*\n			{ LINES; /* eat trailing shell comment */ }
"//".*\n		{ LINES; /* eat trailing C++ comment */ }
"\n"			{ LINES; }
"/\*"			{ COLS; in_block++; }
"\*/"			{ COLS; in_block--; }
"include"		{ COLS; BLOCK return KW_INC; }
"if"			{ COLS; BLOCK return KW_IF; }
"else"			{ COLS; BLOCK return KW_ELSE; }
"while"			{ COLS; BLOCK return KW_WHILE; }
"do"			{ COLS; BLOCK return KW_DO; }
"return"		{ COLS; BLOCK return KW_RETURN; }
"for"			{ COLS; BLOCK return KW_FOR; }
"continue"		{ COLS; BLOCK return KW_CONTINUE; }
"break"			{ COLS; BLOCK return KW_BREAK; }
"switch"		{ COLS; BLOCK return KW_SWITCH; }
"case"			{ COLS; BLOCK return KW_CASE; }
"default"		{ COLS; BLOCK return KW_DEFAULT; }
"forced"		{ COLS; BLOCK return KW_FORCE; }
"try"			{ COLS; BLOCK return KW_TRY; }
"throw"			{ COLS; BLOCK return KW_THROW; }
"catch"			{ COLS; BLOCK return KW_CATCH; }
"template"		{ COLS; BLOCK return KW_TMPL; }
"extends"		{ COLS; BLOCK return KW_EXTENDS; }
"new"			{ COLS; BLOCK return KW_NEW; }
"__FILE__"		{ COLS; BLOCK return KW_FILE; }
"__LINE__"		{ COLS; BLOCK return KW_LINE; }
"::"			{ COLS; BLOCK return KW_STATIC; }
"\(void\)"		{ COLS; BLOCK return CAST_VOID; }
"\(bool\)"		{ COLS; BLOCK return CAST_BOOL; }
"\(int\)"		{ COLS; BLOCK return CAST_INT; }
"\(float\)"		{ COLS; BLOCK return CAST_FLOAT; }
"\(string\)"		{ COLS; BLOCK return CAST_STRING; }
"\(array\)"		{ COLS; BLOCK return CAST_ARRAY; }
"\(struct\)"		{ COLS; BLOCK return CAST_STRUCT; }
"void"			{ COLS; BLOCK return TYPE_VOID; }
"bool"			{ COLS; BLOCK return TYPE_BOOL; }
"int"			{ COLS; BLOCK return TYPE_INT; }
"float"			{ COLS; BLOCK return TYPE_FLOAT; }
"string"		{ COLS; BLOCK return TYPE_STRING; }
"array"			{ COLS; BLOCK return TYPE_ARRAY; }
"struct"		{ COLS; BLOCK return TYPE_STRUCT; }
"fn"			{ COLS; BLOCK return TYPE_FN; }
"resource"		{ COLS; BLOCK return TYPE_RES; }
"mixed"			{ COLS; BLOCK return TYPE_MIXED; }
"=="			{ COLS; BLOCK return OP_EQUAL; }
"!="			{ COLS; BLOCK return OP_NOT_EQUAL; }
"<="			{ COLS; BLOCK return OP_SEQ; }
">="			{ COLS; BLOCK return OP_LEQ; }
"<"			{ COLS; BLOCK return OP_SMALLER; }
">"			{ COLS; BLOCK return OP_LARGER; }
"\+\+"			{ COLS; BLOCK return OP_PLUSPLUS; }
"\-\-"			{ COLS; BLOCK return OP_MINUSMINUS; }
"&&"			{ COLS; BLOCK return OP_BOOL_AND; }
"\|\|"			{ COLS; BLOCK return OP_BOOL_OR; }
"\*\*"			{ COLS; BLOCK return OP_POW; }
"\+"			{ COLS; BLOCK return OP_PLUS; }
"\-"			{ COLS; BLOCK return OP_MINUS; }
"\*"			{ COLS; BLOCK return OP_MUL; }
"/"			{ COLS; BLOCK return OP_DIV; }
"%"			{ COLS; BLOCK return OP_MOD; }
"&"			{ COLS; BLOCK return OP_AND; }
"\|"			{ COLS; BLOCK return OP_OR; }
"\^"			{ COLS; BLOCK return OP_XOR; }
"<<"			{ COLS; BLOCK return OP_LSHIFT; }
">>"			{ COLS; BLOCK return OP_RSHIFT; }
"\!"			{ COLS; BLOCK return OP_NOT; }
"~"			{ COLS; BLOCK return OP_NEG; }
"="			{ COLS; BLOCK return OP_ASSIGN; }
"\+="			{ COLS; BLOCK return OP_APLUS; }
"\-="			{ COLS; BLOCK return OP_AMINUS; }
"\*="			{ COLS; BLOCK return OP_AMUL; }
"/="			{ COLS; BLOCK return OP_ADIV; }
"&="			{ COLS; BLOCK return OP_AAND; }
"\|="			{ COLS; BLOCK return OP_AOR; }
"\^="			{ COLS; BLOCK return OP_AXOR; }
"<<="			{ COLS; BLOCK return OP_ALSHIFT; }
">>="			{ COLS; BLOCK return OP_ARSHIFT; }
"false"			{ COLS; BLOCK copy_string(yytext, yyleng); BLOCK return CONST_BOOL; }
"true"			{ COLS; BLOCK copy_string(yytext, yyleng); BLOCK return CONST_BOOL; }
{INTVAL}		{ COLS; BLOCK copy_string(yytext, yyleng); BLOCK return CONST_INT; }
{OCTVAL}		{ COLS; BLOCK copy_string(yytext, yyleng); BLOCK return CONST_INT; }
{HEXVAL}		{ COLS; BLOCK copy_string(yytext, yyleng); BLOCK return CONST_INT; }
{FLOATVAL}		{ COLS; BLOCK copy_string(yytext, yyleng); BLOCK return CONST_FLOAT; }
{STRINGVAL}		{ literal(yytext, yyleng); BLOCK copy_string(yytext+1, yyleng-2); BLOCK return CONST_STRING; }
{STRINGLIT}		{ literal(yytext, yyleng); BLOCK copy_string(yytext+1, yyleng-2); BLOCK return CONST_STRING; }
{ID}			{ COLS; BLOCK copy_string(yytext, yyleng); BLOCK return ID; }
.			{ COLS; BLOCK return *yytext; }
<<EOF>>			{ if (leave_include() == 0) return 0; }
