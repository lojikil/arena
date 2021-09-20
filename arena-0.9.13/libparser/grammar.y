%{
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

%}


%union {
	char *string;
	int unused;
}

%token <string> CONST_BOOL
%token <string> CONST_INT
%token <string> CONST_FLOAT
%token <string> CONST_STRING

%token <unused> KW_INC
%token <unused> KW_IF
%token <unused> KW_ELSE
%token <unused> KW_WHILE
%token <unused> KW_DO
%token <unused> KW_RETURN
%token <unused> KW_FOR
%token <unused> KW_CONTINUE
%token <unused> KW_BREAK
%token <unused> KW_SWITCH
%token <unused> KW_CASE
%token <unused> KW_DEFAULT
%token <unused> KW_FORCE
%token <unused> KW_TRY
%token <unused> KW_THROW
%token <unused> KW_CATCH
%token <unused> KW_TMPL
%token <unused> KW_EXTENDS
%token <unused> KW_NEW
%token <unused> KW_STATIC
%token <unused> KW_FILE
%token <unused> KW_LINE

%token <unused> TYPE_VOID
%token <unused> TYPE_BOOL
%token <unused> TYPE_INT
%token <unused> TYPE_FLOAT
%token <unused> TYPE_STRING
%token <unused> TYPE_ARRAY
%token <unused> TYPE_STRUCT
%token <unused> TYPE_FN
%token <unsued> TYPE_RES
%token <unused> TYPE_MIXED

%right <unused> OP_ASSIGN OP_APLUS OP_AMINUS OP_AMUL OP_ADIV OP_AAND OP_AOR OP_AXOR OP_ALSHIFT OP_ARSHIFT
%nonassoc <unused> '?' ':'
%right <unused> OP_BOOL_OR
%right <unused> OP_BOOL_AND
%right <unused> OP_NOT
%nonassoc <unused> OP_EQUAL OP_NOT_EQUAL OP_SEQ OP_LEQ OP_SMALLER OP_LARGER
%left <unused> OP_AND OP_OR OP_XOR
%left <unused> OP_PLUS OP_MINUS 
%left <unused> OP_MUL OP_DIV OP_MOD
%right <unused> OP_POW
%left <unused> OP_LSHIFT OP_RSHIFT
%left <unused> UNARY_MINUS OP_NEG
%left <unused> OP_PLUSPLUS OP_MINUSMINUS
%right <unused> CAST_VOID CAST_BOOL CAST_INT CAST_UINT CAST_FLOAT CAST_STRING CAST_ARRAY CAST_STRUCT

%token <string> ID

%%

program: /* empty */
	| fstatements
	;

fstatements: fblock
	| fstatements fblock
	;

fblock:	fundef
	| tmpldef
	| block
	;

statements: block
	| statements block
	;

block:	statement ';'
	| KW_INC CONST_STRING ';' { parser_enter_include($2); }
	| control
	| '{' { stmt_begin_block(); } statements '}' { stmt_end_block(); }
	| '{' '}' { stmt_begin_block(); stmt_end_nop(); stmt_end_block(); }
	| ';' { stmt_end_nop(); } 
	;

control: KW_IF { stmt_begin_if(); } '(' expr ')' block else { stmt_end_if(); }
	| KW_WHILE { stmt_begin_while(); } '(' expr ')' block { stmt_end_while(); }
	| KW_DO { stmt_begin_do(); } block KW_WHILE '(' expr ')' { stmt_end_do(); }
	| KW_FOR { stmt_begin_for(); } '(' nullexpr ';' nullexpr ';' nullexpr ')' block { stmt_end_for(); }
	| KW_SWITCH { stmt_begin_switch(); } '(' expr ')' '{' cases '}'	{ stmt_end_switch(); }
	| KW_TRY { stmt_begin_try(); } block KW_CATCH '(' ID ')' block { stmt_end_try($6); }
	;

else: 	/* empty */
	| KW_ELSE block			{ /* nop */ }
	;

cases: { stmt_begin_case(); } case	{ /* nop */ }
	| cases { stmt_begin_case(); } case { /* nop */ }
	;

case:	KW_CASE	expr ':' statements { stmt_end_case(1); }
        | KW_CASE expr ':' { stmt_end_nop(); stmt_end_case(1); }
	| KW_CASE expr ':' statements KW_BREAK ';' { stmt_end_case(0); }
	| KW_DEFAULT ':' statements { stmt_end_default(); }
	| KW_DEFAULT ':' { stmt_end_nop(); stmt_end_default(); }
	;

nullexpr: expr				{ /* nop */ }
	|				{ expr_end_true(); }
	;

statement: expr				{ stmt_end_expr(); }
	| KW_CONTINUE			{ stmt_end_continue(); }
	| KW_BREAK			{ stmt_end_break(); }
	| KW_RETURN			{ stmt_end_return(); }
	| KW_RETURN expr		{ stmt_end_return_value(); }
	| KW_THROW expr			{ stmt_end_throw(); }
	;

expr:	ref  				{ /* nop */ }
	| indexable			{ /* nop */ }
	| indexable indexes		{ /* nop */ }
	| cast				{ /* nop */ }
	| const				{ /* nop */ }
	| infix				{ /* nop */ }
	| postfix			{ /* nop */ }
	| prefix			{ /* nop */ }
	| assign			{ /* nop */ }
	| lambda			{ /* nop */ }
	| expr '?' expr ':' expr	{ expr_end_if(); }
	| KW_FILE			{ expr_end_file(); }
	| KW_LINE			{ expr_end_line(); }
	;

indexable: '(' expr ')'			{ /* nop */ }
	| call				{ /* nop */ }
	| cons				{ /* nop */ }
	| static			{ /* nop */ }
	| method			{ /* nop */ }
	;

indexes: index
	| indexes index
	;
	
index: '[' expr ']'			{ expr_end_first(); expr_end_index(); }
	| '.' ID			{ expr_end_field($2); expr_end_first(); expr_end_index(); }
	| '.' ID '(' ')'		{ expr_end_method_void($2); }
	| '.' ID '(' arglist ')'	{ expr_end_method($2); }
	;

lambda: '\\' { expr_begin_lambda(); } '(' argdefs ')' '{' statements '}' { expr_end_lambda(); }
	;

call:	ID '(' ')'			{ expr_end_call_void($1, 0); }
	| ID '(' arglist ')'		{ expr_end_call($1, 0); }
	;
	
cons:	KW_NEW ID '(' ')'		{ expr_end_call_void($2, 1); }
	| KW_NEW ID '(' arglist ')'	{ expr_end_call($2, 1); }
	;

static: ID KW_STATIC ID '(' ')'		{ expr_end_static_void($1, $3); }
	| ID KW_STATIC ID '(' arglist ')' { expr_end_static($1, $3); }
	;

method: ID refexp '.' ID '(' ')' { expr_end_ref_array($1); expr_end_method_void($4); }
	| ID refexp '.' ID '(' { expr_end_ref_array($1); } arglist ')' { expr_end_method($4); }
	| ID '.' ID '(' ')' { expr_end_ref($1); expr_end_method_void($3); }
	| ID '.' ID '(' { expr_end_ref($1); } arglist ')' { expr_end_method($3); }
	;

ref:	ID				{ expr_end_ref($1); }
	| ID refexp			{ expr_end_ref_array($1); }
	| ID KW_STATIC ID		{ expr_end_static_ref($1, $3); }
	;

refexp: '[' expr ']'			{ expr_end_first(); }
	| '.' ID			{ expr_end_field($2); expr_end_first(); }
	| refexp '[' expr ']'		{ expr_end_next(); }
	| refexp '.' ID			{ expr_end_field($3); expr_end_next(); }
	;

assign: ID OP_ASSIGN expr		{ expr_end_assign($1); }
	| ID OP_APLUS expr		{ expr_end_op_assign($1, OPTYPE_PLUS); }
	| ID OP_AMINUS expr		{ expr_end_op_assign($1, OPTYPE_MINUS); }
	| ID OP_AMUL expr		{ expr_end_op_assign($1, OPTYPE_MUL); }
	| ID OP_ADIV expr		{ expr_end_op_assign($1, OPTYPE_DIV); }
	| ID OP_AAND expr		{ expr_end_op_assign($1, OPTYPE_AND); }
	| ID OP_AOR expr		{ expr_end_op_assign($1, OPTYPE_OR); }
	| ID OP_AXOR expr		{ expr_end_op_assign($1, OPTYPE_XOR); }
	| ID OP_ALSHIFT expr		{ expr_end_op_assign($1, OPTYPE_LSHIFT); }
	| ID OP_ARSHIFT expr		{ expr_end_op_assign($1, OPTYPE_RSHIFT); }
	| ID refexp OP_ASSIGN expr	{ expr_end_assign_array($1); }
	| ID refexp OP_APLUS expr	{ expr_end_op_assign_array($1, OPTYPE_PLUS); }
	| ID refexp OP_AMINUS expr	{ expr_end_op_assign_array($1, OPTYPE_MINUS); }
	| ID refexp OP_AMUL expr	{ expr_end_op_assign_array($1, OPTYPE_MUL); }
	| ID refexp OP_ADIV expr	{ expr_end_op_assign_array($1, OPTYPE_DIV); }
	| ID refexp OP_AAND expr	{ expr_end_op_assign_array($1, OPTYPE_AND); }
	| ID refexp OP_AOR expr	{ expr_end_op_assign_array($1, OPTYPE_OR); }
	| ID refexp OP_AXOR expr	{ expr_end_op_assign_array($1, OPTYPE_XOR); }
	| ID refexp OP_ALSHIFT expr	{ expr_end_op_assign_array($1, OPTYPE_LSHIFT); }
	| ID refexp OP_ARSHIFT expr	{ expr_end_op_assign_array($1, OPTYPE_RSHIFT); }
	;

prefix:	OP_NOT expr			{ expr_end_prefix(OPTYPE_NOT); }
	| OP_MINUS expr	%prec UNARY_MINUS { expr_end_prefix(OPTYPE_MINUS); }
	| OP_PLUSPLUS expr		{ expr_end_prefix(OPTYPE_PREINC); }
	| OP_MINUSMINUS expr		{ expr_end_prefix(OPTYPE_PREDEC); }
	| OP_NEG expr			{ expr_end_prefix(OPTYPE_NEG); }
	;

infix:	expr OP_PLUS expr		{ expr_end_infix(OPTYPE_PLUS); }
	| expr OP_MINUS expr		{ expr_end_infix(OPTYPE_MINUS); }
	| expr OP_MUL expr		{ expr_end_infix(OPTYPE_MUL); }
	| expr OP_DIV expr		{ expr_end_infix(OPTYPE_DIV); }
	| expr OP_MOD expr		{ expr_end_infix(OPTYPE_MOD); }
	| expr OP_POW expr		{ expr_end_infix(OPTYPE_POW); }
	| expr OP_BOOL_AND expr 	{ expr_end_infix(OPTYPE_BOOL_AND); }
	| expr OP_BOOL_OR expr		{ expr_end_infix(OPTYPE_BOOL_OR); }
	| expr OP_AND expr		{ expr_end_infix(OPTYPE_AND); }
	| expr OP_OR expr		{ expr_end_infix(OPTYPE_OR); }
	| expr OP_XOR expr		{ expr_end_infix(OPTYPE_XOR); }
	| expr OP_LSHIFT expr           { expr_end_infix(OPTYPE_LSHIFT); }
	| expr OP_RSHIFT expr           { expr_end_infix(OPTYPE_RSHIFT); }
	| expr OP_EQUAL expr		{ expr_end_infix(OPTYPE_EQUAL); }
	| expr OP_NOT_EQUAL expr	{ expr_end_infix(OPTYPE_NOT_EQUAL); }
	| expr OP_SEQ expr		{ expr_end_infix(OPTYPE_SEQ); }
	| expr OP_LEQ expr		{ expr_end_infix(OPTYPE_LEQ); }
	| expr OP_SMALLER expr		{ expr_end_infix(OPTYPE_SMALLER); }
	| expr OP_LARGER expr		{ expr_end_infix(OPTYPE_LARGER); }
	;

postfix: expr OP_PLUSPLUS		{ expr_end_postfix(OPTYPE_POSTINC); }
	| expr OP_MINUSMINUS		{ expr_end_postfix(OPTYPE_POSTDEC); }
	;

arglist: argexpr			{ expr_end_first(); }
	| arglist ',' argexpr		{ expr_end_next(); }
	;

argexpr: OP_AND expr			{ expr_end_pass_ref(); }
	| expr				{ /* nop */ }
	;

const:	CONST_BOOL		{ expr_end_const_bool($1); }
	| CONST_INT		{ expr_end_const_int($1); }
	| CONST_FLOAT		{ expr_end_const_float($1); }
	| CONST_STRING		{ expr_end_const_string($1); }
	| '(' ')'		{ expr_end_const_void(); }
	;

cast: 	CAST_VOID expr		{ expr_end_cast("void"); }
	| CAST_BOOL expr	{ expr_end_cast("bool"); }
	| CAST_INT expr		{ expr_end_cast("int"); }
	| CAST_UINT expr	{ expr_end_cast("uint"); }
	| CAST_FLOAT expr	{ expr_end_cast("float"); }
	| CAST_STRING expr	{ expr_end_cast("string"); }
	| CAST_ARRAY expr	{ expr_end_cast("array"); }
	| CAST_STRUCT expr	{ expr_end_cast("struct"); }
	;

fundef: { stmt_begin_func(); } rettype ID '(' argdefs ')' block { stmt_end_func($3); }
	;

rettype: TYPE_VOID		{ stmt_end_rettype('v'); }
	| TYPE_BOOL		{ stmt_end_rettype('b'); }
	| TYPE_INT		{ stmt_end_rettype('i'); }
	| TYPE_FLOAT		{ stmt_end_rettype('f'); }
	| TYPE_STRING		{ stmt_end_rettype('s'); }
	| TYPE_ARRAY		{ stmt_end_rettype('a'); }
	| TYPE_STRUCT		{ stmt_end_rettype('c'); }
	| TYPE_FN		{ stmt_end_rettype('p'); }
	| TYPE_RES		{ stmt_end_rettype('r'); }
	| TYPE_MIXED		{ stmt_end_rettype('?'); }
	| KW_FORCE TYPE_VOID	{ stmt_end_rettype('V'); }
	| KW_FORCE TYPE_BOOL	{ stmt_end_rettype('B'); }
	| KW_FORCE TYPE_INT	{ stmt_end_rettype('I'); }
	| KW_FORCE TYPE_FLOAT	{ stmt_end_rettype('F'); }
	| KW_FORCE TYPE_STRING	{ stmt_end_rettype('S'); }
	| KW_FORCE TYPE_ARRAY	{ stmt_end_rettype('A'); }
	| KW_FORCE TYPE_STRUCT  { stmt_end_rettype('C'); }
	| KW_FORCE TYPE_FN	{ stmt_end_rettype('P'); }
	| KW_FORCE TYPE_RES	{ stmt_end_rettype('R'); }
	| KW_FORCE TYPE_MIXED	{ stmt_end_rettype('?'); }
	;

argdefs: argdef			{ /* nop */ }
	| argdefs ',' argdef	{ /* nop */ }
	|                       { /* nop */ }
	;

argdef: TYPE_VOID ID		  { stmt_end_arg('v', $2); }
	| TYPE_BOOL ID		  { stmt_end_arg('b', $2); }
	| TYPE_INT ID		  { stmt_end_arg('i', $2); }
	| TYPE_FLOAT ID		  { stmt_end_arg('f', $2); }
	| TYPE_STRING ID	  { stmt_end_arg('s', $2); }
	| TYPE_ARRAY ID		  { stmt_end_arg('a', $2); }
	| TYPE_STRUCT ID	  { stmt_end_arg('c', $2); }
	| TYPE_FN ID		  { stmt_end_arg('p', $2); }
	| TYPE_RES ID             { stmt_end_arg('r', $2); }
	| TYPE_MIXED ID		  { stmt_end_arg('?', $2); }
	| KW_FORCE TYPE_VOID ID   { stmt_end_arg('V', $3); }
	| KW_FORCE TYPE_BOOL ID   { stmt_end_arg('B', $3); }
	| KW_FORCE TYPE_INT ID    { stmt_end_arg('I', $3); }
	| KW_FORCE TYPE_FLOAT ID  { stmt_end_arg('F', $3); }
	| KW_FORCE TYPE_STRING ID { stmt_end_arg('S', $3); }
	| KW_FORCE TYPE_ARRAY ID  { stmt_end_arg('A', $3); }
	| KW_FORCE TYPE_STRUCT ID { stmt_end_arg('C', $3); }
	| KW_FORCE TYPE_FN ID	  { stmt_end_arg('P', $3); }
	| KW_FORCE TYPE_RES ID    { stmt_end_arg('R', $3); }
	| KW_FORCE TYPE_MIXED ID  { stmt_end_arg('?', $3); }
	| ID			  { stmt_end_arg('?', $1); }
	;

tmpldef: KW_TMPL { stmt_begin_tmpl(); } ID extends '{' tmpldecls '}' { stmt_end_tmpl($3); }
	;

extends: KW_EXTENDS ID			{ stmt_end_extends($2); }
	|				{ stmt_end_extends(NULL); }
	;

tmpldecls: tmpldecl
	| tmpldecls tmpldecl
	;
	
tmpldecl: fundef			{ /* nop */ }
	| ID ';'			{ expr_end_const_void(); expr_end_assign($1); stmt_end_expr(); }
	| ID OP_ASSIGN expr ';'		{ expr_end_assign($1); stmt_end_expr(); }
	;

%%
