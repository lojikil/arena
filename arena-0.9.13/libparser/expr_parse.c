/*
 * Expression parsing machinery
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "parser.h"

/*
 * Construct argc/argv pair
 */
static void safe_args(int *argc, expr ***argv)
{
  expr **next;
  int i;
  
  *argc = expr_arg_leave();
  sanity(*argc != -1);

  *argv = oom(malloc(*argc * sizeof(expr *)));

  next = (*argv) + (*argc - 1);
  for (i = 0; i < *argc; i++) {
    *next-- = expr_stack_pop();
  }
}

/*
 * End simple expression
 */
static void expr_end_simple(expr_type type)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = type;

  expr_stack_push(ex);  
}

/*
 * End empty expression
 */
void expr_end_nop(void)
{
  expr_end_simple(EXPR_NOP);
}

/*
 * End assignment expression
 */
void expr_end_assign(char *name)
{
  expr *ex, *arg;
  
  arg = expr_stack_pop();
  
  ex = expr_alloc();
  ex->type = EXPR_ASSIGN;
  ex->name = name;
  ex->inner = arg;
  
  expr_stack_push(ex);
}

/*
 * End combined operator and assignment expression
 */
void expr_end_op_assign(char *name, op_type type)
{
  expr *mod, *ref, *ex;
  
  mod = expr_stack_pop();
  
  ref = expr_alloc();
  ref->type = EXPR_REF;
  ref->name = name;
  
  expr_stack_push(ref);
  expr_stack_push(mod);
  
  expr_end_infix(type);
  
  ex = expr_copy(ref);
  ex->type = EXPR_ASSIGN;
  ex->inner = expr_stack_pop();
  
  expr_stack_push(ex);
}

/*
 * End array assignent expression
 */
void expr_end_assign_array(char *name)
{
  expr *ex, *val;
  expr **argv;
  int argc;
  
  val = expr_stack_pop();
  
  safe_args(&argc, &argv);
  
  ex = expr_alloc();
  ex->type = EXPR_ASSIGN_ARRAY;
  ex->name = name;
  ex->inner = val;
  ex->argc = argc;
  ex->argv = argv;
  
  expr_stack_push(ex);
}

/*
 * End combined operator and assignment expression
 */
void expr_end_op_assign_array(char *name, op_type type)
{
  expr *ex, *mod, *ref;
  expr **argv;
  int argc;
  
  mod = expr_stack_pop();
  
  safe_args(&argc, &argv);

  ref = expr_alloc();
  ref->type = EXPR_REF_ARRAY;
  ref->name = name;
  ref->argc = argc;
  ref->argv = argv;
  
  expr_stack_push(ref);
  expr_stack_push(mod);
  
  expr_end_infix(type);
  
  ex = expr_copy(ref);
  ex->type = EXPR_ASSIGN_ARRAY;
  ex->inner = expr_stack_pop();
  
  expr_stack_push(ex);
}

/*
 * End cast expression
 */
void expr_end_cast(char *typespec)
{
  char *tcopy;
  expr *ex;
  
  tcopy = oom(malloc(strlen(typespec) + 1));
  strcpy(tcopy, typespec);
  
  ex = expr_alloc();
  ex->type = EXPR_CAST;
  ex->inner = expr_stack_pop();
  ex->name = tcopy;
  
  expr_stack_push(ex);
}

/*
 * End void function call expression
 */
void expr_end_call_void(char *name, int cons)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = cons ? EXPR_NEW : EXPR_CALL;
  ex->name = name;

  expr_stack_push(ex);  
}

/*
 * End void static method call expression
 */
void expr_end_static_void(char *tname, char *name)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = EXPR_STATIC;
  ex->name = name;
  ex->tname = tname;
  
  expr_stack_push(ex);
}

/*
 * End void method invocation
 */
void expr_end_method_void(char *name)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = EXPR_METHOD;
  ex->inner = expr_stack_pop();
  ex->name = name;
  
  expr_stack_push(ex);
}

/*
 * End function call expression
 */
void expr_end_call(char *name, int cons)
{
  int argc;
  expr **argv;
  expr *ex;
  
  safe_args(&argc, &argv);
  
  ex = expr_alloc();
  ex->type = cons ? EXPR_NEW : EXPR_CALL;
  ex->name = name;
  ex->argc = argc;
  ex->argv = argv;
  
  expr_stack_push(ex);
}

/*
 * End static method call expression
 */
void expr_end_static(char *tname, char *name)
{
  int argc;
  expr **argv;
  expr *ex;
  
  safe_args(&argc, &argv);
  
  ex = expr_alloc();
  ex->type = EXPR_STATIC;
  ex->name = name;
  ex->tname = tname;
  ex->argc = argc;
  ex->argv = argv;
  
  expr_stack_push(ex);
}

/*
 * End method invocation
 */
void expr_end_method(char *name)
{
  int argc;
  expr **argv;
  expr *ex;
  
  safe_args(&argc, &argv);
  
  ex = expr_alloc();
  ex->type = EXPR_METHOD;
  ex->inner = expr_stack_pop();
  ex->name = name;
  ex->argc = argc;
  ex->argv = argv;
  
  expr_stack_push(ex);
}

/*
 * End variable reference expression
 */
void expr_end_ref(char *name)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = EXPR_REF;
  ex->name = name;
  
  expr_stack_push(ex);
}

/*
 * End index reference expression
 */
void expr_end_index(void)
{
  expr *ex;
  expr **argv;
  int argc;
  
  safe_args(&argc, &argv);
  
  ex = expr_alloc();
  ex->type = EXPR_INDEX;
  ex->inner = expr_stack_pop();
  ex->argc = argc;
  ex->argv = argv;
  
  expr_stack_push(ex);
}

/*
 * End array reference expression
 */
void expr_end_ref_array(char *name)
{
  expr *ex;
  expr **argv;
  int argc;
  
  safe_args(&argc, &argv);
  
  ex = expr_alloc();
  ex->type = EXPR_REF_ARRAY;
  ex->name = name;
  ex->argc = argc;
  ex->argv = argv;
  
  expr_stack_push(ex);
}

/*
 * End specified constant expression
 */
static void expr_end_const(expr_type type, char *val)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = type;
  ex->name = val;
  
  expr_stack_push(ex);
}

/*
 * End constant bool expression
 */
void expr_end_const_bool(char *val)
{
  expr_end_const(EXPR_CONST_BOOL, val);
}

/*
 * End true bool expression
 */
void expr_end_true(void)
{
  char *str;
  
  str = oom(malloc(5));
  strcpy(str, "true");
  
  expr_end_const(EXPR_CONST_BOOL, str);
}

/*
 * End constant int expression
 */
void expr_end_const_int(char *val)
{
  expr_end_const(EXPR_CONST_INT, val);
}

/*
 * End constant float expression
 */
void expr_end_const_float(char *val)
{
  expr_end_const(EXPR_CONST_FLOAT, val);
}

/*
 * End constant string expression
 */
void expr_end_const_string(char *val)
{
  expr_end_const(EXPR_CONST_STRING, val);
}

/*
 * End constant void expression
 */
void expr_end_const_void(void)
{
  expr_end_simple(EXPR_CONST_VOID);
}

/*
 * End field name
 */
void expr_end_field(char *val)
{
  expr_end_const(EXPR_FIELD, val);
}

/*
 * End infix operator expression
 */
void expr_end_infix(op_type type)
{
  expr *one, *two, *ex;
  
  two = expr_stack_pop();
  one = expr_stack_pop();
  
  ex = expr_alloc();
  ex->type = EXPR_INFIX;
  ex->inner = one;
  ex->index = two;
  ex->op = type;
  
  expr_stack_push(ex);
}

/*
 * End postfix operator expression
 */
void expr_end_postfix(op_type type)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = EXPR_POSTFIX;
  ex->inner = expr_stack_pop();
  ex->op = type;
  
  expr_stack_push(ex);
}

/*
 * End prefix operator expression
 */
void expr_end_prefix(op_type type)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = EXPR_PREFIX;
  ex->inner = expr_stack_pop();
  ex->op = type;
  
  expr_stack_push(ex);
}

/*
 * End first argument to function call
 */
void expr_end_first(void)
{
  expr_arg_enter();
}

/*
 * End non-first argument to function call
 */
void expr_end_next(void)
{
  expr_arg_push();
}

/*
 * End static template member reference
 */
void expr_end_static_ref(char *tname, char *name)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = EXPR_STATIC_REF;
  ex->tname = tname;
  ex->name = name;
  
  expr_stack_push(ex);
}

/*
 * End conditional expression
 */
void expr_end_if(void)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = EXPR_IF;
  ex->elif = expr_stack_pop();
  ex->index = expr_stack_pop();
  ex->inner = expr_stack_pop();
  
  expr_stack_push(ex);
}

/*
 * End reference passing expression
 */
void expr_end_pass_ref(void)
{
  expr *ex;
  
  ex = expr_alloc();
  ex->type = EXPR_PASS_REF;
  ex->inner = expr_stack_pop();
  
  expr_stack_push(ex);
}

/*
 * End file name reference
 */
void expr_end_file(void)
{
  expr_end_simple(EXPR_FILE);
}

/*
 * End source code line reference
 */
void expr_end_line(void)
{
  expr_end_simple(EXPR_LINE);
}
