/*
 * Symbol table memory management
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "runtime.h"

/*
 * Allocate symbol table entry
 */
symtab_entry *symtab_entry_alloc(void)
{
  return oom(calloc(sizeof(symtab_entry), 1));
}

/*
 * Free symbol table entry
 *
 * This function frees a symtab entry and any contained data
 * that needs freeing.
 */
void symtab_entry_free(symtab_entry *entry)
{
  if (!entry) {
    return;
  }
  if (entry->symbol) free(entry->symbol);
  switch (entry->type) {
    case SYMTAB_ENTRY_VAR:
      value_free(entry->entry_u.var);
      break;
    case SYMTAB_ENTRY_FUNCTION:
      call_sig_free(entry->entry_u.sig);
      break;
    case SYMTAB_ENTRY_TMPL:
      if (entry->entry_u.def.parent) free(entry->entry_u.def.parent);
      break;
  }
#if DEBUG == 1
  memset(entry, 0, sizeof(symtab_entry));
#endif
  free(entry);
}

/*
 * Allocate symbol table node
 */
symtab_node *symtab_node_alloc(void)
{
  return oom(calloc(sizeof(symtab_node), 1));
}

/*
 * Free symbol table node
 *
 * This function frees a symbol table node and all contained
 * symbol table entries.
 */
void symtab_node_free(symtab_node *node)
{
  unsigned int i;

  if (!node) {
    return;
  }

  for (i = 0; i < node->count; i++) {
    symtab_entry_free(node->entries[i]);
  }
  free(node->entries);
#if DEBUG == 1
  memset(node, 0, sizeof(symtab_node));
#endif
  free(node);
}

/*
 * Allocate symbol table
 *
 * This function allocates a symbol table of the given order,
 * where the order is the power of two used as the number of
 * hash buckets. If 0 is passed, a default of 11 is used, which
 * results in 2048 hash table buckets.
 */
symtab *symtab_alloc(unsigned int order)
{
  symtab *table;
  
  if (order > 31) order = 31;
  if (order <= 0) order = SYMTAB_DEFAULT_ORDER;
  
  table = oom(calloc(sizeof(symtab), 1));
  table->nodes = oom(calloc(sizeof(symtab_node *), 1 << order));
  table->order = order;
  
  return table;
}

/*
 * Free symbol table
 *
 * This function frees a symbol table and all contained nodes
 * and entries.
 */
void symtab_free(symtab *symtab)
{
  int i;
  
  if (!symtab) {
    return;
  }
  
  for (i = 0; i < (1 << symtab->order); i++) {
    symtab_node_free(symtab->nodes[i]);
  }
#if DEBUG == 1
  memset(symtab->nodes, 0, sizeof(symtab_node *) * (1 << symtab->order));
#endif
  symtab->order = 0;
  free(symtab->nodes);
  free(symtab);
}
