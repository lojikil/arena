/*
 * Math functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <math.h>
#include <stdlib.h>

#include "stdlib.h"

/*
 * Compute exponential
 */ 
value *math_exp(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(exp(argv[0]->value_u.float_val));
}

/*
 * Compute natural logarithm
 */
value *math_log(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(log(argv[0]->value_u.float_val));
}

/*
 * Compute base-10 logarithm
 */
value *math_log10(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(log10(argv[0]->value_u.float_val));
}

/*
 * Compute square root
 */
value *math_sqrt(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(sqrt(argv[0]->value_u.float_val));
}

/*
 * Compute ceiling (rounding up)
 */
value *math_ceil(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(ceil(argv[0]->value_u.float_val));
}

/*
 * Compute floor (rounding down)
 */
value *math_floor(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(floor(argv[0]->value_u.float_val));
}

/*
 * Compute absolute value
 */
value *math_fabs(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(fabs(argv[0]->value_u.float_val));
}

/*
 * Compute sine
 */
value *math_sin(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(sin(argv[0]->value_u.float_val));
}

/*
 * Compute cosine
 */
value *math_cos(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(cos(argv[0]->value_u.float_val));
}

/*
 * Compute tangent
 */
value *math_tan(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(tan(argv[0]->value_u.float_val));
}

/*
 * Compute arc-sine
 */
value *math_asin(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(asin(argv[0]->value_u.float_val));
}

/*
 * Compute arc-cosine
 */
value *math_acos(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(acos(argv[0]->value_u.float_val));
}

/*
 * Compute arc-tangent
 */
value *math_atan(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(atan(argv[0]->value_u.float_val));
}

/*
 * Compute hyperbolic sine
 */
value *math_sinh(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(sinh(argv[0]->value_u.float_val));
}

/*
 * Compute hyperbolic cosine
 */
value *math_cosh(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(cosh(argv[0]->value_u.float_val));
}

/*
 * Compute hyperbolic tangent
 */
value *math_tanh(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_float(tanh(argv[0]->value_u.float_val));
}

/*
 * Compute absolute value of integer
 */
value *math_abs(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_int(abs(argv[0]->value_u.int_val));
}
