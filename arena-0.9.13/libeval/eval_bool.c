/*
 * Boolean operator evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "eval.h"

/*
 * Evaluate boolean AND
 */
value *eval_bool_and(arena_state *s, expr *a, expr *b)
{
  int bool_val;
  value *val;
  
  sanity(a && b);

  val = eval_expr(s, a);
  value_cast_inplace(s, &val, VALUE_TYPE_BOOL);
  bool_val = val->value_u.bool_val;
  value_free(val);
  
  if (!bool_val) {
    return value_make_bool(0);
  }
  
  val = eval_expr(s, b);
  value_cast_inplace(s, &val, VALUE_TYPE_BOOL);
  
  return val;
}

/*
 * Evaluate boolean OR
 */
value *eval_bool_or(arena_state *s, expr *a, expr *b)
{
  int bool_val;
  value *val;

  sanity(a && b);

  val = eval_expr(s, a);
  value_cast_inplace(s, &val, VALUE_TYPE_BOOL);
  bool_val = val->value_u.bool_val;
  value_free(val);
  
  if (bool_val) {
    return value_make_bool(1);
  }
  
  val = eval_expr(s, b);
  value_cast_inplace(s, &val, VALUE_TYPE_BOOL);
  
  return val;
}

/*
 * Evaluate conditional expression
 */
value *eval_expr_if(arena_state *s, expr *ex)
{
  value *test, *res;
  
  sanity(ex && ex->inner && ex->index && ex->elif);
  
  test = eval_expr(s, ex->inner);
  value_cast_inplace(s, &test, VALUE_TYPE_BOOL);
  
  if (test->value_u.bool_val) {
    res = eval_expr(s, ex->index);
  } else {
    res = eval_expr(s, ex->elif);
  }
  
  value_free(test);
  return res;
}
