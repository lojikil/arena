/*
 * Function call evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
 
#include <stdlib.h>
 
#include "eval.h"

/*
 * Free all floating arguments
 */
void eval_free_floats(arena_state *s)
{
  value **float_args = s->float_args;
  value ***vectors = s->vectors;
  int i;
  
  for (i = 0; i < s->float_count; i++) {
    value_free(float_args[i]);
  }
  free(s->float_args);
  
  for (i = 0; i < s->vector_count; i++) {
    free(vectors[i]);
  }
  free(s->vectors);
}

/*
 * Add allocated function argument to floating list
 */
static void add_float(arena_state *s, value *val)
{
  value **float_args = s->float_args;

  float_args = oom(realloc(float_args,
    (s->float_count + 1) * sizeof(value *)));
  float_args[s->float_count++] = val;
  s->float_args = float_args;
}

/*
 * Add allocated argument vector to floating list
 */
static void add_vector(arena_state *s, value **val)
{
  value ***vectors = s->vectors;

  vectors = oom(realloc(vectors, (s->vector_count + 1) * sizeof(value **)));
  vectors[s->vector_count++] = val;
  s->vectors = vectors;
}

/*
 * Evaluate function call arguments
 */
void eval_call_args(arena_state *s, unsigned int argc, expr **args,
  value ***argv)
{
  unsigned int i;
  
  sanity((argc == 0 || args) && argv);

  *argv = oom(calloc(sizeof(value *), argc));
  add_vector(s, *argv);
  for (i = 0; i < argc; i++) {
    (*argv)[i] = eval_expr(s, args[i]);
    add_float(s, (*argv)[i]);
  }
}

/*
 * Free function call arguments
 */
void free_call_args(arena_state *s, unsigned int argc, value ***argv)
{
  unsigned int i;
  
  sanity(argc == 0 || (argv && *argv));
  
  for (i = 0; i < argc; i++) {
    value_free((*argv)[i]);
  }
  s->float_count -= argc;
  free(*argv);
  --s->vector_count;
}

/*
 * Length of a reference expression
 */
static int reflength(expr *ex)
{
  unsigned int i;
  int buf = 0;

  if (ex->type == EXPR_PASS_REF) {
    buf = reflength(ex->inner);
  } else if (ex->type == EXPR_REF) {
    buf = 1;
  } else if (ex->type == EXPR_REF_ARRAY) {
    buf = 1;
    for (i = 0; i < ex->argc; i++) {
      buf += reflength(ex->argv[i]);
    }
  }
  return buf;
}

/*
 * Maximum length of occuring references
 */
static int maxlength(unsigned int argc, expr **argv)
{
  unsigned int i;
  int max = 0, curr;
  
  for (i = 0; i < argc; i++) {
    curr = reflength(argv[i]);
    if (curr > max) max = curr;
  }
  return max;
}

/*
 * Update references after function call
 */
void update_call_args(arena_state *s, signature *sig, unsigned int argc,
  expr **argv)
{
  char **names;
  expr *ex;
  symtab *sym;
  symtab_entry *entry;
  value *val;
  unsigned int i;
  int maxref, len;
  
  sanity(sig && (argc == 0 || argv));
  
  sym = symtab_stack_pop(s);
  names = sig->data;
  maxref = maxlength(argc, argv);
  
  for (len = maxref; len >= 0; len--) {
    for (i = 0; i < argc; i++) {
      ex = argv[i];
      if (reflength(ex) != len) {
        continue;
      }
      if (ex->type != EXPR_PASS_REF ||
          (ex->inner->type != EXPR_REF && ex->inner->type != EXPR_REF_ARRAY)) {
        continue;
      }
      entry = symtab_lookup(sym, names[i]);
      if (!entry || entry->type == SYMTAB_ENTRY_TMPL) {
        continue;
      }
      if (ex->inner->type == EXPR_REF) {
        if (entry->type == SYMTAB_ENTRY_VAR) {
          symtab_stack_add_variable(s, ex->inner->name, entry->entry_u.var);
        } else {
          symtab_stack_add_function(s, ex->inner->name, entry->entry_u.sig);
        }
      } else {
        if (entry->type == SYMTAB_ENTRY_VAR) {
          eval_assign_array_direct(s, ex->inner->name,
            ex->inner->argc, ex->inner->argv, entry->entry_u.var);
        } else {
          val = value_make_fn(entry->entry_u.sig);
          eval_assign_array_direct(s, ex->inner->name,
          ex->inner->argc, ex->inner->argv, val);
          value_free(val);
        }
      }
    }
  }
  symtab_free(sym);
}

/*
 * Evaluate function call
 */
value *eval_call(arena_state *s, expr *ex)
{
  symtab_entry *entry;
  signature *sig;
  value *res = NULL;
  value **argv;
  
  sanity(ex && ex->name);
  
  entry = symtab_stack_lookup(s, ex->name);
  if (!entry || entry->type == SYMTAB_ENTRY_TMPL ||
      (entry->type == SYMTAB_ENTRY_VAR &&
       entry->entry_u.var->type != VALUE_TYPE_FN)) {
    fatal(s, "call to undefined function `%s'", ex->name);
    return value_make_void();
  }
  if (entry->type == SYMTAB_ENTRY_FUNCTION) {
    sig = entry->entry_u.sig;
  } else {
    sig = entry->entry_u.var->value_u.fn_val;
  }
  
  eval_call_args(s, ex->argc, ex->argv, &argv);

  if (entry->entry_u.sig->type == FUNCTION_TYPE_BUILTIN) {
    res = call_function(s, sig, ex->argc, argv);
  } else {
    symtab_stack_enter(s);
    res = call_function(s, sig, ex->argc, argv);
    update_call_args(s, sig, ex->argc, ex->argv);
  }

  free_call_args(s, ex->argc, &argv);
  return res;
}
