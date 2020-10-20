/*
 * Statement parsing machinery
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "parser.h"

/*
 * Pop statement from stack or die
 */
static stmt *safe_pop(void)
{
  stmt *st;
  
  st = stmt_stack_pop();
  sanity(st);

  return st;
}

/*
 * Start of statement block
 */
void stmt_begin_block(void)
{
  stmt_stack_enter();
}

/*
 * End of statement block
 */
void stmt_end_block(void)
{
  stmt *st;
  
  st = stmt_alloc();
  st->type = STMT_BLOCK;
  st->block = (STMT_LIST *) stmt_stack_leave(0);

  stmt_stack_push(st);
}

/*
 * Start of if control statement
 */
void stmt_begin_if(void)
{
  stmt_stack_enter();
}

/*
 * End of if control statement
 */
void stmt_end_if(void)
{
  stmt *one, *two, *st;
  
  one = safe_pop();
  two = stmt_stack_pop();
  stmt_stack_leave(1);

  st = stmt_alloc();
  if (two) {
    st->type = STMT_IF_ELSE;
    st->true_case = two;
    st->false_case = one;
  } else {
    st->type = STMT_IF;
    st->true_case = one;
  }
  st->expr = expr_stack_pop();
  
  stmt_stack_push(st);
}

/*
 * Start of while control statement
 */
void stmt_begin_while(void)
{
  stmt_stack_enter();
}

/*
 * End of while control statement
 */
void stmt_end_while(void)
{
  stmt *st;
  
  st = stmt_alloc();
  st->type = STMT_WHILE;
  st->expr = expr_stack_pop();
  st->true_case = safe_pop();

  stmt_stack_leave(1);
  
  stmt_stack_push(st);
}

/*
 * Start of do control statement
 */
void stmt_begin_do(void)
{
  stmt_stack_enter();
}

/*
 * End of do control statement
 */
void stmt_end_do(void)
{
  stmt *st;
  
  st = stmt_alloc();
  st->type = STMT_DO;
  st->expr = expr_stack_pop();
  st->true_case = safe_pop();
  
  stmt_stack_leave(1);
  
  stmt_stack_push(st);
}

/*
 * Start of for control statement
 */
void stmt_begin_for(void)
{
  stmt_stack_enter();
}

/*
 * End of for control statement
 */
void stmt_end_for(void)
{
  expr *init, *expr, *guard;
  stmt *st;
  
  guard = expr_stack_pop();
  expr = expr_stack_pop();
  init = expr_stack_pop();
  
  st = stmt_alloc();
  st->type = STMT_FOR;
  st->init = init;
  st->expr = expr;
  st->guard = guard;
  st->true_case = safe_pop();
  
  stmt_stack_leave(1);
  
  stmt_stack_push(st);
}

/*
 * End simple statement
 */
static void end_simple(stmt_type type)
{
  stmt *st;
  
  st = stmt_alloc();
  st->type = type;
  
  stmt_stack_push(st);
}

/*
 * End simple statement with expression parameter
 */
static void end_simple_expr(stmt_type type)
{
  stmt *st;
  
  st = stmt_alloc();
  st->type = type;
  st->expr = expr_stack_pop();
  
  stmt_stack_push(st);
}

/*
 * End continue statement
 */
void stmt_end_continue(void)
{
  end_simple(STMT_CONTINUE);
}

/*
 * End break statement
 */
void stmt_end_break(void)
{
  end_simple(STMT_BREAK);
}

/*
 * End return statement
 */
void stmt_end_return(void)
{
  end_simple(STMT_RETURN);
}

/*
 * End return statement with expression
 */
void stmt_end_return_value(void)
{
  end_simple_expr(STMT_RETURN);
}

/*
 * End empty statement
 */
void stmt_end_nop(void)
{
  end_simple(STMT_NOP);
}

/*
 * End expression statement
 */
void stmt_end_expr(void)
{
  end_simple_expr(STMT_EXPR);
}

/*
 * List for function argument definitions
 */
static unsigned int arg_depth = 0;
static unsigned int *arg_count = NULL;
static char **arg_types = NULL;
static char ***arg_names = NULL;
static char *rettype = NULL;

/*
 * Add argument definition to list
 */
void stmt_end_arg(char typespec, char *name)
{
  char *list;
  char **names;
  unsigned int count = arg_count[arg_depth - 1];
  
  sanity(name);
  
  list = arg_types[arg_depth - 1];
  list = oom(realloc(list, (count + 2) * sizeof(char)));

  names = arg_names[arg_depth - 1];
  names = oom(realloc(names, (count + 1) * sizeof(char *)));

  names[count++] = name;
  list[count-1] = typespec;
  list[count] = 0;

  arg_count[arg_depth - 1] = count;
  arg_types[arg_depth - 1] = list;
  arg_names[arg_depth - 1] = names;
}

/*
 * Start function declaration
 */
void stmt_begin_func(void)
{
  ++arg_depth;
  
  arg_types = oom(realloc(arg_types, arg_depth * sizeof(char *)));
  arg_names = oom(realloc(arg_names, arg_depth * sizeof(char **)));
  arg_count = oom(realloc(arg_count, arg_depth * sizeof(int)));
  rettype   = oom(realloc(rettype, arg_depth * sizeof(char)));

  arg_types[arg_depth - 1] = NULL;
  arg_names[arg_depth - 1] = NULL;
  arg_count[arg_depth - 1] = 0;
  rettype[arg_depth - 1]   = '?';

  stmt_stack_enter();
}

/*
 * End function return type
 */
void stmt_end_rettype(char type)
{
  rettype[arg_depth - 1] = type;
}

/*
 * End function declaration
 */
void stmt_end_func(char *name)
{
  stmt *st;
  
  sanity(arg_depth > 0);

  --arg_depth;
  
  st = stmt_alloc();
  st->type = STMT_FUNC;
  st->true_case = safe_pop();
  st->name = name;
  st->args = arg_count[arg_depth];
  st->proto = arg_types[arg_depth];
  st->rettype = rettype[arg_depth];
  st->names = arg_names[arg_depth];

  stmt_stack_leave(1);
  
  stmt_stack_push(st);
}

/*
 * Begin switch statement
 */
void stmt_begin_switch(void)
{
  stmt_stack_enter();
}

/*
 * End switch statement
 */
void stmt_end_switch(void)
{
  stmt *st;

  st = stmt_alloc();
  st->type = STMT_SWITCH;
  st->expr = expr_stack_pop();
  st->block = (STMT_LIST *) stmt_stack_leave(0);
  
  stmt_stack_push(st);
}

/*
 * Begin case block
 */
void stmt_begin_case(void)
{
  stmt_stack_enter();
}

/*
 * End case block
 */
void stmt_end_case(char thru)
{
  stmt *st;
  stmt_list *list;
  
  list = stmt_stack_leave(0);
  if (list->len == 1 && list->list[0]->type == STMT_BREAK) {
    list->list[0]->type = STMT_NOP;
    thru = 0;
  }

  st = stmt_alloc();
  st->type = STMT_CASE;
  st->expr = expr_stack_pop();
  st->block = (STMT_LIST *) list;
  st->thru = thru;
  
  stmt_stack_push(st);
}

/*
 * End default block
 */
void stmt_end_default(void)
{
  stmt *st;
  
  st = stmt_alloc();
  st->type = STMT_DEFAULT;
  st->block = (STMT_LIST *) stmt_stack_leave(0);
  st->thru = 0;
  
  stmt_stack_push(st);
}

/*
 * Begin try-catch block
 */
void stmt_begin_try(void)
{
  stmt_stack_enter();
}

/*
 * End try-catch block
 */
void stmt_end_try(char *name)
{
  stmt *st;
  
  st = stmt_alloc();
  st->type = STMT_TRY;
  st->false_case = safe_pop();
  st->true_case = safe_pop();
  st->name = name;
  
  stmt_stack_leave(1);
  
  stmt_stack_push(st);
}

/*
 * End throw statement
 */
void stmt_end_throw(void)
{
  end_simple_expr(STMT_THROW);
}

/*
 * Begin template definition
 */
void stmt_begin_tmpl(void)
{
  stmt_stack_enter();
}

/*
 * Name of parent template
 */
static char *tmpl_parent = NULL;

/*
 * End extends declaration
 */
void stmt_end_extends(char *parent)
{
  tmpl_parent = parent;
}

/*
 * End template definition
 */
void stmt_end_tmpl(char *name)
{
  stmt *st;
  
  st = stmt_alloc();
  st->type = STMT_TMPL;
  st->name = name;
  st->proto = tmpl_parent;
  st->block = (STMT_LIST *) stmt_stack_leave(0);
  
  stmt_stack_push(st);
}

/*
 * Begin lambda expression
 */
void expr_begin_lambda(void)
{
  stmt_begin_func();
}

/*
 * End lambda expression
 */
void expr_end_lambda(void)
{
  char *name;
  stmt *block, *st;
  expr *ex;

  sanity(arg_depth > 0);
  
  --arg_depth;

  name = oom(malloc(strlen("\\lambda") + 1));
  strcpy(name, "\\lambda");

  block = stmt_alloc();
  block->type = STMT_BLOCK;
  block->block = (STMT_LIST *) stmt_stack_leave(0);

  st = stmt_alloc();
  st->type = STMT_FUNC;
  st->true_case = block;
  st->name = name;
  st->args = arg_count[arg_depth];
  st->proto = arg_types[arg_depth];
  st->rettype = '?';
  st->names = arg_names[arg_depth];
  
  ex = expr_alloc();
  ex->type = EXPR_LAMBDA;
  ex->lambda = st;
  
  expr_stack_push(ex);
}

/*
 * Tear down memory used by function argument types
 */
void stmt_arg_teardown(void)
{
  free(arg_count);
  free(arg_types);
  free(arg_names);
  free(rettype);
}
