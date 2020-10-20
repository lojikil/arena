/*
 * Symbol table stack
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "runtime.h"

/*
 * Tear down symbol table stack
 *
 * Deallocates all memory used by the symbol table stack.
 */
void symtab_stack_teardown(arena_state *s)
{
  sanity(s->global_table);
  
  while (s->local_depth > 0) {
    symtab_stack_leave(s);
  }

  free(s->local_tables);
  s->local_tables = NULL;
  
  symtab_free(s->global_table);
  s->global_table = NULL;
}

/*
 * Initialize symbol table stack
 *
 * This function allocates memory for the global symbol table
 * and resets the local symbol table stack to depth 0.
 */
void symtab_stack_init(arena_state *s)
{
  if (!s->global_table) {
    s->global_table = oom(symtab_alloc(0));

    s->local_depth = 0;
    s->local_tables = NULL;
  }
}

/*
 * Enter local symbol table
 *
 * This function adds a new local symbol table to the stack. The
 * new symbol table obscures the previous toplevel local table.
 */
void symtab_stack_enter(arena_state *s)
{
  symtab **local;
  symtab *newtab;
 
  newtab = symtab_alloc(7);
 
  local = oom(realloc(s->local_tables,
    (s->local_depth + 1) * sizeof(symtab *)));

  s->local_tables = local;
  local[s->local_depth] = newtab;
  ++s->local_depth;
}

/*
 * Leave local symbol table
 *
 * This function removes and frees the topmost local symbol table.
 * The previous local symbol table becomes visible again.
 */
void symtab_stack_leave(arena_state *s)
{
  symtab **local = s->local_tables;

  if (s->local_depth == 0) {
    return;
  }
  --s->local_depth;
  symtab_free(local[s->local_depth]);
}

/*
 * Pop symbol table stack
 *
 * This function returns the topmost local symbol table and makes
 * the previous local symbol table visible again.
 */
symtab *symtab_stack_pop(arena_state *s)
{
  symtab **local = s->local_tables;

  sanity(s->local_depth > 0);
  
  --s->local_depth;
  return local[s->local_depth];
}

/*
 * Get stack depth
 *
 * This function returns the current depth of the local symbol
 * table stack. It returns 0 if there are no local symbol tables
 * at the moment.
 */
unsigned int symtab_stack_depth(arena_state *s)
{
  return s->local_depth;
}

/*
 * Add symbol table entry to stack
 *
 * This functions adds the given entry to the topmost symbol
 * table of the stack. This means the global table if no
 * local symbol table exists.
 */
void symtab_stack_add(arena_state *s, symtab_entry *entry)
{
  symtab **local = s->local_tables;

  sanity(entry);

  if (s->local_depth > 0) {
    symtab_add(local[s->local_depth-1], entry);
  } else {
    symtab_add(s->global_table, entry);
  }
}

/*
 * Put symbol table entry into global table
 *
 * This function adds the given entry to the global symbol
 * table, no matter whether a current local table exists.
 */
void symtab_stack_add_global(arena_state *s, const char *name, value *val)
{
  sanity(name && val);
  symtab_add_variable(s->global_table, name, val);
}

/*
 * Add variable entry to stack
 *
 * This functions adds the given variable to the topmost symbol
 * table of the stack. This means the global table if no local
 * symbol table exists.
 */
void symtab_stack_add_variable(arena_state *s, const char *name, value *val)
{
  symtab **local = s->local_tables;

  sanity(name && val);

  if (s->local_depth > 0) {
    symtab_add_variable(local[s->local_depth-1], name, val);
  } else {
    symtab_add_variable(s->global_table, name, val);
  }
}

/*
 * Add function entry to stack
 *
 * This function adds the given function to the topmost symbol
 * table of the stack. This means the global table if no local
 * symbol table exists.
 */
void symtab_stack_add_function(arena_state *s, const char *name,
  const signature *sig)
{
  symtab **local = s->local_tables;

  sanity(name && sig);

  if (s->local_depth > 0) {
    symtab_add_function(local[s->local_depth-1], name, sig);
  } else {
    symtab_add_function(s->global_table, name, sig);
  }
}

/*
 * Add template entry to stack
 *
 * This function adds the given template to the topmost symbol table
 * of the stack. This means the global table if no local symbol
 * table exists.
 */
void symtab_stack_add_template(arena_state *s, const char *name,
  const char *parent, void *def)
{
  symtab **local = s->local_tables;

  sanity(name && def);

  if (s->local_depth > 0) {
    symtab_add_template(local[s->local_depth-1], name, parent, def);
  } else {
    symtab_add_template(s->global_table, name, parent, def);
  }
}

/*
 * Lookup symbol in stack
 *
 * This function looks for the given symbol name in the topmost
 * local symbol table. If the symbol is not found there, it is
 * also searched for in the global table.
 */
symtab_entry *symtab_stack_lookup(arena_state *s, const char *symbol)
{
  symtab **local = s->local_tables;
  symtab_entry *entry = NULL;

  if (s->local_depth > 0) {
    entry = symtab_lookup(local[s->local_depth-1], symbol);
  }
  if (!entry) {
    entry = symtab_lookup(s->global_table, symbol);
  }
  return entry;
}

/*
 * Check locality
 *
 * This function returns 1 if the given symbol name would be
 * resolved from a local symbol table. If the global table is
 * active at the moment, the answer is always "yes".
 */
int symtab_stack_local(arena_state *s, const char *symbol)
{
  symtab **local = s->local_tables;
  symtab_entry *entry;
  
  if (s->local_depth > 0) {
    entry = symtab_lookup(local[s->local_depth-1], symbol);
    return (entry != NULL);
  }
  return 1;
}

/*
 * Delete symbol from stack
 *
 * This function deletes the given symbol name from the topmost
 * symbol table in the stack. This means the global table if no
 * local symbol table exists.
 */
void symtab_stack_delete(arena_state *s, const char *symbol)
{
  symtab **local = s->local_tables;

  if (s->local_depth > 0) {
    symtab_delete(local[s->local_depth-1], symbol);
  } else {
    symtab_delete(s->global_table, symbol);
  }
}
