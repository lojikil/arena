/*
 * Evaluation of switch statement
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "eval.h"

/*
 * Evaluate switch
 */
void eval_stmt_switch(arena_state *s, stmt *st, int cookie)
{
  value *val, *guard, *equal;
  stmt_list *list;
  stmt *label;
  unsigned int i, handled = 0, go = 0;
  int def = -1;
  
  sanity(st && st->type == STMT_SWITCH && st->block);
  list = (stmt_list *) st->block;

  val = eval_expr(s, st->expr);
  
  for (i = 0; i < list->len; i++) {
    label = list->list[i];
    sanity(label && (label->type == STMT_CASE || label->type == STMT_DEFAULT));
    
    if (label->type == STMT_DEFAULT) def = i;

    if (!go && label->type != STMT_CASE) continue;

    if (!go) {
      guard = eval_expr(s, label->expr);
      equal = eval_order_equal(val, guard);
      go = equal->value_u.bool_val;
      value_free(guard);
      value_free(equal);
    }
    
    if (go) {
      handled = 1;
      eval_stmt_list(s, (stmt_list *) label->block, cookie);
    }
    
    if (go && !label->thru) break;
  }

  if (!handled && def >= 0) {
    eval_stmt_list(s, (stmt_list *) list->list[def]->block, cookie);
  }

  value_free(val);
}
