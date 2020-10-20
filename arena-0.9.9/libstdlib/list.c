/*
 * List functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "stdlib.h"

/*
 * Create empty list
 */
value *list_nil(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_array();
}

/*
 * Prepend element to list
 */
value *list_cons(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[1]->value_u.array_val.value;
  int      len = argv[1]->value_u.array_val.len;
  int i;
  value *res;
  
  res = value_make_array();
  value_add_to_array(res, argv[0]);
  
  for (i = 0; i < len; i++) {
    value_add_to_array(res, data[i]);
  }
  return res;
}

/*
 * Get first element of list
 */
value *list_head(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[0]->value_u.array_val.value;
  int      len = argv[0]->value_u.array_val.len;

  if (len == 0) {
    return value_make_void();
  }
  return value_copy(data[0]);
}

/*
 * Get all elements of list except the first
 */
value *list_tail(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[0]->value_u.array_val.value;
  int      len = argv[0]->value_u.array_val.len;
  int i;
  value *res;
  
  res = value_make_array();
  for (i = 1; i < len; i++) {
    value_add_to_array(res, data[i]);
  }
  return res;
}

/*
 * Get last element of list
 */
value *list_last(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[0]->value_u.array_val.value;
  int      len = argv[0]->value_u.array_val.len;

  if (len == 0) {
    return value_make_void();
  }  
  return value_copy(data[len - 1]);
}

/*
 * Get all elements of list except the last
 */
value *list_init(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[0]->value_u.array_val.value;
  int      len = argv[0]->value_u.array_val.len;
  int i;
  value *res;
  
  res = value_make_array();
  for (i = 0; i < (len - 1); i++) {
    value_add_to_array(res, data[i]);
  }
  return res;
}

/*
 * Take a number of elements from the front of list
 */
value *list_take(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[0]->value_u.array_val.value;
  int      len = argv[0]->value_u.array_val.len;
  int    count = argv[1]->value_u.int_val;
  int i;
  value *res;
  
  if (count > len) count = len;
  
  res = value_make_array();
  for (i = 0; i < count; i++) {
    value_add_to_array(res, data[i]);
  }
  return res;
}

/*
 * Drop a number of elements from the front of list
 */
value *list_drop(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[0]->value_u.array_val.value;
  int      len = argv[0]->value_u.array_val.len;
  int    count = argv[1]->value_u.int_val;
  int i;
  value *res;

  if (count > len) count = len;
  
  res = value_make_array();
  for (i = count; i < len; i++) {
    value_add_to_array(res, data[i]);
  }
  return res;
}

/*
 * Length of list
 */
value *list_length(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_int(argv[0]->value_u.array_val.len);
}

/*
 * Check for empty list
 */
value *list_null(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_bool(argv[0]->value_u.array_val.len == 0);
}

/*
 * Check for element in list
 */
value *list_elem(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[0]->value_u.array_val.value;
  int      len = argv[0]->value_u.array_val.len;
  int i, flag = 0;
  value *check;
  
  for (i = 0; i < len; i++) {
    check = eval_order_equal(data[i], argv[1]);
    flag = check->value_u.bool_val;
    value_free(check);
    if (flag) break;
  }
  return value_make_bool(flag);
}

/*
 * Intersperse value between list elements
 */
value *list_intersperse(arena_state *s, unsigned int argc, value **argv)
{
  value **data = argv[0]->value_u.array_val.value;
  int      len = argv[0]->value_u.array_val.len;
  int i;
  value *res;
  
  res = value_make_array();
  for (i = 0; i < len; i++) {
    value_add_to_array(res, data[i]);
    if (i != (len - 1)) {
      value_add_to_array(res, argv[1]);
    }
  }
  return res;
}

/*
 * Replicate element to create list
 */
value *list_replicate(arena_state *s, unsigned int argc, value **argv)
{
  int i;
  value *res;
  
  res = value_make_array();
  for (i = 0; i < argv[1]->value_u.int_val; i++) {
    value_add_to_array(res, argv[0]);
  }
  return res;
}
