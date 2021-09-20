/*
 * Memory management
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "runtime.h"

/*
 * Allocate new value
 *
 * This function allocates storage for a new value of the
 * given type and returns a pointer to the new value.
 */
value *value_alloc(value_type type)
{
  value *val;

  val = oom(calloc(1, sizeof(value)));
  val->type = type;
  return val;
}

/*
 * Free value
 *
 * This function frees the memory occupied by a value.
 * For an array, all its elements are freed before before
 * the array itself is.
 */
void value_free(value *val)
{
  value **next;
  
  if (!val) {
    return;
  }
  
  switch (val->type) {
    case VALUE_TYPE_VOID:
    case VALUE_TYPE_BOOL:
    case VALUE_TYPE_INT:
    case VALUE_TYPE_FLOAT:
      break;
    case VALUE_TYPE_STRING:
      free(val->value_u.string_val.value);
      break;
    case VALUE_TYPE_ARRAY:
      next = (value **) val->value_u.array_val.value;
      if (next) {
        for (; *next; next++) {
          value_free(*next);
        }
      }
      free(val->value_u.array_val.value);
      break;
    case VALUE_TYPE_STRUCT:
      symtab_free(val->value_u.struct_val);
      break;
    case VALUE_TYPE_FN:
      call_sig_free(val->value_u.fn_val);
      break;
    case VALUE_TYPE_RES:
      --val->value_u.res_val->refcount;
      if (val->value_u.res_val->refcount == 0) {
        if (val->value_u.res_val->release) {
          val->value_u.res_val->release(val->value_u.res_val->data);
        }
        free(val->value_u.res_val);
      }
      break;
  }
  
  free(val);
}
