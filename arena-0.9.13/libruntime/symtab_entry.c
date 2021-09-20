/*
 * Symbol table entry manipulation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "runtime.h"

/*
 * Add entry to symbol table node
 *
 * This function adds an entry to a symbol table node. The memory
 * allocated for the node is increased as needed.
 */
static void symtab_node_add(symtab_node *node, symtab_entry *entry)
{
  symtab_entry **entries;

  sanity(node && entry);  

  entries = oom(realloc(node->entries,
    (node->count+1) * sizeof(symtab_entry *)));
  entries[node->count] = entry;
  node->count++;
  node->entries = entries;
}

/*
 * The FNV1a-32 hash algorithm
 * (http://www.isthe.com/chongo/tech/comp/fnv/)
 */
static unsigned int fnv1a(const char *str, unsigned int hval)
{
  static const unsigned int fnv_32_prime = 0x01000193;
       
  while (*str) {
    hval ^= *str++;
    hval *= fnv_32_prime;
  }
  return hval;
}

/*
 * Hash symbol name
 *
 * This function computes the hash value of a given symbol
 * name. The 32 bit hash value is reduced to the actual
 * number of bits available for symbol table hash buckets.
 */
static unsigned int symtab_hash(const char *symbol, unsigned int order)
{
  unsigned int hash;

  hash = fnv1a(symbol, 0);
  hash ^= (hash >> (32 - order));
  return (hash & ((1 << order) - 1));
}

/*
 * Add entry to symbol table
 *
 * This function adds an entry to a symbol table. It does not
 * check whether an entry with the same symbol name already
 * exists. If the node for the hash value of the symbol has not
 * yet been allocated, this function will allocate a new node.
 */
void symtab_add(symtab *symtab, symtab_entry *entry)
{
  unsigned int pos;

  sanity(symtab && entry && entry->symbol);

  pos = symtab_hash(entry->symbol, symtab->order);
  if (!symtab->nodes[pos]) {
    symtab->nodes[pos] = symtab_node_alloc();
  }
  
  symtab_node_add(symtab->nodes[pos], entry);
}

/*
 * Lookup symbol in symbol table
 *
 * This function looks for a given symbol and returns a pointer
 * to entry if the symbol is found in the symbol table. If the
 * symbol is not found, NULL is returned.
 */
symtab_entry *symtab_lookup(symtab *symtab, const char *symbol)
{
  symtab_node *node;
  symtab_entry *entry;
  unsigned int pos, i;

  sanity(symtab);

  if (!symbol) {
    return NULL;
  }
  
  pos = symtab_hash(symbol, symtab->order);
  if (!symtab->nodes[pos]) {
    return NULL;
  }

  node = symtab->nodes[pos];
  for (i = 0; i < node->count; i++) {
    entry = node->entries[i];
    if (entry && entry->symbol && strcmp(entry->symbol, symbol) == 0) {
      return entry;
    }
  }
  return NULL;
}

/*
 * Delete symbol from symbol table
 *
 * This function removes the given symbol from the symbol table.
 * It is not an error if the symbol is not contained in the table.
 * Note that this function does not shrink the memory used by
 * the symbol table node that contained the symbol -- the memory
 * will be reused when another symbol is added to that node.
 */
void symtab_delete(symtab *symtab, const char *symbol)
{
  symtab_node *node;
  symtab_entry *entry;
  unsigned int pos, i, j;

  sanity(symtab);

  if (!symbol) {
    return;
  }
  
  pos = symtab_hash(symbol, symtab->order);
  if (!symtab->nodes[pos]) {
    return;
  }

  node = symtab->nodes[pos];
  for (i = 0; i < node->count; i++) {
    entry = node->entries[i];
    if (entry && entry->symbol && strcmp(entry->symbol, symbol) == 0) {
      symtab_entry_free(entry);
      for (j = i; j < node->count - 1; j++) {
        node->entries[j] = node->entries[j+1];
      }
      node->count--;
      break;
    }
  }
}

/*
 * Add variable to symbol table
 *
 * This function adds a variable with the given name and value to
 * the symbol table. The value and its name will be stored as copies.
 * Any previously existing entry with the same name is removed from
 * the symbol table and freed.
 */
void symtab_add_variable(symtab *symtab, const char *name, value *val)
{
  char *symbol;
  value *copy;
  symtab_entry *entry;

  sanity(symtab && name && val);

  symbol = oom(malloc(strlen(name) + 1));
  strcpy(symbol, name);
  
  copy = value_copy(val);
  entry = symtab_entry_alloc();

  symtab_delete(symtab, name);
  
  entry->symbol = symbol;
  entry->entry_u.var = copy;
  symtab_add(symtab, entry);
  entry->type = SYMTAB_ENTRY_VAR;
}

/*
 * Add function to symbol table
 *
 * This function adds a function with the given name and signature
 * to the symbol table. The name and signature will be stored as
 * copies. Any previously existing entry with the same name is removed
 * from the symbol table and freed.
 */
void symtab_add_function(symtab *symtab, const char *name,
  const signature *sig)
{
  char *symbol;
  signature *copy;
  symtab_entry *entry;

  sanity(symtab && name && sig);

  symbol = oom(malloc(strlen(name) + 1));
  strcpy(symbol, name);
  
  copy = call_sig_copy(sig);
  entry = symtab_entry_alloc();

  symtab_delete(symtab, name);
  
  entry->symbol = symbol;
  entry->entry_u.sig = copy;
  symtab_add(symtab, entry);
  entry->type = SYMTAB_ENTRY_FUNCTION;
}

/*
 * Add template to symbol table
 *
 * This function adds a template with the given name, parent template,
 * and definition to the symbol table. The name and parent will
 * be stored as copies. Any previously existing entry with the same
 * name is removed from the symbol table and freed.
 */
void symtab_add_template(symtab *symtab, const char *name, const char *parent,
  void *def)
{
  char *symbol, *pcopy = NULL;
  symtab_entry *entry;
  
  sanity(symtab && name && def);
  
  symbol = oom(malloc(strlen(name) + 1));
  strcpy(symbol, name);
  
  if (parent) {
    pcopy = oom(malloc(strlen(parent) + 1));
    strcpy(pcopy, parent);
  }
  
  entry = symtab_entry_alloc();
  
  symtab_delete(symtab, name);
  
  entry->symbol = symbol;
  entry->entry_u.def.parent = pcopy;
  entry->entry_u.def.def = def;
  symtab_add(symtab, entry);
  entry->type = SYMTAB_ENTRY_TMPL;
}

/*
 * Count number of symtab entries
 */
int symtab_num_entries(symtab *sym)
{
  symtab_node *node;
  unsigned int i, j;
  int count = 0;

  sanity(sym);
  
  for (i = 0; i < (unsigned int) (1 << sym->order); i++) {
    node = sym->nodes[i];
    if (node) {
      for (j = 0; j < node->count; j++) {
        if (node->entries[j]) {
          ++count;
        }
      }
    }
  }
  return count;
}
