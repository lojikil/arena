/*
 * Variable reference evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
 
#include "eval.h"

/*
 * Evaluate variable reference
 */
value *eval_ref(arena_state *s, expr *ex)
{
  symtab_entry *entry;
  
  sanity(ex && ex->name);
  
  entry = symtab_stack_lookup(s, ex->name);
  if (!entry || entry->type == SYMTAB_ENTRY_TMPL) {
    return value_make_void();
  }
  if (entry->type == SYMTAB_ENTRY_VAR) {
    return value_copy(entry->entry_u.var);
  } else {
    return value_make_fn(entry->entry_u.sig);
  }
}

/*
 * Get element from numerical array
 */
static value *array_get(arena_state *s, value *arr, int argc, expr **index)
{
  value *pos, *val, *res;
  int realpos = 0, is_struct;
  char *realidx = NULL;

  is_struct = (index[0]->type == EXPR_FIELD);
  
  if (!arr || (!is_struct && arr->type != VALUE_TYPE_ARRAY) ||
      (is_struct && arr->type != VALUE_TYPE_STRUCT)) {
    return value_make_void();
  }
  
  pos = eval_expr(s, index[0]);
  if (is_struct) {
    realidx = pos->value_u.string_val.value;
  } else {
    value_cast_inplace(s, &pos, VALUE_TYPE_INT);
    realpos = pos->value_u.int_val;
  }
  
  if (is_struct) {
    val = value_get_struct(arr, realidx);
  } else {
    val = value_get_array(arr, realpos);
  }
  value_free(pos);
  
  if (argc == 1) {
    return val;
  } else {
    res = array_get(s, val, argc - 1, index + 1);
    value_free(val);
    return res;
  }
}

/*
 * Evaluate array variable reference
 */
value *eval_ref_array(arena_state *s, expr *ex)
{
  value *res = NULL;
  symtab_entry *entry;
  
  sanity(ex && ex->name);

  entry = symtab_stack_lookup(s, ex->name);
  if (!entry || entry->type != SYMTAB_ENTRY_VAR) {
    return value_make_void();
  }
  res = array_get(s, entry->entry_u.var, ex->argc, ex->argv);
  return res;
}

/*
 * Evaluate index reference
 */
value *eval_ref_index(arena_state *s, expr *ex)
{
  value *val, *res;
  
  sanity(ex && ex->inner);
  
  val = eval_expr(s, ex->inner);
  res = array_get(s, val, ex->argc, ex->argv);
  
  value_free(val);
  return res;
}
