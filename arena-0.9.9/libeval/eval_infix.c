/*
 * Infix operator evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
 
#include <stdlib.h>

#include "eval.h"

/*
 * Check expression type for constant expression
 */
static int is_const(int type)
{
  return (type == EXPR_CONST_BOOL || type == EXPR_CONST_INT ||
          type == EXPR_CONST_STRING);
}

/*
 * Check operator for order expression
 */
static int is_order(int op)
{
  return (op == OPTYPE_SEQ     || op == OPTYPE_LEQ ||
          op == OPTYPE_SMALLER || op == OPTYPE_LARGER);
}

/*
 * Type promotion for order operators
 *
 * If one of the values is from a constant expression, promote
 * the other to the type of the constant. Otherwise, promote
 * the second value to the type of the first value.
 */
static void promote_order(arena_state *s, value **one, value **two,
  int two_type)
{
  if (is_const(two_type)) {
    value_cast_inplace(s, one, (*two)->type);
  } else {
    value_cast_inplace(s, two, (*one)->type);
  }
}

/*
 * Check operator for math expression
 */
static int is_math(int op)
{
  return (op == OPTYPE_PLUS || op == OPTYPE_MINUS ||
          op == OPTYPE_MUL  || op == OPTYPE_DIV   ||
          op == OPTYPE_MOD  || op == OPTYPE_POW);
}

/*
 * Type promotion for math operators
 *
 * Promotes both values to float is any one of them is float,
 * otherwise promotes both to int.
 */
static void promote_math(arena_state *s, value **one, value **two)
{
  if ((*one)->type == VALUE_TYPE_FLOAT ||
      (*two)->type == VALUE_TYPE_FLOAT) {
    value_cast_inplace(s, one, VALUE_TYPE_FLOAT);
    value_cast_inplace(s, two, VALUE_TYPE_FLOAT);
  } else {
    value_cast_inplace(s, one, VALUE_TYPE_INT);
    value_cast_inplace(s, two, VALUE_TYPE_INT);
  }
}

/*
 * Check operator for bitwise expression
 */
static int is_bitwise(int op)
{
  return (op == OPTYPE_AND || op == OPTYPE_OR     ||
          op == OPTYPE_XOR || op == OPTYPE_LSHIFT ||
          op == OPTYPE_RSHIFT);
}

/*
 * Type promotion for bitwise operators
 *
 * Promotes both values to int.
 */
static void promote_bitwise(arena_state *s, value **one, value **two)
{
  value_cast_inplace(s, one, VALUE_TYPE_INT);
  value_cast_inplace(s, two, VALUE_TYPE_INT);
}

/*
 * Evaluate infix operator
 */
value *eval_infix(arena_state *s, expr *ex)
{
  value *one, *two, *res = NULL;
  
  sanity(ex);

  if (ex->op == OPTYPE_BOOL_AND) {
    return eval_bool_and(s, ex->inner, ex->index);
  } else if (ex->op == OPTYPE_BOOL_OR) {
    return eval_bool_or(s, ex->inner, ex->index);
  }

  one = eval_expr(s, ex->inner);
  two = eval_expr(s, ex->index);

  if (is_order(ex->op)) {
    promote_order(s, &one, &two, ex->index->type);
  } else if (is_math(ex->op)) {
    promote_math(s, &one, &two);
  } else if (is_bitwise(ex->op)) {
    promote_bitwise(s, &one, &two);
  }
  
  switch (ex->op) {
    case OPTYPE_PLUS:
      res = eval_math_plus(one, two);
      break;
    case OPTYPE_MINUS:
      res = eval_math_minus(one, two);
      break;
    case OPTYPE_MUL:
      res = eval_math_mul(one, two);
      break;
    case OPTYPE_DIV:
      res = eval_math_div(s, one, two);
      break;
    case OPTYPE_MOD:
      res = eval_math_mod(s, one, two);
      break;
    case OPTYPE_POW:
      res = eval_math_pow(one, two);
      break;
    case OPTYPE_AND:
      res = eval_bit_and(one, two);
      break;
    case OPTYPE_OR:
      res = eval_bit_or(one, two);
      break;
    case OPTYPE_XOR:
      res = eval_bit_xor(one, two);
      break;
    case OPTYPE_LSHIFT:
      res = eval_bit_lshift(one, two);
      break;
    case OPTYPE_RSHIFT:
      res = eval_bit_rshift(one, two);
      break;
    case OPTYPE_EQUAL:
      res = eval_order_equal(one, two);
      break;
    case OPTYPE_NOT_EQUAL:
      res = eval_order_not_equal(one, two);
      break;
    case OPTYPE_SEQ:
      res = eval_order_seq(one, two);
      break;
    case OPTYPE_LEQ:
      res = eval_order_leq(one, two);
      break;
    case OPTYPE_SMALLER:
      res = eval_order_smaller(one, two);
      break;
    case OPTYPE_LARGER:
      res = eval_order_larger(one, two);
      break;
    case OPTYPE_BOOL_AND:
    case OPTYPE_BOOL_OR:
    case OPTYPE_NEG:
    case OPTYPE_NOT:
    case OPTYPE_POSTDEC:
    case OPTYPE_POSTINC:
    case OPTYPE_PREDEC:
    case OPTYPE_PREINC:
      /* not handled here */
      break;
  }
  value_free(one);
  value_free(two);
  return res;
}
