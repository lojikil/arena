/*
 * Value casting
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "runtime.h"

/*
 * Cast value to bool
 *
 * This function casts the given value to a bool value.
 * Non-zero numeric and non-empty string and array values
 * are cast to "true".
 */
static value *cast_to_bool(value *val)
{
  value *res;

  res = value_alloc(VALUE_TYPE_BOOL);

  switch (val->type) {
    case VALUE_TYPE_VOID:
      break;
    case VALUE_TYPE_BOOL:
      res->value_u.bool_val = val->value_u.bool_val;
      break;
    case VALUE_TYPE_INT:
      res->value_u.bool_val = val->value_u.int_val;
      break;
    case VALUE_TYPE_FLOAT:
      res->value_u.bool_val = val->value_u.float_val;
      break;
    case VALUE_TYPE_STRING:
      res->value_u.bool_val = val->value_u.string_val.len;
      break;
    case VALUE_TYPE_ARRAY:
      res->value_u.bool_val = val->value_u.array_val.len;
      break;
    case VALUE_TYPE_STRUCT:
      res->value_u.bool_val = symtab_num_entries(val->value_u.struct_val);
      break;
    case VALUE_TYPE_FN:
      res->value_u.bool_val = 1;
      break;
    case VALUE_TYPE_RES:
      res->value_u.bool_val = 1;
      break;
  }
  if (res->value_u.bool_val != 0) {
    res->value_u.bool_val = 1;
  }
  return res;
}

/*
 * Cast value to int
 *
 * This function casts the given value to an int value.
 * Numeric values are cast to their int equivalent or
 * clipped. Strings are interpreted as numbers if possible.
 * Arrays are cast to their length.
 */
static value *cast_to_int(value *val)
{
  value *res;
  int copy = 0;

  res = value_alloc(VALUE_TYPE_INT);

  switch (val->type) {
    case VALUE_TYPE_VOID:
      break;
    case VALUE_TYPE_BOOL:
      copy = val->value_u.bool_val;
      break;
    case VALUE_TYPE_INT:
      copy = val->value_u.int_val;
      break;
    case VALUE_TYPE_FLOAT:
      copy = val->value_u.float_val;
      break;
    case VALUE_TYPE_STRING:
      if (val->value_u.string_val.len) {
        copy = strtol(val->value_u.string_val.value, NULL, 0);
      }
      break;
    case VALUE_TYPE_ARRAY:
      copy = val->value_u.array_val.len;
      break;
    case VALUE_TYPE_STRUCT:
      copy = symtab_num_entries(val->value_u.struct_val);
      break;
    case VALUE_TYPE_FN:
      copy = 1;
      break;
    case VALUE_TYPE_RES:
      copy = 1;
      break;
  }
  res->value_u.int_val = copy;
  return res;
}

/*
 * Cast value to float
 *
 * This function casts the given value to a float value.
 * Numeric values are cast to their float equivalent or
 * clipped. Strings are interpreted as numbers if possible.
 * Arrays are cast to their length.
 */
static value *cast_to_float(value *val)
{
  value *res;
  double copy = 0.0;

  res = value_alloc(VALUE_TYPE_FLOAT);

  switch (val->type) {
    case VALUE_TYPE_VOID:
      break;
    case VALUE_TYPE_BOOL:
      copy = val->value_u.bool_val;
      break;
    case VALUE_TYPE_INT:
      copy = val->value_u.int_val;
      break;
    case VALUE_TYPE_FLOAT:
      copy = val->value_u.float_val;
      break;
    case VALUE_TYPE_STRING:
      if (val->value_u.string_val.len) {
        copy = strtod(val->value_u.string_val.value, NULL);
      }
      break;
    case VALUE_TYPE_ARRAY:
      copy = val->value_u.array_val.len;
      break;
    case VALUE_TYPE_STRUCT:
      copy = symtab_num_entries(val->value_u.struct_val);
      break;
    case VALUE_TYPE_FN:
      copy = 1.0;
      break;
    case VALUE_TYPE_RES:
      copy = 1.0;
      break;
  }
  res->value_u.float_val = copy;
  return res;
}

/*
 * Cast value to string
 *
 * This function casts the given value to a string value.
 * Numbers are cast into a string representation, arrays
 * are cast into the string "Array".
 */
static value *cast_to_string(value *val)
{
  value *res = NULL;
  char buf[64];

  switch (val->type) {
    case VALUE_TYPE_VOID:
      res = value_make_string(NULL);
      break;
    case VALUE_TYPE_BOOL:
      if (val->value_u.bool_val != 0) {
        res = value_make_string("1");
      } else {
        res = value_make_string(NULL);
      }
      break;
    case VALUE_TYPE_INT:
      sprintf(buf, "%i", val->value_u.int_val);
      res = value_make_string(buf);
      break;
    case VALUE_TYPE_FLOAT:
      sprintf(buf, "%0.10g", val->value_u.float_val);
      res = value_make_string(buf);
      break;
    case VALUE_TYPE_STRING:
      res = value_copy(val);
      break;
    case VALUE_TYPE_ARRAY:
      res = value_make_string("Array");
      break;
    case VALUE_TYPE_STRUCT:
      res = value_make_string("Struct");
      break;
    case VALUE_TYPE_FN:
      res = value_make_string("Function");
      break;
    case VALUE_TYPE_RES:
      res = value_make_string("Resource");
      break;
  }
  return res;
}

/*
 * Cast value to array
 *
 * This function casts the given value to an array value.
 * Non-array values are cast into a one-element array
 * containing a copy of the original value.
 */
static value *cast_to_array(value *val)
{
  value *res;

  if (val->type == VALUE_TYPE_ARRAY) {
    res = value_copy(val);
  } else {
    res = value_alloc(VALUE_TYPE_ARRAY);
    value_add_to_array(res, val);
  }
  return res;
}

/*
 * Cast value to struct
 *
 * This function casts the given value to a struct value.
 * Non-struct values are cast into a one-field struct with
 * the original type as the field name.
 */
static value *cast_to_struct(value *val)
{
  value *res;
  
  if (val->type == VALUE_TYPE_STRUCT) {
    res = value_copy(val);
  } else {
    res = value_make_struct();
    value_set_struct(res, "value", val);
  }
  return res;
}

/*
 * Cast value to function
 *
 * Casting non-function values to function is a fatal error.
 */
static value *cast_to_fn(arena_state *s, value *val)
{
  if (val->type != VALUE_TYPE_FN) {
    fatal(s, "cannot cast `%s' to `fn'", call_typename(val->type));
  }
  return value_copy(val);
}

/*
 * Cast value to resource
 *
 * Casting non-resource values to resource is a fatal error.
 */
static value *cast_to_res(arena_state *s, value *val)
{
  if (val->type != VALUE_TYPE_RES) {
    fatal(s, "cannot cast `%s' to `resource'", call_typename(val->type));
  }
  return value_copy(val);
}

/*
 * Cast value to type
 *
 * This function attempts to cast the given value to the
 * given type. The result of the cast or NULL is returned.
 */
value *value_cast(arena_state *s, value *val, value_type type)
{
  value *res = NULL;
  
  sanity(val);

  switch (type) {
    case VALUE_TYPE_VOID:
      res = value_make_void();
      break;
    case VALUE_TYPE_BOOL:
      res = cast_to_bool(val);
      break;
    case VALUE_TYPE_INT:
      res = cast_to_int(val);
      break;
    case VALUE_TYPE_FLOAT:
      res = cast_to_float(val);
      break;
    case VALUE_TYPE_STRING:
      res = cast_to_string(val);
      break;
    case VALUE_TYPE_ARRAY:
      res = cast_to_array(val);
      break;
    case VALUE_TYPE_STRUCT:
      res = cast_to_struct(val);
      break;
    case VALUE_TYPE_FN:
      res = cast_to_fn(s, val);
      break;
    case VALUE_TYPE_RES:
      res = cast_to_res(s, val);
      break;
  }
  return res;
}

/*
 * Cast value inplace
 *
 * This function casts a value inplace, overwriting the original
 * value.
 */
void value_cast_inplace(arena_state *s, value **val, value_type type)
{
  value *res;
  
  sanity(val && *val);
  
  if ((*val)->type == type) {
    return;
  }

  res = value_cast(s, *val, type);
  value_free(*val);
  *val = res;
}

/*
 * Check compatibility with C string functions
 *
 * This function returns true if the pointer from a string value
 * can be passed into a C function that expects a char pointer.
 * Strings with embedded \0 characters are not compatible.
 */
int value_str_compat(const value *val)
{
  void *data;
  int len;

  if (!val || val->type != VALUE_TYPE_STRING) {
    return 0;
  }

  data = val->value_u.string_val.value;
  len  = val->value_u.string_val.len;

  return (len && memchr(data, 0, len) == NULL);
}
