/*
 * Statement stack
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

/*
 * Depth of list stack
 */
static unsigned int stack_depth = 0;

/*
 * List stack
 */
static stmt_list **stack = NULL;

/*
 * Enter new statement list
 */
void stmt_stack_enter(void)
{
  stmt_list **copy;

  copy = oom(realloc(stack, (stack_depth + 1) * sizeof(stmt_list *)));
  stack = copy;
  stack[stack_depth++] = stmt_list_alloc();
}

/*
 * Leave last statement list
 */
stmt_list *stmt_stack_leave(int free)
{
  stmt_list *list = NULL;
  
  sanity(stack_depth > 0 || free);

  if (stack_depth == 0 && free) {
    return NULL;
  }

  stack_depth--;
  if (free) {
    stmt_list_free(stack[stack_depth]);
  } else {
    list = stack[stack_depth];
  }
  stack[stack_depth] = NULL;
  return list;
}

/*
 * Put statement on stack
 */
void stmt_stack_push(stmt *st)
{
  sanity(stack_depth > 0 && st);

  stmt_list_push(stack[stack_depth - 1], st);
}

/*
 * Get last statment from stack
 */
stmt *stmt_stack_pop(void)
{
  if (stack_depth == 0) {
    return NULL;
  }
  return stmt_list_pop(stack[stack_depth - 1]);
}

/*
 * Tear down statement stack
 */
void stmt_stack_teardown(void)
{
  if (stack) {
    free(stack);
    stack = NULL;
    stack_depth = 0;
  }
}
