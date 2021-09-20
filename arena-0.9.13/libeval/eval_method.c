/*
 * Method call evaluation
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "eval.h"

/*
 * Enter struct namespace
 */
static void enter_struct(arena_state *s, value *val)
{
  symtab_stack_enter(s);
  symtab_stack_add_variable(s, "this", val);
}

/*
 * Leave struct namespace
 */
static value *leave_struct(arena_state *s, signature *sig,
  unsigned int argc, expr **argv)
{
  symtab_entry *entry;
  value *res = NULL;
  
  entry = symtab_stack_lookup(s, "this");
  if (entry) {
    res = value_copy(entry->entry_u.var);
  }
  update_call_args(s, sig, argc, argv);
  return res;
}

/*
 * Recursively construct instance
 */
static void getinstance(arena_state *s, const char *name)
{
  symtab_entry *entry;
  
  entry = symtab_stack_lookup(s, name);
  if (!entry || entry->type != SYMTAB_ENTRY_TMPL) {
    fatal(s, "use of undefined template `%s'", name);
    return;
  }
  if (entry->entry_u.def.parent) {
    getinstance(s, entry->entry_u.def.parent);
  }
  eval_stmt_list(s, (stmt_list *) entry->entry_u.def.def, 0);
  
  entry = symtab_stack_lookup(s, name);
  if (entry && entry->type == SYMTAB_ENTRY_FUNCTION) {
    s->new_cons = entry->symbol;
    s->new_sig  = entry->entry_u.sig;
  }
}

/*
 * Evaluate constructor expression
 */
value *eval_new(arena_state *s, expr *ex)
{
  value *res, *tname;

  sanity(ex && ex->name);
  
  symtab_stack_enter(s);
  s->new_cons = NULL;
  s->new_sig  = NULL;
  getinstance(s, ex->name);

  if (s->except_flag || s->exit_flag) {
    symtab_stack_leave(s);
    return value_make_void();
  }

  res = value_make_struct();
  symtab_free(res->value_u.struct_val);
  res->value_u.struct_val = symtab_stack_pop(s);
  
  tname = value_make_string(ex->name);
  value_set_struct(res, "__template", tname);
  value_free(tname);
  
  if (s->new_cons) {
    value **argv;
    value *temp, *cons;
    
    eval_call_args(s, ex->argc, ex->argv, &argv);
    enter_struct(s, res);
    
    cons = call_function(s, s->new_sig, ex->argc, argv);
    value_free(cons);
    
    temp = leave_struct(s, s->new_sig, ex->argc, ex->argv);
    if (!temp) {
      fatal(s, "no `this' at constructor `%s' exit", s->new_cons);
      temp = value_make_void();
    }
    free_call_args(s, ex->argc, &argv);
    
    value_free(res);
    res = temp;
  }

  return res;
}

/*
 * Evaluate static method call
 */
value *eval_static(arena_state *s, expr *ex)
{
  symtab_entry *entry;
  signature *sig;
  value **argv, *res;
  
  sanity(ex && ex->tname && ex->name);

  symtab_stack_enter(s);
  getinstance(s, ex->tname);

  if (s->except_flag || s->exit_flag) {
    symtab_stack_leave(s);
    return value_make_void();
  }
  
  entry = symtab_stack_lookup(s, ex->name);
  if (!entry || entry->type != SYMTAB_ENTRY_FUNCTION ||
      !symtab_stack_local(s, ex->name)) {
    fatal(s, "call to undefined method `%s::%s'", ex->tname, ex->name);
    symtab_stack_leave(s);
    return value_make_void();
  }
  sig = call_sig_copy(entry->entry_u.sig);
  symtab_stack_leave(s);
  
  eval_call_args(s, ex->argc, ex->argv, &argv);
  symtab_stack_enter(s);

  res = call_function(s, sig, ex->argc, argv);
  update_call_args(s, sig, ex->argc, ex->argv);

  free_call_args(s, ex->argc, &argv);
  
  call_sig_free(sig);
  return res;
}

/*
 * Evaluate static reference
 */
value *eval_static_ref(arena_state *s, expr *ex)
{
  symtab *sym;
  symtab_entry *entry;
  value *res;
  
  sanity(ex && ex->tname && ex->name);
  
  symtab_stack_enter(s);
  getinstance(s, ex->tname);
  sym = symtab_stack_pop(s);
  
  entry = symtab_lookup(sym, ex->name);
  if (!entry) {
    fatal(s, "use of undefined template member `%s::%s'", ex->tname,
      ex->name);
    symtab_free(sym);
    return value_make_void();
  }
  if (entry->type == SYMTAB_ENTRY_VAR) {
    res = value_copy(entry->entry_u.var);
  } else {
    res = value_make_fn(entry->entry_u.sig);
  }
  symtab_free(sym);
  return res;
}

/*
 * Evaluate method call
 */
value *eval_method(arena_state *s, expr *ex)
{
  symtab_entry *entry;
  value *val, *res, *temp, **argv;

  sanity(ex && ex->inner && ex->name);
  
  val = eval_expr(s, ex->inner);
  if (val->type != VALUE_TYPE_STRUCT) {
    value_free(val);
    fatal(s, "method call on non-struct value");
    return value_make_void();
  }
  
  entry = symtab_lookup(val->value_u.struct_val, ex->name);
  if (!entry || entry->type != SYMTAB_ENTRY_FUNCTION) {
    value_free(val);
    fatal(s, "call to undefined method `%s'", ex->name);
    return value_make_void();
  }

  eval_call_args(s, ex->argc, ex->argv, &argv);
  enter_struct(s, val);

  res = call_function(s, entry->entry_u.sig, ex->argc, argv);

  temp = leave_struct(s, entry->entry_u.sig, ex->argc, ex->argv);
  free_call_args(s, ex->argc, &argv);

  value_free(val);
  
  if (temp) {
    if (ex->inner->type == EXPR_REF) {
      symtab_stack_add_variable(s, ex->inner->name, temp);
    }
    if (ex->inner->type == EXPR_REF_ARRAY) {
      eval_assign_array_direct(s, ex->inner->name, ex->inner->argc,
        ex->inner->argv, temp);
    }
    value_free(temp);
  }
  
  return res;
}
