/*
 * Runtime functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "stdlib.h"

/*
 * Return type of expression
 *
 * This function returns a string representation of the type of
 * the first argument.
 */
value *rt_type_of(arena_state *s, unsigned int argc, value **argv)
{
  char *buf;
  switch (argv[0]->type) {
    case VALUE_TYPE_VOID:
      buf = "void";
      break;
    case VALUE_TYPE_BOOL:
      buf = "bool";
      break;
    case VALUE_TYPE_INT:
      buf = "int";
      break;
    case VALUE_TYPE_FLOAT:
      buf = "float";
      break;
    case VALUE_TYPE_STRING:
      buf = "string";
      break;
    case VALUE_TYPE_ARRAY:
      buf = "array";
      break;
    case VALUE_TYPE_STRUCT:
      buf = "struct";
      break;
    case VALUE_TYPE_FN:
      buf = "fn";
      break;
    case VALUE_TYPE_RES:
      buf = "resource";
      break;
    default:
      buf = "unknown";
  }
  return value_make_string(buf);
}

/*
 * Return template of value
 *
 * Returns the template of a struct value if it was instantiated from a
 * template definition and the "__template" member has not been overwritten
 * since. It returns void otherwise.
 */
value *rt_tmpl_of(arena_state *s, unsigned int argc, value **argv)
{
  if (argv[0]->type != VALUE_TYPE_STRUCT) {
    return value_make_void();
  }
  return value_get_struct(argv[0], "__template");
}

/*
 * Check whether all arguments have given type
 */
static value *is_type(unsigned int argc, value **argv, unsigned int type)
{
  unsigned int i;
  
  for (i = 0; i < argc; i++) {
    if (argv[i]->type != type) {
      return value_make_bool(0);
    }
  }
  return value_make_bool(1);
}

/*
 * Check whether arguments are all voids
 */
value *rt_is_void(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_VOID);
}

/*
 * Check whether arguments are all bools
 */
value *rt_is_bool(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_BOOL);
}

/*
 * Check whether arguments are all ints
 */
value *rt_is_int(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_INT);
}

/*
 * Check whether arguments are all floats
 */
value *rt_is_float(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_FLOAT);
}

/*
 * Check whether arguments are all strings
 */
value *rt_is_string(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_STRING);
}

/*
 * Check whether arguments are all arrays
 */
value *rt_is_array(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_ARRAY);
}

/*
 * Check whether arguments are all structs
 */
value *rt_is_struct(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_STRUCT);
}

/*
 * Check whether arguments are all functions
 */
value *rt_is_fn(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_FN);
}

/*
 * Check whether arguments are all resources
 */
value *rt_is_resource(arena_state *s, unsigned int argc, value **argv)
{
  return is_type(argc, argv, VALUE_TYPE_RES);
}

/*
 * Check whether struct is of a given template  (including parent templates)
 */
static value *is_tmpl(arena_state *s, value *val, const char *wanted)
{
  symtab_entry *entry;
  value *type;
  char *typename;
  int res = 0;

  type = value_get_struct(val, "__template");
  if (type->type != VALUE_TYPE_STRING) {
    value_free(type);
    return value_make_bool(0);
  }
  typename = type->value_u.string_val.value;
  
  while (typename) {
    entry = symtab_stack_lookup(s, typename);
    if (!entry || entry->type != SYMTAB_ENTRY_TMPL) {
      break;
    }
    if (strcmp(entry->symbol, wanted) == 0) {
      res = 1;
      break;
    }
    typename = entry->entry_u.def.parent;
  }
  
  value_free(type);
  return value_make_bool(res);
}

/*
 * Return numeric type for type name
 */
static int nametype(const char *name)
{
  int wanted = 0;

  if (strcmp(name, "void") == 0) {
    wanted = VALUE_TYPE_VOID;
  } else if (strcmp(name, "bool") == 0) {
    wanted = VALUE_TYPE_BOOL;
  } else if (strcmp(name, "int") == 0) {
    wanted = VALUE_TYPE_INT;
  } else if (strcmp(name, "float") == 0) {
    wanted = VALUE_TYPE_FLOAT;
  } else if (strcmp(name, "string") == 0) {
    wanted = VALUE_TYPE_STRING;
  } else if (strcmp(name, "array") == 0) {
    wanted = VALUE_TYPE_ARRAY;
  } else if (strcmp(name, "struct") == 0) {
    wanted = VALUE_TYPE_STRUCT;
  } else if (strcmp(name, "fn") == 0) {
    wanted = VALUE_TYPE_FN;
  } else if (strcmp(name, "resource") == 0) {
    wanted = VALUE_TYPE_RES;
  }
  return wanted;
}

/*
 * Check whether argument has specified type
 *
 * The type is given as a string identifying the desired type.
 */
value *rt_is_a(arena_state *s, unsigned int argc, value **argv)
{
  const char *name = argv[1]->value_u.string_val.value;
  unsigned int wanted = 0;
  
  if (!value_str_compat(argv[1])) {
    return value_make_bool(0);
  }

  wanted = nametype(name);  
  if (wanted == 0 && argv[0]->type == VALUE_TYPE_STRUCT) {
    return is_tmpl(s, argv[0], name);
  }
  return value_make_bool(argv[0]->type == wanted);
}

/*
 * Check existence of symtab entry of specific type
 */
static value *isdefined(arena_state *s, value *val, unsigned int wanted)
{
  char *name = val->value_u.string_val.value;
  symtab_entry *entry;
  
  if (!value_str_compat(val)) {
    return value_make_bool(0);
  }
  
  entry = symtab_stack_lookup(s, name);
  return value_make_bool(entry && entry->type == wanted);
}

/*
 * Check existence of function
 *
 * This function returns true if the given function name exists in
 * the current symbol table scope.
 */
value *rt_is_function(arena_state *s, unsigned int argc, value **argv)
{
  return isdefined(s, argv[0], SYMTAB_ENTRY_FUNCTION);
}

/*
 * Check existence of variable
 *
 * This function returns true if the given variable name exists in
 * the current symbol table scope.
 */
value *rt_is_var(arena_state *s, unsigned int argc, value **argv)
{
  return isdefined(s, argv[0], SYMTAB_ENTRY_VAR);
}

/*
 * Check existence of template
 *
 * This function returns true if the given template name exists in
 * the current symbol table scope.
 */
value *rt_is_tmpl(arena_state *s, unsigned int argc, value **argv)
{
  return isdefined(s, argv[0], SYMTAB_ENTRY_TMPL);
}

/*
 * Check for local symbol
 *
 * Returns true if the given name is from the local scope.
 */
value *rt_is_local(arena_state *s, unsigned int argc, value **argv)
{
  char *name = argv[0]->value_u.string_val.value;
  
  if (!value_str_compat(argv[0])) {
    return value_make_bool(0);
  }
  return value_make_bool(symtab_stack_local(s, name));
}

/*
 * Check for global symbol
 */
value *rt_is_global(arena_state *s, unsigned int argc, value **argv)
{
  char *name = argv[0]->value_u.string_val.value;
  symtab_entry *entry;
  
  if (!value_str_compat(argv[0])) {
    return value_make_bool(0);
  }
  entry = symtab_stack_lookup(s, name);
  return value_make_bool(entry && !symtab_stack_local(s, name));
}

/*
 * Define a variable
 *
 * This function uses its first parameter as a variable names and
 * assigns the value of the second parameter to the new variable.
 * It returns true on success and false on failure.
 */
value *rt_set(arena_state *s, unsigned int argc, value **argv)
{
  char *name = argv[0]->value_u.string_val.value;
  
  if (!value_str_compat(argv[0])) {
    return value_make_bool(0);
  }

  if (argv[1]->type != VALUE_TYPE_FN) {
    symtab_stack_add_variable(s, name, argv[1]);
  } else {
    symtab_stack_add_function(s, name, argv[1]->value_u.fn_val);
  }
  return value_make_bool(1);
}

/*
 * Variable reference
 *
 * This function takes the name of a variable as argument and returns
 * the value of the variable if it exists. If not, a void value is
 * returned.
 */
value *rt_get(arena_state *s, unsigned int argc, value **argv)
{
  char *name = argv[0]->value_u.string_val.value;
  symtab_entry *entry;
  
  if (!value_str_compat(argv[0])) {
    return value_make_void();
  }
  
  entry = symtab_stack_lookup(s, name);
  if (!entry || entry->type == SYMTAB_ENTRY_TMPL) {
    return value_make_void();
  }
  if (entry->type == SYMTAB_ENTRY_VAR) {
    return value_copy(entry->entry_u.var);
  } else {
    return value_make_fn(entry->entry_u.sig);
  }
}

/*
 * Unset variable or function
 *
 * Removes a variable or function from the current symbol table. In
 * the case of variables, the memory used by their values will also
 * be freed.
 */
value *rt_unset(arena_state *s, unsigned int argc, value **argv)
{
  unsigned int i;
  
  for (i = 0; i < argc; i++) {
    value_cast_inplace(s, &argv[i], VALUE_TYPE_STRING);
    if (value_str_compat(argv[i])) {
      symtab_stack_delete(s, argv[i]->value_u.string_val.value);
    }
  }
  
  return value_make_void();
}

/*
 * Debugging assertion
 *
 * Terminates the program if one the arguments evaluates to false.
 */
value *rt_assert(arena_state *s, unsigned int argc, value **argv)
{
  unsigned int i;
  
  for (i = 0; i < argc; i++) {
    value_cast_inplace(s, &argv[i], VALUE_TYPE_BOOL);
    if (!argv[i]->value_u.bool_val) {
      fatal(s, "assertion failure");
      break;
    }
  }
  return value_make_void();
}

/*
 * Make symbols global
 *
 * This function treats its arguments as variable names and
 * adds them to the global scope.
 */
value *rt_global(arena_state *s, unsigned int argc, value **argv)
{
  symtab_entry *entry;
  unsigned int i;
  
  for (i = 0; i < argc; i++) {
    value_cast_inplace(s, &argv[i], VALUE_TYPE_STRING);
    if (argv[i]->value_u.string_val.value) {
      entry = symtab_stack_lookup(s, argv[i]->value_u.string_val.value);
      if (entry && entry->type == SYMTAB_ENTRY_VAR) {
        symtab_stack_add_global(s, entry->symbol, entry->entry_u.var);
      }
    }
  }
  return value_make_void();
}

/*
 * Get static template member by name(s)
 */
value *rt_get_static(arena_state *s, unsigned int argc, value **argv)
{
  char *tmpl = argv[0]->value_u.string_val.value;
  char *name = argv[1]->value_u.string_val.value;
  symtab_entry *entry;
  expr ex;
  
  if (!value_str_compat(argv[0]) || !value_str_compat(argv[1])) {
    return value_make_void();
  }
  
  entry = symtab_stack_lookup(s, tmpl);
  if (!entry || entry->type != SYMTAB_ENTRY_TMPL) {
    return value_make_void();
  }
  
  ex.type  = EXPR_STATIC_REF;
  ex.tname = tmpl;
  ex.name  = name;
  
  return eval_static_ref(s, &ex);
}

/*
 * Cast to given type
 */
value *rt_cast_to(arena_state *s, unsigned int argc, value **argv)
{
  const char *name = argv[1]->value_u.string_val.value;
  int wanted;
  
  wanted = nametype(name);
  if (wanted == 0) {
    fatal(s, "unknown type name `%s'", name);
    return value_make_void();
  }
  return value_cast(s, argv[0], wanted);
}

/*
 * Get language and library versions
 */
value *rt_versions(arena_state *s, unsigned int argc, value **argv)
{
  value *res, *elem;
  
  res = value_make_struct();
  
  elem = value_make_int(2);
  value_set_struct(res, "v_language_major", elem);
  value_free(elem);

  elem = value_make_int(2);
  value_set_struct(res, "v_language_minor", elem);
  value_free(elem);

  elem = value_make_int(3);
  value_set_struct(res, "v_library_major", elem);
  value_free(elem);

  elem = value_make_int(0);
  value_set_struct(res, "v_library_minor", elem);
  value_free(elem);
  
  return res;
}
