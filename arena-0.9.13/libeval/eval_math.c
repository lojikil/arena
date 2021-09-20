/*
 * Math operator evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <math.h>
#include <stdlib.h>

#include "eval.h"

/*
 * Evaluate addition
 */
value *eval_math_plus(value *a, value *b)
{
  value *res;
  
  sanity(a && b);

  if (a->type == VALUE_TYPE_INT) {
    res = value_make_int(a->value_u.int_val + b->value_u.int_val);
  } else {
    res = value_make_float(a->value_u.float_val + b->value_u.float_val);
  }
  return res;
}

/*
 * Evaluate subtraction
 */
value *eval_math_minus(value *a, value *b)
{
  value *res;

  sanity(a && b);

  if (a->type == VALUE_TYPE_INT) {
    res = value_make_int(a->value_u.int_val - b->value_u.int_val);
  } else {
    res = value_make_float(a->value_u.float_val - b->value_u.float_val);
  }
  return res;
}

/*
 * Evaluate multiplication
 */
value *eval_math_mul(value *a, value *b)
{
  value *res;
  
  sanity(a && b);

  if (a->type == VALUE_TYPE_INT) {
    res = value_make_int(a->value_u.int_val * b->value_u.int_val);
  } else {
    res = value_make_float(a->value_u.float_val * b->value_u.float_val);
  }
  return res;
}

/*
 * Evaluate division
 */
value *eval_math_div(arena_state *s, value *a, value *b)
{
  value *res = NULL;
  
  sanity(a && b);

  if (a->type == VALUE_TYPE_INT) {
    if (b->value_u.int_val != 0) {
      res = value_make_int(a->value_u.int_val / b->value_u.int_val);
    } else {
      fatal(s, "integer division by zero");
      return value_make_int(0);
    }
  } else {
    if (b->value_u.float_val != 0.0) {
      res = value_make_float(a->value_u.float_val / b->value_u.float_val);
    } else {
      fatal(s, "floating point division by zero");
      return value_make_float(0.0);
    }
  }
  return res;
}

/*
 * Evaluate modulus
 */
value *eval_math_mod(arena_state *s, value *a, value *b)
{
  value *res = NULL;
  
  sanity(a && b);

  if (a->type == VALUE_TYPE_INT) {
    if (b->value_u.int_val != 0) {
      res = value_make_int(a->value_u.int_val % b->value_u.int_val);
    } else {
      fatal(s, "integer division by zero");
      return value_make_int(0);
    }
  } else {
    if (b->value_u.float_val != 0.0) {
      res = value_make_float(fmod(a->value_u.float_val, b->value_u.float_val));
    } else {
      fatal(s, "floating point division by zero");
      return value_make_float(0.0);
    }
  }
  return res;
}

/*
 * Evaluate power
 */
value *eval_math_pow(value *a, value *b)
{
  value *res;
  int ival = 1, iorig;
  
  sanity(a && b);

  if (a->type == VALUE_TYPE_INT) {
    iorig = b->value_u.int_val;
    if (iorig < 0) iorig = 0;
    while (iorig-- > 0) {
      ival *= a->value_u.int_val;
    }
    res = value_make_int(ival);
  } else {
    res = value_make_float(pow(a->value_u.float_val, b->value_u.float_val));
  }
  return res;
}
