/*
 * Assignment evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "eval.h"

/*
 * Evaluate variable assignment
 */
value *eval_assign(arena_state *s, expr *ex)
{
  value *val;
  
  sanity(ex && ex->name);
  
  val = eval_expr(s, ex->inner);

  if (!s->except_flag && !s->exit_flag) {
    if (val->type != VALUE_TYPE_FN) {
      symtab_stack_add_variable(s, ex->name, val);
    } else {
      symtab_stack_add_function(s, ex->name, val->value_u.fn_val);
    }
  }
  return val;
}

/*
 * Set value in nested array
 */
value *array_set(arena_state *s, value *arr, int argc, expr **index,
  value *val)
{
  value *pos, *elem;
  int realpos = 0, is_struct, is_inner_struct;
  char *realidx = NULL;
  
  sanity(arr && index && *index && val);
  
  is_struct = (index[0]->type == EXPR_FIELD);
  is_inner_struct = (argc > 1 && index[1]->type == EXPR_FIELD);
  
  pos = eval_expr(s, index[0]);

  if (s->except_flag || s->exit_flag) {
    value_free(pos);
    return value_make_void();
  }
  
  if (is_struct) {
    realidx = pos->value_u.string_val.value;
  } else {
    value_cast_inplace(s, &pos, VALUE_TYPE_INT);
    realpos = pos->value_u.int_val;
    value_free(pos);
  }

  if (argc > 1) {
    if (is_struct) {
      elem = value_get_struct(arr, realidx);
    } else {
      elem = value_get_array(arr, realpos);
    }
    if (is_inner_struct) {
      if (elem->type != VALUE_TYPE_STRUCT) {
        value_free(elem);
        elem = value_make_struct();
      }
    } else {
      if (elem->type != VALUE_TYPE_ARRAY) {
        value_free(elem);
        elem = value_make_array();
      }
    }
    elem = array_set(s, elem, argc - 1, index + 1, val);
    if (is_struct) {
      value_set_struct(arr, realidx, elem);
      value_free(pos);
    } else {
      value_set_array(arr, realpos, elem);
    }
    value_free(elem);
    return arr;
  } else {
    if (is_struct) {
      value_set_struct(arr, realidx, val);
      value_free(pos);
    } else {
      value_set_array(arr, realpos, val);
    }
    return arr;
  }
}

/**
 * Direct array assignment
 *
 * This function can be used by other evaluation functions to
 * make updates to array elements.
 */
void eval_assign_array_direct(arena_state *s, const char *name,
  int argc, expr **index, value *val)
{
  symtab_entry *entry;
  value *arr = NULL;
  int is_struct;
  
  sanity(name && index && *index && val);
  
  is_struct = (index[0]->type == EXPR_FIELD);
  
  entry = symtab_stack_lookup(s, name);
  if (!entry || entry->type != SYMTAB_ENTRY_VAR) {
    if (is_struct) {
      arr = value_make_struct();
    } else {
      arr = value_make_array();
    }
  } else {
    if (is_struct) {
      if (entry->entry_u.var->type == VALUE_TYPE_STRUCT) {
        arr = value_copy(entry->entry_u.var);
      } else {
        arr = value_make_struct();
      }
    } else {
      if (entry->entry_u.var->type == VALUE_TYPE_ARRAY) {
        arr = value_copy(entry->entry_u.var);
      } else {
        arr = value_make_array();
      }
    }
  }

  arr = array_set(s, arr, argc, index, val);
  if (!s->except_flag && !s->exit_flag) {
    symtab_stack_add_variable(s, name, arr);
  }
  value_free(arr);
}

/*
 * Evaluate array assignment
 */
value *eval_assign_array(arena_state *s, expr *ex)
{
  value *val;

  sanity(ex && ex->name && ex->argc > 0 && ex->argv[0]);
  
  val = eval_expr(s, ex->inner);
  if (!s->except_flag && !s->exit_flag) {
    eval_assign_array_direct(s, ex->name, ex->argc, ex->argv, val);
  }
  return val;
}
