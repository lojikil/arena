/*
 * Random number functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <time.h>

#include "stdlib.h"

/*
 * Generate random int
 *
 * This function generates a random unsigned integer inside a
 * specific range. The upper and lower bound are considered part
 * of the range.
 */
value *rnd_random(arena_state *s, unsigned int argc, value **argv)
{
  int lower = argv[0]->value_u.int_val;
  int upper = argv[1]->value_u.int_val;
  int scale, res;
  
  if (lower > upper) {
    return value_make_void();
  }
  
  if (lower > RAND_MAX) {
    return value_make_int(lower);
  }
  
  if (upper > RAND_MAX) {
    upper = RAND_MAX;
  }

  if (!s->seed_init) {
    srand(time(NULL));
    s->seed_init = 1;
  }
  
  scale = upper - lower + 1;
  res = (rand() % scale) + lower;
  
  return value_make_int(res);
}

/*
 * Seed random generator
 *
 * This function seeds the random generator with the given unsigned
 * int value.
 */
value *rnd_srandom(arena_state *s, unsigned int argc, value **argv)
{
  srand(argv[0]->value_u.int_val);
  return value_make_void();
}
