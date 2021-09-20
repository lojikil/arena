/*
 * Parser library
 *
 * Provides function to parse source code into statement and
 * expression structures.
 *
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
#ifndef LIBPARSER_H
#define LIBPARSER_H

#include "../libmisc/misc.h"

#define DEBUG	0

/*
 * -- parser internals --
 */

/*
 * Parser status information
 */
extern int parser_error;

/*
 * State information
 */
extern arena_state *parser_state;

/*
 * Error reporting
 */
void yyerror(char *msg);

/*
 * Include file handling in lexer
 */
void parser_enter_include(char *path);
void parser_include_teardown(void);

/*
 * -- statements --
 */

/*
 * Statement types
 */
typedef enum {
  STMT_NOP	= 0,
  STMT_BLOCK	= 1,
  STMT_IF	= 2,
  STMT_IF_ELSE	= 3,
  STMT_WHILE	= 4,
  STMT_DO	= 5,
  STMT_FOR	= 6,
  STMT_CONTINUE = 7,
  STMT_BREAK	= 8,
  STMT_RETURN	= 9,
  STMT_EXPR	= 10,
  STMT_FUNC	= 11,
  STMT_SWITCH	= 12,
  STMT_CASE	= 13,
  STMT_DEFAULT  = 14,
  STMT_TRY	= 15,
  STMT_THROW	= 16,
  STMT_TMPL	= 17
} stmt_type;

typedef struct stmt STMT;
typedef struct stmt_list STMT_LIST;
typedef struct expr EXPR;

/*
 * Statements
 */
typedef struct stmt {
  stmt_type	type;
  EXPR		*init;
  EXPR		*expr;
  EXPR		*guard;
  STMT		*true_case;
  STMT		*false_case;
  STMT_LIST	*block;
  char		thru;
  unsigned int	args;
  char		*name;
  char		*proto;
  char		rettype;
  char		**names;
} stmt;

/*
 * Statement memory management
 */
stmt *stmt_alloc(void);
void stmt_free(stmt *st);

/*
 * Statment list
 */
typedef struct {
  unsigned int	len;
  stmt		**list;
} stmt_list;

/*
 * Statement list management
 */
stmt_list *stmt_list_alloc(void);
void stmt_list_free(stmt_list *list);
void stmt_list_push(stmt_list *list, stmt *stmt);
stmt *stmt_list_pop(stmt_list *list);

/*
 * Statement stack management
 */
void stmt_stack_enter(void);
stmt_list *stmt_stack_leave(int free);
void stmt_stack_push(stmt *stmt);
stmt *stmt_stack_pop(void);
void stmt_stack_teardown(void);

/*
 * -- expressions --
 */

/*
 * Expression types
 */
typedef enum {
  EXPR_NOP		= 0,
  EXPR_ASSIGN		= 1,
  EXPR_ASSIGN_ARRAY	= 2,
  EXPR_CAST		= 3,
  EXPR_CALL		= 4,
  EXPR_REF		= 5,
  EXPR_REF_ARRAY	= 6,
  EXPR_CONST_BOOL	= 7,
  EXPR_CONST_INT	= 8,
  EXPR_CONST_FLOAT	= 9,
  EXPR_CONST_STRING	= 10,
  EXPR_CONST_VOID	= 11,
  EXPR_INFIX		= 12,
  EXPR_POSTFIX		= 13,
  EXPR_PREFIX		= 14,
  EXPR_FIELD		= 15,
  EXPR_INDEX		= 16,
  EXPR_NEW		= 17,
  EXPR_STATIC		= 18,
  EXPR_METHOD		= 19,
  EXPR_STATIC_REF	= 20,
  EXPR_LAMBDA		= 21,
  EXPR_IF		= 22,
  EXPR_PASS_REF		= 23,
  EXPR_FILE		= 24,
  EXPR_LINE		= 25
} expr_type;

/*
 * Operator types
 */
typedef enum {
  OPTYPE_PLUS		= 1,
  OPTYPE_MINUS		= 2,
  OPTYPE_MUL		= 3,
  OPTYPE_DIV		= 4,
  OPTYPE_MOD		= 5,
  OPTYPE_BOOL_AND	= 6,
  OPTYPE_BOOL_OR	= 7,
  OPTYPE_AND		= 8,
  OPTYPE_OR		= 9,
  OPTYPE_XOR		= 10,
  OPTYPE_POW		= 11,
  OPTYPE_EQUAL		= 12,
  OPTYPE_NOT_EQUAL	= 13,
  OPTYPE_SEQ		= 14,
  OPTYPE_LEQ		= 15,
  OPTYPE_SMALLER	= 16,
  OPTYPE_LARGER		= 17,
  OPTYPE_POSTINC	= 18,
  OPTYPE_POSTDEC	= 19,
  OPTYPE_NOT		= 20,
  OPTYPE_PREINC		= 21,
  OPTYPE_PREDEC		= 22,
  OPTYPE_NEG		= 23,
  OPTYPE_LSHIFT         = 24,
  OPTYPE_RSHIFT         = 25
} op_type;

/*
 * Expressions
 */
typedef struct expr {
  expr_type	type;
  int		line;
  char		*file;
  EXPR		*inner;
  char		*name;
  char		*tname;
  EXPR		*index;
  EXPR		*elif;
  unsigned int	argc;
  EXPR		**argv;
  op_type	op;
  stmt		*lambda;
} expr;

/*
 * Expression memory management
 */
expr *expr_alloc(void);
expr *expr_copy(expr *ex);
void expr_free(expr *ex);

/*
 * Expression stack
 */
void expr_stack_push(expr *ex);
expr *expr_stack_pop(void);
void expr_stack_teardown(void);
void expr_arg_enter(void);
void expr_arg_push(void);
int expr_arg_leave(void);
void expr_arg_teardown(void);

/*
 * -- parsing machinery --
 */

/*
 * Statement parsing
 */
void stmt_begin_block(void);
void stmt_end_block(void);
void stmt_begin_if(void);
void stmt_end_if(void);
void stmt_begin_while(void);
void stmt_end_while(void);
void stmt_begin_do(void);
void stmt_end_do(void);
void stmt_begin_for(void);
void stmt_end_for(void);
void stmt_end_continue(void);
void stmt_end_break(void);
void stmt_end_return(void);
void stmt_end_return_value(void);
void stmt_end_nop(void);
void stmt_end_expr(void);
void stmt_begin_func(void);
void stmt_end_rettype(char type);
void stmt_end_func(char *name);
void stmt_end_arg(char typespec, char *name);
void stmt_begin_switch(void);
void stmt_end_switch(void);
void stmt_begin_case(void);
void stmt_end_case(char thru);
void stmt_end_default(void);
void stmt_begin_try(void);
void stmt_end_try(char *name);
void stmt_end_throw(void);
void stmt_begin_tmpl(void);
void stmt_end_extends(char *parent);
void stmt_end_tmpl(char *name);
void expr_begin_lambda(void);
void expr_end_lambda(void);
void stmt_arg_teardown(void);

/*
 * Expression parsing
 */
void expr_end_nop(void);
void expr_end_assign(char *name);
void expr_end_assign_array(char *name);
void expr_end_op_assign(char *name, op_type type);
void expr_end_op_assign_array(char *name, op_type type);
void expr_end_cast(char *typespec);
void expr_end_call_void(char *name, int cons);
void expr_end_call(char *name, int cons);
void expr_end_static_void(char *tname, char *name);
void expr_end_static(char *tname, char *name);
void expr_end_method_void(char *name);
void expr_end_method(char *name);
void expr_end_ref(char *name);
void expr_end_ref_array(char *name);
void expr_end_index(void);
void expr_end_const_bool(char *val);
void expr_end_true(void);
void expr_end_const_int(char *val);
void expr_end_const_float(char *val);
void expr_end_const_string(char *val);
void expr_end_const_void(void);
void expr_end_field(char *val);
void expr_end_infix(op_type type);
void expr_end_postfix(op_type type);
void expr_end_prefix(op_type type);
void expr_end_first(void);
void expr_end_next(void);
void expr_end_static_ref(char *tname, char *name);
void expr_end_if(void);
void expr_end_pass_ref(void);
void expr_end_file(void);
void expr_end_line(void);

/*
 * Dumping
 */
void expr_dump(expr *ex);
void stmt_dump_mode(int mode);
void stmt_dump(stmt *st);
void stmt_list_dump(stmt_list *list, int internal);

/*
 * high-level interface
 */
 
stmt_list *parse_file(arena_state *s, char *path);

#endif
