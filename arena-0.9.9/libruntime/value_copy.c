/*
 * Value copy functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "runtime.h"

/*
 * Copy array value
 *
 * This functions returns a full recursive copy of the
 * given input array.
 */
static value *copy_array(value *val)
{
  int size  = val->value_u.array_val.size;
  value **a = val->value_u.array_val.value;
  value **b, *copy;
  
  copy  = value_alloc(VALUE_TYPE_ARRAY);
  *copy = *val;

  if (a) {
    copy->value_u.array_val.value = oom(malloc((size + 1) * sizeof(value *)));
    b = copy->value_u.array_val.value;
    while (*a) {
      *b++ = value_copy(*a++);
    }
    *b = NULL;
  }
  return copy;
}

/*
 * String duplication
 */
static char *xstrdup(char *orig)
{
  char *copy;
  
  copy = oom(malloc(strlen(orig) + 1));
  strcpy(copy, orig);
  return copy;
}

/*
 * Symtab entry duplication
 */
static symtab_entry *entrydup(symtab_entry *orig)
{
  symtab_entry *copy = NULL;
  
  if (!orig || orig->type == SYMTAB_ENTRY_TMPL) {
    return NULL;
  }
  
  copy = symtab_entry_alloc();
  copy->symbol = xstrdup(orig->symbol);
  copy->type   = orig->type;
  
  switch (orig->type) {
    case SYMTAB_ENTRY_VAR:
      copy->entry_u.var = value_copy(orig->entry_u.var);
      break;
    case SYMTAB_ENTRY_FUNCTION:
      copy->entry_u.sig = call_sig_copy(orig->entry_u.sig);
      break;
    case SYMTAB_ENTRY_TMPL:
      /* handled above switch */
      break;
  }
  
  return copy;
}

/*
 * Copy struct value
 *
 * This functions returns a full recursive copy of the
 * given input struct.
 */
static value *copy_struct(value *val)
{
  symtab *nsym, *sym = val->value_u.struct_val;
  symtab_node *node, *nnode;
  unsigned int i, j;
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_STRUCT);
  nsym = symtab_alloc(sym->order);
  copy->value_u.struct_val = nsym;
  
  for (i = 0; i < (unsigned int) (1 << sym->order); i++) {
    node = sym->nodes[i];
    if (node) {
      nsym->nodes[i] = nnode = symtab_node_alloc();
      nnode->count = node->count;
      nnode->entries =
        oom(calloc(sizeof(symtab_entry *) * node->count, 1));
      for (j = 0; j < node->count; j++) {
        nnode->entries[j] = entrydup(node->entries[j]);
      }
    }
  }
  return copy;
}

/*
 * Copy resource value
 *
 * Increases the reference count of the original resource
 * structure.
 */
value *copy_resource(value *val)
{
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_RES);
  copy->value_u.res_val = val->value_u.res_val;
  ++copy->value_u.res_val->refcount;
  
  return copy;
}

/*
 * Copy value
 *
 * This function makes a recursive copy of the input value.
 */
value *value_copy(value *val)
{
  int len;
  char *str;
  value *copy = NULL;
  
  switch (val->type) {
    case VALUE_TYPE_VOID:
    case VALUE_TYPE_BOOL:
    case VALUE_TYPE_INT:
    case VALUE_TYPE_FLOAT:
      copy  = value_alloc(val->type);
      *copy = *val;
      break;
    case VALUE_TYPE_STRING:
      copy = value_alloc(VALUE_TYPE_STRING);
      len  = val->value_u.string_val.len;
      if (len > 0) {
        str = oom(malloc(len + 1));
        memcpy(str, val->value_u.string_val.value, len);
        str[len] = 0;
      } else {
        str = NULL;
      }
      copy->value_u.string_val.len = len;
      copy->value_u.string_val.value = str;
      break; 
    case VALUE_TYPE_ARRAY:
      copy = copy_array(val);
      break;
    case VALUE_TYPE_STRUCT:
      copy = copy_struct(val);
      break;
    case VALUE_TYPE_FN:
      copy = value_make_fn(val->value_u.fn_val);
      break;
    case VALUE_TYPE_RES:
      copy = copy_resource(val);
      break;
  }
  return copy;
}
