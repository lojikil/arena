/*
 * Dictionary functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "stdlib.h"

/*
 * Callback for freeing a dictionary
 */
static void dict_free(void *data)
{
  symtab_free(data);
}

/*
 * Create a new dictionary
 *
 * Creates a new dictionary of the given order, where order n
 * means the dictionary will use 2**n hash buckets.
 */
value *dict_open(arena_state *st, unsigned int argc, value **argv)
{
  int order = argv[0]->value_u.int_val;
  
  if (order < 1) {
    return value_make_void();
  }
  
  return value_make_resource(symtab_alloc(order), dict_free);
}

/*
 * Check whether resource is dictionary resource
 */
value *dict_is_resource(arena_state *s, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  
  return value_make_bool(type == dict_free);
}

/*
 * Read dictionary entry
 *
 * Returns the value stored in the dictionary under the given
 * name, or void if the name is not contained in the dictionary.
 */
value *dict_read(arena_state *st, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  symtab *s  = argv[0]->value_u.res_val->data;
  const char *name = argv[1]->value_u.string_val.value; 
  symtab_entry *entry;
  
  if (type != dict_free || !s || !value_str_compat(argv[1])) {
    return value_make_void();
  }
  entry = symtab_lookup(s, name);
  if (!entry) {
    return value_make_void();
  }
  return value_copy(entry->entry_u.var);
}

/*
 * Write dictionary entry
 *
 * Stores a value in the dictionary under the given name. If the
 * name was used before, the old entry is removed first. Returns
 * true on success, false on failure.
 */
value *dict_write(arena_state *st, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  symtab *s  = argv[0]->value_u.res_val->data;
  const char *name = argv[1]->value_u.string_val.value;
  value *val = argv[2];
  
  if (type != dict_free || !s || !value_str_compat(argv[1])) {
    return value_make_bool(0);
  }
  
  symtab_add_variable(s, name, val);
  return value_make_bool(1);
}

/*
 * Remove name from dictionary
 *
 * Returns true on success and false on failure.
 */
value *dict_remove(arena_state *st, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  symtab *s  = argv[0]->value_u.res_val->data;
  const char *name = argv[1]->value_u.string_val.value;
  
  if (type != dict_free || !s || !value_str_compat(argv[1])) {
    return value_make_bool(0);
  }
  
  symtab_delete(s, name);
  return value_make_bool(1);
}

/*
 * Check dictionary entry
 *
 * Returns true if the given name exists in the dictionary.
 */
value *dict_exists(arena_state *st, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  symtab *s  = argv[0]->value_u.res_val->data;
  const char *name = argv[1]->value_u.string_val.value;
  symtab_entry *entry;
  
  if (type != dict_free || !s || !value_str_compat(argv[1])) {
    return value_make_bool(0);
  }
  entry = symtab_lookup(s, name);
  return value_make_bool(entry != NULL);
}

/*
 * Close dictionary
 *
 * This function closes a dictionary, which means all entries
 * will be removed and the space used by the dictionary freed.
 */
value *dict_close(arena_state *st, unsigned int argc, value **argv)
{
  void *type = argv[0]->value_u.res_val->release;
  symtab *s  = argv[0]->value_u.res_val->data;
  
  if (type == dict_free && s) {
    symtab_free(s);
    argv[0]->value_u.res_val->data = NULL;
  }
  return value_make_void();
}
