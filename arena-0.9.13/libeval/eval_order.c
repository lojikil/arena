/*
 * Order operator evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "eval.h"

/*
 * compare fn values for equality
 */
static int fns_are_equal(value *a, value *b)
{
  signature *asig = a->value_u.fn_val;
  signature *bsig = b->value_u.fn_val;
  
  if (asig->type != bsig->type) {
    return 0;
  }
  if (asig->type == FUNCTION_TYPE_BUILTIN) {
    return (asig->call_u.builtin_vector == bsig->call_u.builtin_vector);
  } else {
    return (asig->def == bsig->def);
  }
}

/*
 * order constants
 */
#define ORDER_SMALLER	(-1)
#define ORDER_EQUAL	0
#define ORDER_LARGER	1
#define ORDER_UNKNOWN	42

/*
 * get ordering of two values
 */
static int getorder(value *a, value *b)
{
  int res = ORDER_UNKNOWN;

  switch (a->type) {
    case VALUE_TYPE_VOID:
      res = ORDER_EQUAL;
    case VALUE_TYPE_BOOL:
      if (a->value_u.bool_val < b->value_u.bool_val) {
        res = ORDER_SMALLER;
      } else if (a->value_u.bool_val > b->value_u.bool_val) {
        res = ORDER_LARGER;
      } else {
        res = ORDER_EQUAL;
      }
      break;
    case VALUE_TYPE_INT:
      if (a->value_u.int_val < b->value_u.int_val) {
        res = ORDER_SMALLER;
      } else if (a->value_u.int_val > b->value_u.int_val) {
        res = ORDER_LARGER;
      } else {
        res = ORDER_EQUAL;
      }
      break;
    case VALUE_TYPE_FLOAT:
      if (a->value_u.float_val < b->value_u.float_val) {
        res = ORDER_SMALLER;
      } else if (a->value_u.float_val > b->value_u.float_val) {
        res = ORDER_LARGER;
      } else {
        res = ORDER_EQUAL;
      }
      break;
    case VALUE_TYPE_STRING:
      if (a->value_u.string_val.len == 0 && b->value_u.string_val.len == 0) {
        res = ORDER_EQUAL;
      } else if (a->value_u.string_val.len == 0) {
        res = ORDER_SMALLER;
      } else if (b->value_u.string_val.len == 0) {
        res = ORDER_LARGER;
      } else {
        int min, tmp;
        
        if (a->value_u.string_val.len > b->value_u.string_val.len) {
          res = ORDER_LARGER;
          min = b->value_u.string_val.len;
        } else if (a->value_u.string_val.len < b->value_u.string_val.len) {
          res = ORDER_SMALLER;
          min = a->value_u.string_val.len;
        } else {
          res = ORDER_EQUAL;
          min = a->value_u.string_val.len;
        }
        tmp = memcmp(a->value_u.string_val.value,
          b->value_u.string_val.value, min);
        if (tmp < 0) {
          res = ORDER_SMALLER;
        } else if (tmp > 0) {
          res = ORDER_LARGER;
        }
      }
      break;
    case VALUE_TYPE_FN:
      if (fns_are_equal(a, b)) {
        res = ORDER_EQUAL;
      }
      break;
    case VALUE_TYPE_ARRAY:
    case VALUE_TYPE_STRUCT:
    case VALUE_TYPE_RES:
      /* can't compute, assume not equal */
      break;
  }
  return res;
}

/*
 * Evaluate equality operator
 */
value *eval_order_equal(value *a, value *b)
{
  int res;
  
  sanity(a && b);
  
  res = (a->type == b->type && getorder(a,b) == ORDER_EQUAL);
  return value_make_bool(res);
}

/*
 * Evaluate non-equality operator
 */
value *eval_order_not_equal(value *a, value *b)
{
  int res;

  sanity(a && b);

  res = (a->type != b->type || getorder(a,b) != ORDER_EQUAL);
  return value_make_bool(res);
}

/*
 * Evaluate smaller-or-equal operator
 */
value *eval_order_seq(value *a, value *b)
{
  int order;
  
  sanity(a && b);
  
  order = getorder(a, b);
  return value_make_bool(order == ORDER_SMALLER || order == ORDER_EQUAL);
}

/*
 * Evaluate larger-or-equal operator
 */
value *eval_order_leq(value *a, value *b)
{
  int order;
  
  sanity(a && b);
  
  order = getorder(a, b);
  return value_make_bool(order == ORDER_LARGER || order == ORDER_EQUAL);
}

/*
 * Evaluate smaller operator
 */
value *eval_order_smaller(value *a, value *b)
{
  int order;
  
  sanity(a && b);
  
  order = getorder(a, b);
  return value_make_bool(order == ORDER_SMALLER);
}

/*
 * Evaluate larger operator
 */
value *eval_order_larger(value *a, value *b)
{
  int order;
  
  sanity(a && b);
  
  order = getorder(a, b);
  return value_make_bool(order == ORDER_LARGER);
}
