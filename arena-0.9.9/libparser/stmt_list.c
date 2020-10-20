/*
 * Statement lists
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

/*
 * Add statement to list
 */
void stmt_list_push(stmt_list *list, stmt *st)
{
  stmt **elems;
  
  sanity(list && st);

  if (list->len == 0) {
    elems = oom(malloc(sizeof(stmt *)));
    *elems = st;
    list->list = elems;
    list->len = 1;
  } else {
    elems = oom(realloc(list->list, (list->len + 1) * sizeof(stmt *)));
    list->list = elems;
    elems += list->len++;
    *elems = st;
  }
}

/*
 * Get last statement from list
 */
stmt *stmt_list_pop(stmt_list *list)
{
  sanity(list);

  if (list->len == 0) {
    return NULL;
  }
  list->len--;
  return list->list[list->len];
}
