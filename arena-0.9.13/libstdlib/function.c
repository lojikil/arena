/*
 * Functions on functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <ctype.h>
#include <stdlib.h>

#include "stdlib.h"

/*
 * Call function by reference
 */
value *fn_call(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  value *res;

  symtab_stack_enter(s);
  if (argc > 1) {
    res = call_function(s, sig, argc - 1, argv + 1);
  } else {
    res = call_function(s, sig, 0, NULL);
  }
  symtab_stack_leave(s);

  return res;
}

/*
 * Call function by reference and array of arguments
 */
value *fn_call_array(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  int uargc      = argv[1]->value_u.array_val.len;
  value **uargv  = argv[1]->value_u.array_val.value;
  value *res;

  symtab_stack_enter(s);  
  if (uargc > 0) {
    res = call_function(s, sig, uargc, uargv);
  } else {
    res = call_function(s, sig, 0, NULL);
  }
  symtab_stack_leave(s);

  return res;
}

/*
 * Get type description struct
 */
static value *typestruct(char typechar)
{
  const char *name;
  value *typename, *typeforce, *elem;
  
  if (typechar == '?' || typechar == '*') {
    typename = value_make_string("mixed");
  } else {
    name = call_typename(call_chartype(tolower(typechar)));
    typename = value_make_string(name);
  }
  typeforce = value_make_bool(isupper(typechar));
  
  elem = value_make_struct();
  value_set_struct(elem, "type", typename);
  value_set_struct(elem, "force", typeforce);
  
  value_free(typeforce);
  value_free(typename);
  
  return elem;
}

/*
 * Append type description to array
 */
static void appendtype(value *arr, char typechar)
{
  value *elem;
  
  elem = typestruct(typechar);
  value_add_to_array(arr, elem);
  value_free(elem);
}

/*
 * Get function prototype
 *
 * Returns an array that lists first the return type of the given
 * function, then the argument types. Each individual type is
 * given as a struct containing the fields "type" and "forced". The
 * former is the name of the expected type, the latter is true when
 * the type of the argument will be enforced.
 */
value *fn_prototype(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  unsigned int i;
  char *next;
  value *ret, *args, *res;
  
  ret = typestruct(sig->rettype);
  
  args = value_make_array();  
  next = sig->proto;
  for (i = 0; i < sig->args; i++) {
    appendtype(args, *next++);
  }

  res = value_make_struct();
  value_set_struct(res, "ret", ret);
  value_set_struct(res, "args", args);
  
  value_free(args);
  value_free(ret);
  return res;
}

/*
 * Map function over array
 */
value *fn_map(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  value *array   = argv[1];
  value **data   = array->value_u.array_val.value;
  int len        = array->value_u.array_val.len;
  value *res, *elem;
  int i;
  
  res = value_make_array();
  for (i = 0; i < len; i++) {
    argv[1] = data[i];
    symtab_stack_enter(s);
    elem = call_function(s, sig, argc - 1, argv + 1);
    symtab_stack_leave(s);
    value_add_to_array(res, elem);
    value_free(elem);
  }
  argv[1] = array;

  return res;
}

/*
 * Filter array with function
 */
value *fn_filter(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  value *array   = argv[1];
  value **data   = array->value_u.array_val.value;
  int len        = array->value_u.array_val.len;
  value *res, *test;
  int i;
  
  res = value_make_array();
  for (i = 0; i < len; i++) {
    argv[1] = data[i];
    symtab_stack_enter(s);
    test = call_function(s, sig, argc - 1, argv + 1);
    symtab_stack_leave(s);
    value_cast_inplace(s, &test, VALUE_TYPE_BOOL);
    if (test->value_u.bool_val) {
      value_add_to_array(res, data[i]);
    }
    value_free(test);
  }
  argv[1] = array;

  return res;
}

/*
 * Fold array from left
 */
value *fn_foldl(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  value *init    = argv[1];
  value *array   = argv[2];
  value **data   = array->value_u.array_val.value;
  int len        = array->value_u.array_val.len;
  value *temp    = value_copy(init);
  value *step;
  int i;
  
  for (i = 0; i < len; i++) {
    argv[1] = temp;
    argv[2] = data[i];
    symtab_stack_enter(s);
    step = call_function(s, sig, argc - 1, argv + 1);
    symtab_stack_leave(s);
    value_free(temp);
    temp = step;
  }
  argv[1] = init;
  argv[2] = array;

  return temp;
}

/*
 * Fold array from right
 */
value *fn_foldr(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  value *array   = argv[1];
  value **data   = array->value_u.array_val.value;
  int len        = array->value_u.array_val.len;
  value *init    = argv[2];
  value *temp    = value_copy(init);
  value *step;
  int i;
  
  for (i = len - 1; i >= 0; i--) {
    argv[1] = data[i];
    argv[2] = temp;
    symtab_stack_enter(s);
    step = call_function(s, sig, argc - 1, argv + 1);
    symtab_stack_leave(s);
    value_free(temp);
    temp = step;
  }
  argv[1] = array;
  argv[2] = init;

  return temp;
}

/*
 * Take elements from array while condition is true
 */
value *fn_take_while(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  value *array   = argv[1];
  value **data   = array->value_u.array_val.value;
  int len        = array->value_u.array_val.len;
  int i, flag;
  value *check, *res;

  res = value_make_array();
  for (i = 0; i < len; i++) {
    argv[1] = data[i];
    symtab_stack_enter(s);
    check = call_function(s, sig, argc - 1, argv + 1);
    symtab_stack_leave(s);
    value_cast_inplace(s, &check, VALUE_TYPE_BOOL);
    flag = check->value_u.bool_val;
    value_free(check);
    if (flag) {
      value_add_to_array(res, data[i]);
    } else {
      break;
    }
  }
  argv[1] = array;

  return res;
}

/*
 * Drop elements from array while condition is true
 */
value *fn_drop_while(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  value *array   = argv[1];
  value **data   = array->value_u.array_val.value;
  int len        = array->value_u.array_val.len;
  int i, flag;
  value *check, *res;

  for (i = 0; i < len; i++) {
    argv[1] = data[i];
    symtab_stack_enter(s);
    check = call_function(s, sig, argc - 1, argv + 1);
    symtab_stack_leave(s);
    value_cast_inplace(s, &check, VALUE_TYPE_BOOL);
    flag = check->value_u.bool_val;
    value_free(check);
    if (!flag) {
      break;
    }
  }
  argv[1] = array;

  res = value_make_array();
  for (; i < len; i++) {
    value_add_to_array(res, data[i]);
  }
  
  return res;
}

/*
 * Call method by name and struct, arguments as varargs
 */
value *fn_call_method(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  value *res;
  
  symtab_stack_enter(s);
  symtab_stack_add_variable(s, "this", argv[1]);
  res = call_function(s, sig, argc - 2, argv + 2);
  symtab_stack_leave(s);
  
  return res;
}

/*
 * Call method by name and struct, arguments as array
 */
value *fn_call_method_array(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  int     uargc  = argv[2]->value_u.array_val.len;
  value **uargv  = argv[2]->value_u.array_val.value;
  value *res;
  
  symtab_stack_enter(s);
  symtab_stack_add_variable(s, "this", argv[1]);
  res = call_function(s, sig, uargc, uargv);
  symtab_stack_leave(s);
  
  return res;
}

/*
 * Check whether function is a builtin function
 */
value *fn_is_builtin(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  
  return value_make_bool(sig->type == FUNCTION_TYPE_BUILTIN);
}

/*
 * Check whether function is a user-defined function
 */
value *fn_is_userdef(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  
  return value_make_bool(sig->type == FUNCTION_TYPE_USERDEF);
}

/*
 * Return function name of function value
 */
value *fn_name(arena_state *s, unsigned int argc, value **argv)
{
  signature *sig = argv[0]->value_u.fn_val;
  
  return value_make_string(sig->name);
}
