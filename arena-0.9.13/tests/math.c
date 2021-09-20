/*
 * Math operator tests
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
 
#include "test.h"
#include "../libruntime/runtime.h"
#include "../libeval/eval.h"

void math_test(void)
{
  arena_state *s = state_alloc();

  value *a, *b, *res;
  expr *aex, *bex;
  expr etrue, efalse;

  etrue.type = EXPR_CONST_BOOL;
  etrue.name = "true";
  
  efalse.type = EXPR_CONST_BOOL;
  efalse.name = "false";

  test_banner("libeval");

  test_section("math operators");
  
  a = value_make_int(42);
  b = value_make_int(-42);
  
  test_start("eval_math_plus (int)");
  res = eval_math_plus(a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == 0);
  value_free(res);
  
  test_start("eval_math_minus (int)");
  res = eval_math_minus(a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == 84);
  value_free(res);

  test_start("eval_math_mul (int)");
  res = eval_math_mul(a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == -1764);
  value_free(res);
  
  value_free(b);
  b = value_make_int(10);
  
  test_start("eval_math_div (int)");
  res = eval_math_div(s, a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == 4);
  value_free(res);

  test_start("eval_math_mod (int)");
  res = eval_math_mod(s, a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == 2);
  value_free(res);

  value_free(b);
  b = value_make_int(2);

  test_start("eval_math_pow (int)");
  res = eval_math_pow(a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == 1764);
  value_free(res);
  
  value_free(a);
  value_free(b);
  
  a = value_make_float(42.25);
  b = value_make_float(0.5);

  test_start("eval_math_plus (float)");
  res = eval_math_plus(a, b);
  test_assert(res && res->type == VALUE_TYPE_FLOAT &&
              res->value_u.float_val == 42.75);
  value_free(res);

  test_start("eval_math_minus (float)");
  res = eval_math_minus(a, b);
  test_assert(res && res->type == VALUE_TYPE_FLOAT &&
              res->value_u.float_val == 41.75);
  value_free(res);

  test_start("eval_math_mul (float)");
  res = eval_math_mul(a, b);
  test_assert(res && res->type == VALUE_TYPE_FLOAT &&
              res->value_u.float_val == 21.125);
  value_free(res);

  test_start("eval_math_div (float)");
  res = eval_math_div(s, a, b);
  test_assert(res && res->type == VALUE_TYPE_FLOAT &&
              res->value_u.float_val == 84.5);
  value_free(res);

  test_start("eval_math_mod (float)");
  res = eval_math_mod(s, a, b);
  test_assert(res && res->type == VALUE_TYPE_FLOAT &&
              res->value_u.float_val == 0.25);
  value_free(res);
  
  value_free(a);
  value_free(b);
  a = value_make_float(42.0);
  b = value_make_float(2.0);

  test_start("eval_math_pow (float)");
  res = eval_math_pow(a, b);
  test_assert(res && res->type == VALUE_TYPE_FLOAT &&
              res->value_u.float_val == 1764.0);
  value_free(res);
  
  value_free(a);
  value_free(b);
  
  test_section("bitwise math operators");
  
  a = value_make_int(8);
  b = value_make_int(25);
  
  test_start("eval_bit_and (int)");
  res = eval_bit_and(a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == 8);
  value_free(res);

  test_start("eval_bit_or (int)");
  res = eval_bit_or(a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == 25);
  value_free(res);

  test_start("eval_bit_xor (int)");
  res = eval_bit_xor(a, b);
  test_assert(res && res->type == VALUE_TYPE_INT &&
              res->value_u.int_val == 17);
  value_free(res);
  
  value_free(a);
  value_free(b);

  test_section("boolean operators");
  
  aex = &etrue;
  bex = &efalse;
  
  test_start("eval_bool_and (false)");
  res = eval_bool_and(s, aex, bex);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);
  
  test_start("eval_bool_and (true)");
  bex = &etrue;
  res = eval_bool_and(s, aex, bex);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);
  
  test_start("eval_bool_or (false)");
  aex = bex = &efalse;
  res = eval_bool_or(s, aex, bex);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);
  
  test_start("eval_bool_or (true)");
  aex = &etrue;
  res = eval_bool_or(s, aex, bex);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);
  
  test_section("order operators");
  
  a = value_make_bool(0);
  b = value_make_bool(1);
  
  test_start("eval_order_equal (bool)");
  res = eval_order_equal(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);

  test_start("eval_order_not_equal (bool)");
  res = eval_order_not_equal(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_seq (bool)");
  res = eval_order_seq(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_leq (bool)");
  res = eval_order_leq(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);

  test_start("eval_order_smaller (bool)");
  res = eval_order_smaller(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_larger (bool)");
  res = eval_order_larger(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);
  
  value_free(a);
  value_free(b);

  a = value_make_int(-42);
  b = value_make_int(42);
  
  test_start("eval_order_equal (int)");
  res = eval_order_equal(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);

  test_start("eval_order_not_equal (int)");
  res = eval_order_not_equal(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_seq (int)");
  res = eval_order_seq(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_leq (int)");
  res = eval_order_leq(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);

  test_start("eval_order_smaller (int)");
  res = eval_order_smaller(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_larger (int)");
  res = eval_order_larger(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);
  
  value_free(a);
  value_free(b);

  a = value_make_float(2.1);
  b = value_make_float(42.75);
  
  test_start("eval_order_equal (float)");
  res = eval_order_equal(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);

  test_start("eval_order_not_equal (float)");
  res = eval_order_not_equal(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_seq (float)");
  res = eval_order_seq(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_leq (float)");
  res = eval_order_leq(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);

  test_start("eval_order_smaller (float)");
  res = eval_order_smaller(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_larger (float)");
  res = eval_order_larger(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);
  
  value_free(a);
  value_free(b);

  a = value_make_string("a boat");
  b = value_make_string("the harbour");
  
  test_start("eval_order_equal (string)");
  res = eval_order_equal(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);

  test_start("eval_order_not_equal (string)");
  res = eval_order_not_equal(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_seq (string)");
  res = eval_order_seq(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_leq (string)");
  res = eval_order_leq(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);

  test_start("eval_order_smaller (string)");
  res = eval_order_smaller(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 1);
  value_free(res);

  test_start("eval_order_larger (string)");
  res = eval_order_larger(a, b);
  test_assert(res && res->type == VALUE_TYPE_BOOL &&
              res->value_u.bool_val == 0);
  value_free(res);
  
  value_free(a);
  value_free(b);
  
  state_free(s);
}
