/*
 * Expression stack handling
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

/*
 * Depth of stack
 */
static int expr_depth = 0;

/*
 * Expression stack
 */
static expr **expr_stack = NULL;

/*
 * Depth of argument count stack
 */
static int arg_depth = 0;

/*
 * Argument count stack
 */
static unsigned int *arg_count = NULL;

/*
 * Push expression onto stack
 *
 * This function pushed an expression onto the stack. It returns 0
 * on success and -1 on failure.
 */
void expr_stack_push(expr *ex)
{
  expr **copy;
  
  sanity(ex);
  
  copy = oom(realloc(expr_stack, (expr_depth + 1) * sizeof(expr *)));
  expr_stack = copy;
  expr_stack[expr_depth++] = ex;
}

/*
 * Pop expression from stack
 *
 * This function returns the last expression that was pushed onto the
 * stack. It returns NULL if no such expression exists.
 */
expr *expr_stack_pop(void)
{
  sanity(expr_depth > 0);
  
  expr_depth--;
  return expr_stack[expr_depth];
}

/*
 * Tear down expression stack
 */
void expr_stack_teardown(void)
{
  if (expr_stack) {
    free(expr_stack);
    expr_stack = NULL;
    expr_depth = 0;
  }
}

/*
 * Enter new argument count
 *
 * This function extends the argument count stack one level. It is
 * called whenever the parser enters the scope of a new function
 * call with arguments.
 */
void expr_arg_enter(void)
{
  unsigned int *count;

  count = oom(realloc(arg_count, (arg_depth + 1) * sizeof(int *)));
  arg_count = count;
  arg_count[arg_depth++] = 1;
}

/*
 * Push argument count
 *
 * This function increases the argument count stored in the top level
 * of the argument count stack by one. It is called whenever the
 * parser encounters a new argument to a function call.
 */
void expr_arg_push(void)
{
  sanity(arg_depth > 0);

  arg_count[arg_depth - 1]++;
}

/*
 * Leave argument count
 *
 * This function reduces the argument count stack by one level and
 * returns the count of arguments stored in the now-discarded level.
 * It is called by the parser when it is finished with parsing
 * function arguments and needs to know their number. This function
 * returns -1 if there was no argument count on the stack.
 */
int expr_arg_leave(void)
{
  sanity(arg_depth > 0);

  arg_depth--;
  return arg_count[arg_depth];
}

/*
 * Tear down argument count stack
 */
void expr_arg_teardown(void)
{
  if (arg_count) {
    free(arg_count);
    arg_count = NULL;
    arg_depth = 0;
  }
}
