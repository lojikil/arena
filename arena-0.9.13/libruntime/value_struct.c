/*
 * Structures of values
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "runtime.h"

/*
 * Set struct field
 */
void value_set_struct(value *st, const char *pos, value *val)
{
  symtab *sym;
  
  sanity(st && pos && val);
  sym = st->value_u.struct_val;
  sanity(sym);
  
  if (val->type != VALUE_TYPE_FN) {
    symtab_add_variable(sym, pos, val);
  } else {
    symtab_add_function(sym, pos, val->value_u.fn_val);
  }
}

/*
 * Get struct field
 */
value *value_get_struct(value *st, const char *pos)
{
  symtab *sym;
  symtab_entry *entry;
  
  sanity(st && pos);
  sym = st->value_u.struct_val;
  sanity(sym);
  
  entry = symtab_lookup(sym, pos);
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
 * Delete struct field
 */
void value_delete_struct(value *st, const char *pos)
{
  symtab *sym;
  
  sanity(st && pos);
  sym = st->value_u.struct_val;
  sanity(sym);
  
  symtab_delete(sym, pos);
}
