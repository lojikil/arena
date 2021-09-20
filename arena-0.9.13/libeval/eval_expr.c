/*
 * Expression evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>

#include "eval.h"

/*
 * Evaluate lambda expression
 */
value *eval_lambda(arena_state *s, expr *ex)
{
  symtab_entry *entry;
  value *res;

  sanity(ex && ex->lambda);

  symtab_stack_enter(s);
  eval_stmt(s, ex->lambda, 0);
  
  entry = symtab_stack_lookup(s, "\\lambda");
  if (!entry || entry->type != SYMTAB_ENTRY_FUNCTION) {
    fatal(s, "lambda expression did not yield function");
    return value_make_void();
  }
  res = value_make_fn(entry->entry_u.sig);
  symtab_stack_leave(s);
  
  return res;
}

/*
 * Evaluate expression
 *
 * This function returns the value that results from evaluating the
 * given expression. Recursion on subexpressions is used as needed.
 */
value *eval_expr(arena_state *s, expr *ex)
{
  value *res = NULL;
  
  sanity(ex);

  if (s->except_flag || s->exit_flag) {
    return value_make_void();
  }

  /*
   * record source position for error printing
   */
  s->source_line = ex->line;
  s->source_file = ex->file;
  
  switch (ex->type) {
    case EXPR_NOP:
      res = value_make_void();
      break;
    case EXPR_ASSIGN:
      res = eval_assign(s, ex);
      break;
    case EXPR_ASSIGN_ARRAY:
      res = eval_assign_array(s, ex);
      break;
    case EXPR_CAST:
      res = eval_cast(s, ex);
      break;
    case EXPR_CALL:
      res = eval_call(s, ex);
      break;
    case EXPR_NEW:
      res = eval_new(s, ex);
      break;
    case EXPR_STATIC:
      res = eval_static(s, ex);
      break;
    case EXPR_METHOD:
      res = eval_method(s, ex);
      break;
    case EXPR_REF:
      res = eval_ref(s, ex);
      break;
    case EXPR_REF_ARRAY:
      res = eval_ref_array(s, ex);
      break;
    case EXPR_INDEX:
      res = eval_ref_index(s, ex);
      break;
    case EXPR_CONST_VOID:
      res = eval_const_void();
      break;
    case EXPR_CONST_BOOL:
      res = eval_const_bool(ex);
      break;
    case EXPR_CONST_INT:
      res = eval_const_int(ex);
      break;
    case EXPR_CONST_FLOAT:
      res = eval_const_float(ex);
      break;
    case EXPR_CONST_STRING:
      res = eval_const_string(s, ex);
      break;
    case EXPR_INFIX:
      res = eval_infix(s, ex);
      break;
    case EXPR_POSTFIX:
      res = eval_postfix(s, ex);
      break;
    case EXPR_PREFIX:
      res = eval_prefix(s, ex);
      break;
    case EXPR_FIELD:
      res = eval_const_string(s, ex);
      break;
    case EXPR_STATIC_REF:
      res = eval_static_ref(s, ex);
      break;
    case EXPR_LAMBDA:
      res = eval_lambda(s, ex);
      break;
    case EXPR_IF:
      res = eval_expr_if(s, ex);
      break;
    case EXPR_PASS_REF:
      res = eval_expr(s, ex->inner);
      break;
    case EXPR_FILE:
      res = value_make_string(ex->file);
      break;
    case EXPR_LINE:
      res = value_make_int(ex->line);
      break;
  }
  
  return res;
}
