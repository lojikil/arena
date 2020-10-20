/*
 * parser primitives tests
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "../libparser/parser.h"

void parse_test(void)
{
  stmt *st;
  stmt_list *list;
  int res, i, j, buf;
  expr *ex;

  parser_state = state_alloc();

  test_banner("libparser");

  test_section("statements and statement lists");
  
  test_start("stmt_alloc");
  st = stmt_alloc();
  test_assert(st != NULL);
  
  test_start("stmt_free");
  stmt_free(st);
  test_assert(1);
  
  test_start("stmt_list_alloc");
  list = stmt_list_alloc();
  test_assert(list != NULL && list->len == 0 && list->list == NULL);
  
  test_start("stmt_list_free");
  stmt_list_free(list);
  test_assert(1);
  
  test_start("stmt_list_push");
  list = stmt_list_alloc();
  st = stmt_alloc();
  st->type = STMT_BLOCK;
  stmt_list_push(list, st);
  test_assert(1);
  
  test_start("stmt_list_pop");
  st = stmt_list_pop(list);
  test_assert(st != NULL && st->type == STMT_BLOCK);
  stmt_free(st);
  
  test_start("stmt_list_pop (emtpy list)");
  st = stmt_list_pop(list);
  test_assert(st == NULL);
  
  test_start("stmt_list_free (after use)");
  stmt_list_free(list);
  test_assert(1);
  
  test_start("stmt_list_push (10500 entries)");
  list = stmt_list_alloc();
  buf = 0;
  for (i = 0; i < 10500; i++) {
    st = stmt_alloc();
    if (!st) {
      buf++;
      break;
    }
    st->type = i % 7;
    stmt_list_push(list, st);
  }
  test_assert(buf == 0);
  
  test_start("stmt_list_pop (10500) entries");
  buf = 0;
  for (i = 10499; i >= 0; i--) {
    st = stmt_list_pop(list);
    if (!st || st->type != (unsigned int) i % 7) buf++;
    stmt_free(st);
  }
  test_assert(buf == 0);
  
  test_start("stmt_list_free (after 21000 uses)");
  stmt_list_free(list);
  test_assert(1);
  
  test_section("statement list stack");
  
  test_start("stmt_stack_enter");
  stmt_stack_enter();
  test_assert(1);
  
  test_start("stmt_stack_leave (free)");
  list = stmt_stack_leave(1);
  test_assert(list == NULL);
  
  test_start("stmt_stack_leave (no free)");
  stmt_stack_enter();
  list = stmt_stack_leave(0);
  test_assert(list != NULL && list->len == 0);
  stmt_list_free(list);
  
  test_start("stmt_stack_push");
  stmt_stack_enter();
  st = stmt_alloc();
  if (st) st->type = STMT_BLOCK;
  stmt_stack_push(st);
  test_assert(st != NULL);
  
  test_start("stmt_stack_enter (level 2)");
  stmt_stack_enter();
  test_assert(1);
  
  test_start("stmt_stack_pop (level 2)");
  st = stmt_stack_pop();
  test_assert(st == NULL);
  
  test_start("stmt_stack_leave (level 2)");
  list = stmt_stack_leave(1);
  test_assert(list == NULL);
  
  test_start("stmt_stack_pop (back on level 1)");
  st = stmt_stack_pop();
  test_assert(st != NULL && st->type == STMT_BLOCK);
  stmt_free(st);
  
  test_start("stmt_stack_leave (to toplevel)");
  list = stmt_stack_leave(0);
  test_assert(list != NULL && list->len == 0);
  stmt_list_free(list);
  
  test_section("expressions and expression stack");
  
  test_start("expr_alloc");
  ex = expr_alloc();
  test_assert(ex != NULL);
  
  test_start("expr_free");
  expr_free(ex);
  test_assert(1);
  
  test_start("expr_stack_push");
  ex = expr_alloc();
  ex->type = EXPR_CAST;
  expr_stack_push(ex);
  test_assert(1);
  
  test_start("expr_stack_pop");
  ex = expr_stack_pop();
  test_assert(ex != NULL && ex->type == EXPR_CAST);
  expr_free(ex);
  
  test_start("expr_stack_push (10500 entries)");
  buf = 0;
  for (i = 0; i < 10500; i++) {
    ex = expr_alloc();
    if (!ex) { buf++; break; }
    ex->type = i % 11;
    expr_stack_push(ex);
  }
  test_assert(buf == 0);
  
  test_start("expr_stack_pop (10500 entries)");
  buf = 0;
  for (i = 10499; i >= 0; i--) {
    ex = expr_stack_pop();
    if (!ex || ex->type != (unsigned int) i % 11) buf++;
    expr_free(ex);
  }
  test_assert(buf == 0);
  
  test_start("expr_arg_enter");
  expr_arg_enter();
  test_assert(1);
  
  test_start("expr_arg_leave");
  res = expr_arg_leave();
  test_assert(res == 1);
  
  test_start("expr_arg_push");
  expr_arg_enter();
  expr_arg_push();
  res = expr_arg_leave();
  test_assert(res == 2);
  
  test_start("expr_arg_enter (4200 levels)");
  for (i = 0; i < 4200; i++) {
    expr_arg_enter();
    for (j = 0; j < i; j++) {
      expr_arg_push();
    }
  }
  test_assert(1);
  
  test_start("expr_arg_leave (4200 levels)");
  buf = 0;
  for (i = 4199; i >= 0; i--) {
    res = expr_arg_leave();
    if (res != i + 1) buf++;
  }
  test_assert(buf == 0);
  
  state_free(parser_state);
}
