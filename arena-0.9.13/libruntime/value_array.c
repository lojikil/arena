/*
 * Array functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "runtime.h"

/*
 * Append value to end of array
 *
 * This function appends a copy of the given value to the
 * end of the array.
 */
void value_add_to_array(value *arr, value *val)
{
  value_array *av;
  value **elems;

  sanity(arr && val && arr->type == VALUE_TYPE_ARRAY);

  av = &arr->value_u.array_val;

  if (av->size <= av->len) {
    av->size += ARRAY_GROWTH;
    elems = oom(realloc(av->value, (av->size + 1) * sizeof(value *)));
    av->value = elems;
  }
  av->value[av->len++] = value_copy(val);
  
  /*
   * Maintain a NULL sentinel at the end of the pointer array.
   * This makes iteration over the array entries easy.
   */
  av->value[av->len] = NULL;
}

/*
 * Set value at specific array index
 *
 * This function puts a copy of the given value at a specified
 * index in the array. If the index is higher then the current
 * maximum index, the missing indices are filled in with void
 * values.
 */
void value_set_array(value *arr, int pos, value *val)
{
  value *copy;
  value **elems;
  
  sanity(arr && val && arr->type == VALUE_TYPE_ARRAY);

  if (pos < 0) {
    pos = arr->value_u.array_val.len + pos;
  }
  if (pos < 0) {
    pos = 0;
  }

  if (pos > arr->value_u.array_val.len) {  
    value *fill = value_make_void();
    while (pos > arr->value_u.array_val.len) {
      value_add_to_array(arr, fill);
    }
    value_free(fill);
  }

  if (pos == arr->value_u.array_val.len) {
    value_add_to_array(arr, val);
  } else {
    copy = value_copy(val);

    elems = arr->value_u.array_val.value;
    elems += pos;
    value_free(*elems);
    *elems = copy;
  }
}

/*
 * Get value from specific array index
 *
 * This functions returns a copy of the value stored at
 * a specific array index. Returns a void value if the
 * index is out of bounds for the array.
 */
value *value_get_array(value *arr, int pos)
{
  value **elems;
  
  sanity(arr && arr->type == VALUE_TYPE_ARRAY);
  
  if (pos < 0) {
    pos = arr->value_u.array_val.len + pos;
  }
  
  if (pos < 0 || pos > arr->value_u.array_val.len - 1) {
    return value_make_void();
  }

  elems = arr->value_u.array_val.value;
  elems += pos;
  return value_copy(*elems);
}

/*
 * Delete element from array
 *
 * This function removes the array element at the given index.
 * The element is freed and replaced by a void value.
 */
void value_delete_array(value *arr, int pos)
{
  value **elems;
  
  sanity(arr && arr->type == VALUE_TYPE_ARRAY);

  if (pos < 0) {
    pos = arr->value_u.array_val.len + pos;
  }

  if (pos < 0 || pos >= arr->value_u.array_val.len) {
    return;
  }

  elems = arr->value_u.array_val.value;
  elems += pos;
  value_free(*elems);
  *elems = value_make_void();
}
