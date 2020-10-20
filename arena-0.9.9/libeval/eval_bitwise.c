/*
 * Bitwise operator evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "eval.h"

/*
 * Evaluate bitwise AND
 */
value *eval_bit_and(value *a, value *b)
{
  sanity(a && b);

  return value_make_int(a->value_u.int_val & b->value_u.int_val);
}

/*
 * Evaluate bitwise OR
 */
value *eval_bit_or(value *a, value *b)
{
  sanity(a && b);

  return value_make_int(a->value_u.int_val | b->value_u.int_val);
}

/*
 * Evaluate bitwise XOR
 */
value *eval_bit_xor(value *a, value *b)
{
  sanity(a && b);

  return value_make_int(a->value_u.int_val ^ b->value_u.int_val);
}

/*
 * Evaluate bitwise left shift
 */
value *eval_bit_lshift(value *a, value *b)
{
  sanity(a && b);

  return value_make_int(a->value_u.int_val << b->value_u.int_val);
}

/*
 * Evaluate bitwise right shift
 */
value *eval_bit_rshift(value *a, value *b)
{
  sanity(a && b);

  return value_make_int(a->value_u.int_val >> b->value_u.int_val);
}
