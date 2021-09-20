/*
 * Top-level interpreter API
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "libmisc/misc.h"
#include "libruntime/runtime.h"
#include "libparser/parser.h"
#include "libeval/eval.h"
#include "libstdlib/stdlib.h"

#include "api.h"

/*
 * Create new interpreter context
 */
arena_ctx arena_new_ctx(int argc, char **argv)
{
  arena_state *state = state_alloc();
  
  symtab_stack_init(state);
  stdlib_register(state, argc, argv);
  
  return state;
}

/* 
 * Free interpreter context
 */
void arena_free_ctx(arena_ctx ctx)
{
  arena_state *state = ctx;
  
  symtab_stack_teardown(state);
  eval_free_floats(state);
  state_free(state);
}

/*
 * Remove a named entity from the interpreter context
 */
void arena_inhibit_ctx(arena_ctx ctx, const char *name)
{
  arena_state *state = ctx;
  
  symtab_stack_delete(state, name);
}

/*
 * Create new script by parsing source file
 */
arena_script arena_new_script(char *name)
{
  arena_state *state = state_alloc();
  stmt_list *list;
  
  state->source_line = 1;
  state->source_col  = 0;
  
  list = parse_file(state, name);
  state_free(state);

  return list;
}

/*
 * Free script data
 */
void arena_free_script(arena_script script)
{
  stmt_list *list = script;
  
  stmt_list_free(list);
}

/*
 * Execute a script inside a given interpreter context
 */
int arena_execute_script(arena_ctx ctx, arena_script script)
{
  arena_state *state = ctx;
  stmt_list *list = script;

  state->source_line = 1;
  state->source_col  = 0;
  
  eval_stmt_list(state, list, 0);
  
  return state->exit_value;
}

/*
 * Dump a script to standard output
 */
void arena_dump_script(arena_script script)
{
  stmt_list *list = script;
  
  stmt_list_dump(list, 0);
}

/*
 * Execute an Arena function
 */
arena_result arena_execute_function(arena_ctx ctx, const char *name, ...)
{
  arena_state *state = ctx;
  signature *sig;
  char *proto;
  symtab_entry *entry;
  va_list ap;
  int i, argc = 0;
  value **argv, *res;

  symtab_stack_init(state);
  
  entry = symtab_stack_lookup(state, name);
  if (!entry || entry->type != SYMTAB_ENTRY_FUNCTION) {
    return NULL;
  }
  sig = entry->entry_u.sig;
  proto = sig->proto;
  
  if (strpbrk(proto, "?*aAcCpPrR")) {
    return NULL;
  }
  
  argv = malloc(strlen(proto) * sizeof(value *));
  if (!argv) {
    return NULL;
  }
  
  va_start(ap, name);
  while (*proto) {
    switch (*proto) {
      case 'v':
      case 'V':
        argv[argc++] = value_make_void();
        break;
      case 'b':
      case 'B':
        argv[argc++] = value_make_bool(va_arg(ap, int));
        break;
      case 'i':
      case 'I':
        argv[argc++] = value_make_int(va_arg(ap, int));
        break;
      case 'f':
      case 'F':
        argv[argc++] = value_make_float(va_arg(ap, double));
        break;
      case 's':
      case 'S':
        argv[argc++] = value_make_string(va_arg(ap, char *));
        break;
    }
    ++proto;
  }
  va_end(ap);
  
  symtab_stack_enter(state);
  res = call_named_function(state, name, argc, argv);
  symtab_stack_leave(state);
  
  for (i = 0; i < argc; ++i) {
    value_free(argv[i]);
  }
  free(argv);
  
  return res;
}

/* 
 * Get int version of function call result
 */
int arena_int_result(arena_result result)
{
  value *cast, *in = result;
  int res;
  
  cast = value_cast(NULL, in, VALUE_TYPE_INT);
  res = INT_OF(cast);
  value_free(cast);
  
  return res;
}

/* 
 * Get double version of function call result
 */
double arena_double_result(arena_result result)
{
  value *cast, *in = result;
  double res;
  
  cast = value_cast(NULL, in, VALUE_TYPE_FLOAT);
  res = FLOAT_OF(cast);
  value_free(cast);
  
  return res;
}

/*
 * Get string version of function call result
 */
char *arena_string_result(arena_result result)
{
  value *cast, *in = result;
  char *res;
  
  cast = value_cast(NULL, in, VALUE_TYPE_STRING);
  res = malloc(STRLEN_OF(cast) + 1);
  if (res) {
    if (STRLEN_OF(cast) > 0) {
      strcpy(res, STR_OF(cast));
    } else {
      res[0] = 0;
    }
  }
  value_free(cast);
  
  return res;
}

/*
 * Free function call result
 */
void arena_free_result(arena_result result)
{
  value *res = result;
  
  value_free(res);
}
