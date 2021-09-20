/*
 * Expression memory management
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

/*
 * Allocate expression structure
 */
expr *expr_alloc(void)
{
  expr *ex;
  
  ex = oom(calloc(sizeof(expr), 1));
  ex->file = parser_state->source_file;
  ex->line = parser_state->source_line;
  
  return ex;
}

/*
 * Free expression structure
 */
void expr_free(expr *ex)
{
  unsigned int i;
  
  if (!ex) {
    return;
  }
  
  expr_free(ex->inner);
  expr_free(ex->index);
  expr_free(ex->elif);
  for (i = 0; i < ex->argc; i++) {
    expr_free(ex->argv[i]);
  }
  
  stmt_free(ex->lambda);

  free(ex->argv);
  free(ex->name);
  free(ex->tname);
  free(ex);
}

/*
 * Copy expression
 */
expr *expr_copy(expr *ex)
{
  expr *copy;
  char *scopy;
  unsigned int i;
  
  if (!ex) {
    return NULL;
  }
  
  copy = expr_alloc();
  *copy = *ex;
  
  if (ex->name) {
    scopy = oom(malloc(strlen(ex->name) + 1));
    strcpy(scopy, ex->name);
    copy->name = scopy;
  }
  if (ex->tname) {
    scopy = oom(malloc(strlen(ex->tname) + 1));
    strcpy(scopy, ex->tname);
    copy->tname = scopy;
  }
  
  copy->inner = expr_copy(ex->inner);
  copy->index = expr_copy(ex->index);
  
  if (ex->argc > 0) {
    copy->argv = oom(malloc(sizeof(expr *) * ex->argc));
    for (i = 0; i < ex->argc; i++) {
      copy->argv[i] = expr_copy(ex->argv[i]);
    }
  }
  
  return copy;
}
