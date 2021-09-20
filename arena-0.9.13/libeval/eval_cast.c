/*
 * Cast evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "eval.h"

/*
 * Map type name to type enum
 */
static value_type typeval(const char *typespec)
{
  sanity(typespec);

  if (strcmp(typespec, "void") == 0) {
    return VALUE_TYPE_VOID;
  } else if (strcmp(typespec, "bool") == 0) {
    return VALUE_TYPE_BOOL;
  } else if (strcmp(typespec, "int") == 0) {
    return VALUE_TYPE_INT;
  } else if (strcmp(typespec, "float") == 0) {
    return VALUE_TYPE_FLOAT;
  } else if (strcmp(typespec, "string") == 0) {
    return VALUE_TYPE_STRING;
  } else if (strcmp(typespec, "array") == 0) {
    return VALUE_TYPE_ARRAY;
  } else if (strcmp(typespec, "struct") == 0) {
    return VALUE_TYPE_STRUCT;
  }
  return VALUE_TYPE_VOID;
}

/*
 * Evaluate cast
 */
value *eval_cast(arena_state *s, expr *ex)
{
  value *val;
  
  sanity(ex);
  
  val = eval_expr(s, ex->inner);
  value_cast_inplace(s, &val, typeval(ex->name));
  return val;
}
