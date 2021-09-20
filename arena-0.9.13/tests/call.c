/*
 * Signature and function call tests
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../libruntime/runtime.h"

/*
 * Test builtin function that returns first argument
 */
static value *myhead(arena_state *s, unsigned int argc, value **argv)
{
  if (argc > 0) {
    return value_copy(argv[0]);
  } else {
    return value_make_void();
  }
}

/*
 * Test builtin function that adds two ints
 */
static value *myadd(arena_state *s, unsigned int argc, value **argv)
{
  int a, b;
  
  a = argv[0]->value_u.int_val;
  b = argv[1]->value_u.int_val;
  return value_make_int(a + b);
}

/*
 * Test userdef function
 */
static value *myfunc(arena_state *s, void *data, void *def,
  unsigned int args, unsigned int argc, value **argv)
{
  if ((int) data == 0xdead &&
      (int) def  == 0xbeef &&
      args       == 1      &&
      argc       == 1      &&
      argv[0]    != NULL) {
    return value_make_bool(1);
  } else {
    return value_make_bool(0);
  }
}

void call_test(void)
{
  arena_state *s = state_alloc();

  signature usersig;
  signature *sig, *sig2;
  value *foo, *bar, *baz, *val;
  value *str;
  value **argv;
  value *userv[] = { value_make_int(42) };

  test_banner("libruntime");

  foo = value_make_int(42);
  bar = value_make_int(21);
  str = value_make_string("foo");
  
  test_section("function signatures");

  /* allocators */
  
  test_start("call_sig_alloc");
  sig = call_sig_alloc();
  test_assert(sig != NULL);
  
  test_start("call_sig_free");
  call_sig_free(sig);
  test_assert(1);
  
  test_start("call_sig_builtin");
  sig = call_sig_builtin("myadd", 2, "ii", myadd);
  test_assert(sig != NULL && sig->type == FUNCTION_TYPE_BUILTIN &&
              sig->args == 2 && strcmp(sig->proto, "ii") == 0 &&
              sig->call_u.builtin_vector == myadd);
              
  test_start("call_sig_builtin (varargs)");
  sig2 = call_sig_builtin("myhead", 1, "*", myhead);
  test_assert(sig2 != NULL && sig2->type == FUNCTION_TYPE_BUILTIN &&
              sig2->args == 1 && strcmp(sig2->proto, "*") == 0 &&
              sig2->call_u.builtin_vector == myhead);


  argv = malloc(sizeof(value *) * 2);
  argv[0] = foo; argv[1] = bar;

  test_start("call_check");
  call_check(s, "", sig, 2, argv);
  test_assert(1);
  
  /* two args match a vararg function with only "*" prototype */
  test_start("call_check (varargs)");
  argv[1] = bar;
  call_check(s, "", sig2, 2, argv);
  test_assert(1);
  
  test_section("function calls");

  /* direct calls with signature */
  
  test_start("call_function");
  baz = call_function(s, sig, 2, argv);
  test_assert(baz != NULL && baz->type == VALUE_TYPE_INT &&
              baz->value_u.int_val == 63);
  value_free(baz);
  
  test_start("call_function (varargs)");
  baz = call_function(s, sig2, 2, argv);
  test_assert(baz != NULL && baz->type == VALUE_TYPE_INT &&
              baz->value_u.int_val == 42);
  value_free(baz);
  
  /* indirect calls by name */
  
  symtab_stack_init(s);
  
  test_start("symtab_stack_add_function (builtins)");
  symtab_stack_add_function(s, "add", sig);
  symtab_stack_add_function(s, "head", sig2);
  test_assert(1);
  
  test_start("call_named_function");
  baz = call_named_function(s, "add", 2, argv);
  test_assert(baz != NULL && baz->type == VALUE_TYPE_INT &&
              baz->value_u.int_val == 63);
  value_free(baz);
  
  test_start("call_named_function (varargs)");
  baz = call_named_function(s, "head", 2, argv);  
  test_assert(baz != NULL && baz->type == VALUE_TYPE_INT &&
              baz->value_u.int_val == 42);
  value_free(baz);
  
  /*
   * Userdef call mechanism
   */
  
  usersig.type    = FUNCTION_TYPE_USERDEF;
  usersig.args    = 1;
  usersig.proto   = "i";
  usersig.rettype = '?';
  usersig.data    = (void *) 0xdead;
  usersig.def     = (void *) 0xbeef;
  usersig.call_u.userdef_vector = myfunc;
  
  test_start("symtab_stack_add_function (userdef)");
  symtab_stack_add_function(s, "myfunc", &usersig);
  test_assert(1);
  
  test_start("call_named_function (userdef)");
  val = call_named_function(s, "myfunc", 1, userv);
  test_assert(val != NULL && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);
  
  symtab_stack_teardown(s);
  state_free(s);
}
