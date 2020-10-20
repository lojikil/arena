/*
 * Struct functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
 
#include "stdlib.h"

/*
 * Create struct from parameter values
 */
value *struct_mkstruct(arena_state *s, unsigned int argc, value **argv)
{
  value *st, *elem;
  unsigned int i = 0;
  
  st = value_make_struct();
  while (i < argc) {
    value_cast_inplace(s, &argv[i], VALUE_TYPE_STRING);
    if (argv[i]->value_u.string_val.len > 0) {
      if (i + 1 < argc) {
        value_set_struct(st, argv[i]->value_u.string_val.value, argv[i+1]);
      } else {
        elem = value_make_void();
        value_set_struct(st, argv[i]->value_u.string_val.value, elem);
        value_free(elem);
      }
    }
    i += 2;
  }
  return st;
}

/*
 * Delete value from struct
 *
 * This function the field with the given name from the struct
 * and returns the resulting struct.
 */
value *struct_unset(arena_state *s, unsigned int argc, value **argv)
{
  char *field = argv[1]->value_u.string_val.value;

  if (field) {
    value_delete_struct(argv[0], field);
  }
  return value_copy(argv[0]);
}

/*
 * Get field from struct
 */
value *struct_get(arena_state *s, unsigned int argc, value **argv)
{
  char *field = argv[1]->value_u.string_val.value;
  
  if (!field) {
    return value_make_void();
  }
  return value_get_struct(argv[0], field);
}

/*
 * Set field in struct
 */
value *struct_set(arena_state *s, unsigned int argc, value **argv)
{
  char *field = argv[1]->value_u.string_val.value;
  
  if (field) {
    value_set_struct(argv[0], field, argv[2]);
  }
  return value_copy(argv[0]);
}

/*
 * Get names of structure elements of some type
 */
static value *getelements(value *val, unsigned int wanted)
{
  symtab *sym = val->value_u.struct_val;
  symtab_node *node;
  symtab_entry *entry;
  value *name, *arr;
  unsigned int i, j;
  
  arr = value_make_array();
  
  for (i = 0; i < (unsigned int) (1 << sym->order); i++) {
    node = sym->nodes[i];
    if (node) {
      for (j = 0; j < node->count; j++) {
        entry = node->entries[j];
        if (entry && entry->type == wanted) {
          name = value_make_string(entry->symbol);
          value_add_to_array(arr, name);
          value_free(name);
        }
      }
    }
  }
  return arr;
}

/*
 * Get structure fields
 *
 * Returns an array of strings containing the field names of the
 * given structure.
 */
value *struct_fields(arena_state *s, unsigned int argc, value **argv)
{
  return getelements(argv[0], SYMTAB_ENTRY_VAR);
}

/*
 * Get structure methods
 *
 * Returns an array of strings containing the method names of the
 * given structure.
 */
value *struct_methods(arena_state *s, unsigned int argc, value **argv)
{
  return getelements(argv[0], SYMTAB_ENTRY_FUNCTION);
}

/*
 * Check for element with specific type
 */
static value *checkelement(value *hay, value *needle, unsigned int wanted)
{
  symtab *sym = hay->value_u.struct_val;
  char *field = needle->value_u.string_val.value;
  symtab_entry *entry;
  
  if (!field) {
    return value_make_bool(0);
  }
  entry = symtab_lookup(sym, field);
  return value_make_bool(entry && entry->type == wanted);
}

/*
 * Check field existence
 *
 * Returns true if the given field name exists in the given struct.
 */
value *struct_is_field(arena_state *s, unsigned int argc, value **argv)
{
  return checkelement(argv[0], argv[1], SYMTAB_ENTRY_VAR);
}

/*
 * Check method existence
 *
 * Returns true if the given method name exists in the given struct.
 */
value *struct_is_method(arena_state *s, unsigned int argc, value **argv)
{
  return checkelement(argv[0], argv[1], SYMTAB_ENTRY_FUNCTION);
}

/*
 * Merge multiple structs
 *
 * Returns a structure with all fields from the input structures. If
 * a field occurs multiple times, the value from last structure wins.
 */
value *struct_merge(arena_state *s, unsigned int argc, value **argv)
{
  symtab *sym;
  symtab_node *node;
  symtab_entry *entry;
  unsigned int i, si, sj;
  value *st;
  
  st = value_make_struct();
  
  for (i = 0; i < argc; i++) {
    value_cast_inplace(s, &argv[i], VALUE_TYPE_STRUCT);
    sym = argv[i]->value_u.struct_val;
    for (si = 0; si < (unsigned int) (1 << sym->order); si++) {
      node = sym->nodes[si];
      if (node) {
        for (sj = 0; sj < node->count; sj++) {
          entry = node->entries[sj];
          if (entry && entry->type == SYMTAB_ENTRY_VAR) {
            value_set_struct(st, entry->symbol, entry->entry_u.var);
          }
          if (entry && entry->type == SYMTAB_ENTRY_FUNCTION) {
            symtab_add_function(st->value_u.struct_val, entry->symbol,
              entry->entry_u.sig);
          }
        }
      }
    }
  }
  return st;
}
