/*
 * Constructor functions
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "runtime.h"

/*
 * Make void value
 *
 * This function returns a new void value.
 */
value *value_make_void(void)
{
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_VOID);
  return copy;
}

/*
 * Make bool value
 *
 * This functions returns a new bool value. The value
 * contains "false" if the given C integer is 0 and
 * "true" otherwise.
 */
value *value_make_bool(int val)
{
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_BOOL);
  if (val) {
    copy->value_u.bool_val = 1;
  }
  return copy;
}

/*
 * Make int value
 *
 * This functions returns a new int value with the same
 * numerical value as the given C integer.
 */
value *value_make_int(int val)
{
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_INT);
  copy->value_u.int_val = val;
  return copy;
}

/*
 * Make float value
 *
 * This function returns a new float value with the same
 * numerical value as the given C double-precision float.
 */
value *value_make_float(double val)
{
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_FLOAT);
  copy->value_u.float_val = val;
  return copy;
}

/*
 * Make string value
 *
 * This function returns a new string value with the same
 * content as the given C string. The value contains a
 * newly allocated copy of the string data.
 */
value *value_make_string(const char *str)
{
  int len;
  char *cstr;
  value *copy;
  
  if (str) {
    len = strlen(str);
  } else {
    len = 0;
  }
  
  copy = value_alloc(VALUE_TYPE_STRING);

  if (len > 0) {
    cstr = oom(malloc(len + 1));
    copy->value_u.string_val.len = len;
    copy->value_u.string_val.value = cstr;
    memcpy(cstr, str, len + 1);
  }
  return copy;
}

/*
 * Make string from memory buffer
 *
 * This function returns a new string with the same contents as the
 * given memory buffer. In contrast to value_make_string(), this
 * function can create string with embedded 0 bytes.
 */
value *value_make_memstring(const void *buf, int len)
{
  value *copy;

  if (!buf || len == 0) {
    return value_make_string(NULL);
  }
  
  copy = value_alloc(VALUE_TYPE_STRING);

  if (len > 0) {
    char *mem = oom(malloc(len + 1));
  
    copy->value_u.string_val.len = len;
    copy->value_u.string_val.value = mem;
    memcpy(mem, buf, len);
    mem[len] = 0;
  }

  return copy;
}

/*
 * Make array value
 *
 * This functions returns a new array value representing
 * an empty array.
 */
value *value_make_array(void)
{
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_ARRAY);
  return copy;
}

/*
 * Make struct value
 *
 * This function returns a new struct value with no fields.
 */
value *value_make_struct(void)
{
  value *copy;

  copy = value_alloc(VALUE_TYPE_STRUCT);
  copy->value_u.struct_val = symtab_alloc(5);

  return copy;
}

/*
 * Make function value
 *
 * This function returns a new function value pointing to the given
 * signature.
 */
value *value_make_fn(void *sig)
{
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_FN);
  copy->value_u.fn_val = call_sig_copy(sig);
  
  return copy;
}

/*
 * Make resource value
 */
value *value_make_resource(void *data, void (*release)(void *))
{
  value *copy;
  
  copy = value_alloc(VALUE_TYPE_RES);

  copy->value_u.res_val = oom(malloc(sizeof(value_res)));
  copy->value_u.res_val->refcount = 1;
  copy->value_u.res_val->data     = data;
  copy->value_u.res_val->release  = release;
  
  return copy;
}
