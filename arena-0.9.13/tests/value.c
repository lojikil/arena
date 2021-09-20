/*
 * Tests for basic type system
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

void value_test(void)
{
  value *val, *val2, *elem, *elem2;
  int i, j, res, buf;
  signature *sig;
  
  sig = call_sig_builtin("dummy", 0, "", dummy);

  test_banner("libruntime");
  
  /*
   * Section: allocation of values
   */
  test_section("value allocators");

  /*
   * Basics
   */
  test_start("value_alloc");
  val = value_alloc(VALUE_TYPE_VOID);
  test_assert(val != NULL && val->type == VALUE_TYPE_VOID);

  test_start("value_free");
  value_free(val);
  test_assert(1);
  
  test_start("value_free (null)");
  value_free(NULL);
  test_assert(1);
  
  /*
   * Construction of fixed values
   */
  test_start("value_make_void");
  val = value_make_void();
  test_assert(val != NULL && val->type == VALUE_TYPE_VOID);
  value_free(val);

  test_start("value_make_bool (false)");
  val = value_make_bool(0);
  test_assert(val != NULL && val->type == VALUE_TYPE_BOOL && 
              val->value_u.bool_val == 0);
  value_free(val);

  test_start("value_make_bool (true)");
  val = value_make_bool(42);
  test_assert(val != NULL && val->type == VALUE_TYPE_BOOL && 
              val->value_u.bool_val == 1);
  value_free(val);

  test_start("value_make_int (-42)");
  val = value_make_int(-42);
  test_assert(val != NULL && val->type == VALUE_TYPE_INT && 
              val->value_u.int_val == -42);
  value_free(val);
  
  test_start("value_make_float (4.2)");
  val = value_make_float(4.2);
  test_assert(val != NULL && val->type == VALUE_TYPE_FLOAT && 
              val->value_u.float_val == 4.2);
  value_free(val);

  test_start("value_make_string (\"42\")");
  val = value_make_string("42");
  test_assert(val != NULL && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 2 &&
              strcmp(val->value_u.string_val.value, "42") == 0);
  value_free(val);
  
  test_start("value_make_array");
  val = value_make_array();
  test_assert(val != NULL && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 0 &&
              val->value_u.array_val.value == NULL);
  value_free(val);
  
  test_start("value_make_struct");
  val = value_make_struct();
  test_assert(val != NULL && val->type == VALUE_TYPE_STRUCT &&
              val->value_u.struct_val != NULL);
  value_free(val);
  
  test_start("value_make_fn");
  val = value_make_fn(sig);
  test_assert(val != NULL && val->type == VALUE_TYPE_FN);
  value_free(val);

  /*
   * Section: array functions
   */
  test_section("value arrays");  

  test_start("value_add_to_array (42000 elements)");
  val = value_make_array();
  for (i = 0; i < 42000; i++) {
    elem = value_make_int(i);
    value_add_to_array(val, elem);
    value_free(elem);
  }
  test_assert(val != NULL && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 42000);

  test_start("value_get_array (42000 elements)");
  res = 0;
  for (i = 0; i < 42000; i++) {
    elem = value_get_array(val, i);
    if (!elem || elem->type != VALUE_TYPE_INT || elem->value_u.int_val != i) {
      res++;
    }
    value_free(elem);
  }
  test_assert(res == 0);
  
  test_start("value_set_array (84000 elements)");
  for (i = 0; i < 84000; i++) {
    elem = value_make_int(i * (-42));
    value_set_array(val, i, elem);
    value_free(elem);
  }
  test_assert(val != NULL && val->type == VALUE_TYPE_ARRAY &&
              val->value_u.array_val.len == 84000);

  test_start("value_get_array (84000 elements)");
  res = 0;
  for (i = 0; i < 84000; i++) {
    elem = value_get_array(val, i);
    if (!elem || elem->type != VALUE_TYPE_INT ||
        elem->value_u.int_val != i * (-42)) {
      res++;
    }
    value_free(elem);
  }
  test_assert(res == 0);
  
  test_start("value_set_array (autofill)");
  elem = value_make_int(100000);
  value_set_array(val, 100000, elem);
  value_free(elem);
  elem = value_get_array(val, 100000);
  buf = 0;
  for (i = 84000; i < 100000; i++) {
    elem2 = value_get_array(val, i);
    if (!elem2 || !elem2->type == VALUE_TYPE_VOID) buf++;
    value_free(elem2);
  }
  test_assert(buf == 0 && elem->type == VALUE_TYPE_INT &&
              elem->value_u.int_val == 100000 &&
              val->value_u.array_val.len == 100001);
  value_free(elem);

  test_start("value_get_array (out of bounds)");
  elem = value_get_array(val, 200000);
  test_assert(elem && elem->type == VALUE_TYPE_VOID);
  value_free(elem);

  test_start("value_delete_array (42000 elements)");
  for (i = 0; i < 42000; i++) {
    value_delete_array(val, i);
  }
  buf = 0;
  for (i = 0; i < 84000; i++) {
    elem = value_get_array(val, i);
    if (i < 42000) {
      if (!elem || elem->type != VALUE_TYPE_VOID) buf++;
    } else {
      if (!elem || elem->type != VALUE_TYPE_INT ||
          elem->value_u.int_val != i * (-42)) buf++;
    }
    value_free(elem);
  }
  test_assert(buf == 0);

  /*
   * Section: copying of values
   */
  test_section("value copy");

  test_start("value_copy (int)");
  elem = value_make_int(4200);
  elem2 = value_copy(elem);
  test_assert(elem && elem2 &&
              elem2->type == VALUE_TYPE_INT &&
              elem2->value_u.int_val == 4200);
  value_free(elem);
  value_free(elem2);
  
  test_start("value_copy (string)");
  elem = value_make_string("foo");
  elem2 = value_copy(elem);
  test_assert(elem && elem2 &&
              elem2->type == VALUE_TYPE_STRING &&
              elem2->value_u.string_val.len == 3 &&
              elem2->value_u.string_val.value &&
              strcmp(elem2->value_u.string_val.value, "foo") == 0);
  value_free(elem);
  value_free(elem2);
  
  test_start("value_copy (large array)");
  elem2 = value_copy(val);  /* large array from above */
  res = 0;
  for (i = 0; i < 84000; i++) {
    elem = value_get_array(elem2, i);
    if (i < 42000) {
      if (!elem || elem->type != VALUE_TYPE_VOID) res++;
    } else {
      if (!elem || elem->type != VALUE_TYPE_INT ||
          elem->value_u.int_val != i * (-42)) {
        res++;
      }
    }
    value_free(elem);
  }
  test_assert(elem2 &&
              elem2->type == VALUE_TYPE_ARRAY &&
              elem2->value_u.array_val.len == val->value_u.array_val.len &&
              res == 0);

  /*
   * Freeing
   */
  test_start("value_free (large arrays)");
  value_free(val);
  value_free(elem2);
  test_assert(1);

  /*
   * Section: nested arrays
   */
  test_section("nested value arrays");

  test_start("value_add_to_array (nested arrays)");
  val = value_make_array();
  for (i = 0; i < 100; i++) {
    elem = value_make_array();
    for (j = 0; j < i; j++) {
      elem2 = value_make_int(j);
      value_add_to_array(elem, elem2);
      value_free(elem2);
    }
    value_add_to_array(val, elem);
    value_free(elem);
  }
  test_assert(1);

  test_start("value_get_array (nested arrays)");
  res = 0;
  for (i = 0; i < 100; i++) {
    elem = value_get_array(val, i);
    if (!elem || elem->type != VALUE_TYPE_ARRAY ||
        elem->value_u.array_val.len != i) {
      res++;
    } else {
      for (j = 0; j < i; j++) {
        elem2 = value_get_array(elem, j);
        if (!elem2 || elem2->type != VALUE_TYPE_INT ||
            elem2->value_u.int_val != j) res++;
        value_free(elem2);
      }
    }
    value_free(elem);
  }
  test_assert(res == 0);

  test_start("value_copy (nested arrays)");
  val2 = value_copy(val);
  res = 0;
  for (i = 0; i < 100; i++) {
    elem = value_get_array(val2, i);
    if (!elem || elem->type != VALUE_TYPE_ARRAY ||
        elem->value_u.array_val.len != i) {
      res++;
    } else {
      for (j = 0; j < i; j++) {
        elem2 = value_get_array(elem, j);
        if (!elem2 || elem2->type != VALUE_TYPE_INT ||
            elem2->value_u.int_val != j) res++;
        value_free(elem2);
      }
    }
    value_free(elem);
  }
  test_assert(res == 0 && val2);
  
  test_start("value_free (nested arrays)");
  value_free(val);
  value_free(val2);
  test_assert(1);
}
