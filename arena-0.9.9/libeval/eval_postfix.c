/*
 * Postfix operator evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "eval.h"

/*
 * Evaluate post-increment operator
 */
static value *postincrement(arena_state *s, expr *ex)
{
  value *val, *copy;
  
  val = eval_expr(s, ex);
  value_cast_inplace(s, &val, VALUE_TYPE_INT);

  copy = value_make_int(val->value_u.int_val);
  
  ++val->value_u.int_val;

  if (!s->except_flag && !s->exit_flag) {  
    if (ex->type == EXPR_REF) {
      symtab_stack_add_variable(s, ex->name, val);
    } else if (ex->type == EXPR_REF_ARRAY) {
      eval_assign_array_direct(s, ex->name, ex->argc, ex->argv, val);
    }
  }
  value_free(val);

  return copy;
}

/*
 * Evaluate post-decrement operator
 */
static value *postdecrement(arena_state *s, expr *ex)
{
  value *val, *copy;
  
  val = eval_expr(s, ex);
  value_cast_inplace(s, &val, VALUE_TYPE_INT);

  copy = value_make_int(val->value_u.int_val);
  
  --val->value_u.int_val;

  if (!s->except_flag && !s->exit_flag) {  
    if (ex->type == EXPR_REF) {
      symtab_stack_add_variable(s, ex->name, val);
    } else if (ex->type == EXPR_REF_ARRAY) {
      eval_assign_array_direct(s, ex->name, ex->argc, ex->argv, val);
    }
  }
  value_free(val);

  return copy;
}

/*
 * Evaluate postfix operator
 */
value *eval_postfix(arena_state *s, expr *ex)
{
  value *res = NULL;
  
  sanity(ex);

  switch (ex->op) {
    case OPTYPE_POSTINC:
      res = postincrement(s, ex->inner);
      break;
    case OPTYPE_POSTDEC:
      res = postdecrement(s, ex->inner);
      break;
    default:
      sanity(0);
  }
  return res;
}
