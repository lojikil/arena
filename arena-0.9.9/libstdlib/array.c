/*
 * Array functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
 
#include "stdlib.h"

/*
 * Comparison function for qsort
 */
static int compar(const void *a, const void *b)
{
  value *first = *(value **) a;
  value *second = *(value **) b;
  value *res, *cast = NULL;
  int order;
  
  if (first->type != second->type) {
    cast = value_cast(NULL, second, first->type);
    second = cast;
  }
  
  res = eval_order_seq(first, second);
  order = res->value_u.bool_val;

  value_free(res);
  value_free(cast);

  if (order) {
    return -1;
  } else {
    return 1;
  }
}

/*
 * Create array from parameter values
 */
value *array_mkarray(arena_state *s, unsigned int argc, value **argv)
{
  value *arr;
  unsigned int i;
  
  arr = value_make_array();
  for (i = 0; i < argc; i++) {
    value_add_to_array(arr, argv[i]);
  }
  return arr;
}

/*
 * Quicksort
 *
 * This function sorts a numerically indexed array based on the
 * contained values.
 */
value *array_sort(arena_state *s, unsigned int argc, value **argv)
{
  qsort(argv[0]->value_u.array_val.value, argv[0]->value_u.array_val.len,
        sizeof(value *), compar);
  return value_copy(argv[0]);
}

/*
 * Check if sorted
 *
 * This function returns true if the argument array is sorted.
 */
value *array_is_sorted(arena_state *s, unsigned int argc, value **argv)
{
  value **next = argv[0]->value_u.array_val.value;
  int max = argv[0]->value_u.array_val.len;
  int i, res;
  
  for (i = 0; i < max - 1; i++) {
    res = compar(next, next+1);
    if (res > 0) {
      return value_make_bool(0);
    }
    next++;
  }
  return value_make_bool(1);
}

/*
 * Delete value from array
 *
 * This function removes the value at the given index from the
 * array and returns the resulting array.
 */
value *array_unset(arena_state *s, unsigned int argc, value **argv)
{
  value_delete_array(argv[0], argv[1]->value_u.int_val);
  return value_copy(argv[0]);
}

/*
 * Compact array
 *
 * Removes all void values from the given array and returns an
 * array of the remaining values.
 */
value *array_compact(arena_state *s, unsigned int argc, value **argv)
{
  value *arr = argv[0];
  value *copy;
  int i;
  
  copy = value_make_array();
  for (i = 0; i < arr->value_u.array_val.len; i++) {
    if (arr->value_u.array_val.value[i] &&
        arr->value_u.array_val.value[i]->type != VALUE_TYPE_VOID) {
      value_add_to_array(copy, arr->value_u.array_val.value[i]);
    }
  }
  return copy;
}

/*
 * Search for element
 *
 * Returns the index of the element in the array, or void if the element
 * is not found.
 */
value *array_search(arena_state *s, unsigned int argc, value **argv)
{
  value *cmp;
  int i, cmpval;
  
  for (i = 0; i < argv[0]->value_u.array_val.len; i++) {
    cmp = eval_order_equal(argv[0]->value_u.array_val.value[i], argv[1]);
    cmpval = cmp->value_u.bool_val;
    value_free(cmp);
    if (cmpval) {
      return value_make_int(i);
    }
  }
  return value_make_void();
}

/*
 * Merge multiple arrays
 *
 * Returns a new array with the values from all input arrays.
 */
value *array_merge(arena_state *s, unsigned int argc, value **argv)
{
  unsigned int i;
  int j;
  value *arr;
  
  arr = value_make_array();
  
  for (i = 0; i < argc; i++) {
    value_cast_inplace(s, &argv[i], VALUE_TYPE_ARRAY);
    for (j = 0; j < argv[i]->value_u.array_val.len; j++) {
      value_add_to_array(arr, argv[i]->value_u.array_val.value[j]);
    }
  }
  return arr;
}

/*
 * Reverse array
 *
 * Reverses the order of the elements in the given array and returns
 * the reversed array.
 */
value *array_reverse(arena_state *s, unsigned int argc, value **argv)
{
  int i;
  int len = argv[0]->value_u.array_val.len;
  value *arr;
  
  arr = value_make_array();
  for (i = 0; i < len; i++) {
    value_add_to_array(arr, argv[0]->value_u.array_val.value[len - i - 1]);
  }
  return arr;
}
