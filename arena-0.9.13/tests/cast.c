/*
 * Tests for libruntime casts
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../libruntime/runtime.h"

static value *dummy(arena_state *s, unsigned int argc, value **argv)
{
  return (value *) (argc + (int) argv);
}

void cast_test(void)
{
  arena_state *s = state_alloc();

  value *val, *elem;
  signature *sig;
  value *vvoid, *vbool, *vint, *vfloat, *vstring, *varray, *vstruct, *vfn;

  sig = call_sig_builtin("dummy", 0, "", dummy);

  test_banner("libruntime");
  
  test_section("value casting");
  /*
   * Casts
   */
  vvoid = value_make_void();
  vbool = value_make_bool(1);
  vint  = value_make_int(-42);
  vfloat = value_make_float(4.2);
  vstring = value_make_string("4.2");
  varray = value_make_array();
  value_add_to_array(varray, vint);
  vstruct = value_make_struct();
  value_set_struct(vstruct, "foo", vint);
  vfn = value_make_fn(sig);
  
  /*
   * Casts to void
   */
  test_start("value_cast (void to void)");
  val = value_cast(s, vvoid, VALUE_TYPE_VOID);
  test_assert(val && val->type == VALUE_TYPE_VOID);
  value_free(val);
  test_start("value_cast (bool to void)");
  val = value_cast(s, vbool, VALUE_TYPE_VOID);
  test_assert(val && val->type == VALUE_TYPE_VOID);
  value_free(val);
  test_start("value_cast (int to void)");
  val = value_cast(s, vint, VALUE_TYPE_VOID);
  test_assert(val && val->type == VALUE_TYPE_VOID);
  value_free(val);
  test_start("value_cast (float to void)");
  val = value_cast(s, vfloat, VALUE_TYPE_VOID);
  test_assert(val && val->type == VALUE_TYPE_VOID);
  value_free(val);
  test_start("value_cast (string to void)");
  val = value_cast(s, vstring, VALUE_TYPE_VOID);
  test_assert(val && val->type == VALUE_TYPE_VOID);
  value_free(val);
  test_start("value_cast (array to void)");
  val = value_cast(s, varray, VALUE_TYPE_VOID);
  test_assert(val && val->type == VALUE_TYPE_VOID);
  value_free(val);
  test_start("value_cast (struct to void)");
  val = value_cast(s, vstruct, VALUE_TYPE_VOID);
  test_assert(val && val->type == VALUE_TYPE_VOID);
  value_free(val);
  test_start("value_cast (fn to void)");
  val = value_cast(s, vfn, VALUE_TYPE_VOID);
  test_assert(val && val->type == VALUE_TYPE_VOID);
  value_free(val);

  /*
   * Casts to bool
   */
  test_start("value_cast (void to bool)");
  val = value_cast(s, vvoid, VALUE_TYPE_BOOL);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 0);
  value_free(val);
  test_start("value_cast (bool to bool)");
  val = value_cast(s, vbool, VALUE_TYPE_BOOL);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);
  test_start("value_cast (int to bool)");
  val = value_cast(s, vint, VALUE_TYPE_BOOL);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);
  test_start("value_cast (float to bool)");
  val = value_cast(s, vfloat, VALUE_TYPE_BOOL);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);
  test_start("value_cast (string to bool)");
  val = value_cast(s, vstring, VALUE_TYPE_BOOL);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);
  test_start("value_cast (array to bool)");
  val = value_cast(s, varray, VALUE_TYPE_BOOL);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);
  test_start("value_cast (struct to bool)");
  val = value_cast(s, vstruct, VALUE_TYPE_BOOL);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);
  test_start("value_cast (fn to bool)");
  val = value_cast(s, vfn, VALUE_TYPE_BOOL);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);
  
  /*
   * Casts to int
   */
  test_start("value_cast (void to int)");
  val = value_cast(s, vvoid, VALUE_TYPE_INT);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 0);
  value_free(val);
  test_start("value_cast (bool to int)");
  val = value_cast(s, vbool, VALUE_TYPE_INT);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 1);
  value_free(val);
  test_start("value_cast (int to int)");
  val = value_cast(s, vint, VALUE_TYPE_INT);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == -42);
  value_free(val);
  test_start("value_cast (float to int)");
  val = value_cast(s, vfloat, VALUE_TYPE_INT);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 4);
  value_free(val);
  test_start("value_cast (string to int)");
  val = value_cast(s, vstring, VALUE_TYPE_INT);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 4);
  value_free(val);
  test_start("value_cast (array to int)");
  val = value_cast(s, varray, VALUE_TYPE_INT);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 1);
  value_free(val);
  test_start("value_cast (struct to int)");
  val = value_cast(s, vstruct, VALUE_TYPE_INT);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 1);
  value_free(val);
  test_start("value_cast (fn to int)");
  val = value_cast(s, vfn, VALUE_TYPE_INT);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 1);
  value_free(val);

  /*
   * Casts to float
   */
  test_start("value_cast (void to float)");
  val = value_cast(s, vvoid, VALUE_TYPE_FLOAT);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == 0.0);
  value_free(val);
  test_start("value_cast (bool to float)");
  val = value_cast(s, vbool, VALUE_TYPE_FLOAT);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == 1.0);
  value_free(val);
  test_start("value_cast (int to float)");
  val = value_cast(s, vint, VALUE_TYPE_FLOAT);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == -42.0);
  value_free(val);
  test_start("value_cast (float to float)");
  val = value_cast(s, vfloat, VALUE_TYPE_FLOAT);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == 4.2);
  value_free(val);
  test_start("value_cast (string to float)");
  val = value_cast(s, vstring, VALUE_TYPE_FLOAT);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == 4.2);
  value_free(val);
  test_start("value_cast (array to float)");
  val = value_cast(s, varray, VALUE_TYPE_FLOAT);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == 1.0);
  value_free(val);
  test_start("value_cast (struct to float)");
  val = value_cast(s, vstruct, VALUE_TYPE_FLOAT);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == 1.0);
  value_free(val);
  test_start("value_cast (fn to float)");
  val = value_cast(s, vstruct, VALUE_TYPE_FLOAT);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == 1.0);
  value_free(val);

  /*
   * Casts to string
   */
  test_start("value_cast (void to string)");
  val = value_cast(s, vvoid, VALUE_TYPE_STRING);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 0 &&
              val->value_u.string_val.value == NULL);
  value_free(val);
  test_start("value_cast (bool to string)");
  val = value_cast(s, vbool, VALUE_TYPE_STRING);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 1 &&
              val->value_u.string_val.value &&
              strcmp(val->value_u.string_val.value, "1") == 0);
  value_free(val);
  test_start("value_cast (int to string)");
  val = value_cast(s, vint, VALUE_TYPE_STRING);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 3 &&
              strcmp(val->value_u.string_val.value, "-42") == 0);
  value_free(val);
  test_start("value_cast (float to string)");
  val = value_cast(s, vfloat, VALUE_TYPE_STRING);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 3 &&
              strcmp(val->value_u.string_val.value, "4.2") == 0);
  value_free(val);
  test_start("value_cast (string to string)");
  val = value_cast(s, vstring, VALUE_TYPE_STRING);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 3 &&
              strcmp(val->value_u.string_val.value, "4.2") == 0);
  value_free(val);
  test_start("value_cast (array to string)");
  val = value_cast(s, varray, VALUE_TYPE_STRING);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 5 &&
              strcmp(val->value_u.string_val.value, "Array") == 0);
  value_free(val);
  test_start("value_cast (struct to string)");
  val = value_cast(s, vstruct, VALUE_TYPE_STRING);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 6 &&
              strcmp(val->value_u.string_val.value, "Struct") == 0);
  value_free(val);
  test_start("value_cast (fn to string)");
  val = value_cast(s, vfn, VALUE_TYPE_STRING);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 8 &&
              strcmp(val->value_u.string_val.value, "Function") == 0);
  value_free(val);

  /*
   * Casts to array
   */
  test_start("value_cast (void to array)");
  val = value_cast(s, vvoid, VALUE_TYPE_ARRAY);
  elem = value_get_array(val, 0);
  test_assert(val && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 1 &&
              elem && elem->type == VALUE_TYPE_VOID);
  value_free(elem);
  value_free(val);
  test_start("value_cast (bool to array)");
  val = value_cast(s, vbool, VALUE_TYPE_ARRAY);
  elem = value_get_array(val, 0);
  test_assert(val && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 1 &&
              elem && elem->type == VALUE_TYPE_BOOL);
  value_free(elem);
  value_free(val);
  test_start("value_cast (int to array)");
  val = value_cast(s, vint, VALUE_TYPE_ARRAY);
  elem = value_get_array(val, 0);
  test_assert(val && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 1 &&
              elem && elem->type == VALUE_TYPE_INT);
  value_free(elem);
  value_free(val);
  test_start("value_cast (float to array)");
  val = value_cast(s, vfloat, VALUE_TYPE_ARRAY);
  elem = value_get_array(val, 0);
  test_assert(val && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 1 &&
              elem && elem->type == VALUE_TYPE_FLOAT);
  value_free(elem);
  value_free(val);
  test_start("value_cast (string to array)");
  val = value_cast(s, vstring, VALUE_TYPE_ARRAY);
  elem = value_get_array(val, 0);
  test_assert(val && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 1 &&
              elem && elem->type == VALUE_TYPE_STRING);
  value_free(elem);
  value_free(val);
  test_start("value_cast (array to array)");
  val = value_cast(s, varray, VALUE_TYPE_ARRAY);
  elem = value_get_array(val, 0);
  test_assert(val && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 1 &&
              elem && elem->type == VALUE_TYPE_INT);
  value_free(elem);
  value_free(val);
  test_start("value_cast (struct to array)");
  val = value_cast(s, vstruct, VALUE_TYPE_ARRAY);
  elem = value_get_array(val, 0);
  test_assert(val && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 1 &&
              elem && elem->type == VALUE_TYPE_STRUCT);
  value_free(elem);
  value_free(val);
  test_start("value_cast (fn to array)");
  val = value_cast(s, vfn, VALUE_TYPE_ARRAY);
  elem = value_get_array(val, 0);
  test_assert(val && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 1 &&
              elem && elem->type == VALUE_TYPE_FN);
  value_free(elem);
  value_free(val);

  /*
   * Casts to struct
   */
  test_start("value_cast (void to struct)");
  val = value_cast(s, vvoid, VALUE_TYPE_STRUCT);
  elem = value_get_struct(val, "value");
  test_assert(val && val->type == VALUE_TYPE_STRUCT &&
              elem && elem->type == VALUE_TYPE_VOID);
  value_free(elem);
  value_free(val);
  test_start("value_cast (bool to struct)");
  val = value_cast(s, vbool, VALUE_TYPE_STRUCT);
  elem = value_get_struct(val, "value");
  test_assert(val && val->type == VALUE_TYPE_STRUCT &&
              elem && elem->type == VALUE_TYPE_BOOL);
  value_free(elem);
  value_free(val);
  test_start("value_cast (int to struct)");
  val = value_cast(s, vint, VALUE_TYPE_STRUCT);
  elem = value_get_struct(val, "value");
  test_assert(val && val->type == VALUE_TYPE_STRUCT &&
              elem && elem->type == VALUE_TYPE_INT);
  value_free(elem);
  value_free(val);
  test_start("value_cast (float to struct)");
  val = value_cast(s, vfloat, VALUE_TYPE_STRUCT);
  elem = value_get_struct(val, "value");
  test_assert(val && val->type == VALUE_TYPE_STRUCT &&
              elem && elem->type == VALUE_TYPE_FLOAT);
  value_free(elem);
  value_free(val);
  test_start("value_cast (string to struct)");
  val = value_cast(s, vstring, VALUE_TYPE_STRUCT);
  elem = value_get_struct(val, "value");
  test_assert(val && val->type == VALUE_TYPE_STRUCT &&
              elem && elem->type == VALUE_TYPE_STRING);
  value_free(elem);
  value_free(val);
  test_start("value_cast (array to struct)");
  val = value_cast(s, varray, VALUE_TYPE_STRUCT);
  elem = value_get_struct(val, "value");
  test_assert(val && val->type == VALUE_TYPE_STRUCT &&
              elem && elem->type == VALUE_TYPE_ARRAY);
  value_free(elem);
  value_free(val);
  test_start("value_cast (struct to struct)");
  val = value_cast(s, vstruct, VALUE_TYPE_STRUCT);
  elem = value_get_struct(val, "value");
  test_assert(val && val->type == VALUE_TYPE_STRUCT &&
              elem && elem->type == VALUE_TYPE_VOID);
  value_free(elem);
  value_free(val);
  test_start("value_cast (fn to struct)");
  val = value_cast(s, vfn, VALUE_TYPE_STRUCT);
  elem = value_get_struct(val, "value");
  test_assert(val && val->type == VALUE_TYPE_STRUCT &&
              elem && elem->type == VALUE_TYPE_FN);
  value_free(elem);
  value_free(val);
  
  /*
   * Casts to fn
   */
  test_start("value_cast (fn to fn)");
  val = value_cast(s, vfn, VALUE_TYPE_FN);
  test_assert(val && val->type == VALUE_TYPE_FN);
  value_free(val);
  
  state_free(s);
}
