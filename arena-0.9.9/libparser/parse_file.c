/*
 * Parse file
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "y.tab.h"

extern FILE *yyin;

void yyparse(void);

/*
 * Current interpreter state
 */
arena_state *parser_state = NULL;

/*
 * Tear down internal parser memory
 */
static void parse_teardown(void)
{
  parser_include_teardown();
  expr_stack_teardown();
  expr_arg_teardown();
  stmt_stack_teardown();
  stmt_arg_teardown();
}

/*
 * Parse file
 *
 * This function tries to parse the given file and returns the
 * resulting statement list.
 */
stmt_list *parse_file(arena_state *s, char *path)
{
  FILE *file;
  
  sanity(path);
  
  parser_state = s;
  s->source_file = path;

  file = fopen(path, "r");
  if (!file) {
    s->source_line = 0;
    fatal(s, "could not open input file");
    return stmt_list_alloc();
  }

  atexit(parse_teardown);

  stmt_stack_enter();

  yyin = file;
  yyparse();
  fclose(file);
  if (parser_error != 0) {
    stmt_stack_leave(1);
    return NULL;
  }
  
  return stmt_stack_leave(0);
}
