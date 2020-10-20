/*
 * Prefix operator evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "eval.h"

/*
 * Type promotion for prefix operators
 *
 * Promotes the value to int if the operator only allows
 * ints, otherwise float is also allowed.
 */
static void promote_prefix(arena_state *s, value **one, int allow_float)
{
  if (!allow_float || (*one)->type != VALUE_TYPE_FLOAT) {
    value_cast_inplace(s, one, VALUE_TYPE_INT);
  }
}

/*
 * Evaluate unary minus operator
 */
static value *unary_minus(arena_state *s, expr *ex)
{
  value *val;
  
  val = eval_expr(s, ex);
  promote_prefix(s, &val, 1);

  if (val->type == VALUE_TYPE_INT) {
    val->value_u.int_val = - val->value_u.int_val;
  } else if (val->type == VALUE_TYPE_FLOAT) {
    val->value_u.float_val = - val->value_u.float_val;
  }
  return val;
}

/*
 * Evaluate logical NOT operator
 */
static value *logical_not(arena_state *s, expr *ex)
{
  value *val;
  
  val = eval_expr(s, ex);
  value_cast_inplace(s, &val, VALUE_TYPE_BOOL);
  
  val->value_u.bool_val ^= 1;

  return val;
}

/*
 * Evaluate pre-increment operator
 */
static value *preincrement(arena_state *s, expr *ex)
{
  value *val;
  
  val = eval_expr(s, ex);
  promote_prefix(s, &val, 0);

  ++val->value_u.int_val;

  if (!s->except_flag && !s->exit_flag) {  
    if (ex->type == EXPR_REF) {
      symtab_stack_add_variable(s, ex->name, val);
    } else if (ex->type == EXPR_REF_ARRAY) {
      eval_assign_array_direct(s, ex->name, ex->argc, ex->argv, val);
    }
  }

  return val;
}

/*
 * Evaluate pre-decrement operator
 */
static value *predecrement(arena_state *s, expr *ex)
{
  value *val;
  
  val = eval_expr(s, ex);
  promote_prefix(s, &val, 0);

  --val->value_u.int_val;

  if (!s->except_flag && !s->exit_flag) {  
    if (ex->type == EXPR_REF) {
      symtab_stack_add_variable(s, ex->name, val);
    } else if (ex->type == EXPR_REF_ARRAY) {
      eval_assign_array_direct(s, ex->name, ex->argc, ex->argv, val);
    }
  }

  return val;
}

/*
 * Evaluate bit-negation operator
 */
value *negate(arena_state *s, expr *ex)
{
  value *val;
  
  val = eval_expr(s, ex);
  promote_prefix(s, &val, 0);

  val->value_u.int_val = ~ val->value_u.int_val;

  return val;
}

/*
 * Evaluate prefix operator
 */
value *eval_prefix(arena_state *s, expr *ex)
{
  value *res = NULL;
  
  sanity(ex);

  switch (ex->op) {
    case OPTYPE_MINUS:
      res = unary_minus(s, ex->inner);
      break;
    case OPTYPE_NOT:
      res = logical_not(s, ex->inner);
      break;
    case OPTYPE_PREINC:
      res = preincrement(s, ex->inner);
      break;
    case OPTYPE_PREDEC:
      res = predecrement(s, ex->inner);
      break;
    case OPTYPE_NEG:
      res = negate(s, ex->inner);
      break;
    default:
      sanity(0);
  }
  return res;
}
