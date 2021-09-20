/*
 * Evaluation tests
 * (C) 2006, Pascal Schmidt <arena-language@ewetel.net>
 * see file ../doc/LICENSE for license
 */

#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../libparser/parser.h"
#include "../libeval/eval.h"

/*
 * Dummy function
 */
value *myfunc(arena_state *s, unsigned int argc, value **argv)
{
  return value_make_int((argc + (int) argv)*0 + 21);
}

void eval_test(void)
{
  arena_state *s = state_alloc();

  expr ex, ex2, vari, varj, five, init, guard;
  expr etrue, efalse, zero, one, two, three, eincj;
  expr *exlist = { &five };
  stmt st, strue, sfalse, sincj;
  value *val, *val2, *val3;
  signature *sig;
  symtab_entry *entry;
  stmt_list *slist;

  /* add myfunc to symbol table */
  sig = call_sig_builtin("myfunc", 0, "", myfunc);
  symtab_stack_init(s);
  symtab_stack_enter(s);
  symtab_stack_add_function(s, "func", sig);

  /*
   * initialize some expressions and statements
   */

  vari.type = EXPR_REF;
  vari.name = "i";
  
  varj.type = EXPR_REF;
  varj.name = "j";
  
  zero.type = EXPR_CONST_INT;
  zero.name = "0";
  
  three.type = EXPR_CONST_INT;
  three.name = "3";
  
  five.type = EXPR_CONST_INT;
  five.name = "5";
  
  init.type = EXPR_ASSIGN;
  init.name = "i";
  init.inner = &zero;
  
  guard.type = EXPR_POSTFIX;
  guard.op = OPTYPE_POSTINC;
  guard.inner = &vari;

  eincj.type = EXPR_POSTFIX;
  eincj.op = OPTYPE_POSTINC;
  eincj.inner = &varj;
  
  sincj.type = STMT_EXPR;
  sincj.expr = &eincj;

  test_banner("libeval");
  
  test_section("simple expressions");
  
  /* constant bool true should yield true */
  test_start("eval_expr (true)");
  ex.type = EXPR_CONST_BOOL;
  ex.name = "true";
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 1);
  value_free(val);

  /* constant bool false should yield false */
  test_start("eval_expr (false)");
  ex.name = "false";
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_BOOL &&
              val->value_u.bool_val == 0);
  value_free(val);
  
  /* constant int should yield identical int value */
  test_start("eval_expr (42)");
  ex.type = EXPR_CONST_INT;
  ex.name = "42";
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 42);
  symtab_stack_add_variable(s, "i", val);
  value_free(val);

  /* constant float should yield identical float value */
  test_start("eval_expr (4.2)");
  ex.type = EXPR_CONST_FLOAT;
  ex.name = "4.2";
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_FLOAT &&
              val->value_u.float_val == 4.2);
  value_free(val);

  /* constant string should yield identical string value */
  test_start("eval_expr (hello)");
  ex.type = EXPR_CONST_STRING;
  ex.name = "hello";
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 5 &&
              strcmp(val->value_u.string_val.value, ex.name) == 0);
  value_free(val);
  
  /* casting 5 to string should yield "5" */
  test_start("eval_expr (cast)");
  ex.type = EXPR_CAST;
  ex.name = "string";
  ex.inner = &five;
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_STRING &&
              val->value_u.string_val.len == 1 &&
              strcmp(val->value_u.string_val.value, "5") == 0);
  value_free(val);

  /* calling user defined function should yield its result */
  test_start("eval_expr (call)");
  ex.type = EXPR_CALL;
  ex.name = "func";
  ex.argc = 0;
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 21);
  value_free(val);

  /* variable reference should return previously stored value */
  test_start("eval_expr (ref)");
  ex.type = EXPR_REF;
  ex.name = "i";
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 42);
  value_free(val);

  /* store int value 420 at a[5] */
  val = value_make_array();
  val2 = value_make_int(420);
  value_set_array(val, 5, val2);
  value_free(val2);
  symtab_stack_add_variable(s, "a", val);
  value_free(val);

  /* a[5] should yield value previously stored at that index */
  test_start("eval_expr (ref array)");
  ex.type = EXPR_REF_ARRAY;
  ex.name = "a";
  ex.argc = 1;
  ex.argv = &exlist;
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 420);
  value_free(val);

  /* assignment i=5 should make i contain the value 5 */
  test_start("eval_expr (assign)");
  ex.type = EXPR_ASSIGN;
  ex.name = "i";
  ex.inner = &five;
  val = eval_expr(s, &ex);
  entry = symtab_stack_lookup(s, "i");
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 5 &&
              entry && entry->type == SYMTAB_ENTRY_VAR &&
              entry->entry_u.var->type == VALUE_TYPE_INT &&
              entry->entry_u.var->value_u.int_val == 5);
  value_free(val);

  /* assignment a[5]=5 should make a[5] yield 5 */
  test_start("eval_expr (assign array)");
  ex.type = EXPR_ASSIGN_ARRAY;
  ex.name = "a";
  ex.argc = 1;
  ex.argv = &exlist;
  ex.inner = &five;
  val = eval_expr(s, &ex);
  ex.type = EXPR_REF_ARRAY;
  val2 = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 5 &&
              val2 && val2->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 5);
  value_free(val);
  value_free(val2);

  /* nested assignment should assign to both variables */
  test_start("eval_expr (nested assign)");
  ex.type = EXPR_ASSIGN;
  ex.name = "i";
  ex.inner = &ex2;
  ex2.type = EXPR_ASSIGN;
  ex2.name = "j";
  ex2.inner = &three;
  val = eval_expr(s, &ex);
  val2 = eval_expr(s, &vari);
  val3 = eval_expr(s, &varj);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 3 &&
              val2 && val2->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 3 &&
              val3 && val3->type == VALUE_TYPE_INT &&
              val3->value_u.int_val == 3);
  value_free(val);
  value_free(val2);
  value_free(val3);

  /* multiplication of 5 by 5 should yield 25 */
  test_start("eval_expr (infix)");
  ex.type = EXPR_INFIX;
  ex.inner = ex.index = &five;
  ex.op = OPTYPE_MUL;
  val = eval_expr(s, &ex);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 25);
  value_free(val);

  test_section("mixfix expressions");

  symtab_stack_add_variable(s, "i", value_make_int(42));
  
  /* preincrement value should match variable value */
  test_start("eval_expr (preinc)");
  ex.type = EXPR_PREFIX;
  ex.inner = &vari;
  ex.op = OPTYPE_PREINC;
  val = eval_expr(s, &ex);
  val2 = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 43 &&
              val2 && val2->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 43);
  value_free(val);
  value_free(val2);

  /* predecrement value should match variable value */
  test_start("eval_expr (predec)");
  ex.type = EXPR_PREFIX;
  ex.inner = &vari;
  ex.op = OPTYPE_PREDEC;
  val = eval_expr(s, &ex);
  val2 = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 42 &&
              val2 && val2->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 42);
  value_free(val);
  value_free(val2);

  /* unary minus should change sign of variable value */
  test_start("eval_expr (unary minus)");
  ex.type = EXPR_PREFIX;
  ex.inner = &vari;
  ex.op = OPTYPE_MINUS;
  val = eval_expr(s, &ex);
  val2 = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == -42 &&
              val2 && val2->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 42);
  value_free(val);
  value_free(val2);

  /* bitwise negation */
  test_start("eval_expr (bit negation)");
  ex.type = EXPR_PREFIX;
  ex.inner = &vari;
  ex.op = OPTYPE_NEG;
  val = eval_expr(s, &ex);
  val2 = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == -43 &&
              val2 && val2->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 42);
  value_free(val);
  value_free(val2);

  /* postincrement should change variable after returning original value */
  test_start("eval_expr (postinc)");
  ex.type = EXPR_POSTFIX;
  ex.inner = &vari;
  ex.op = OPTYPE_POSTINC;
  val = eval_expr(s, &ex);
  val2 = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 42 &&
              val2 && val2->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 43);
  value_free(val);
  value_free(val2);

  /* postdecrement should change variable after returning original value */
  test_start("eval_expr (postdec)");
  ex.type = EXPR_POSTFIX;
  ex.inner = &vari;
  ex.op = OPTYPE_POSTDEC;
  val = eval_expr(s, &ex);
  val2 = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 43 &&
              val2 && val2->type == VALUE_TYPE_INT &&
              val2->value_u.int_val == 42);
  value_free(val);
  value_free(val2);

  test_section("simple statements");

  /* empty expression should run okay */
  test_start("eval_stmt (nop)");
  st.type = STMT_NOP;
  eval_stmt(s, &st, 0);
  test_assert(1);
  
  /* expression statement should run okay */
  test_start("eval_stmt (expr)");
  st.type = STMT_EXPR;
  st.expr = &ex;
  eval_stmt(s, &st, 0);
  test_assert(1);

  /*
   * initialize some extra expressions and statements
   */

  symtab_stack_add_variable(s, "i", value_make_int(6));

  ex.type = EXPR_INFIX;
  ex.inner = &vari;
  ex.index = &five;
  ex.op = OPTYPE_SMALLER;

  one.type = EXPR_CONST_INT;
  one.name = "1";

  two.type = EXPR_CONST_INT;
  two.name = "2";

  etrue.type = EXPR_ASSIGN;
  etrue.name = "i";
  etrue.inner = &one;
  
  efalse.type = EXPR_ASSIGN;
  efalse.name = "i";
  efalse.inner = &two;
  
  strue.type = STMT_EXPR;
  strue.expr = &etrue;
  
  sfalse.type = STMT_EXPR;
  sfalse.expr = &efalse;

  /* if without else and false condition, true block is i=1 */
  test_start("eval_stmt (if false)");  
  st.type = STMT_IF;
  st.expr = &ex;
  st.true_case = &strue;
  eval_stmt(s, &st, 0);
  val = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 6);
  value_free(val);

  /* if without else and true condition, true block is i=1 */
  test_start("eval_stmt (if true)");
  ex.op = OPTYPE_LARGER;
  eval_stmt(s, &st, 0);
  val = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 1);
  value_free(val);
  
  /* if with else and false condition, false block is i=2 */
  test_start("eval_stmt (if_else false)");
  st.type = STMT_IF_ELSE;
  st.false_case = &sfalse;
  eval_stmt(s, &st, 0);
  val = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 2);
  value_free(val);

  /* if with else and true condition, true block is i=1 */
  test_start("eval_stmt (if_else true)");
  ex.op = OPTYPE_SMALLER;
  eval_stmt(s, &st, 0);
  val = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 1);
  value_free(val);

  /* while block that should run four times, changing i from 1 to 5 */
  test_start("eval_stmt (while)");
  eval_expr(s, &etrue);

  ex.type = EXPR_INFIX;
  ex.op = OPTYPE_SMALLER;
  ex.inner = &vari;
  ex.index = &five;

  sfalse.type = STMT_EXPR;
  sfalse.expr = &guard;

  st.type = STMT_WHILE;
  st.expr = &ex;
  st.true_case = &sfalse;

  eval_stmt(s, &st, 0);
  val = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 5);
  value_free(val);

  /* do block with false condition executes once */
  test_start("eval_stmt (do)");
  st.type = STMT_DO;
  eval_stmt(s, &st, 0);
  val = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 6);
  value_free(val);
  
  /* for block executing 5 times j++ changes j from 0 to 5 */
  test_start("eval_stmt (for)");
  symtab_stack_add_variable(s, "j", value_make_int(0));
  st.type = STMT_FOR;
  st.init = &init;
  st.expr = &ex;
  st.guard = &guard;
  st.true_case = &sincj;
  eval_stmt(s, &st, 0);
  val = eval_expr(s, &varj);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 5);
  value_free(val);

  /* for block with break causes counter to stay at init value */
  test_start("eval_stmt (break)");
  sincj.type = STMT_BREAK;
  eval_stmt(s, &st, 0);
  val = eval_expr(s, &vari);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 0);
  value_free(val);

  /* for block with continue and j++ must not change j */
  test_start("eval_stmt (continue)");
  symtab_stack_add_variable(s, "j", value_make_int(0));
  sincj.type = STMT_EXPR;
  sfalse.type = STMT_CONTINUE;
  slist = stmt_list_alloc();
  stmt_list_push(slist, &sfalse);
  stmt_list_push(slist, &sincj);
  strue.type = STMT_BLOCK;
  strue.block = (STMT_LIST *) slist;
  st.true_case = &strue;
  eval_stmt(s, &st, 0);
  val = eval_expr(s, &varj);
  test_assert(val && val->type == VALUE_TYPE_INT &&
              val->value_u.int_val == 0);
  value_free(val);

  symtab_stack_leave(s);
  symtab_stack_teardown(s);
  state_free(s);
}
