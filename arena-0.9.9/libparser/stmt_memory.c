/*
 * Statement memory management
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "parser.h"

/*
 * Allocate statement structure
 */
stmt *stmt_alloc(void)
{
  return oom(calloc(sizeof(stmt), 1));
}

/*
 * Free statment structure
 */
void stmt_free(stmt *st)
{
  if (!st) {
    return;
  }

  if (st->init) expr_free(st->init);
  if (st->expr) expr_free(st->expr);
  if (st->guard) expr_free(st->guard);
  if (st->true_case) stmt_free(st->true_case);
  if (st->false_case) stmt_free(st->false_case);
  if (st->block) stmt_list_free((stmt_list *) st->block);
  
  if (st->args > 0) {
    unsigned int i;
    
    for (i = 0; i < st->args; i++) {
      free(st->names[i]);
    }
  }

  free(st->name);
  free(st->proto);
  free(st->names);

  free(st);
}

/*
 * Allocate statement list structure
 */
stmt_list *stmt_list_alloc(void)
{
  return oom(calloc(sizeof(stmt_list), 1));
}

/*
 * Free statement list structure
 */
void stmt_list_free(stmt_list *list)
{
  unsigned int i;

  if (!list) {
    return;
  }

  for (i = 0; i < list->len; i++) {
    stmt_free(list->list[i]);
  }
  free(list->list);
  free(list);
}
