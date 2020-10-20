/*
 * Tests for symbol tables
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../libruntime/runtime.h"

/*
 * Create string containing index
 */
char *index_string(unsigned int i)
{
  char buf[25];
  char *res;

  buf[24] = 0;
  sprintf(buf, "index_%u", i);
  
  res = malloc(25);
  strcpy(res, buf);
  return res;
}

void symtab_test(void)
{
  arena_state *s = state_alloc();

  value *val, *var;
  symtab_entry *entry, *found;
  symtab_node *node;
  symtab *symtab;
  char *symbol;
  int i, buf;
  unsigned int depth;

  val = value_make_void();
  var = value_make_int(42);
  
  test_banner("libruntime");
  test_section("symtab allocators");

  /*
   * Memory management
   */
  test_start("symtab_entry_alloc");
  entry = symtab_entry_alloc();
  test_assert(entry != NULL);
  
  test_start("symtab_entry_free");
  symtab_entry_free(entry);
  test_assert(1);
  
  test_start("symtab_node_alloc");
  node = symtab_node_alloc();
  test_assert(node != NULL && node->count == 0 && node->entries == NULL);
  
  test_start("symtab_node_free");
  symtab_node_free(node);
  test_assert(1);
  
  test_start("symtab_alloc");
  symtab = symtab_alloc(0);
  test_assert(symtab != NULL && symtab->order == 11 && symtab->nodes != NULL);

  test_start("symtab_free");
  symtab_free(symtab);
  test_assert(1);

  test_section("symtab primitives");
  
  symtab = symtab_alloc(0);

  /*
   * Entry manipulation
   */
  test_start("symtab_add_variable");
  symtab_add_variable(symtab, "foobar", var);
  test_assert(1);
  
  test_start("symtab_lookup");
  entry = symtab_lookup(symtab, "foobar");
  test_assert(entry != NULL && entry->type == SYMTAB_ENTRY_VAR &&
              entry->entry_u.var != NULL &&
              entry->entry_u.var->type == VALUE_TYPE_INT &&
              entry->entry_u.var->value_u.int_val == 42);
              
  test_start("symtab_delete");
  symtab_delete(symtab, "foobar");
  test_assert(1);
  
  test_start("symtab_lookup (no match)");
  entry = symtab_lookup(symtab, "foobar");
  test_assert(entry == NULL);
   
  test_start("symtab_add (21000 entries)");
  buf = 0;
  for (i = 0; i < 21000; i++) {
    entry = symtab_entry_alloc();
    entry->type = SYMTAB_ENTRY_VAR;
    entry->symbol = index_string(i);
    entry->entry_u.var = value_copy(val);
  
    symtab_add(symtab, entry);
  }
  test_assert(buf == 0);
  
  test_start("symtab_lookup (21000 entries)");
  buf = 0;
  for (i = 0; i < 21000; i++) {
    symbol = index_string(i);
    entry = symtab_lookup(symtab, symbol);
    if (!entry || !entry->symbol || entry->type != SYMTAB_ENTRY_VAR ||
        strcmp(entry->symbol, symbol) != 0) buf++;
    free(symbol);
  }
  test_assert(buf == 0);

  /* deletes all the even-numbered entries */
  test_start("symtab_delete (10500 entries)");
  for (i = 0; i < 21000; i += 2) {
    symbol = index_string(i);
    symtab_delete(symtab, symbol);
    free(symbol);
  }
  test_assert(1);

  /* checks whether the above delete loop killed the right entries */
  test_start("symtab_lookup (21000 entries)");
  buf = 0;
  for (i = 0; i < 21000; i++) {
    symbol = index_string(i);
    entry = symtab_lookup(symtab, symbol);
    if (i % 2 == 0 && entry != NULL) buf++;
    if (i % 2 == 1 && (!entry || !entry->symbol ||
        entry->type != SYMTAB_ENTRY_VAR ||
        strcmp(entry->symbol, symbol) != 0)) buf++;
    free(symbol);
  }
  test_assert(buf == 0);

  test_start("symtab_free (10500 entries)");
  symtab_free(symtab);
  test_assert(1);
  
  /*
   * symbol table stack
   */
  test_section("symtab stack");

  entry = symtab_entry_alloc();
  entry->type = SYMTAB_ENTRY_VAR;
  entry->symbol = malloc(7);
  strcpy(entry->symbol, "foobar");
  entry->entry_u.var = value_copy(val);
  
  test_start("symtab_stack_init");
  symtab_stack_init(s);
  test_assert(1);
  
  test_start("symtab_stack_depth");
  depth = symtab_stack_depth(s);
  test_assert(depth == 0);

  /* following calls operate on global symtab */
  
  test_start("symtab_stack_add");
  symtab_stack_add(s, entry);
  test_assert(1);
  
  test_start("symtab_stack_lookup");
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found != NULL);

  test_start("symtab_stack_delete");
  symtab_stack_delete(s, "foobar");
  test_assert(1);
  
  test_start("symtab_stack_lookup (no match)");
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found == NULL);
  
  entry = symtab_entry_alloc();
  entry->type = SYMTAB_ENTRY_VAR;
  entry->symbol = malloc(7);
  strcpy(entry->symbol, "foobar");
  entry->entry_u.var = value_copy(val);
  symtab_stack_add(s, entry);

  /* increase depth of symtab stack */
  
  test_start("symtab_stack_enter (local)");
  symtab_stack_enter(s);
  test_assert(symtab_stack_depth(s) == 1);

  test_start("symtab_stack_add_variable (local)");
  symtab_stack_add_variable(s, "barfoo", var);
  test_assert(1);

  test_start("symtab_stack_lookup (local)");
  found = symtab_stack_lookup(s, "barfoo");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_INT &&
              found->entry_u.var->value_u.int_val == 42);

  test_start("symtab_stack_local (local)");
  test_assert(symtab_stack_local(s, "barfoo"));
              
  /* symbols from the global table must still be visible */
  test_start("symtab_stack_lookup (fall through)");
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_VOID);

  test_start("symtab_stack_local (global)");
  test_assert(!symtab_stack_local(s, "foobar"));

  /* local symbol with same name as global symbol hides global symbol */
  test_start("symtab_stack_lookup (obscured)");
  symtab_stack_add_variable(s, "foobar", var);
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_INT &&
              found->entry_u.var->value_u.int_val == 42);

  test_start("symtab_stack_local (obscured)");
  test_assert(symtab_stack_local(s, "foobar"));
          
  /* delete local symbol that hides global symbol */
  test_start("symtab_stack_delete (local)");
  symtab_stack_delete(s, "foobar");
  test_assert(1);

  /* global symbol must be visible again */
  test_start("symtab_stack_lookup (unobscured)");
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_VOID);

  /* cannot delete global symbol while inside local symtab */
  test_start("symtab_stack_delete (global from local)");
  symtab_stack_delete(s, "foobar");
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_VOID);

  /* hide global variable again */
  test_start("symtab_stack_add_variable (again)");
  symtab_stack_add_variable(s, "foobar", var);
  test_assert(1);

  /* increase stacking depth again */
              
  test_start("symtab_stack_enter (local 2)");
  symtab_stack_enter(s);
  test_assert(symtab_stack_depth(s) == 2);

  /* global variable hidden in depth 1 is not hidden in depth 2 */
  test_start("symtab_stack_lookup (fall through 2)");
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_VOID);
              
  test_start("symtab_stack_add_variable (local 2)");
  symtab_stack_add_variable(s, "something", val);
  test_assert(1);
  
  test_start("symtab_stack_lookup (local 2)");
  found = symtab_stack_lookup(s, "something");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_VOID);
              
  /* decrease stacking depth */

  test_start("symtab_stack_leave (to local)");
  symtab_stack_leave(s);
  test_assert(symtab_stack_depth(s) == 1);

  /* check that symbol from depth 2 is no longer there */
  test_start("symtab_stack_lookup (leftover)");
  found = symtab_stack_lookup(s, "something");
  test_assert(found == NULL);

  /* check that symbol from this depth is still there */
  test_start("symtab_stack_lookup (local again)");
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_INT &&
              found->entry_u.var->value_u.int_val == 42);

  /* decrease stacking level back to 0 */
              
  test_start("symtab_stack_leave (to global)");
  symtab_stack_leave(s);
  test_assert(symtab_stack_depth(s) == 0);

  /* hidden global symbol should be visible again */
  test_start("symtab_stack_lookup (global again)");
  found = symtab_stack_lookup(s, "foobar");
  test_assert(found != NULL && found->type == SYMTAB_ENTRY_VAR &&
              found->entry_u.var != NULL &&
              found->entry_u.var->type == VALUE_TYPE_VOID);

  /* leave at top level has no effect */
  test_start("symtab_stack_leave");
  symtab_stack_leave(s);
  test_assert(symtab_stack_depth(s) == 0);
  
  symtab_stack_teardown(s);
  state_free(s);
}
